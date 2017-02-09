/*****************************************************************************
 * -- AGM SAR --
 * --------------------------------------------------------------------
 * Copyright (C) 2001-2008 AGM, a team comprising Andre Oboler, Gareth
 * Thompson and Michael Eldridge.
 * --------------------------------------------------------------------
 * This file is part of AGM SAR.
 *
 * AGM SAR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation. However, this
 * notice must be retained.
 *
 * AGM SAR uses the SORAL library, available separately under the GNU
 * General Public License, and distributed here in compliance with
 * that license.
 *
 * AGM SAR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Use is at your
 * own risk. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AGM SAR (see license.txt). If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * We are willing to offer alternative licensing arrangements if
 * necessary.  Our contact details are in readme.txt.
 * --------------------------------------------------------------------
 * --------------------------------------------------------------------
 * global.h
 *
 * Global functions, variables and definitions used by the
 * Search and Rescue program.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 17/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 21/04/01 |  2  | Updated.  Additional global functions added.
 *     |          |     | Global bool 'testmode' added.
 *----------------------------------------------------------------------------
 * GT  | 27/04/01 |  3  | Updated.  More global functions added. PRECISION
 *     |          |     | now defined here.
 *----------------------------------------------------------------------------
 * GT  | 07/05/01 |  4  | Updated.  More global functions added.
 *----------------------------------------------------------------------------
 * GT  | 25/05/01 |  5  | Updated.  More global functions added.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 5.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#ifndef _global_h_
#define _global_h_

/* Precision for floating-point number comparisons in program */
#define PRECISION 0.0001

/* Limits for floating point input to program */
#define FLOATMAXCHARS 15 // maximum number of characters that may be used to represent a float at input
#define FLOATMAXVAL 999999999999999.0	// maximum possible value for float at input (can be represented with 15 characters)
#define FLOATMINVAL -99999999999999.0	// minimum possible value for float at input (can be represented with 15 characters)

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <sstream> // ASO 12/1/03 Updated for G++ 3.1.1 compatability was #include <strstream>

using namespace std;

class Assignment;
class SearchManager;



extern bool testmode; /* Is program running in verbose test mode? */

string GetInputString(istream& in);
bool GetInputInteger(istream& in, int& i);
int GetValidInputInteger(string prompt, string errorMsg, int min = INT_MIN, int max = INT_MAX);
bool GetInputFloat(istream& in, double& d);
double GetValidInputFloat(string prompt, string errorMsg, double min = FLOATMINVAL, double max = FLOATMAXVAL);
vector<string> Tokenise(string str, char c);

string StripWhite(string str);
vector<string> StripWhite(vector<string> data);

string TruncateString(string str, int max);
string ExpandString(string str, int min);
string ResizeString(string str, int min, int max);

bool FloatEqual(double num1, double num2);
bool FloatLess(double num1, double num2);

void CalcOptimalAssignment(SearchManager* searchMan);
vector<int> DescendingPdenList(SearchManager* searchMan);
void Swap(vector<int>::iterator a, vector<int>::iterator b);
double AreaEffectivelySweptRemaining(SearchManager* searchMan);
bool AssignSRUs(SearchManager* searchMan, int areaNum, double coverage);

void UpdateAllPOAs(SearchManager* searchMan);

char delaykey(string prompts);

void PrintAssignmentVector(vector<Assignment>& theVector);
void PrintIntVector(vector<int>& theVector);
void PrintDoubleVector(vector<double>& theVector);
void PrintStringVector(vector<string>& theVector);

bool IsInt(string str);
bool IsFloat(string str);

bool GetResponce(string input);

/* Specialisation for converting doubles to strings */
string ConvertToStr(double d);

/******************************************************************************
 * ConvertToStr()
 *
 * Takes a variable of class T and returns the representation of
 * T produced using the output operator, <<, as a string.
 *
 * PRECONDITION: Output operator must be defined for class T.
 *
 * Author : Gareth Thompson
 */

template <class T> string ConvertToStr(T t)
{
	if (testmode) cout << "entering ConvertToStr(" << t << ")\n";

	std::ostringstream ostr;// ASO 12/1/03 Updated for G++ 3.1.1 compatability was: ostrstream ostr;
	ostr << t << '\0';

	string str = ostr.str();
	return str;
}

#endif
