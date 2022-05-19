//---------------------------------------------------------------------------------------
// pBlockRange.cpp : Calculate the EBD file range using pBlock coordinates
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
vector<int> pBlockRange(vector<int> coordinates, int &pairMax)
{
	// Variables Definition
	vector<int> fileRange;					// Vector with EBD File pBlock Ranges

											// Obtain Board Type
	if (coordinates.at(0) == 1) {
		//----------
		// ZedBoard
		//----------
		// Y1 and Y2 € Reg1-2
		if ((coordinates.at(2) >= (ZB_Y2 + 1)) && (coordinates.at(4) <= ZB_MAX_Y)) {
			fileRange.push_back(ZB_SLOPE * coordinates.at(1));					// X1
			fileRange.push_back(ZB_SLOPE * coordinates.at(3));					// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg3-4
		else if ((coordinates.at(2) >= (ZB_Y1 + 1)) && (coordinates.at(4) <= ZB_Y2)) {
			fileRange.push_back(ZB_SLOPE * coordinates.at(1) + ZB_ORD_34);		// X1
			fileRange.push_back(ZB_SLOPE * coordinates.at(3) + ZB_ORD_34);		// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg5-6
		else if (coordinates.at(4) <= ZB_Y1) {
			fileRange.push_back(ZB_SLOPE * coordinates.at(1) + ZB_ORD_56);		// X1
			fileRange.push_back(ZB_SLOPE * coordinates.at(3) + ZB_ORD_56);		// X2
			pairMax = 1;
		}
		// Y1 € Reg3-4 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= (ZB_Y1 + 1)) && (coordinates.at(2) <= ZB_Y2)) && ((coordinates.at(4) >= (ZB_Y2 + 1)) && (coordinates.at(4) <= ZB_MAX_Y))) {
			fileRange.push_back(ZB_SLOPE * coordinates.at(1));					// X1 (Reg1-2)
			fileRange.push_back(ZB_SLOPE * coordinates.at(3));					// X2 (Reg1-2)
			fileRange.push_back(ZB_SLOPE * coordinates.at(1) + ZB_ORD_34);		// X1 (Reg3-4)
			fileRange.push_back(ZB_SLOPE * coordinates.at(3) + ZB_ORD_34);		// X2 (Reg3-4)
			pairMax = 2;
		}
		// Y1 € Reg5-6 and Y2 € Reg3-4
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZB_Y1)) && ((coordinates.at(4) >= (ZB_Y1 + 1)) && (coordinates.at(4) <= ZB_Y2))) {
			fileRange.push_back(ZB_SLOPE * coordinates.at(1) + ZB_ORD_34);		// X1 (Reg3-4)
			fileRange.push_back(ZB_SLOPE * coordinates.at(3) + ZB_ORD_34);		// X2 (Reg3-4)
			fileRange.push_back(ZB_SLOPE * coordinates.at(1) + ZB_ORD_56);		// X1 (Reg5-6)
			fileRange.push_back(ZB_SLOPE * coordinates.at(3) + ZB_ORD_56);		// X2 (Reg5-6)
			pairMax = 2;
		}
		// Y1 € Reg5-6 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZB_Y1)) && ((coordinates.at(4) >= (ZB_Y2 + 1)) && (coordinates.at(4) <= ZB_MAX_Y))) {
			fileRange.push_back(ZB_SLOPE * coordinates.at(1));					// X1 (Reg1-2)
			fileRange.push_back(ZB_SLOPE * coordinates.at(3));					// X2 (Reg1-2)
			fileRange.push_back(ZB_SLOPE * coordinates.at(1) + ZB_ORD_34);		// X1 (Reg3-4)
			fileRange.push_back(ZB_SLOPE * coordinates.at(3) + ZB_ORD_34);		// X2 (Reg3-4)
			fileRange.push_back(ZB_SLOPE * coordinates.at(1) + ZB_ORD_56);		// X1 (Reg5-6)
			fileRange.push_back(ZB_SLOPE * coordinates.at(3) + ZB_ORD_56);		// X2 (Reg5-6)
			pairMax = 3;
		}
		// Erroneus Data
		else {
			cout << "pBlock Range Error!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else if (coordinates.at(0) == 2) {
		//----------
		// Basys3
		//----------
		// Y1 and Y2 € Reg1-2
		if ((coordinates.at(2) >= (B3_Y2 + 1)) && (coordinates.at(4) <= B3_MAX_Y)) {
			fileRange.push_back(B3_SLOPE * coordinates.at(1) + B3_ORD_12);		// X1
			fileRange.push_back(B3_SLOPE * coordinates.at(3) + B3_ORD_12);		// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg3-4
		else if ((coordinates.at(2) >= (B3_Y1 + 1)) && (coordinates.at(4) <= B3_Y2)) {
			fileRange.push_back(B3_SLOPE * coordinates.at(1));					// X1
			fileRange.push_back(B3_SLOPE * coordinates.at(3));					// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg5-6
		else if (coordinates.at(4) <= B3_Y1) {
			fileRange.push_back(B3_SLOPE * coordinates.at(1) + B3_ORD_56);		// X1
			fileRange.push_back(B3_SLOPE * coordinates.at(3) + B3_ORD_56);		// X2
			pairMax = 1;
		}
		// Y1 € Reg3-4 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= (B3_Y1 + 1)) && (coordinates.at(2) <= B3_Y2)) && ((coordinates.at(4) >= (B3_Y2 + 1)) && (coordinates.at(4) <= B3_MAX_Y))) {
			fileRange.push_back(B3_SLOPE * coordinates.at(1));					// X1 (Reg3-4)
			fileRange.push_back(B3_SLOPE * coordinates.at(3));					// X2 (Reg3-4)
			fileRange.push_back(B3_SLOPE * coordinates.at(1) + B3_ORD_12);		// X1 (Reg1-2)
			fileRange.push_back(B3_SLOPE * coordinates.at(3) + B3_ORD_12);		// X2 (Reg1-2)
			pairMax = 2;
		}
		// Y1 € Reg5-6 and Y2 € Reg3-4
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= B3_Y1)) && ((coordinates.at(4) >= (B3_Y1 + 1)) && (coordinates.at(4) <= B3_Y2))) {
			fileRange.push_back(B3_SLOPE * coordinates.at(1));					// X1 (Reg3-4)
			fileRange.push_back(B3_SLOPE * coordinates.at(3));					// X2 (Reg3-4)
			fileRange.push_back(B3_SLOPE * coordinates.at(1) + B3_ORD_56);		// X1 (Reg5-6)
			fileRange.push_back(B3_SLOPE * coordinates.at(3) + B3_ORD_56);		// X2 (Reg5-6)
			pairMax = 2;
		}
		// Y1 € Reg5-6 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= B3_Y1)) && ((coordinates.at(4) >= (B3_Y1 + 1)) && (coordinates.at(4) <= B3_MAX_Y))) {
			fileRange.push_back(B3_SLOPE * coordinates.at(1));					// X1 (Reg3-4)
			fileRange.push_back(B3_SLOPE * coordinates.at(3));					// X2 (Reg3-4)
			fileRange.push_back(B3_SLOPE * coordinates.at(1) + B3_ORD_12);		// X1 (Reg1-2)
			fileRange.push_back(B3_SLOPE * coordinates.at(3) + B3_ORD_12);		// X2 (Reg1-2)
			fileRange.push_back(B3_SLOPE * coordinates.at(1) + B3_ORD_56);		// X1 (Reg5-6)
			fileRange.push_back(B3_SLOPE * coordinates.at(3) + B3_ORD_56);		// X2 (Reg5-6)
			pairMax = 3;
		}
		// Erroneus Data
		else {
			cout << "pBlock Range Error!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else if (coordinates.at(0) == 3) {
		//----------
		// Nexys4
		//----------
		// Y1 and Y2 € Reg1-2
		if ((coordinates.at(2) >= (N4_Y3 + 1)) && (coordinates.at(4) <= N4_MAX_Y)) {
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_12);		// X1
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_12);		// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg3-4
		else if ((coordinates.at(2) >= (N4_Y2 + 1)) && (coordinates.at(4) <= N4_Y3)) {
			fileRange.push_back(N4_SLOPE * coordinates.at(1));					// X1
			fileRange.push_back(N4_SLOPE * coordinates.at(3));					// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg5-6
		else if ((coordinates.at(2) >= (N4_Y1 + 1)) && (coordinates.at(4) <= N4_Y2)) {
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_56);		// X1
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_56);		// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg7-8
		else if (coordinates.at(4) <= N4_Y1) {
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_78);		// X1
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_78);		// X2
			pairMax = 1;
		}
		// Y1 € Reg3-4 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= (N4_Y2 + 1)) && (coordinates.at(2) <= N4_Y3)) && ((coordinates.at(4) >= (N4_Y3 + 1)) && (coordinates.at(4) <= N4_MAX_Y))) {
			fileRange.push_back(N4_SLOPE * coordinates.at(1));					// X1 (Reg3-4)
			fileRange.push_back(N4_SLOPE * coordinates.at(3));					// X2 (Reg3-4)
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_12);		// X1 (Reg1-2)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_12);		// X2 (Reg1-2)
			pairMax = 2;
		}
		// Y1 € Reg5-6 and Y2 € Reg3-4
		else if (((coordinates.at(2) >= (N4_Y1 + 1)) && (coordinates.at(2) <= N4_Y2)) && ((coordinates.at(4) >= (N4_Y2 + 1)) && (coordinates.at(4) <= N4_Y3))) {
			fileRange.push_back(N4_SLOPE * coordinates.at(1));					// X1 (Reg3-4)
			fileRange.push_back(N4_SLOPE * coordinates.at(3));					// X2 (Reg3-4)
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_56);		// X1 (Reg5-6)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_56);		// X2 (Reg5-6)
			pairMax = 2;
		}
		// Y1 € Reg7-8 and Y2 € Reg5-6
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= N4_Y1)) && ((coordinates.at(4) >= (N4_Y1 + 1)) && (coordinates.at(4) <= N4_Y2))) {
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_56);		// X1 (Reg5-6)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_56);		// X2 (Reg5-6)
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_78);		// X1 (Reg7-8)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_78);		// X2 (Reg7-8)
			pairMax = 2;
		}
		// Y1 € Reg5-6 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= (N4_Y1 + 1)) && (coordinates.at(2) <= N4_Y2)) && ((coordinates.at(4) >= (N4_Y3 + 1)) && (coordinates.at(4) <= N4_MAX_Y))) {
			fileRange.push_back(N4_SLOPE * coordinates.at(1));					// X1 (Reg3-4)
			fileRange.push_back(N4_SLOPE * coordinates.at(3));					// X2 (Reg3-4)
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_12);		// X1 (Reg1-2)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_12);		// X2 (Reg1-2)
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_56);		// X1 (Reg5-6)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_56);		// X2 (Reg5-6)
			pairMax = 3;
		}
		// Y1 € Reg7-8 and Y2 € Reg3-4
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= N4_Y1)) && ((coordinates.at(4) >= (N4_Y2 + 1)) && (coordinates.at(4) <= N4_Y3))) {
			fileRange.push_back(N4_SLOPE * coordinates.at(1));					// X1 (Reg3-4)
			fileRange.push_back(N4_SLOPE * coordinates.at(3));					// X2 (Reg3-4)
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_56);		// X1 (Reg5-6)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_56);		// X2 (Reg5-6)
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_78);		// X1 (Reg7-8)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_78);		// X2 (Reg7-8)
			pairMax = 3;
		}
		// Y1 € Reg7-8 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= N4_Y1)) && ((coordinates.at(4) >= (N4_Y3 + 1)) && (coordinates.at(4) <= N4_MAX_Y))) {
			fileRange.push_back(N4_SLOPE * coordinates.at(1));					// X1 (Reg3-4)
			fileRange.push_back(N4_SLOPE * coordinates.at(3));					// X2 (Reg3-4)
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_12);		// X1 (Reg1-2)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_12);		// X2 (Reg1-2)
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_56);		// X1 (Reg5-6)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_56);		// X2 (Reg5-6)
			fileRange.push_back(N4_SLOPE * coordinates.at(1) + N4_ORD_78);		// X1 (Reg7-8)
			fileRange.push_back(N4_SLOPE * coordinates.at(3) + N4_ORD_78);		// X2 (Reg7-8)
			pairMax = 4;
		}
		else {
			cout << "pBlock Range Error!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else if (coordinates.at(0) == 4) {
		// Y1 and Y2 € Reg1-2
		if ((coordinates.at(2) >= (ZC706_Y6 + 1)) && (coordinates.at(4) <= ZC706_MAX_Y)) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1));					// X1
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3));					// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg3-4
		else if ((coordinates.at(2) >= (ZC706_Y5 + 1)) && (coordinates.at(4) <= ZC706_Y6)) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg5-6
		else if ((coordinates.at(2) >= (ZC706_Y4 + 1)) && (coordinates.at(4) <= ZC706_Y5)) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg7-8
		else if ((coordinates.at(2) >= (ZC706_Y3 + 1)) && (coordinates.at(4) <= ZC706_Y4)) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg9-10
		else if ((coordinates.at(2) >= (ZC706_Y2 + 1)) && (coordinates.at(4) <= ZC706_Y3)) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg11-12
		else if ((coordinates.at(2) >= (ZC706_Y1 + 1)) && (coordinates.at(4) <= ZC706_Y2)) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg13-14
		else if ((coordinates.at(2) >= 0) && (coordinates.at(4) <= ZC706_Y1)) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1314);	// X1
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1314);	// X2
			pairMax = 1;
		}
		// Y1 € Reg13-14 and Y2 € Reg11-12
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZC706_Y1)) && ((coordinates.at(4) >= (ZC706_Y1 + 1)) && (coordinates.at(4) <= ZC706_Y2))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1314);	// X1 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1314);	// X2 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			pairMax = 2;
		}
		// Y1 € Reg11-12 and Y2 € Reg9-10
		else if (((coordinates.at(2) >= (ZC706_Y1 + 1)) && (coordinates.at(2) <= ZC706_Y2)) && ((coordinates.at(4) >= (ZC706_Y2 + 1)) && (coordinates.at(4) <= ZC706_Y3))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			pairMax = 2;
		}
		// Y1 € Reg9-10 and Y2 € Reg7-8
		else if (((coordinates.at(2) >= (ZC706_Y2 + 1)) && (coordinates.at(2) <= ZC706_Y3)) && ((coordinates.at(4) >= (ZC706_Y3 + 1)) && (coordinates.at(4) <= ZC706_Y4))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			pairMax = 2;
		}
		// Y1 € Reg7-8 and Y2 € Reg5-6
		else if (((coordinates.at(2) >= (ZC706_Y3 + 1)) && (coordinates.at(2) <= ZC706_Y4)) && ((coordinates.at(4) >= (ZC706_Y4 + 1)) && (coordinates.at(4) <= ZC706_Y5))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			pairMax = 2;
		}
		// Y1 € Reg5-6 and Y2 € Reg3-4
		else if (((coordinates.at(2) >= (ZC706_Y4 + 1)) && (coordinates.at(2) <= ZC706_Y5)) && ((coordinates.at(4) >= (ZC706_Y5 + 1)) && (coordinates.at(4) <= ZC706_Y6))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			pairMax = 2;
		}
		// Y1 € Reg3-4 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= (ZC706_Y5 + 1)) && (coordinates.at(2) <= ZC706_Y6)) && ((coordinates.at(4) >= (ZC706_Y6 + 1)) && (coordinates.at(4) <= ZC706_MAX_Y))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1));					// X1 (Reg1-2)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3));					// X2 (Reg1-2)
			pairMax = 2;
		}
		// Y1 € Reg13-14 and Y2 € Reg9-10
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZC706_Y1)) && ((coordinates.at(4) >= (ZC706_Y2 + 1)) && (coordinates.at(4) <= ZC706_Y3))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1314);	// X1 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1314);	// X2 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			pairMax = 3;
		}
		// Y1 € Reg11-12 and Y2 € Reg7-8
		else if (((coordinates.at(2) >= (ZC706_Y1 + 1)) && (coordinates.at(2) <= ZC706_Y2)) && ((coordinates.at(4) >= (ZC706_Y3 + 1)) && (coordinates.at(4) <= ZC706_Y4))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			pairMax = 3;
		}
		// Y1 € Reg9-10 and Y2 € Reg5-6
		else if (((coordinates.at(2) >= (ZC706_Y2 + 1)) && (coordinates.at(2) <= ZC706_Y3)) && ((coordinates.at(4) >= (ZC706_Y4 + 1)) && (coordinates.at(4) <= ZC706_Y5))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			pairMax = 3;
		}
		// Y1 € Reg7-8 and Y2 € Reg3-4
		else if (((coordinates.at(2) >= (ZC706_Y3 + 1)) && (coordinates.at(2) <= ZC706_Y4)) && ((coordinates.at(4) >= (ZC706_Y5 + 1)) && (coordinates.at(4) <= ZC706_Y6))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			pairMax = 3;
		}
		// Y1 € Reg5-6 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= (ZC706_Y4 + 1)) && (coordinates.at(2) <= ZC706_Y5)) && ((coordinates.at(4) >= (ZC706_Y6 + 1)) && (coordinates.at(4) <= ZC706_MAX_Y))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1));					// X1 (Reg1-2)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3));					// X2 (Reg1-2)
			pairMax = 3;
		}
		// Y1 € Reg13-14 and Y2 € Reg7-8
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZC706_Y1)) && ((coordinates.at(4) >= (ZC706_Y3 + 1)) && (coordinates.at(4) <= ZC706_Y4))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1314);	// X1 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1314);	// X2 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			pairMax = 4;
		}
		// Y1 € Reg11-12 and Y2 € Reg5-6
		else if (((coordinates.at(2) >= (ZC706_Y1 + 1)) && (coordinates.at(2) <= ZC706_Y2)) && ((coordinates.at(4) >= (ZC706_Y4 + 1)) && (coordinates.at(4) <= ZC706_Y5))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			pairMax = 4;
		}
		// Y1 € Reg9-10 and Y2 € Reg3-4
		else if (((coordinates.at(2) >= (ZC706_Y2 + 1)) && (coordinates.at(2) <= ZC706_Y3)) && ((coordinates.at(4) >= (ZC706_Y5 + 1)) && (coordinates.at(4) <= ZC706_Y6))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			pairMax = 4;
		}
		// Y1 € Reg7-8 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= (ZC706_Y3 + 1)) && (coordinates.at(2) <= ZC706_Y4)) && ((coordinates.at(4) >= (ZC706_Y6 + 1)) && (coordinates.at(4) <= ZC706_MAX_Y))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1));					// X1 (Reg1-2)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3));					// X2 (Reg1-2)
			pairMax = 4;
		}
		// Y1 € Reg13-14 and Y2 € Reg5-6
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZC706_Y1)) && ((coordinates.at(4) >= (ZC706_Y4 + 1)) && (coordinates.at(4) <= ZC706_Y5))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1314);	// X1 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1314);	// X2 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			pairMax = 5;
		}
		// Y1 € Reg11-12 and Y2 € Reg3-4
		else if (((coordinates.at(2) >= (ZC706_Y1 + 1)) && (coordinates.at(2) <= ZC706_Y2)) && ((coordinates.at(4) >= (ZC706_Y5 + 1)) && (coordinates.at(4) <= ZC706_Y6))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			pairMax = 5;
		}
		// Y1 € Reg9-10 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= (ZC706_Y2 + 1)) && (coordinates.at(2) <= ZC706_Y3)) && ((coordinates.at(4) >= (ZC706_Y6 + 1)) && (coordinates.at(4) <= ZC706_MAX_Y))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1));					// X1 (Reg1-2)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3));					// X2 (Reg1-2)
			pairMax = 5;
		}
		// Y1 € Reg13-14 and Y2 € Reg3-4
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZC706_Y1)) && ((coordinates.at(4) >= (ZC706_Y5 + 1)) && (coordinates.at(4) <= ZC706_Y6))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1314);	// X1 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1314);	// X2 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			pairMax = 6;
		}
		// Y1 € Reg11-12 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= (ZC706_Y1 + 1)) && (coordinates.at(2) <= ZC706_Y2)) && ((coordinates.at(4) >= (ZC706_Y6 + 1)) && (coordinates.at(4) <= ZC706_MAX_Y))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1));					// X1 (Reg1-2)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3));					// X2 (Reg1-2)
			pairMax = 6;
		}
		// Y1 € Reg13-14 and Y2 € Reg1-2
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZC706_Y1)) && ((coordinates.at(4) >= (ZC706_Y6 + 1)) && (coordinates.at(4) <= ZC706_MAX_Y))) {
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1314);	// X1 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1314);	// X2 (Reg13-14)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_1112);	// X1 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_1112);	// X2 (Reg11-12)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_910);	// X1 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_910);	// X2 (Reg9-10)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_78);	// X1 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_78);	// X2 (Reg7-8)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_56);	// X1 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_56);	// X2 (Reg5-6)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1) + ZC706_ORD_34);	// X1 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3) + ZC706_ORD_34);	// X2 (Reg3-4)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(1));					// X1 (Reg1-2)
			fileRange.push_back(ZC706_SLOPE * coordinates.at(3));					// X2 (Reg1-2)
			pairMax = 7;
		}
		// Erroneus Data
		else {
			cout << "pBlock Range Error!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else if (coordinates.at(0) == 5) {
		//----------
		// KCU105
		//----------
		// Y1 and Y2 € Reg1-4
		if ((coordinates.at(2) >= (KCU105_Y4 + 1)) && (coordinates.at(4) <= KCU105_MAX_Y)) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_14);		// X1
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_14);		// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg5-8
		else if ((coordinates.at(2) >= (KCU105_Y3 + 1)) && (coordinates.at(4) <= KCU105_Y4)) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_58);		// X1
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_58);		// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg9-12
		else if ((coordinates.at(2) >= (KCU105_Y2 + 1)) && (coordinates.at(4) <= KCU105_Y3)) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_912);		// X1
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_912);		// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg13-16
		else if ((coordinates.at(2) >= (KCU105_Y1 + 1)) && (coordinates.at(4) <= KCU105_Y2)) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_1316);	// X1
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_1316);	// X2
			pairMax = 1;
		}
		// Y1 and Y2 € Reg17-20
		else if ((coordinates.at(2) >= 0) && (coordinates.at(4) <= KCU105_Y1)) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1));						// X1
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3));						// X2
			pairMax = 1;
		}
		// Y1 € Reg5-8 and Y2 € Reg1-4
		else if (((coordinates.at(2) >= (KCU105_Y3 + 1)) && (coordinates.at(2) <= KCU105_Y4)) && ((coordinates.at(4) >= (KCU105_Y4 + 1)) && (coordinates.at(4) <= KCU105_MAX_Y))) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_58);		// X1 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_58);		// X2 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_14);		// X1 (Reg1-4)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_14);		// X2 (Reg1-4)
			pairMax = 2;
		}
		// Y1 € Reg9-12 and Y2 € Reg5-8
		else if (((coordinates.at(2) >= (KCU105_Y2 + 1)) && (coordinates.at(2) <= KCU105_Y3)) && ((coordinates.at(4) >= (KCU105_Y3 + 1)) && (coordinates.at(4) <= KCU105_Y4))) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_912);		// X1 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_912);		// X2 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_58);		// X1 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_58);		// X2 (Reg5-8)
			pairMax = 2;
		}
		// Y1 € Reg13-16 and Y2 € Reg9-12
		else if (((coordinates.at(2) >= (KCU105_Y1 + 1)) && (coordinates.at(2) <= KCU105_Y2)) && ((coordinates.at(4) >= (KCU105_Y2 + 1)) && (coordinates.at(4) <= KCU105_Y3))) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_1316);	// X1 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_1316);	// X2 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_912);		// X1 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_912);		// X2 (Reg9-12)
			pairMax = 2;
		}
		// Y1 € Reg17-20 and Y2 € Reg13-16
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= KCU105_Y1)) && ((coordinates.at(4) >= (KCU105_Y1 + 1)) && (coordinates.at(4) <= KCU105_Y2))) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1));						// X1 (Reg17-20)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3));						// X2 (Reg17-20)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_1316);	// X1 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_1316);	// X2 (Reg13-16)
			pairMax = 2;
		}
		// Y1 € Reg9-12 and Y2 € Reg1-4
		else if (((coordinates.at(2) >= (KCU105_Y2 + 1)) && (coordinates.at(2) <= KCU105_Y3)) && ((coordinates.at(4) >= (KCU105_Y4 + 1)) && (coordinates.at(4) <= KCU105_MAX_Y))) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_14);		// X1 (Reg1-4)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_14);		// X2 (Reg1-4)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_58);		// X1 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_58);		// X2 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_912);		// X1 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_912);		// X2 (Reg9-12)
			pairMax = 3;
		}
		// Y1 € Reg13-16 and Y2 € Reg5-8
		else if (((coordinates.at(2) >= (KCU105_Y1 + 1)) && (coordinates.at(2) <= KCU105_Y2)) && ((coordinates.at(4) >= (KCU105_Y3 + 1)) && (coordinates.at(4) <= KCU105_Y4))) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_58);		// X1 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_58);		// X2 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_912);		// X1 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_912);		// X2 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_1316);	// X1 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_1316);	// X2 (Reg13-16)
			pairMax = 3;
		}
		// Y1 € Reg17-20 and Y2 € Reg9-12
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= KCU105_Y1)) && ((coordinates.at(4) >= (KCU105_Y2 + 1)) && (coordinates.at(4) <= KCU105_Y3))) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_912);		// X1 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_912);		// X2 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_1316);	// X1 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_1316);	// X2 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1));						// X1 (Reg17-20)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3));						// X2 (Reg17-20)
			pairMax = 3;
		}
		// Y1 € Reg13-16 and Y2 € Reg1-4
		else if (((coordinates.at(2) >= (KCU105_Y1 + 1)) && (coordinates.at(2) <= KCU105_Y2)) && ((coordinates.at(4) >= (KCU105_Y4 + 1)) && (coordinates.at(4) <= KCU105_MAX_Y))) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_14);		// X1 (Reg1-4)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_14);		// X2 (Reg1-4)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_58);		// X1 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_58);		// X2 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_912);		// X1 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_912);		// X2 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_1316);	// X1 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_1316);	// X2 (Reg13-16)
			pairMax = 4;
		}
		// Y1 € Reg17-20 and Y2 € Reg5-8
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= KCU105_Y1)) && ((coordinates.at(4) >= (KCU105_Y3 + 1)) && (coordinates.at(4) <= KCU105_Y4))) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_58);		// X1 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_58);		// X2 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_912);		// X1 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_912);		// X2 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_1316);	// X1 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_1316);	// X2 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1));						// X1 (Reg17-20)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3));						// X2 (Reg17-20)
			pairMax = 4;
		}
		// Y1 € Reg17-20 and Y2 € Reg1-4
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= KCU105_Y1)) && ((coordinates.at(4) >= (KCU105_Y4 + 1)) && (coordinates.at(4) <= KCU105_MAX_Y))) {
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_14);		// X1 (Reg1-4)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_14);		// X2 (Reg1-4)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_58);		// X1 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_58);		// X2 (Reg5-8)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_912);		// X1 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_912);		// X2 (Reg9-12)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1) + KCU105_ORD_1316);	// X1 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3) + KCU105_ORD_1316);	// X2 (Reg13-16)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(1));						// X1 (Reg17-20)
			fileRange.push_back(KCU105_SLOPE * coordinates.at(3));						// X2 (Reg17-20)
			pairMax = 5;
		}
		// Erroneus Data
		else {
			cout << "pBlock Range Error!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else {
		cout << "Incorrect board" << endl;
	}

	return fileRange;
}
