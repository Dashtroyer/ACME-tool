//---------------------------------------------------------------------------------------
// ebdTranslate.cpp : Read and translate EBD lines into SEM injection addresses
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
int ebdTranslate(string name, vector<int> coordinates, vector<int> frames, vector<int> words, int clk_regions)
{
	// Variables Definition
	bitset<BITS_IN_LINE> EBDline;				// 32-bits EBD File Line
	ifstream EBDfile;							// Input EBD File
	ofstream addrfile;							// Output File
	string fileLine;							// EBD File Line
	string LA, WD_BT;							// Linear Address and Word+Bit strings
	stringstream WD_BT_str;						// String Stream for Word+Bit manipulation
	int lineMin, lineMax, wordMin, wordMax;		// EBD File Min-Max Ranges
	int addresses = 0;							// Number of Injection Addresses Created

	// Open Input and Output Files
	EBDfile.open(name, ifstream::in);
	addrfile.open("injectionRange.txt", ofstream::out);

	// Read EBD File
	for (int i = 0; i < clk_regions; i++) {
		// Skip Header and Dummy Frames
		if (coordinates.at(0) == 1) {
			// UltraScale
			for (int j = 0; j < DUMMY_ULTRASCALE; j++) {
				getline(EBDfile, fileLine);
			}
		}
		else {
			// 7-Series
			for (int j = 0; j < DUMMY_7SERIES; j++) {
				getline(EBDfile, fileLine);
			}
		}

		// Get Line and Word Ranges
		lineMin = frames.at(i * 2);
		lineMax = frames.at(i * 2 + 1);
		wordMin = words.at(i * 2);
		wordMax = words.at(i * 2 + 1);
		/*cout << "linemin " << lineMin << endl;
		cout << "linemax " << lineMax << endl;
		cout << "wordmin " << wordMin << endl;
		cout << "wordmax " << wordMax << endl;*/

		// Go to First Frame Position and Read the Correct Amount of Words
		EBDfile.seekg((BITS_IN_LINE + 2) * lineMin, ios_base::cur);
		for (int k = lineMin; k <= lineMax; k = k + WF_ULTRASCALE) {
			for (int m = 0; m < WF_ULTRASCALE; m++) {
				if ((m >= wordMin) && (m <= wordMax)) {
					getline(EBDfile, fileLine);
					EBDline = (bitset<BITS_IN_LINE>(fileLine));
					// If Line /= 0
					if (EBDline.count() != 0) {
						for (int n = 0; n < BITS_IN_LINE; n++) {
							// For each 1 (Essential Bit) in the EBD Line
							if (EBDline[n]) {
								// UltraScale
								if (coordinates.at(0) == 1) {
									// Linear Address
									LA = bin2hex(bitset<BITS_IN_LINE>(stoi("000" + dec2bin(k / WF_ULTRASCALE), nullptr, 2)), 5);
								}
								// 7-Series
								else {
									// Linear Address
									LA = bin2hex(bitset<BITS_IN_LINE>(stoi("000" + dec2bin(k / WF_7SERIES), nullptr, 2)), 5);
								}
								// Word
								WD_BT_str << setfill('0') << setw(7) << dec2bin(m);

								// Bit
								WD_BT_str << setfill('0') << setw(5) << dec2bin(n);

								// Combine Word and Bit into Hex
								WD_BT = bin2hex(bitset<BITS_IN_LINE>(stoi(WD_BT_str.str(), nullptr, 2)), 3);

								// Write Injection Address to File
								addrfile << "C0" << LA << WD_BT << endl;

								// Clear Stringstream and Increase Counter
								WD_BT_str.str(string());
								addresses++;
							}
						}
						//cout << "line: " << EBDline << endl;
					}
				}
			}
		}
		// Go to Beginning of File
		EBDfile.seekg(0, ios_base::beg);
	}

	// Close Files
	EBDfile.close();
	addrfile.close();

	return addresses;
}
