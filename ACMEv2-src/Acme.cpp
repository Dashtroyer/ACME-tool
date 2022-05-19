//---------------------------------------------------------------------------------------
// Acme.cpp : Automatic Configuration Memory Error-Injection (Main)
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
// MAIN
//---------------------------------------------------------------------------------------
int main()
{
	//-------------------------------------------
	// Variables Definition
	//-------------------------------------------
	vector<int> coordinates;					// Input Vector with pBlock Coordinates
	vector<int> frames;							// Vector with Starting and Ending Frames to Read from the EBD File
	vector<int> words;							// Vector with the First and Last Words to Read
	string name;								// EBD File Name
	int clk_regions = 0;						// Number of Different Clock Regions in which the Design is
	int addresses = 0;							// Number of Injection Addresses Created

	//-------------------------------------------
	// Print Welcome Message and Instructions
	//-------------------------------------------
	coordinates = welcome();

	//-------------------------------------------
	// Obtain EBD File Name
	//-------------------------------------------
	name = ebdName();

	//-------------------------------------------
	// Correct X Axis Coordinates
	//-------------------------------------------
	adjustCoordinates(coordinates);

	//-------------------------------------------
	// Calculate Frames and Words to Read
	//-------------------------------------------
	cout << " Obtaining frames   ...";
	// Obtain Device Type
	if (coordinates.at(0) == 1) {		// KCU105
		frames = KCU105(coordinates, words, clk_regions);
	}
	else {
		cout << "-> ERROR, incorrect device" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "  Done" << endl;

	//-------------------------------------------
	// Translate Lines from the EBD File
	//-------------------------------------------
	cout << " Creating addresses ...";
	addresses = ebdTranslate(name, coordinates, frames, words, clk_regions);
	cout << "  Done" << endl;
	cout << " Addresses created  ...  " << addresses << endl;

	//----------------------------------
	// Free Vectors
	//----------------------------------
	vector<int>().swap(coordinates);
	vector<int>().swap(frames);
	vector<int>().swap(words);

	//----------------------------------
	// Exit
	//----------------------------------
	cout << endl;
	cout << "-> Press <ENTER> to exit" << endl;
	cin.clear();
	cin.ignore(256, '\n');
	cin.get();
	return 0;
}
