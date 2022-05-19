//---------------------------------------------------------------------------------------
// welcome.cpp : Print welcome message and instructions and return pBlock coordinates
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
vector<int> welcome()
{
	// Variables Definition
	vector<int> coordinates;					// Output Vector with pBlock Coordinates and Board Type
	int input_val;								// Input Value Read from the User
	bool error_flag = false;					// Non-valid Input Value
	int MAX_X, MAX_Y;							// Maximum Range Values

	cout << "/*****************************************************/" << endl;
	cout << "/**" << "                -  A C M E  -                    " << "**/" << endl;
	cout << "/**" << "                                                 " << "**/" << endl;
	cout << "/**" << " usage : EBD files must be in the .exe directory " << "**/" << endl;
	cout << "/**" << "                                                 " << "**/" << endl;
	cout << "/**" << "   - Board type:                                 " << "**/" << endl;
	cout << "/**" << "      (1) ZedBoard    :   X [0,113] - Y [0,149]  " << "**/" << endl;
	cout << "/**" << "      (2) Basys 3     :   X [0, 65] - Y [0,149]  " << "**/" << endl;
	cout << "/**" << "      (3) Nexys 4 DDR :   X [0, 89] - Y [0,199]  " << "**/" << endl;
	cout << "/**" << "      (4) ZC706       :   X [9,171] - Y [0,349]  " << "**/" << endl;
	cout << "/**" << "      (5) KCU105      :   X [0,100] - Y [0,299]  " << "**/" << endl;
	cout << "/**" << "                                                 " << "**/" << endl;
	cout << "/**" << "   - pBlock coordinates:                         " << "**/" << endl;
	cout << "/**" << "                          (X2,Y2)                " << "**/" << endl;
	cout << "/**" << "                  -------x                       " << "**/" << endl;
	cout << "/**" << "                  |      |                       " << "**/" << endl;
	cout << "/**" << "                  |      |                       " << "**/" << endl;
	cout << "/**" << "                  |      |                       " << "**/" << endl;
	cout << "/**" << "                  |      |                       " << "**/" << endl;
	cout << "/**" << "                  |      |                       " << "**/" << endl;
	cout << "/**" << "                  x-------                       " << "**/" << endl;
	cout << "/**" << "           (X1,Y1)                               " << "**/" << endl;
	cout << "/**" << "                                                 " << "**/" << endl;
	cout << "/**" << "                         Dr. Luis Aranda Barjola " << "**/" << endl;
	cout << "/**" << "                      2020 - Universidad Nebrija " << "**/" << endl;
	cout << "/**" << "                           ARIES Research Center " << "**/" << endl;
	cout << "/*****************************************************/" << endl;
	cout << endl;

	// Read Board Type
	cout << "-> Please enter board type: ";
	cin >> input_val;
	while (((cin.fail()) || ((input_val != 1) && (input_val != 2) && (input_val != 3) && (input_val != 4) && (input_val != 5)))) {
		cout << "-> ERROR, please enter a valid board type: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input_val;
	}
	coordinates.push_back(input_val);

	// Set Maximum Range Values
	if (coordinates.at(0) == 1) {
		MAX_X = ZB_MAX_X;
		MAX_Y = ZB_MAX_Y;
	}
	else if (coordinates.at(0) == 2) {
		MAX_X = B3_MAX_X;
		MAX_Y = B3_MAX_Y;
	}
	else if (coordinates.at(0) == 3) {
		MAX_X = N4_MAX_X;
		MAX_Y = N4_MAX_Y;
	}
	else if (coordinates.at(0) == 4) {
		MAX_X = ZC706_MAX_X;
		MAX_Y = ZC706_MAX_Y;
	}
	else if (coordinates.at(0) == 5) {
		MAX_X = KCU105_MAX_X;
		MAX_Y = KCU105_MAX_Y;
	}

	// Read Input pBlock Coordinates
	cout << "-> Please enter pBlock coordinates:" << endl;
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			cout << " X1 = ";
			break;
		case 1:
			cout << " Y1 = ";
			break;
		case 2:
			cout << " X2 = ";
			break;
		default:
			cout << " Y2 = ";
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
			if ((input_val >= 0) && (input_val <= MAX_X) && ((i == 0) || (i == 2))) {
				// Check if X1 < X2
				if (i == 0) {
					coordinates.push_back(input_val);
				}
				else if ((i == 2) && (coordinates.at(1) < input_val)) {
					coordinates.push_back(input_val);
				}
				else {
					cout << "-> ERROR, X2 must be bigger than X1." << endl;
					error_flag = true;
				}
			}
			else if ((input_val >= 0) && (input_val <= MAX_Y) && ((i == 1) || (i == 3))) {
				// Check if Y1 < Y2
				if (i == 1) {
					coordinates.push_back(input_val);
				}
				else if ((i == 3) && (coordinates.at(2) < input_val)) {
					coordinates.push_back(input_val);
				}
				else {
					cout << "-> ERROR, Y2 must be bigger than Y1." << endl;
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
	cout << " Board type      : ";
	if (coordinates.at(0) == 1) {
		cout << "ZedBoard" << endl;
	}
	else if (coordinates.at(0) == 2) {
		cout << "Basys3" << endl;
	}
	else if (coordinates.at(0) == 3) {
		cout << "Nexys4 DDR" << endl;
	}
	else if (coordinates.at(0) == 4) {
		cout << "ZC706" << endl;
	}
	else if (coordinates.at(0) == 5) {
		cout << "KCU105" << endl;
	}
	cout << " Selected region : SLICE_X" << coordinates.at(1) << "Y" << coordinates.at(2) << ":SLICE_X" << coordinates.at(3) << "Y" << coordinates.at(4) << endl;

	return coordinates;
}
