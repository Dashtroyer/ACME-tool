//---------------------------------------------------------------------------------------
// welcome.cpp : Print welcome message and instructions and return pBlock coordinates
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
vector<int> welcome()
{
	// Variables Definition
	vector<int> coordinates;					// Output Vector with pBlock Coordinates and Board Type
	int input_val;								// Input Value Read from the User
	bool error_flag = false;					// Non-valid Input Value
	int MIN_X, MAX_X, MIN_Y, MAX_Y;				// Minimum and Maximum Range Values

	cout << "/****************************************************/" << endl;
	cout << "/**" << "                -  A C M E  -                   " << "**/" << endl;
	cout << "/**" << "                                                " << "**/" << endl;
	cout << "/**" << " usage : EBD file must be in the .exe directory " << "**/" << endl;
	cout << "/**" << "                                                " << "**/" << endl;
	cout << "/**" << "   - Supported devices:                         " << "**/" << endl;
	cout << "/**" << "      (1) KCU105 :    X [50,357] - Y [0,309]    " << "**/" << endl;
	//cout << "/**" << "      (2) ZedBoard :    X [,] - Y [,]    " << "**/" << endl;
	cout << "/**" << "                                                " << "**/" << endl;
	cout << "/**" << "   - Design coordinates:                        " << "**/" << endl;
	cout << "/**" << "       (X Lo,Y Lo)                              " << "**/" << endl;
	cout << "/**" << "                  x-------                      " << "**/" << endl;
	cout << "/**" << "                  |      |                      " << "**/" << endl;
	cout << "/**" << "                  |      |                      " << "**/" << endl;
	cout << "/**" << "                  |      |                      " << "**/" << endl;
	cout << "/**" << "                  |      |                      " << "**/" << endl;
	cout << "/**" << "                  |      |                      " << "**/" << endl;
	cout << "/**" << "                  -------x                      " << "**/" << endl;
	cout << "/**" << "                          (X Hi,Y Hi)           " << "**/" << endl;
	cout << "/**" << "                                                " << "**/" << endl;
	cout << "/**" << "                        Dr. Luis Alberto Aranda " << "**/" << endl;
	cout << "/**" << "                     2021 - Universidad Nebrija " << "**/" << endl;
	cout << "/**" << "                          ARIES Research Center " << "**/" << endl;
	cout << "/****************************************************/" << endl;
	cout << endl;

	// Read Board Type
	cout << "-> Please select device: ";
	cin >> input_val;
	while (((cin.fail()) || ((input_val != 1)))) {// && (input_val != 2) && (input_val != 3) && (input_val != 4) && (input_val != 5)))) {
		cout << "-> ERROR, please enter a valid number: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input_val;
	}
	coordinates.push_back(input_val);

	// Set Maximum Range Values
	if (coordinates.at(0) == 1) {
		MIN_X = KCU105_MIN_X;
		MAX_X = KCU105_MAX_X;
		MIN_Y = KCU105_MIN_Y;
		MAX_Y = KCU105_MAX_Y;
	}
	/*else if (coordinates.at(0) == 2) {
		MAX_X = ZEDBOARD_MAX_X;
		MAX_Y = ZEDBOARD_MAX_Y;
	}*/

	// Read Input Coordinates
	cout << "-> Please enter design coordinates:" << endl;
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			cout << " X Lo = ";
			break;
		case 1:
			cout << " Y Lo = ";
			break;
		case 2:
			cout << " X Hi = ";
			break;
		default:
			cout << " Y Hi = ";
		}
		// Read Value
		cin >> input_val;

		// Not an Integer Value -> Read Again
		if (cin.fail()) {
			cout << "-> ERROR, please enter a number." << endl;
			error_flag = true;
		}
		// Input Value is a Number
		else {
			// Check if Input Value is Between Range
			if ((input_val >= MIN_X) && (input_val <= MAX_X) && ((i == 0) || (i == 2))) {
				// Check if X Lo < X Hi
				if (i == 0) {
					coordinates.push_back(input_val);
				}
				else if ((i == 2) && (coordinates.at(1) <= input_val)) {
					coordinates.push_back(input_val);
				}
				else {
					cout << "-> ERROR, X Hi cannot be lower than X Lo." << endl;
					error_flag = true;
				}
			}
			else if ((input_val >= MIN_Y) && (input_val <= MAX_Y) && ((i == 1) || (i == 3))) {
				// Check if Y Lo < Y Hi
				if (i == 1) {
					coordinates.push_back(input_val);
				}
				else if ((i == 3) && (coordinates.at(2) <= input_val)) {
					coordinates.push_back(input_val);
				}
				else {
					cout << "-> ERROR, Y Hi cannot be lower than Y Lo." << endl;
					error_flag = true;
				}
			}
			else {
				cout << "-> ERROR, out of range." << endl;
				error_flag = true;
			}
		}

		// Error Message
		if (error_flag) {
			cin.clear();
			cin.ignore(256, '\n');
			error_flag = false;
			i--;
		}
	}
	cout << endl;

	// Print Summary
	cout << " --------- " << endl;
	cout << "  SUMMARY " << endl;
	cout << " --------- " << endl;
	cout << " Device  : ";
	if (coordinates.at(0) == 1) {
		cout << "KCU105" << endl;
	}
	/*else if (coordinates.at(0) == 2) {
		cout << "ZedBoard" << endl;
	}*/
	cout << " Region  : (" << coordinates.at(1) << "," << coordinates.at(2) << "):(" << coordinates.at(3) << "," << coordinates.at(4) << ")" << endl;

	return coordinates;
}
