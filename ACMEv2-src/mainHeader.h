//---------------------------------------------------------------------------------------
// mainHeader.h : Header with preprocessor instructions and function prototypes
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
#pragma once
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <strsafe.h>
#include <vector>
#include <Windows.h>

//---------------------------------------------------------------------------------------
// NAMESPACES
//---------------------------------------------------------------------------------------
using namespace std;

//---------------------------------------------------------------------------------------
// DEFINES
//---------------------------------------------------------------------------------------
#define BITS_IN_LINE 32				// Number of Bits in an EBD Line
#define WF_ULTRASCALE 123			// Words per Frame (UltraScale Family)
#define WF_7SERIES 101				// Words per Frame (7-Series Family)
#define DUMMY_ULTRASCALE 141		// UltraScale EBD Header + Dummy Lines (8 + 123 + 10)
#define DUMMY_7SERIES 109			// 7-Series EBD Header + Dummy Lines (8 + 101)

#define KCU105_MIN_X 50				// KCU105 Minimum X Coordinate
#define KCU105_MAX_X 357			// KCU105 Maximum X Coordinate
#define KCU105_MIN_Y 0				// KCU105 Minimum Y Coordinate
#define KCU105_MAX_Y 309			// KCU105 Maximum Y Coordinate
#define KCU105_Y4 61				// KCU105 Maximum Row of Clock Region Y4
#define KCU105_Y3 123				// KCU105 Maximum Row of Clock Region Y3
#define KCU105_Y2 185				// KCU105 Maximum Row of Clock Region Y2
#define KCU105_Y1 247				// KCU105 Maximum Row of Clock Region Y1
#define KCU105_FX 22				// KCU105 Frames per X Coordinate (Tile Column)
#define KCU105_FY 5236				// KCU105 Frames per Horizontal Clock Regions

//---------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//---------------------------------------------------------------------------------------
void adjustCoordinates(vector<int>&);
string bin2hex(bitset<BITS_IN_LINE> b, int w);
string dec2bin(unsigned long);
vector<int> KCU105(vector<int>, vector<int>&, int&);
string ebdName();
int ebdTranslate(string, vector<int>, vector<int>, vector<int>, int);
vector<int> welcome();
