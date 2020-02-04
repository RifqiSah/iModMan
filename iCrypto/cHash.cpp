#include "hMain.h"

#define LEN_MD5			16
#define LEN_SHA256		32

INT WINAPI GetMD5FileHash(PCHAR sFilepath, LPSTR sHash) {
	BOOL bResult = FALSE;
	HANDLE hFile = NULL;

	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;

	BYTE rgbHash[LEN_MD5];
	CHAR rgbDigits[] = "0123456789abcdef";

	hFile = CreateFile(sFilepath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (INVALID_HANDLE_VALUE == hFile) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetMD5FileHash", (LPSTR)"CreateFile");

		return 0;
	}

	// Get handle to the crypto provider
	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetMD5FileHash", (LPSTR)"CryptAcquireContext");
		CloseHandle(hFile);

		return 0;
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetMD5FileHash", (LPSTR)"CryptCreateHash");

		CloseHandle(hFile);
		CryptReleaseContext(hProv, 0);

		return 0;
	}

	DWORD hSize;
	PBYTE rgbFile;

	hSize = GetFileSize(hFile, NULL);
	if (!hFile) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetMD5FileHash", (LPSTR)"GetFileSize");
		CloseHandle(hFile);

		return 0;
	}

	rgbFile = (PBYTE)LocalAlloc(LMEM_FIXED, hSize);
	if (!rgbFile) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetMD5FileHash", (LPSTR)"LocalAlloc");
		CloseHandle(hFile);

		return 0;
	}

	DWORD cbRead = 0;
	while (bResult = ReadFile(hFile, rgbFile, hSize, &cbRead, NULL)) {
		if (0 == cbRead) break;

		if (!CryptHashData(hHash, rgbFile, cbRead, 0)) {
			DisplayErrorEx((LPSTR)"iCrypto:cHash:GetMD5FileHash", (LPSTR)"CryptHashData");

			CryptReleaseContext(hProv, 0);
			CryptDestroyHash(hHash);
			CloseHandle(hFile);

			return 0;
		}
	}

	if (!bResult) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetMD5FileHash", (LPSTR)"ReadFile");

		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		CloseHandle(hFile);

		return 0;
	}

	INT length = 0;
	PCHAR hash = new CHAR[(LEN_MD5 * 2) + 1];

	DWORD cbHash = LEN_MD5;
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
	{
		for (DWORD i = 0; i < cbHash; i++)
			length += snprintf(hash + length, ((LEN_MD5 * 2) + 1) - length, "%02X", rgbHash[i]);

		hash[strlen(hash)] = '\0';
	}
	else
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetMD5FileHash", (LPSTR)"CryptGetHashParam");

	strcpy(sHash, hash);

	LocalFree(rgbFile);

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	CloseHandle(hFile);

	return 1;
}

INT WINAPI GetSHA256FileHash(PCHAR sFilepath, LPSTR sHash) {
	BOOL bResult = FALSE;
    HANDLE hFile = NULL;

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    
    BYTE rgbHash[LEN_SHA256];
    CHAR rgbDigits[] = "0123456789abcdef";

    hFile = CreateFile(sFilepath, GENERIC_READ, FILE_SHARE_READ, NULL,  OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (INVALID_HANDLE_VALUE == hFile) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetSHA256FileHash", (LPSTR)"CreateFile");

        return 0;
    }

    // Get handle to the crypto provider
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetSHA256FileHash", (LPSTR)"CryptAcquireContext");
        CloseHandle(hFile);

        return 0;
    }

    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetSHA256FileHash", (LPSTR)"CryptCreateHash");

        CloseHandle(hFile);
        CryptReleaseContext(hProv, 0);

        return 0;
    }

	DWORD hSize;
	PBYTE rgbFile;

	hSize = GetFileSize(hFile, NULL);
	if (!hFile) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetSHA256FileHash", (LPSTR)"GetFileSize");
		CloseHandle(hFile);

		return 0;
	}

	rgbFile = (PBYTE)LocalAlloc(LMEM_FIXED, hSize);
	if (!rgbFile) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetSHA256FileHash", (LPSTR)"LocalAlloc");
		CloseHandle(hFile);

		return 0;
	}

	DWORD cbRead = 0;
    while (bResult = ReadFile(hFile, rgbFile, hSize, &cbRead, NULL)) {
        if (0 == cbRead) break;

        if (!CryptHashData(hHash, rgbFile, cbRead, 0)) {
			DisplayErrorEx((LPSTR)"iCrypto:cHash:GetSHA256FileHash", (LPSTR)"CryptHashData");

            CryptReleaseContext(hProv, 0);
            CryptDestroyHash(hHash);
            CloseHandle(hFile);

            return 0;
        }
    }

    if (!bResult) {
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetSHA256FileHash", (LPSTR)"ReadFile");

        CryptReleaseContext(hProv, 0);
        CryptDestroyHash(hHash);
        CloseHandle(hFile);

        return 0;
    }

	INT length = 0;
	PCHAR hash = new CHAR[(LEN_SHA256 * 2) + 1];

	DWORD cbHash = LEN_SHA256;
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
	{
		for (DWORD i = 0; i < cbHash; i++)
			length += snprintf(hash + length, ((LEN_SHA256 * 2) + 1) - length, "%02X", rgbHash[i]);

		hash[strlen(hash)] = '\0';
	}
	else
		DisplayErrorEx((LPSTR)"iCrypto:cHash:GetSHA256FileHash", (LPSTR)"CryptGetHashParam");

	strcpy(sHash, hash);

	LocalFree(rgbFile);

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    CloseHandle(hFile);

    return 1; 
}