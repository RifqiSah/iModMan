#include "iDias.h"

#define HEADER_SIZE		32
#define FILE_INFO_SIZE	316

typedef struct _DIAS_HEADER {
	CHAR MagicNumber[16]; // File magic number / identifier string.
	UINT Major; // Major version.
	UINT Minor; // Minor version
	UINT FileCount; // Number of files in this PAK.
	UINT FileIndexTableOffset; // A pointer to the location of the file index table
} DIAS_HEADER, *PDIAS_HEADER;

typedef struct _PAK_FILEINFO {
	CHAR FilePath[256]; // Virtual pak of file
	UINT RawSize; // Size of this file
	UINT RealSize; // Size of this file, in bytes, when decompressed. This value may be zero, which simply means that you will not be able to pre - allocate a buffer when decompressing.
	UINT CompressedSize; // The size of this file, in bytes, when compressed in the PAK. Should be the same as Raw Size.
	UINT FileDataOffset; // A pointer to the location of this file's data.
} PAK_FILEINFO, *PPAK_FILEINFO;

VOID Msg(const CHAR* a, UINT type) {
	MessageBox(GetActiveWindow(), a, "iDias", type);
}

BOOL WINAPI DiasPakRead(LPSTR sSource, LPSTR sMessage) {
	return TRUE;
}

BOOL WINAPI DiasPakPack(LPSTR sSource, LPSTR sDestination) {
	HANDLE hFile;
	DIAS_HEADER dHeader;

	hFile = CreateFile(sSource, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		Msg("File tidak ditemukan", MB_ICONERROR);
		return FALSE;
	}

	strcpy(dHeader.MagicNumber, "DIAS");
	dHeader.Major = 0x1;
	dHeader.Minor = 0x0;
	dHeader.FileCount = 0xAB;
	dHeader.FileIndexTableOffset = 0xFFAD;

	if (!WriteFile(hFile, &dHeader, HEADER_SIZE, NULL, NULL)) {
		Msg("Gagal menulis kedalam file!", MB_ICONERROR);
		CloseHandle(hFile);
	}

	CloseHandle(hFile);

	Msg("Sukses membuat file pak!", MB_ICONINFORMATION);
	return TRUE;
}

BOOL WINAPI DiasPakUnpack(LPSTR sSource, LPSTR sDestination) {
	return TRUE;
}