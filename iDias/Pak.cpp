/////////////////////////////////////////////////////////////////////////////////////////////
//
// Name:		Pak.cpp
//
// Author:		Raymond Wilson - ray.wilson@blueyonder.co.uk
//
// Date:		26th May 2003
//
// Notice:		Copyright (C) 2003, Raymond Wilson
//
/////////////////////////////////////////////////////////////////////////////////////////////

#include "pak.h"

/////////////////////////////////////////////////////////////////////////////////////////////

CPakFile::CPakFile()
{
	// Default the header
	ZeroMemory(&m_Header, sizeof(sPakHeader));

	// Default other variables
	ZeroMemory(m_szFolderPath, 300);
	ZeroMemory(m_szPakName, 300);

	// Add a blank dummy node to the file table
	sFileTableEntry* Dummy = new sFileTableEntry();
	ZeroMemory(Dummy, sizeof(sFileTableEntry));
	m_FileTable = Dummy;
}

CPakFile::~CPakFile()
{
	// Default the header
	ZeroMemory(&m_Header, sizeof(sPakHeader));

	// Default other variables
	ZeroMemory(m_szFolderPath, 300);
	ZeroMemory(m_szPakName, 300);

	// Clear the file table

	m_FileTable = NULL;
}

BOOL CPakFile::GenerateHFT()
{
	// Declare local variables
	int					iRandom = 0;			// Recieves a random number
	DWORD				dwFileCount = 0;		// Number of files in compile directory
	WIN32_FIND_DATA		FileData;				// Found file data is stored here
	HANDLE				hSearch;				// Search handle
	BOOL				bSearchFinished = FALSE;// Is search finished?
	char				Buffer[300] = { 0 };		// All purpose buffer

	// Deault the file data
	ZeroMemory(&FileData, sizeof(WIN32_FIND_DATA));

	// Seed the timer with the clock
	srand((unsigned)time(NULL));

	// Create the header signature
	memcpy(m_Header.szSignature, "DIAS", 6);

	// Set the file version
	m_Header.fVersion = 1.0;

	// Get a random 1 or 0 (TRUE or FALSE) and set cypher direction
	iRandom = rand() % 2;
	m_Header.bCypherAddition = (BOOL)iRandom;

	// Get the caesar cypher value
	iRandom = rand() % 256;
	m_Header.iCypherValue = (BYTE)iRandom;

	// Create a unique ID
	for (int i = 0; i < 10; i++)
	{
		iRandom = rand() % 256;
		m_Header.szUniqueID[i] = (char)iRandom;
	}

	// Get a local copy of the compilation folder name so that the one
	// in the class isn't altered
	if (strlen(m_szFolderPath) == 0) { return FALSE; }
	memcpy(Buffer, m_szFolderPath, 300);

	// Search in the specified folder for hte first file
	lstrcat(Buffer, "\\*.*");
	hSearch = FindFirstFile(Buffer, &FileData);
	if (hSearch == INVALID_HANDLE_VALUE) { return FALSE; }

	// Start filling in the file table
	while (bSearchFinished == FALSE)
	{
		// Error Check
		if (strcmp(FileData.cFileName, ".") == 0)
		{
			// Acquire the next file in the directory
			if (!FindNextFile(hSearch, &FileData)) { bSearchFinished = TRUE; }
			continue;
		}

		// Error Check
		if (strcmp(FileData.cFileName, "..") == 0)
		{
			// Acquire the next file in the directory
			if (!FindNextFile(hSearch, &FileData)) { bSearchFinished = TRUE; }
			continue;
		}

		// Create a node entry for the file table
		sFileTableEntry* TempEntry = new sFileTableEntry();

		// Store the file name
		memcpy(TempEntry->szFileName, FileData.cFileName, 30);
		// Store the file size
		TempEntry->dwFileSize = FileData.nFileSizeLow;
		// Default the offset value (worked out later)
		TempEntry->dwOffset = 0;

		// Add this to the file table
		TempEntry->Next = m_FileTable;
		m_FileTable = TempEntry;

		// Increment the files counter
		dwFileCount++;

		// Acquire the next file in the directory
		if (!FindNextFile(hSearch, &FileData)) { bSearchFinished = TRUE; }
	}

	// Close the search handle
	FindClose(hSearch);

	// Mark the number of files added in the header
	m_Header.dwNumFTEntries = dwFileCount;

	return TRUE;
}

BOOL CPakFile::WorkOutOffsets()
{
	// Declare local variables
	DWORD	dwFileHFTData = 0;			// Size of header and file table
	DWORD	dwOffset = 0;				// Individual files offset in to the PAK

	// Work out the size, in bytes, of the header and FT
	dwFileHFTData = sizeof(sPakHeader) + (m_Header.dwNumFTEntries * sizeof(sFileTableEntry));

	// Create a temporary node and make it the head of the linked list
	sFileTableEntry* Current;
	Current = m_FileTable;

	// Get the first offset
	dwOffset = dwFileHFTData + 1;

	while (Current != NULL)
	{
		// Check for the dummy entry
		if (Current->Next == NULL)
			return TRUE;

		// Set the offset
		Current->dwOffset = dwOffset;

		// Update the offset
		dwOffset = dwOffset + Current->dwFileSize;

		// Update the current variable
		Current = Current->Next;
	}

	return TRUE;
}

BOOL CPakFile::CreatePak(char* Path, char* Output)
{
	// Declare local variables
	FILE*	PAKStream;					// File pointer for writing to the PAK
	FILE*	InputStream;				// For reading in each file to be added
	fpos_t	Pos = 0;					// Position in the PAK file
	char	Buffer[300] = { 0 };			// General purpose buffer
	int		iStringLength = 0;			// String length

	// Error check
	if ((Path == NULL) || (Output == NULL)) { return FALSE; }

	// Store the function paramaters in the class
	iStringLength = strlen(Path);
	memcpy(m_szFolderPath, Path, iStringLength);
	iStringLength = strlen(Output);
	memcpy(m_szPakName, Output, iStringLength);

	// Create the header and file table
	if (!GenerateHFT()) { return FALSE; }

	// Work out the offsets
	if (!WorkOutOffsets()) { return FALSE; }

	// Open the file stream for writing the PAK
	PAKStream = fopen(Output, "wb");
	if (!PAKStream) { return FALSE; }

	// Write the PAK header
	fwrite(&m_Header, sizeof(sPakHeader), 1, PAKStream);

	// Get a local copy of the file table head
	sFileTableEntry* Current;
	Current = m_FileTable;

	// Encrypt and write out each file table entry
	while (Current != NULL)
	{
		// Check for the dummy entry (break if found)
		if (Current->Next == NULL) { break; }

		// Create a BYTE pointer for byte access to a file table entry
		BYTE* Ptr = NULL;

		// Create a BYTE array the same size as a file table entry
		Ptr = new BYTE[sizeof(sFileTableEntry)];

		// Copy the current file table entry in to the byte array
		memcpy(Ptr, Current, sizeof(sFileTableEntry));

		for (int i = 0; i < sizeof(sFileTableEntry); i++)
		{
			// Temporary BYTE variable
			BYTE Temp = 0;

			// Make equal to the relevant byte of the FT entry
			Temp = Ptr[i];

			// Encrypt BYTE according to the caesar cypher
			if (m_Header.bCypherAddition == TRUE)
				Temp += m_Header.iCypherValue;
			else
				Temp -= m_Header.iCypherValue;

			// Write the FT encrypted BYTE value
			fwrite(&Temp, sizeof(BYTE), 1, PAKStream);
		}

		// Move on to the next file table entry
		Current = Current->Next;

		// Delete the temporary BYTE pointer
		delete[] Ptr;
	}

	// Close the stream used for the header and file table
	fclose(PAKStream);

	// Reset variable to be the head of the file table
	Current = m_FileTable;

	// Read in each file at a time, encrypt it using the cypher and add to PAK
	while (Current != NULL)
	{
		// Declare local variables
		BYTE		DataBuffer = 0;

		// Check for the dummy file table entry
		if (Current->Next == NULL) { return TRUE; }

		// Open the PAK file for writing
		PAKStream = fopen(Output, "r+b");
		if (!PAKStream) { return FALSE; }

		// Create the absolute path of the file to be added to the PAK
		memcpy(Buffer, m_szFolderPath, 300);
		lstrcat(Buffer, "\\");
		lstrcat(Buffer, Current->szFileName);

		// Open the data stream for reading in a file to be added to the PAK
		InputStream = fopen(Buffer, "rb");
		if (!InputStream)
		{
			fclose(PAKStream);
			return FALSE;
		}

		// Set the position in the PAK file for this file to be written at
		Pos = Current->dwOffset;
		fsetpos(PAKStream, &Pos);

		// Read in the file a byte at a time, encrypt it and write to PAK
		for (DWORD i = 0; i < Current->dwFileSize; i++)
		{
			// Get the first BYTE from the file to be added
			DataBuffer = fgetc(InputStream);

			// Encrypt the file accordingly
			if (m_Header.bCypherAddition == TRUE)
				DataBuffer += m_Header.iCypherValue;
			else
				DataBuffer -= m_Header.iCypherValue;

			// Write to the PAK file starting at the offset
			fwrite(&DataBuffer, sizeof(BYTE), 1, PAKStream);
		}

		// Close both the file streams
		fclose(InputStream);
		fclose(PAKStream);

		// Advance to the next file to be written according to the FT
		Current = Current->Next;
	}

	return TRUE;
}