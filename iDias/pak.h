/////////////////////////////////////////////////////////////////////////////////////////////
//
// Name:		Pak.h
//
// Author:		Raymond Wilson - ray.wilson@blueyonder.co.uk
//
// Date:		25th May 2003
//
// Notice:		Copyright (C) 2003, Raymond Wilson
//
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PAK_H
#define PAK_H

// INCLUDES
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// PAK file header
struct sPakHeader
{
	char		szSignature[4];						// PAK Signature should be 'DIAS'
	float		fVersion;							// Version of PAK file
	DWORD		dwNumFTEntries;						// Number of file table entries
	BOOL		bCypherAddition;					// Should the caesar cypher add (or subtract)
	BYTE		iCypherValue;						// Random value used for the caesar cypher between 0-255
	char		szUniqueID[10];						// A unique ID for the file (other programs can check it)
	DWORD		dwReserved;							// Reserved Value
};

// Table Entry per file in the PAK file
struct sFileTableEntry
{
	char				szFileName[30];				// Name of one file in the PAK
	DWORD				dwFileSize;					// The size of the file in bytes
	DWORD				dwOffset;					// Offset of file in the PAK
	sFileTableEntry*	Next;						// Next file table entry (is a linked list)

	// Constructor
	sFileTableEntry()
	{
		ZeroMemory(szFileName, sizeof(szFileName));
		dwFileSize = 0;
		dwOffset = 0;
		Next = NULL;
	}

	// Deconstructor
	~sFileTableEntry()
	{
		ZeroMemory(szFileName, sizeof(szFileName));
		dwFileSize = 0;
		dwOffset = 0;
		delete Next;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////

class CPakFile
{
private:
	// Private Variables
	char					m_szFolderPath[300];		// Folder to compile in to PAK
	char					m_szPakName[300];			// Output PAK file path and name

	sPakHeader				m_Header;					// The header of the PAK file
	sFileTableEntry*		m_FileTable;				// The master file table for the PAK

	// Private Functions
	BOOL		GenerateHFT();							// Create a Header and File Table
	BOOL		WorkOutOffsets();						// Work out the file offsets in the PAK

public:
	CPakFile();											// Constructor
	~CPakFile();										// Deconstructor

	BOOL		CreatePak(char* Path, char* Output);	// Create the PAK file
};

#endif