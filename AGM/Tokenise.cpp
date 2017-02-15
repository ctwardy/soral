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
 * Tokenise.cpp
 *
 * Utility used for tokenising a string with a specified character.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 17/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <vector>
#include <string>
#include "global.h"
using namespace std;

/******************************************************************************
 * Tokenise()
 *
 * Takes a string str, and a character c, as arguments and tokenises
 * str using c.
 * Returns a vector of strings, where each element of the vector
 * is the section of str between two occurrences of c.  The first
 * element of the vector is the section of str before the first
 * occurrence of c; the last element of the vector is the section
 * of str after the last occurrence of c.  These two elements may
 * be strings of 0 length if c occurs at the beginning or end of str.
 * If str does not contain c, the vector returned will have one element,
 * equal to str.  If str is a string of length 0, the vector returned
 * will have one element of length 0.
 *
 * Author : Gareth Thompson
 */
vector<string> Tokenise(string str, char c)
{
	if (testmode) cout << "entering Tokenise(" << str << ", " << c << ")\n";
	int firstChar = 0;
	int lastChar = 0;
	vector<string> data;
	for (lastChar = 0; lastChar <= str.length(); lastChar++)
	{
		if (str[lastChar] == c || lastChar == str.length())
		{
			/*
			 * Have found a piece of data that
			 * begins at firstChar and ends
			 * at the position before lastChar.
			 */
			data.push_back(str.substr(firstChar, lastChar-firstChar));
			firstChar = lastChar+1;
		}
	}
	return data;
}
