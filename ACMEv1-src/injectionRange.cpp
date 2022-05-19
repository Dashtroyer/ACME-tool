//---------------------------------------------------------------------------------------
// injectionRange.cpp : Create injection range file using best EBD matrix
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
// FUNCTION
//---------------------------------------------------------------------------------------
int injectionRange(vector<bitset<BITS_IN_LINE>> EBDlines, vector<int> fileRange, vector<int> coordinates, int &pairMax)
{
	// Variables Definition
	vector<bool> onesVector(BITS_IN_LINE);	// Vector with the Position of the Ones in a Line
	ofstream injectionFile;					// Output File
	string part1, part2;					// Two Parts of Injection Range
	stringstream part2_str;					// String Stream for Second Part
	int lineMin = 0, lineMax = 0;			// EBD File Line Min-Max Ranges
	int k = 0;								// Loop Counter
	int frames = 0;							// Number of Frames Written in the Text File

											// Open Output File
	injectionFile.open("frameRange.txt", ofstream::out);

	// Save Injection Range in File
	for (int p = 0; p < pairMax; p++) {
		// Get Line Ranges
		lineMin = fileRange.at(2 * p);
		lineMax = fileRange.at(2 * p + 1);

		for (int i = lineMin; i <= lineMax; i++) {
			// If Line /= 0
			if (EBDlines.at(k).count() != 0) {
				// Find the Ones' Indexes
				for (int j = 0; j < BITS_IN_LINE; j++) {
					if (EBDlines.at(k)[j]) {
						onesVector[j] = true;
					}
				}

				// For Every One in the Line
				for (int j = 0; j < BITS_IN_LINE; j++) {
					if (onesVector[j] == true) {
						//-------------------
						// UltraScale Family
						//-------------------
						if (coordinates.at(0) == 5) {
							// First Part
							part1 = bin2hex(bitset<BITS_IN_LINE>(stoi("000" + dec2bin(((i - ((i - 10) % FRAME_SIZE_ULTRASCALE) - 10) / FRAME_SIZE_ULTRASCALE) - 1), nullptr, 2)), 5);

							// Second Part
							part2_str << setfill('0') << setw(7) << dec2bin((i - 10) % FRAME_SIZE_ULTRASCALE);
						}
						//-------------------
						// 7-Series Family
						//-------------------
						else {
							// First Part
							part1 = bin2hex(bitset<BITS_IN_LINE>(stoi("000" + dec2bin(((i - (i % FRAME_SIZE)) / FRAME_SIZE) - 1), nullptr, 2)), 5);

							// Second Part
							part2_str << setfill('0') << setw(7) << dec2bin(i % FRAME_SIZE);
						}

						part2_str << setfill('0') << setw(5) << dec2bin(j);
						part2 = bin2hex(bitset<BITS_IN_LINE>(stoi(part2_str.str(), nullptr, 2)), 3);

						// Write Injection Address to File
						injectionFile << "C0" << part1 << part2 << endl;

						// Clear Stringstream and Vector
						part2_str.str(string());
						onesVector[j] = false;

						// Increment Frame Counter
						frames++;
					}
				}
			}
			// Increment Counter
			k++;
		}
	}

	// Close Output File
	injectionFile.close();

	return frames;
}
