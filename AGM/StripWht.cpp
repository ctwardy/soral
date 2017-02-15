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
 * StripWht.cpp
 *
 * Utilities for removing whitespace from the beginning and end of strings.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 17/04/01 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <vector>
#include <string>
#include "global.h"
using namespace std;

/******************************************************************************
 * StripWhite(string)
 *
 * Takes a string, and returns a version of that string that has all
 * leading an trailing whitespace removed.
 * The string returned may still contain whitespace between non-whitespace
 * characters.
 * If the string passes as argument contains no non-whitespace
 * characters, the string returned will have length 0.
 *
 * Author : Gareth Thompson
 */
string StripWhite(string str)
{
	if (testmode) cout << "entering StripWhite(" << str << ")\n";
	/* Find first non-whitespace character */
	int firstChar = 0;
	while (firstChar < str.length() && isspace(str[firstChar]))
	{
		firstChar++;
	}
	/* Find last non-whitespace character */
	int lastChar = str.length() - 1;
	while (lastChar >= firstChar && isspace(str[lastChar]))
	{
		lastChar--;
	}
	return str.substr(firstChar, lastChar-firstChar+1);
}

/******************************************************************************
 * StripWhite(vector<string>)
 *
 * Takes a vector of strings, and returns a version of
 * that vector where each string has all leading and
 * trailing whitespace removed.
 * The output for special cases of input strings is
 * described under StripWhite(string) above.
 *
 * Author : Gareth Thompson
 */
vector<string> StripWhite(vector<string> data)
{
	if (testmode) cout << "entering StripWhite(vector<str>)\n";
	/* Strip whitespace from each string in vector in turn */
	vector<string>::iterator i;
	for (i=data.begin(); i < data.end(); i++)
	{
		*i = StripWhite(*i);
	}
	return data;
}
