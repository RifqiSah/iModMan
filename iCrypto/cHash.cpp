#include "hMain.h"
#include "hash_library/sha256.h"

#define BUFFERSIZE 1024 * 1024
DWORD g_BytesTransferred = 0;

BOOL GetSHA256Hash(PCHAR buffer, DWORD dwBufferSize, PBYTE byteFinalHash, PDWORD dwFinalHashSize)
{
	DWORD dwStatus = 0;
	BOOL bResult = FALSE;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	// PBYTE byteHash;
	DWORD cbHashSize = 0;
	DWORD dwCount = sizeof(DWORD);

	// Get handle to the crypto provider
	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		printf("\nCryptAcquireContext failed, Error=0x%.8x", GetLastError());
		return FALSE;
	}

	//Specify the Hash Algorithm here
	if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash))
	{
		printf("\nCryptCreateHash failed,  Error=0x%.8x", GetLastError());
		goto EndHash;
	}

	//Create the hash with input buffer
	if (!CryptHashData(hHash, (const BYTE*)buffer, dwBufferSize, 0))
	{
		printf("\nCryptHashData failed,  Error=0x%.8x", GetLastError());
		goto EndHash;
	}

	//Get the final hash size 
	if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE *)&cbHashSize, &dwCount, 0))
	{
		printf("\nCryptGetHashParam failed, Error=0x%.8x", GetLastError());
		goto EndHash;
	}

	//check if the output buffer is enough to copy the hash data
	if (*dwFinalHashSize < cbHashSize)
	{
		printf("\nOutput buffer (%d) is not sufficient, Required Size = %d", *dwFinalHashSize, cbHashSize);
		goto EndHash;
	}

	//Now get the computed hash 
	if (CryptGetHashParam(hHash, HP_HASHVAL, byteFinalHash, dwFinalHashSize, 0))
	{
		printf("\n********** Hash Computed successfully ");
		bResult = TRUE;
	}
	else
		printf("\nCryptGetHashParam failed,  Error=0x%.8x", GetLastError());


EndHash:
	if (hHash) CryptDestroyHash(hHash);
	if (hProv) CryptReleaseContext(hProv, 0);

	return bResult;
}

INT WINAPI GetSHA265File(PCHAR sFilepath, LPSTR sHash)
{
	INT		ret = 0;
	HANDLE	hFile;
	DWORD	hSize;
	DWORD	dwBytesRead = 0;
	LPVOID	ReadBuffer;

	// Buat handle filenya
	hFile = CreateFile(sFilepath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);                 // no attr. template
	if (hFile == INVALID_HANDLE_VALUE)
	{
		// DisplayError(TEXT("CreateFile"));
		// _tprintf(TEXT("Terminal failure: unable to open file \"%s\" for read.\n"), argv[1]);
		return 0;
	}

	// Cari ukuran filenya untuk read data nantinya
	ret = GetFileSize(hFile, &hSize);
	if (!ret)
		return 0;

	// Alokasi memory sebanyak ukuran file
	ReadBuffer = malloc(hSize);
	if (!ReadBuffer)
		return 0;

	// Mulai baca filenya
	ret = ReadFile(hFile, &ReadBuffer, hSize, &dwBytesRead, NULL);
	if (!ret)
		return 0;

	// Dapatkna hashnya
	BYTE byteHashbuffer[256];
	DWORD dwFinalHashSize = 256;

	GetSHA256Hash((PCHAR)ReadBuffer, hSize, byteHashbuffer, &dwFinalHashSize);
	strcpy(sHash, (LPSTR)byteHashbuffer);

	// Kosongkan lagi jika sudah selesai
	free(ReadBuffer);

	// Jangan lupa tutup filenya dulu ya setelah selesai
	CloseHandle(hFile);

	// Keluarkan hasil hashnya
	return 1;
}