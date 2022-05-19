//---------------------------------------------------------------------------------------
// ebdName.cpp : Search for the EBD file in the directory and return its name
//---------------------------------------------------------------------------------------
//
// Copyright(C) 2021 - Dr. Luis Aranda Barjola
// Universidad Nebrija - ARIES Research Center
//
// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//
//---------------------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------------------
#include "stdafx.h"
#include "mainHeader.h"

//---------------------------------------------------------------------------------------
// FUNCTION
//---------------------------------------------------------------------------------------
string ebdName()
{
	// Variables Definition
	string name;							// EBD File Name
	char executingPath[MAX_PATH];			// Executing Path
	char searchPath[MAX_PATH];				// EBD Search Path
	string currentPath;						// Current Path
	WIN32_FIND_DATA ffd;					// Win32 Data
	bool found = false;						// EBD File Found

	// Get Current Directory Path
	if (GetModuleFileName(NULL, executingPath, sizeof(executingPath)) == 0) {
		cout << "Error obtaining path" << endl;
		exit(EXIT_FAILURE);
	}
	currentPath = string(executingPath).substr(0, string(executingPath).find_last_of("/\\"));

	// Copy the String to a Buffer, then Append '\*' to the Directory Name
	StringCchCopy(searchPath, MAX_PATH, currentPath.c_str());
	StringCchCat(searchPath, MAX_PATH, TEXT("\\*"));

	// Find First File
	HANDLE hFind = FindFirstFile(searchPath, &ffd);
	if (INVALID_HANDLE_VALUE == hFind) {
		cout << "Error searching files" << endl;
		exit(EXIT_FAILURE);
	}

	// Search for EBD Files
	do {
		if (strstr(ffd.cFileName, ".ebd")) {
			// Save EBD File Name
			name = ffd.cFileName;
			found = true;
			break;
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	// No EBDs in Directory
	if (!found) {
		cout << endl;
		cout << "-> No EBD files found!! Press <ENTER> to exit" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin.get();
		exit(EXIT_FAILURE);
	}
	else {
		cout << " EBDfile : " << name << endl;
	}
	cout << endl;

	return name;
}
