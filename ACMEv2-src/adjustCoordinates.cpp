//---------------------------------------------------------------------------------------
// adjustCoordinates.cpp : Modify X coordinates by removing BRAM, DSP, etc. columns
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
void adjustCoordinates(vector<int>& coordinates)
{
	// Variables Definition
	

	// Obtain Device Type
	if (coordinates.at(0) == 1) {		// KCU105
		// Check both X Coordinates
		for (int i = 1; i < 4; i = i + 2) {
			// Clock Region X0
			if ((coordinates.at(i) >= 50) && (coordinates.at(i) <= 57)) {/* NOTHING */}
			else if ((coordinates.at(i) >= 58)  && (coordinates.at(i) <= 65))  { coordinates.at(i) = coordinates.at(i) - 1; }
			else if ((coordinates.at(i) >= 66)  && (coordinates.at(i) <= 73))  { coordinates.at(i) = coordinates.at(i) - 2; }
			else if ((coordinates.at(i) >= 74)  && (coordinates.at(i) <= 80))  { coordinates.at(i) = coordinates.at(i) - 3; }
			else if ((coordinates.at(i) >= 81)  && (coordinates.at(i) <= 94))  { coordinates.at(i) = coordinates.at(i) - 4; }
			else if ((coordinates.at(i) >= 95)  && (coordinates.at(i) <= 102)) { coordinates.at(i) = coordinates.at(i) - 5; }
			else if ((coordinates.at(i) >= 103) && (coordinates.at(i) <= 110)) { coordinates.at(i) = coordinates.at(i) - 6; }
			// Clock Region X1
			else if ((coordinates.at(i) >= 111) && (coordinates.at(i) <= 118)) { coordinates.at(i) = coordinates.at(i) - 7; }
			else if ((coordinates.at(i) >= 119) && (coordinates.at(i) <= 126)) { coordinates.at(i) = coordinates.at(i) - 8; }
			else if ((coordinates.at(i) >= 127) && (coordinates.at(i) <= 134)) { coordinates.at(i) = coordinates.at(i) - 9; }
			else if ((coordinates.at(i) >= 135) && (coordinates.at(i) <= 141)) { coordinates.at(i) = coordinates.at(i) - 10; }
			else if ((coordinates.at(i) >= 142) && (coordinates.at(i) <= 155)) { coordinates.at(i) = coordinates.at(i) - 11; }
			else if ((coordinates.at(i) >= 156) && (coordinates.at(i) <= 163)) { coordinates.at(i) = coordinates.at(i) - 12; }
			else if ((coordinates.at(i) >= 164) && (coordinates.at(i) <= 171)) { coordinates.at(i) = coordinates.at(i) - 13; }
			// Clock Region X2
			else if ((coordinates.at(i) >= 172) && (coordinates.at(i) <= 221)) { coordinates.at(i) = coordinates.at(i) - 57; }
			else if ((coordinates.at(i) >= 222) && (coordinates.at(i) <= 234)) { coordinates.at(i) = coordinates.at(i) - 58; }
			else if ((coordinates.at(i) >= 235) && (coordinates.at(i) <= 245)) { coordinates.at(i) = coordinates.at(i) - 59; }
			else if ((coordinates.at(i) >= 246) && (coordinates.at(i) <= 251)) { coordinates.at(i) = coordinates.at(i) - 60; }
			else if ((coordinates.at(i) >= 252) && (coordinates.at(i) <= 258)) { coordinates.at(i) = coordinates.at(i) - 61; }
			else if ((coordinates.at(i) >= 259) && (coordinates.at(i) <= 269)) { coordinates.at(i) = coordinates.at(i) - 62; }
			else if ((coordinates.at(i) >= 270) && (coordinates.at(i) <= 281)) { coordinates.at(i) = coordinates.at(i) - 63; }
			else if ((coordinates.at(i) >= 282) && (coordinates.at(i) <= 286)) { coordinates.at(i) = coordinates.at(i) - 64; }
			else if ((coordinates.at(i) >= 287) && (coordinates.at(i) <= 293)) { coordinates.at(i) = coordinates.at(i) - 65; }
			// Clock Region X3
			else if ((coordinates.at(i) >= 294) && (coordinates.at(i) <= 302)) { coordinates.at(i) = coordinates.at(i) - 66; }
			else if ((coordinates.at(i) >= 303) && (coordinates.at(i) <= 309)) { coordinates.at(i) = coordinates.at(i) - 67; }
			else if ((coordinates.at(i) >= 310) && (coordinates.at(i) <= 317)) { coordinates.at(i) = coordinates.at(i) - 68; }
			else if ((coordinates.at(i) >= 318) && (coordinates.at(i) <= 336)) { coordinates.at(i) = coordinates.at(i) - 69; }
			else if ((coordinates.at(i) >= 337) && (coordinates.at(i) <= 357)) { coordinates.at(i) = coordinates.at(i) - 70; }
			else {
				cout << "-> ERROR, incorrect coordinates" << endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	else {
		cout << "-> ERROR, incorrect device" << endl;
		exit(EXIT_FAILURE);
	}
}
