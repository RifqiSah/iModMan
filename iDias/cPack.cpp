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

#define OBJ_MEMDESC(o) { sizeof(o), (uint8_t*)&(o) }
#define DESC_COUNT(descs) (sizeof(descs) / sizeof((descs)[0]))

struct memdesc
{
	size_t length;
	uint8_t * ptr;
};

#define MIN(a,b) ((a) < (b) ? (a) : (b))

size_t memcat(uint8_t * dst,
	struct memdesc * descriptors,
	size_t descriptor_count,
	size_t max_len)
{
	size_t remaining = max_len;
	uint8_t * next = dst;

	for (size_t i = 0; i < descriptor_count; i++)
	{
		struct memdesc * desc = &descriptors[i];
		size_t copy_len = MIN(remaining, desc->length);

		memcpy(next, desc->ptr, copy_len);
		next += copy_len;
		remaining -= copy_len;

		if (remaining <= 0)
			break;
	}

	return (max_len - remaining);
}

VOID dirListFiles(LPSTR startDir)
{
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	CHAR path[MAX_PATH];

	sprintf(path, "%s\\*", startDir);

	fprintf(stdout, "In Directory \"%s\"\n\n", startDir);

	if ((hFind = FindFirstFile(path, &wfd)) == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "FindFirstFIle failed on path = \"%s\"\n", path);
		abort();
	}

	BOOL cont = TRUE;
	while (cont == TRUE)
	{
		if ((strncmp(".", wfd.cFileName, 1) != 0) && (strncmp("..", wfd.cFileName, 2) != 0))
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				sprintf(path, "%s\\%s", startDir, wfd.cFileName);
				
				dirListFiles(path);
			}
			else
			{
				//do your work here -- mildly klugy comparison
				CHAR wkwk[MAX_PATH];
				sprintf(wkwk, "%s\\%s", substr(path, 0, strlen(path) - 1), wfd.cFileName);
				OutputDebugString(wkwk);

				int len = strlen(wfd.cFileName);
				if (len > 4)
					if (strncmp(".cpp", wfd.cFileName + len - 4, 4) == 0)
						fprintf(stdout, "match = \"%s\"\n", wfd.cFileName);

			}
		}
		cont = FindNextFile(hFind, &wfd);
	}
	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		fprintf(stderr, "FindNextFile died for some reason; path = \"%s\"\n", path);
		abort();
	}
	if (FindClose(hFind) == FALSE)
	{
		fprintf(stderr, "FindClose failed\n");
		abort();
	}
}

PVOID memcat(PVOID s1, size_t n1, PVOID s2, size_t n2) {
	memcpy((PCHAR)s1 + n1, s2, n2);
	return s1;
}

BOOL WINAPI ReadPak(LPSTR sSource, LPSTR sMessage) {
	CHAR msg[MSGLEN];
	INT msg_len = 0;

	CHAR DataBuffer[] = "Haiii cobalah ini datanya wkkwkw";

	CHAR sFile[MAX_PATH];
	HANDLE hFile;
	PAK_HEADER pakHeader;
	PAK_FILEINFO pakFileInfo;

	sprintf(sFile, "%s\\%s", sSource, "test.pak");
	hFile = CreateFile(sFile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	INT fCount = 2;
	UINT fileOffset = HEADER_SIZE;
	PPAK_FILEINFO fInfo = new PAK_FILEINFO[fCount];
	LPVOID fileTotalBuffer;

	for (INT i = 0; i < 2; i++) {
		HANDLE hsFile;
		DWORD hSize;
		LPVOID fileBuffer;
		LPVOID fileBufferOut;

		hsFile = CreateFile("G:\\iModMan\\bin\\iModMan\\00Resource_dv_lk_cyclones.pak\\dv_blank_model_cyclone_original.skn", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (!hsFile) {
			DisplayErrorEx((LPSTR)"iDias:cPack:ReadingFile", (LPSTR)"CreateFile");
			return FALSE;
		}

		hSize = GetFileSize(hsFile, NULL);
		if (!hSize) {
			DisplayErrorEx((LPSTR)"iDias:cPack:ReadingFile", (LPSTR)"GetFileSize");
			CloseHandle(hsFile);

			return FALSE;
		}

		fileBuffer = malloc(hSize);
		fileBufferOut = malloc(hSize);

		ReadFile(hsFile, fileBuffer, hSize, NULL, NULL);
		CloseHandle(hsFile);

		PAK_FILEINFO pakFileInfo;

		// zlib struct
		z_stream defstream;
		defstream.zalloc = Z_NULL;
		defstream.zfree = Z_NULL;
		defstream.opaque = Z_NULL;
		// setup "a" as the input and "b" as the compressed output
		defstream.avail_in = hSize; // size of input, string + terminator
		defstream.next_in = (Bytef *)fileBuffer; // input char array
		defstream.avail_out = hSize; // size of output
		defstream.next_out = (Bytef *)fileBufferOut; // output char array

		// the actual compression work.
		deflateInit(&defstream, Z_BEST_COMPRESSION);
		deflate(&defstream, Z_FINISH);
		deflateEnd(&defstream);

		hsFile = CreateFile("G:\\iModMan\\bin\\iModMan\\00Resource_dv_lk_cyclones.pak\\temppak.tmp", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD a = GetFileSize(hsFile, NULL);
		LPVOID b = malloc(a);
		ReadFile(hsFile, b, a, NULL, NULL);
		SetFilePointer(hsFile, a, NULL, NULL);
		WriteFile(hsFile, fileBufferOut, defstream.total_out + 1, NULL, NULL);;
		CloseHandle(hsFile);

		pakFileInfo.RawSize = hSize;
		pakFileInfo.CompressedSize = defstream.total_out;
		pakFileInfo.FileDataOffset = fileOffset;
		sprintf(pakFileInfo.FilePath, "\\File no %d.testing", i + 1);

		fInfo[i] = pakFileInfo;

		fileOffset += defstream.total_out + 1;
	}

	pakHeader.FileCount = fCount;
	pakHeader.FileIndexTableOffset = fileOffset;
	strcpy(pakHeader.MagicNumber, "EyedentityGames Packing File 0.1");
	pakHeader.Unknown = 0x0B;

	WriteFile(hFile, &pakHeader, HEADER_SIZE, NULL, NULL);

	HANDLE tf = CreateFile("G:\\iModMan\\bin\\iModMan\\00Resource_dv_lk_cyclones.pak\\temppak.tmp", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD a = GetFileSize(tf, NULL);
	fileTotalBuffer = malloc(a);
	ReadFile(tf, fileTotalBuffer, a, NULL, NULL);
	WriteFile(hFile, fileTotalBuffer, a, NULL, NULL);
	free(fileTotalBuffer);
	CloseHandle(tf);
	DeleteFile("G:\\iModMan\\bin\\iModMan\\00Resource_dv_lk_cyclones.pak\\temppak.tmp");

	for (INT i = 0; i < 2; i++)
		WriteFile(hFile, &fInfo[i], FILE_INFO_SIZE, NULL, NULL);

	CloseHandle(hFile);

	// strcpy(msg, "hmm");
	strcpy(sMessage, msg);
	return TRUE;
}

BOOL WINAPI DiasPackFile(LPSTR sSource, LPSTR sDestination) {
	BOOL ret = FALSE;
	return ret;
}

BOOL WINAPI DiasUnpackFile(LPSTR sSource, LPSTR sDestination) {
	HANDLE hFile;
	DWORD hSize;
	LPVOID lBuffer;
	DWORD bytesRead;
	DWORD oldProtection;

	PPAK_HEADER pakHeader = {};

	hFile = CreateFile(sSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile) {
		DisplayErrorEx((LPSTR)"iDias:cPack:DiasUnpackFile", (LPSTR)"CreateFile");
		return FALSE;
	}

	hSize = GetFileSize(hFile, NULL);
	if (!hSize) {
		DisplayErrorEx((LPSTR)"iDias:cPack:DiasUnpackFile", (LPSTR)"GetFileSize");
		CloseHandle(hFile);

		return FALSE;
	}

	lBuffer = VirtualAlloc(NULL, hSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!lBuffer) {
		DisplayErrorEx((LPSTR)"iDias:cPack:DiasUnpackFile", (LPSTR)"VirtualAlloc");
		CloseHandle(hFile);

		return FALSE;
	}

	if (!VirtualProtect(lBuffer, hSize, PAGE_EXECUTE_READWRITE, &oldProtection)) {
		DisplayErrorEx((LPSTR)"iDias:cPack:DiasUnpackFile", (LPSTR)"VirtualProtect");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	if (!ReadFile(hFile, lBuffer, hSize, &bytesRead, NULL)) {
		DisplayErrorEx((LPSTR)"iDias:cPack:DiasUnpackFile", (LPSTR)"ReadFile");
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
		DisplayErrorEx((LPSTR)"iDias:cPack:DiasUnpackFile", (LPSTR)"SetFilePointer");
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

	/*
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

		strcpy(sDir, sDestination);
		strcat(sDir, ExtractFileName(sSource));
		strcat(sDir, RemoveFilename(virtualPath));
		strcat(sDir, "\\");

		CreateDirectoryAndSub(sDir);
		strcat(sDir, ExtractFileName(virtualPath));

		hdFile = CreateFile(sDir, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hdFile, sBuffAfterDecompress, realSize, NULL, NULL);
		CloseHandle(hdFile);

		free(sBuffFromPak);
		free(sBuffAfterDecompress);
	}
	// -- End Decompressing --
	*/

	// strcpy(sMessage, msg);
	strcpy(sDestination, msg);

	VirtualFree(lBuffer, hSize, MEM_RELEASE);
	CloseHandle(hFile);
	return TRUE;
}

BOOL WINAPI DiasPackBuffer(LPVOID sBuffer, LPSTR sDestination) {
	return FALSE;
}

BOOL WINAPI DiasUnpackBuffer(LPVOID sBuffer, LPSTR sDestination) {
	return FALSE;
}