#include "iDias.h"

#include "zlib/zlib.h"
#pragma comment(lib, "..\\lib\\zlibwapi.lib")

#define MSGLEN			1024 * 1000
#define HEADER_SIZE		1024
#define FILE_INFO_SIZE	316

typedef struct _PAK_HEADER {
	CHAR MagicNumber[256]; // PAK file magic number / identifier string.
	INT Unknown; // Unknown. Always 11 (0x0B).
	UINT FileCount; // Number of files in this PAK.
	UINT FileIndexTableOffset; // A pointer to the location of the file index table
	UINT8 Padding[756]; // Padding bytes to make the PAK header 1024 bytes in total
} PAK_HEADER, *PPAK_HEADER;

typedef struct _PAK_FILEINFO {
	CHAR FilePath[256]; // Virtual pak of file
	UINT RawSize; // Size of this file
	UINT RealSize; // Size of this file, in bytes, when decompressed.This value may be zero, which simply means that you will not be able to pre - allocate a buffer when decompressing.
	UINT CompressedSize; // The size of this file, in bytes, when compressed in the PAK. Should be the same as Raw Size.
	UINT FileDataOffset; // A pointer to the location of this file's data.
	UINT UnknownA; // Unknown. Seems to have no effect.
	// UnknownB = 40 bytes
} PAK_FILEINFO, *PPAK_FILEINFO;

std::string ExtractFileName(const std::string& fullPath)
{
	const size_t lastSlashIndex = fullPath.find_last_of("/\\");
	return fullPath.substr(lastSlashIndex + 1);
}

VOID CreateDirectoryAndSub(LPSTR path) {
	CHAR folder[MAX_PATH];
	PCHAR end;

	ZeroMemory(folder, MAX_PATH * sizeof(CHAR));
	end = strchr(path, L'\\');

	while (end != NULL) {
		strncpy(folder, path, end - path + 1);
		if (!CreateDirectory(folder, NULL)) {
			DWORD err = GetLastError();

			if (err != ERROR_ALREADY_EXISTS)
			{
				// do whatever handling you'd like
			}
		}

		end = strchr(++end, L'\\');
	}
}

LPSTR RemoveFilename(LPSTR myStr) {
	LPSTR retStr;
	LPSTR lastExt;

	if (myStr == NULL)
		return NULL;

	if ((retStr = (PCHAR)malloc(strlen(myStr) + 1)) == NULL)
		return NULL;

	strcpy(retStr, myStr);
	lastExt = strrchr(retStr, '\\');
	if (lastExt != NULL)
		*lastExt = '\0';

	return retStr;
}

BOOL WINAPI ReadPak(LPSTR sSource, LPSTR sMessage) {
	HANDLE hFile;
	DWORD hSize;
	LPVOID lBuffer;
	DWORD bytesRead;
	DWORD oldProtection;

	PPAK_HEADER pakHeader = {};

	hFile = CreateFile(sSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadPak", (LPSTR)"CreateFile");
		return FALSE;
	}

	hSize = GetFileSize(hFile, NULL);
	if (!hSize) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadPak", (LPSTR)"GetFileSize");
		CloseHandle(hFile);

		return FALSE;
	}

	lBuffer = VirtualAlloc(NULL, hSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!lBuffer) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadPak", (LPSTR)"VirtualAlloc");
		CloseHandle(hFile);

		return FALSE;
	}

	if (!VirtualProtect(lBuffer, hSize, PAGE_EXECUTE_READWRITE, &oldProtection)) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadPak", (LPSTR)"VirtualProtect");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	if (!ReadFile(hFile, lBuffer, hSize, &bytesRead, NULL)) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadPak", (LPSTR)"ReadFile");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	// -- Header --
	pakHeader = (PPAK_HEADER)lBuffer;
	
	CHAR msg[MSGLEN];
	INT msg_len = 0;

	msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "-----\r\nHEADER\r\n-----\r\nMagic: %s\r\nNumber of Files: %d\r\nFile Index Offset: 0x%08X\r\n\r\n",
		pakHeader->MagicNumber,
		pakHeader->FileCount,
		pakHeader->FileIndexTableOffset);
	// -- End Header --
	
	// -- FileEntry --
	msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "-----\r\nFILES\r\n-----\r\n");

	if (!SetFilePointer(hFile, pakHeader->FileIndexTableOffset, NULL, NULL)) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadPak", (LPSTR)"SetFilePointer");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	UINT fCount = pakHeader->FileCount;
	PPAK_FILEINFO fileEntries = new PAK_FILEINFO[fCount];

	for (UINT i = 0; i < fCount; i++) {
		PPAK_FILEINFO pakFileInfo = {};

		ReadFile(hFile, lBuffer, FILE_INFO_SIZE, &bytesRead, NULL);
		pakFileInfo = (PPAK_FILEINFO)lBuffer;

		msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "[%03d] [0x%08X] %s\r\n", i + 1, pakFileInfo->FileDataOffset, pakFileInfo->FilePath);
		fileEntries[i] = *pakFileInfo;
	}
	// -- End File Entry --

	// -- Decompressing --
	for (UINT i = 0; i < fCount; i++) {
		LPVOID sBuffFromPak;
		LPVOID sBuffAfterDecompress;
		PAK_FILEINFO fInfo = fileEntries[i];

		UINT rawSize = fInfo.RawSize;
		UINT realSize = fInfo.RealSize;
		LPSTR virtualPath = fInfo.FilePath;
		DWORD filePointer = fInfo.FileDataOffset;

		sBuffFromPak = malloc(rawSize);
		sBuffAfterDecompress = malloc(realSize);

		SetFilePointer(hFile, filePointer, NULL, NULL);
		ReadFile(hFile, sBuffFromPak, rawSize, &bytesRead, NULL);

		// zlib inflate start
		z_stream infstream;
		infstream.zalloc = Z_NULL;
		infstream.zfree = Z_NULL;
		infstream.opaque = Z_NULL;

		infstream.avail_in = rawSize; // size of input
		infstream.next_in = (Bytef *)sBuffFromPak; // input char array
		infstream.avail_out = realSize; // size of output
		infstream.next_out = (Bytef *)sBuffAfterDecompress; // output char array
		
		// the actual DE-compression work.
		inflateInit(&infstream);
		inflate(&infstream, Z_NO_FLUSH);
		inflateEnd(&infstream);

		// Write to file
		HANDLE hdFile;
		CHAR sDir[MAX_PATH];
		
		strcpy(sDir, "G:\\iModMan\\bin\\iModMan\\");
		strcat(sDir, ExtractFileName(sSource).c_str());
		strcat(sDir, RemoveFilename(virtualPath));
		strcat(sDir, "\\");
		
		CreateDirectoryAndSub(sDir);
		strcat(sDir, ExtractFileName(virtualPath).c_str());

		hdFile = CreateFile(sDir, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hdFile, sBuffAfterDecompress, realSize, NULL, NULL);
		CloseHandle(hdFile);

		free(sBuffFromPak);
		free(sBuffAfterDecompress);
	}
	// -- End Decompressing --

	strcpy(sMessage, msg);
	
	VirtualFree(lBuffer, hSize, MEM_RELEASE);
	CloseHandle(hFile);
	return TRUE;
}

BOOL WINAPI DiasPackFile(LPSTR sSource, LPSTR sDestination) {
	BOOL ret = FALSE;
	return ret;
}

VOID WINAPI DiasUnpackFile(LPSTR sSource, LPSTR sDestination) {

}

VOID WINAPI DiasPackBuffer(LPVOID sBuffer, LPSTR sDestination) {

}

VOID WINAPI DiasUnpackBuffer(LPVOID sBuffer, LPSTR sDestination) {

}