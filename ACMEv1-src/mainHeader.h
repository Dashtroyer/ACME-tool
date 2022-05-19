//---------------------------------------------------------------------------------------
// mainHeader.h : Header with preprocessor instructions and function prototypes
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
#define FRAME_SIZE 101				// Frame Size 7-Series Family
#define FRAME_SIZE_ULTRASCALE 123	// Frame Size UltraScale Family

#define ZB_MAX_X 113				// ZedBoard Maximum X Size
#define ZB_MAX_Y 149				// ZedBoard Maximum Y Size
#define ZB_Y1 49					// ZedBoard Maximum Size of Clock Region 5-6
#define ZB_Y2 99					// ZedBoard Maximum Size of Clock Region 3-4
#define ZB_SLOPE 2500				// ZedBoard Clock Region Slope
#define ZB_ORD_34 235000			// ZedBoard Clock Region 3-4 Intercept
#define ZB_ORD_56 517500			// ZedBoard Clock Region 5-6 Intercept

#define B3_MAX_X 65					// Basys3 Maximum X Size
#define B3_MAX_Y 149				// Basys3 Maximum Y Size
#define B3_Y1 49					// Basys3 Maximum Size of Clock Region 5-6
#define B3_Y2 99					// Basys3 Maximum Size of Clock Region 3-4
#define B3_SLOPE 2500				// Basys3 Clock Region Slope
#define B3_ORD_12 141500			// Basys3 Clock Region 1-2 Intercept
#define B3_ORD_56 293500			// Basys3 Clock Region 5-6 Intercept

#define N4_MAX_X 89					// Nexys4 Maximum X Size
#define N4_MAX_Y 199				// Nexys4 Maximum Y Size
#define N4_Y1 49					// Nexys4 Maximum Size of Clock Region 7-8
#define N4_Y2 99					// Nexys4 Maximum Size of Clock Region 5-6
#define N4_Y3 149					// Nexys4 Maximum Size of Clock Region 3-4
#define N4_SLOPE 2200				// Nexys4 Clock Region Slope
#define N4_ORD_12 206200			// Nexys4 Clock Region 1-2 Intercept
#define N4_ORD_56 390000			// Nexys4 Clock Region 5-6 Intercept
#define N4_ORD_78 591200			// Nexys4 Clock Region 7-8 Intercept

#define ZC706_MAX_X 171				// ZC706 Maximum X Size
#define ZC706_MAX_Y 349				// ZC706 Maximum Y Size
#define ZC706_Y1 49					// ZC706 Maximum Size of Clock Region 13-14
#define ZC706_Y2 99					// ZC706 Maximum Size of Clock Region 11-12
#define ZC706_Y3 149				// ZC706 Maximum Size of Clock Region 9-10
#define ZC706_Y4 199				// ZC706 Maximum Size of Clock Region 7-8
#define ZC706_Y5 249				// ZC706 Maximum Size of Clock Region 5-6
#define ZC706_Y6 299				// ZC706 Maximum Size of Clock Region 3-4
#define ZC706_SLOPE 2000			// ZC706 Clock Region Slope
#define ZC706_ORD_34 400000			// ZC706 Clock Region 3-4 Intercept
#define ZC706_ORD_56 800000			// ZC706 Clock Region 5-6 Intercept
#define ZC706_ORD_78 1183000		// ZC706 Clock Region 7-8 Intercept
#define ZC706_ORD_910 1533000		// ZC706 Clock Region 9-10 Intercept
#define ZC706_ORD_1112 1883000		// ZC706 Clock Region 11-12 Intercept
#define ZC706_ORD_1314 2233000		// ZC706 Clock Region 13-14 Intercept

#define KCU105_MAX_X 100			// KCU105 Maximum X Size
#define KCU105_MAX_Y 299			// KCU105 Maximum Y Size
#define KCU105_Y1 59				// KCU105 Maximum Size of Clock Region 17-20
#define KCU105_Y2 119				// KCU105 Maximum Size of Clock Region 13-16
#define KCU105_Y3 179				// KCU105 Maximum Size of Clock Region 9-12
#define KCU105_Y4 239				// KCU105 Maximum Size of Clock Region 5-8
#define KCU105_SLOPE 6615			// KCU105 Clock Region Slope
#define KCU105_ORD_1316 630000		// KCU105 Clock Region 13-16 Intercept
#define KCU105_ORD_912 1280000		// KCU105 Clock Region 9-12 Intercept
#define KCU105_ORD_58 1918000		// KCU105 Clock Region 5-8 Intercept
#define KCU105_ORD_14 2566000		// KCU105 Clock Region 1-4 Intercept

//---------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//---------------------------------------------------------------------------------------
string bin2hex(bitset<BITS_IN_LINE> b, int w);
string dec2bin(unsigned long);
vector<string> ebdNames();
int injectionRange(vector<bitset<BITS_IN_LINE>>, vector<int>, vector<int>, int&);
vector<int> pBlockRange(vector<int>, int&);
vector<int> welcome();
