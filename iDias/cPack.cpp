#include "iDias.h"

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
	UINT RealSize; // Size of this file, in bytes, when decompressed. This value may be zero, which simply means that you will not be able to pre - allocate a buffer when decompressing.
	UINT CompressedSize; // The size of this file, in bytes, when compressed in the PAK. Should be the same as Raw Size.
	UINT FileDataOffset; // A pointer to the location of this file's data.
	UINT UnknownA; // Unknown. Seems to have no effect.
	// UnknownB = 40 bytes
} PAK_FILEINFO, *PPAK_FILEINFO;

VOID dirListFiles(const CHAR *startDir)
{
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	CHAR path[MAX_PATH];

	sprintf(path, "%s\\*", startDir);

	fprintf(stdout, "In Directory \"%s\"\n\n", startDir);

	if ((hFind = FindFirstFile(path, &wfd)) == INVALID_HANDLE_VALUE) {
		DisplayErrorEx("iDias:dirListFiles", "FindFirstFile");
		return;
	}

	BOOL cont = TRUE;
	while (cont == TRUE)
	{
		if ((strncmp(".", wfd.cFileName, 1) != 0) && (strncmp("..", wfd.cFileName, 2) != 0)) {
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				sprintf(path, "%s\\%s", startDir, wfd.cFileName);
				dirListFiles(path);
			}
			else {
				CHAR wkwk[MAX_PATH];
				sprintf(wkwk, "%s\\%s", substr(path, 0, strlen(path) - 1), wfd.cFileName);
				OutputDebugString(wkwk);
			}
		}

		cont = FindNextFile(hFind, &wfd);
	}

	FindClose(hFind);
}

BOOL WINAPI DnPakRead(LPSTR sSource, LPSTR sMessage) {
	HANDLE hFile;
	DWORD hSize;
	LPVOID lBuffer;
	DWORD bytesRead;
	DWORD oldProtection;

	PPAK_HEADER pakHeader = {};

	WriteLog("iDias:DnPakRead", 5, "Attemtping to open %s", sSource);
	hFile = CreateFile(sSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		DisplayErrorEx("iDias:DnReadPak", "CreateFile");
		return FALSE;
	}

	hSize = GetFileSize(hFile, NULL);
	if (!hSize) {
		DisplayErrorEx("iDias:DnReadPak", "GetFileSize");
		CloseHandle(hFile);

		return FALSE;
	}
	
	lBuffer = VirtualAlloc(NULL, hSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!lBuffer) {
		DisplayErrorEx("iDias:DnReadPak", "VirtualAlloc");
		CloseHandle(hFile);

		return FALSE;
	}

	if (!VirtualProtect(lBuffer, hSize, PAGE_EXECUTE_READWRITE, &oldProtection)) {
		DisplayErrorEx("iDias:DnReadPak", "VirtualProtect");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	WriteLog("iDias:DnPakRead", 5, "Allocated memory: %d bytes", hSize);
	if (!ReadFile(hFile, lBuffer, hSize, &bytesRead, NULL)) {
		DisplayErrorEx("iDias:DnReadPak", "ReadFile");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	// -- Header --
	WriteLog("iDias:DnPakRead", 5, "Reading file header");
	pakHeader = (PPAK_HEADER)lBuffer;

	CHAR msg[MSGLEN];
	INT msg_len = 0;

	msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "-----\r\nHEADER\r\n-----\r\nMagic: %s\r\nNumber of Files: %d\r\nFile Index Offset: 0x%08X\r\n\r\n",
		pakHeader->MagicNumber,
		pakHeader->FileCount,
		pakHeader->FileIndexTableOffset);
	WriteLog("iDias:DnPakRead", 5, "OK");
	// -- End Header --

	// -- FileEntry --
	WriteLog("iDias:DnPakRead", 5, "Reading file entry in 0x%08X", pakHeader->FileIndexTableOffset);
	msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "-----\r\nFILES\r\n-----\r\n");

	if (!SetFilePointer(hFile, pakHeader->FileIndexTableOffset, NULL, NULL)) {
		DisplayErrorEx("iDias:DnReadPak", "SetFilePointer");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	UINT fCount = pakHeader->FileCount;
	for (UINT i = 0; i < fCount; i++) {
		PPAK_FILEINFO pakFileInfo = {};

		ReadFile(hFile, lBuffer, FILE_INFO_SIZE, &bytesRead, NULL);
		pakFileInfo = (PPAK_FILEINFO)lBuffer;

		msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "[%03d] [0x%08X] [Disk: %04d bytes] [Raw: %04d bytes] %s\r\n", i + 1, pakFileInfo->FileDataOffset, pakFileInfo->RealSize, pakFileInfo->RawSize, pakFileInfo->FilePath);
	}
	WriteLog("iDias:DnPakRead", 5, "OK");
	// -- End File Entry --

	strcpy(sMessage, msg);

	VirtualFree(lBuffer, hSize, MEM_RELEASE);
	CloseHandle(hFile);

	WriteLog("iDias:DnPakRead", 5, "OK");
	return TRUE;
}

BOOL WINAPI DnPakPack(LPSTR sSource, LPSTR sDestination) {
	// CHAR sFile[MAX_PATH];
	CHAR pakFileTemp[MAX_PATH];
	HANDLE hFile;
	PAK_HEADER pakHeader;

	WriteLog("iDias:DnPakPack", 5, "Attemtping to create %s", sDestination);
	hFile = CreateFile(sDestination, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		DisplayErrorEx("iDias:DnPakPack", "CreateFile");
		return FALSE;
	}

	INT fCount = 5;
	UINT fileOffset = HEADER_SIZE;
	PPAK_FILEINFO fInfo = new PAK_FILEINFO[fCount];
	LPVOID fileTotalBuffer;

	if (!GetTempFile(pakFileTemp)) {
		DisplayErrorEx("iDias:DnPakPack", "GetTempFile");
		CloseHandle(hFile);

		return FALSE;
	}

	WriteLog("iDias:DnPakPack", 5, "Temp file is %s", pakFileTemp);
	WriteLog("iDias:DnPakPack", 5, "Adding %d file(s)", fCount);
	for (INT i = 0; i < fCount; i++) {
		HANDLE hsFile;
		DWORD hSize;

		hsFile = CreateFile("H:\\Dragon Nest\\PAK WIP\\00Resource_dv_lk_cyclones.pak\\resource\\dv\\dv_blank_model_cyclone.skn", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (!hsFile) {
			DisplayErrorEx("iDias:DnPakPack", "CreateFile");
			return FALSE;
		}

		hSize = GetFileSize(hsFile, NULL);
		if (!hSize) {
			DisplayErrorEx("iDias:DnPakPack", "GetFileSize");
			CloseHandle(hsFile);

			return FALSE;
		}

		LPVOID fileBuffer = malloc(hSize);
		LPVOID fileBufferOut = malloc(hSize);

		if (!ReadFile(hsFile, fileBuffer, hSize, NULL, NULL)) {
			DisplayErrorEx("iDias:DnPakPack", "ReadFile");
			CloseHandle(hsFile);

			return FALSE;
		}

		CloseHandle(hsFile);

		PAK_FILEINFO pakFileInfo;

		// zlib struct
		z_stream defstream;
		defstream.zalloc = Z_NULL;
		defstream.zfree = Z_NULL;
		defstream.opaque = Z_NULL;

		defstream.avail_in = hSize; // size of input, string + terminator
		defstream.next_in = (Bytef *)fileBuffer; // input char array
		defstream.avail_out = hSize; // size of output
		defstream.next_out = (Bytef *)fileBufferOut; // output char array

		// the actual compression work.
		deflateInit(&defstream, Z_BEST_COMPRESSION);
		deflate(&defstream, Z_FINISH);
		deflateEnd(&defstream);

		// temporary file
		hsFile = CreateFile(pakFileTemp, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hsFile == INVALID_HANDLE_VALUE) {
			DisplayErrorEx("iDias:DnPakPack", "CreateFile");
			CloseHandle(hsFile);

			free(fileBuffer);
			free(fileBufferOut);

			return FALSE;
		}

		DWORD hsSize = GetFileSize(hsFile, NULL);
		LPVOID hsBuffer = malloc(hsSize);

		if (!ReadFile(hsFile, hsBuffer, hsSize, NULL, NULL)) {
			DisplayErrorEx("iDias:DnPakPack", "ReadFile");
			CloseHandle(hsFile);

			free(hsBuffer);

			return FALSE;
		}

		SetFilePointer(hsFile, 0, NULL, FILE_END);

		WriteLog("iDias:DnPakPack", 5, "File %d of %d", i + 1, fCount);
		if (!WriteFile(hsFile, fileBufferOut, defstream.total_out + 1, NULL, NULL)) {
			DisplayErrorEx("iDias:DnPakPack", "WriteFile");
			CloseHandle(hsFile);

			free(hsBuffer);

			return FALSE;
		}

		CloseHandle(hsFile);

		// init pakFileInfo struct
		pakFileInfo.RealSize = hSize;
		pakFileInfo.RawSize = defstream.total_out;
		pakFileInfo.CompressedSize = defstream.total_out;
		pakFileInfo.FileDataOffset = fileOffset;
		sprintf(pakFileInfo.FilePath, "\\File_no_%d.testing", i + 1);

		// add to array
		fInfo[i] = pakFileInfo;

		// increment offset for pakHeader
		fileOffset += (defstream.total_out + 1);
	}
	WriteLog("iDias:DnPakPack", 5, "OK");

	// init pakHeader
	WriteLog("iDias:DnPakPack", 5, "Writing PAK header");
	pakHeader.FileCount = fCount;
	pakHeader.FileIndexTableOffset = fileOffset;
	strcpy(pakHeader.MagicNumber, "EyedentityGames Packing File 0.1");
	pakHeader.Unknown = 0x0B;
	
	// writing pakHeader to file
	WriteFile(hFile, &pakHeader, HEADER_SIZE, NULL, NULL);
	WriteLog("iDias:DnPakPack", 5, "OK");

	WriteLog("iDias:DnPakPack", 5, "Writing compressed file data");
	HANDLE tempFile = CreateFile(pakFileTemp, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD tempSize = GetFileSize(tempFile, NULL);
	fileTotalBuffer = malloc(tempSize);

	if (!ReadFile(tempFile, fileTotalBuffer, tempSize, NULL, NULL)) {
		DisplayErrorEx("iDias:DnPakPack", "ReadFile");
		CloseHandle(tempFile);

		free(fileTotalBuffer);

		return FALSE;
	}

	if (!WriteFile(hFile, fileTotalBuffer, tempSize, NULL, NULL)) {
		DisplayErrorEx("iDias:DnPakPack", "WriteFile");
		CloseHandle(tempFile);

		free(fileTotalBuffer);

		return FALSE;
	}

	WriteLog("iDias:DnPakPack", 5, "OK");
	free(fileTotalBuffer);
	CloseHandle(tempFile);

	DeleteFile(pakFileTemp);

	WriteLog("iDias:DnPakPack", 5, "Writing fileInfo");
	// write filePakInfo
	for (INT i = 0; i < fCount; i++)
		WriteFile(hFile, &fInfo[i], FILE_INFO_SIZE, NULL, NULL);

	WriteLog("iDias:DnPakPack", 5, "OK");

	// end all
	CloseHandle(hFile);
	WriteLog("iDias:DnPakPack", 5, "OK");
	return TRUE;
}

BOOL WINAPI DnPakUnpack(LPSTR sSource, LPSTR sDestination) {
	HANDLE hFile;
	DWORD hSize;
	LPVOID lBuffer;
	DWORD bytesRead;
	DWORD oldProtection;

	PPAK_HEADER pakHeader = {};

	WriteLog("iDias:DnPakUnpack", 5, "Attempting to open %s", sSource);
	hFile = CreateFile(sSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		DisplayErrorEx("iDias:DnPakUnpack", "CreateFile");
		return FALSE;
	}

	hSize = GetFileSize(hFile, NULL);
	if (!hSize) {
		DisplayErrorEx("iDias:DnPakUnpack", "GetFileSize");
		CloseHandle(hFile);

		return FALSE;
	}

	lBuffer = VirtualAlloc(NULL, hSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!lBuffer) {
		DisplayErrorEx("iDias:DnPakUnpack", "VirtualAlloc");
		CloseHandle(hFile);

		return FALSE;
	}

	if (!VirtualProtect(lBuffer, hSize, PAGE_EXECUTE_READWRITE, &oldProtection)) {
		DisplayErrorEx("iDias:DnPakUnpack", "VirtualProtect");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	WriteLog("iDias:DnPakUnpack", 5, "Allocated memory: %d bytes", hSize);
	if (!ReadFile(hFile, lBuffer, hSize, &bytesRead, NULL)) {
		DisplayErrorEx("iDias:DnPakUnpack", "ReadFile");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	// -- Header --
	WriteLog("iDias:DnPakUnpack", 5, "Reading file header");
	pakHeader = (PPAK_HEADER)lBuffer;
	WriteLog("iDias:DnPakUnpack", 5, "OK");
	// -- End Header --

	// -- FileEntry --
	WriteLog("iDias:DnPakUnpack", 5, "Reading file entry in 0x%08X", pakHeader->FileIndexTableOffset);
	if (!SetFilePointer(hFile, pakHeader->FileIndexTableOffset, NULL, NULL)) {
		DisplayErrorEx("iDias:DnPakUnpack", "SetFilePointer");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}
	WriteLog("iDias:DnPakUnpack", 5, "OK");

	UINT fCount = pakHeader->FileCount;
	PPAK_FILEINFO fileEntries = new PAK_FILEINFO[fCount];
	WriteLog("iDias:DnPakUnpack", 5, "Number of files: %d", fCount);

	for (UINT i = 0; i < fCount; i++) {
		PPAK_FILEINFO pakFileInfo = {};

		ReadFile(hFile, lBuffer, FILE_INFO_SIZE, &bytesRead, NULL);
		pakFileInfo = (PPAK_FILEINFO)lBuffer;

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

		strcpy(sDir, sDestination);
		strcat(sDir, "\\");
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

		WriteLog("iDias:DnPakUnpack", 5, "File %d: [0x%08X] [%d] [%d] %s", i + 1, filePointer, rawSize, realSize, virtualPath);
	}
	WriteLog("iDias:DnPakUnpack", 5, "OK");
	// -- End Decompressing --

	VirtualFree(lBuffer, hSize, MEM_RELEASE);
	CloseHandle(hFile);

	WriteLog("iDias:DnPakUnpack", 5, "OK");
	return TRUE;
}