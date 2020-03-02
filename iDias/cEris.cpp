#include "iDias.h"

#define MSGLEN			1024 * 1000
#define HEADER_SIZE		1024
#define METADATA_SIZE	192 + 260

typedef struct _PAK_HEADER {
	CHAR MagicNumber[8];
	DWORD UnknownOffset;
	UINT8 Unknown[124];
	DWORD MetadataOffset;
	// INT Unknown;
	// UINT FileIndexTableOffset;
	// UINT8 Padding[756];
} PAK_HEADER, *PPAK_HEADER;

typedef struct _PAK_METADATA {
	CHAR id[32];
	CHAR name[64];
	CHAR version[32];
	CHAR projectUrl[64];
	CHAR test[260];
} PAK_METADATA, *PPAK_METADATA;

VOID test(Bytef *sBuff, UINT rawSize) {
	UINT realSize = rawSize * 10;
	Bytef *sResult = (Bytef *)malloc(realSize);

	// zlib inflate start
	z_stream infstream;
	infstream.zalloc = Z_NULL;
	infstream.zfree = Z_NULL;
	infstream.opaque = Z_NULL;

	infstream.avail_in = rawSize; // size of input
	infstream.next_in = sBuff; // input char array
	infstream.avail_out = realSize; // size of output
	infstream.next_out = sResult; // output char array

	// the actual DE-compression work.
	inflateInit(&infstream);
	inflate(&infstream, Z_NO_FLUSH);
	inflateEnd(&infstream);

	CHAR msg[MSGLEN];
	sprintf(msg, "%s", sResult);
	MessageBox(GetActiveWindow(), msg, "Test", MB_OK | MB_ICONINFORMATION);

	free(sResult);
}

BOOL WINAPI ReadEris(LPSTR sSource, LPSTR sMessage) {
	HANDLE hFile;
	DWORD hSize;
	LPVOID lBuffer;
	DWORD bytesRead;
	DWORD oldProtection;

	PPAK_HEADER pakHeader = {};
	PPAK_METADATA pakMetadata = {};

	if (!strstr(sSource, ".eris.pak")) {
		MessageBox(GetActiveWindow(), "File yang Anda berikan bukan merupakan mod ERIS!", "Error", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	WriteLog("iDias:ReadEris", 5, "Attemtping to open %s", sSource);
	hFile = CreateFile(sSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		DisplayErrorEx("iDias:ReadEris", "CreateFile");
		return FALSE;
	}

	hSize = GetFileSize(hFile, NULL);
	if (!hSize) {
		DisplayErrorEx("iDias:ReadEris", "GetFileSize");
		CloseHandle(hFile);

		return FALSE;
	}

	lBuffer = VirtualAlloc(NULL, hSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!lBuffer) {
		DisplayErrorEx("iDias:ReadEris", "VirtualAlloc");
		CloseHandle(hFile);

		return FALSE;
	}

	if (!VirtualProtect(lBuffer, hSize, PAGE_EXECUTE_READWRITE, &oldProtection)) {
		DisplayErrorEx("iDias:ReadEris", "VirtualProtect");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	WriteLog("iDias:ReadEris", 5, "Allocated memory: %d bytes", hSize);
	if (!ReadFile(hFile, lBuffer, hSize, &bytesRead, NULL)) {
		DisplayErrorEx("iDias:ReadEris", "ReadFile");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	CHAR msg[MSGLEN];
	INT msg_len = 0;

	// -- Header --
	pakHeader = (PPAK_HEADER)lBuffer;

	msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "-----\r\nHEADER\r\n-----\r\nMagic: %s\r\n\r\nUnknown Offset: 0x%08X\r\nMeta Data Offset: 0x%08X\r\n\r\n",
		pakHeader->MagicNumber,
		pakHeader->UnknownOffset,
		pakHeader->MetadataOffset);

	WriteLog("iDias:ReadEris", 5, "Metadata offset: 0x%08X", pakHeader->MetadataOffset);
	// -- End Header --

	// -- Metadata --
	if (!SetFilePointer(hFile, pakHeader->MetadataOffset, NULL, NULL)) {
		DisplayErrorEx("iDias:ReadEris", "SetFilePointer");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	if (!ReadFile(hFile, lBuffer, METADATA_SIZE, &bytesRead, NULL)) {
		DisplayErrorEx("iDias:ReadEris", "ReadFile");
		VirtualFree(lBuffer, hSize, MEM_RELEASE);
		CloseHandle(hFile);

		return FALSE;
	}

	pakMetadata = (PPAK_METADATA)lBuffer;
	msg_len += snprintf(msg + msg_len, MSGLEN - msg_len, "-----\r\nMETADATA\r\n-----\r\nID: %s\r\nName: %s\r\nVersion: %s\r\nProject URL: %s\r\n\r\n",
		pakMetadata->id,
		pakMetadata->name,
		pakMetadata->version,
		pakMetadata->projectUrl);

	// test((Bytef *)pakMetadata->test, 260);
	// -- End Metadata --

	strcpy(sMessage, msg);

	VirtualFree(lBuffer, hSize, MEM_RELEASE);
	CloseHandle(hFile);

	WriteLog("iDias:ReadEris", 5, "OK");
	return TRUE;
}