#include "iDias.h"

#define MSGLEN			1024 * 1000
#define HEADER_SIZE		1024
#define METADATA_SIZE	192

typedef struct _PAK_HEADER {
	CHAR MagicNumber[8];
	UINT8 Unknown[128];
	DWORD MetadataOffset;
	// INT Unknown;
	// UINT FileIndexTableOffset;
	// UINT8 Padding[756];
} PAK_HEADER, *PPAK_HEADER;

typedef struct _PAK_METADATA {
	CHAR FileName[32];
	CHAR ErisName[64];
	CHAR Version[32];
	CHAR Other[64];
} PAK_METADATA, *PPAK_METADATA;

BOOL WINAPI ReadEris(LPSTR sSource, LPSTR sMessage) {
	HANDLE hFile;
	DWORD hSize;
	LPVOID lBuffer;
	DWORD bytesRead;
	DWORD oldProtection;

	PPAK_HEADER pakHeader = {};
	PPAK_METADATA pakMetadata = {};

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
	pakHeader = (PPAK_HEADER)lBuffer;

	msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "-----\r\nHEADER\r\n-----\r\nMagic: %s\r\nMeta Data Offset: 0x%08X\r\n\r\n",
		pakHeader->MagicNumber,
		pakHeader->MetadataOffset);
	// -- End Header --

	// -- Metadata --
	if (!SetFilePointer(hFile, pakHeader->MetadataOffset, NULL, NULL)) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadEris", (LPSTR)"SetFilePointer");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	if (!ReadFile(hFile, lBuffer, METADATA_SIZE, &bytesRead, NULL)) {
		DisplayErrorEx((LPSTR)"iDias:cPack:ReadEris", (LPSTR)"ReadFile");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	pakMetadata = (PPAK_METADATA)lBuffer;
	msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "-----\r\nMETADATA\r\n-----\r\nEris Name: %s\r\nVersion: %s\r\nFilename: %s\r\nOther: %s\r\n\r\n",
		pakMetadata->ErisName,
		pakMetadata->Version,
		pakMetadata->FileName,
		pakMetadata->Other);
	// -- End Metadata --

	strcpy(sMessage, msg);

	VirtualFree(lBuffer, hSize, MEM_RELEASE);
	CloseHandle(hFile);

	return TRUE;
}
