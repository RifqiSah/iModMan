#include "iDias.h"

#define MSGLEN			1024 * 1000

BOOL WINAPI ReadEris(LPSTR sSource, LPSTR sMessage) {
	HANDLE hFile;
	DWORD hSize;
	LPVOID lBuffer;
	DWORD bytesRead;
	DWORD oldProtection;

	hFile = CreateFile(sSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadEris", (LPSTR)"CreateFile");
		return FALSE;
	}

	hSize = GetFileSize(hFile, NULL);
	if (!hSize) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadEris", (LPSTR)"GetFileSize");
		CloseHandle(hFile);

		return FALSE;
	}

	lBuffer = VirtualAlloc(NULL, hSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!lBuffer) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadEris", (LPSTR)"VirtualAlloc");
		CloseHandle(hFile);

		return FALSE;
	}

	if (!VirtualProtect(lBuffer, hSize, PAGE_EXECUTE_READWRITE, &oldProtection)) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadEris", (LPSTR)"VirtualProtect");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	if (!ReadFile(hFile, lBuffer, hSize, &bytesRead, NULL)) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadEris", (LPSTR)"ReadFile");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	CHAR msg[MSGLEN];
	INT msg_len = 0;

	// -- Header --
	/*
	pakHeader = (PPAK_HEADER)lBuffer;

	msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "-----\r\nHEADER\r\n-----\r\nMagic: %s\r\nNumber of Files: %d\r\nFile Index Offset: 0x%08X\r\n\r\n",
		pakHeader->MagicNumber,
		pakHeader->FileCount,
		pakHeader->FileIndexTableOffset);
		*/
	// -- End Header --

	// -- FileEntry --
	/*
	msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "-----\r\nFILES\r\n-----\r\n");

	if (!SetFilePointer(hFile, pakHeader->FileIndexTableOffset, NULL, NULL)) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadPak", (LPSTR)"SetFilePointer");
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
	*/
	// -- End File Entry --

	strcpy(sMessage, msg);

	VirtualFree(lBuffer, hSize, MEM_RELEASE);
	CloseHandle(hFile);

	return TRUE;
}
