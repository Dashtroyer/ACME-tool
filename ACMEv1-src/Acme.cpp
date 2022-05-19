//---------------------------------------------------------------------------------------
// Acme.cpp : Automatic Configuration Memory Error-Injection (Main)
//---------------------------------------------------------------------------------------
//
// Copyright(C) 2020 - Dr. Luis Aranda Barjola
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
// MAIN
//---------------------------------------------------------------------------------------
int main()
{
	//----------------------
	// Variables Definition
	//----------------------
	vector<string> names;						// EBD Vector Names
	vector<int> coordinates;					// Input Vector with pBlock Coordinates
	vector<int> fileRange;						// Vector with EBD File pBlock Ranges
	vector<bitset<BITS_IN_LINE>> EBDlines;		// 32-bits Vector with EBD File Lines
	ifstream EBDfile;							// Stream File
	string fileLine;							// EBD File Line
	int lineMin = 0, lineMax = 0, pairMax = 0;	// EBD File Line Min-Max Ranges
	int frames = 0;								// Number of Frames Extracted from the EBD File

	//----------------------------------------
	// Print Welcome Message and Instructions
	//----------------------------------------
	coordinates = welcome();

	//----------------------------------------
	// Calculate pBlock File Range
	//----------------------------------------
	fileRange = pBlockRange(coordinates, pairMax);

	//----------------------------------------
	// Obtain EBD File Names
	//----------------------------------------
	names = ebdNames();

	//----------------------------------------
	// Read and Store EBD Files
	//----------------------------------------
	cout << " Reading files   ...";
	for (vector<string>::iterator it = names.begin(); it < names.end(); it++) {
		// Open File
		EBDfile.open(*it, ifstream::in);

		// Process pBlock File Range
		for (int i = 0; i < pairMax; i++) {
			// Skip File Header
			for (int j = 0; j < 8; j++) {
				getline(EBDfile, fileLine);
			}

			// Get Line Ranges
			lineMin = fileRange.at(2 * i);
			lineMax = fileRange.at(2 * i + 1);

			// Go to File Position lineMin and Read this Number of Lines
			EBDfile.seekg((BITS_IN_LINE + 2)*lineMin, ios_base::cur);
			for (int k = lineMin; k <= lineMax; k++) {
				// Get Line
				getline(EBDfile, fileLine);
				EBDlines.push_back(bitset<BITS_IN_LINE>(fileLine));
			}
			// Go to Beginning of File
			EBDfile.seekg(0, ios_base::beg);
		}

		// Close File
		EBDfile.close();
	}
	cout << "  Done" << endl;

	// Free Vectors
	vector<string>().swap(names);

	//----------------------------------
	// Create Injection Range File
	//----------------------------------
	cout << " Injection file  ...";
	frames = injectionRange(EBDlines, fileRange, coordinates, pairMax);
	cout << "  Done" << endl << endl;
	cout << " Frames created  : " << frames << endl << endl;

	// Free Vectors
	vector<int>().swap(coordinates);
	vector<int>().swap(fileRange);
	vector<bitset<BITS_IN_LINE>>().swap(EBDlines);

	//----------------------------------
	// Exit
	//----------------------------------
	cout << endl;
	cout << "-> Press <ENTER> to exit" << endl;
	cin.clear();
	cin.ignore(256, '\n');
	cin.get();

	// Return
	return 0;
}
