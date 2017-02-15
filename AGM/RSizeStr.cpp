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
 * RSizeStr.cpp
 *
 * Utilities for resizing a string to a required length.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 20/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *---------------------------------------------------------------------------- */
#include <string>
#include "global.h"
using namespace std;

/******************************************************************************
 * TruncateString()
 *
 * Takes a string str and an integer max as argument, and returns a
 * string based on str that has length no greater than max.
 *
 * If max > 3, TrunacateString behaves as follows:
 * - If str has length equal to or less than max, str is returned.
 * - If str has length greater than max, the string returned has
 *   the first (max-3) characters of str, followed by an ellipsis "..."
 *
 * If max <= 3, the string cannot be correctly truncated,
 * so an empty string "" is returned.
 *
 * Author : Gareth Thompson
 */
string TruncateString(string str, int max)
{
	if (testmode) cout << "entering TruncateString(" << str << ", " << max << ")\n";
	if (max < 4)
	{
		return "";
	}
	else
	{
		if (str.size() <= max)
		{
			/* str does not need to be truncated */
			return str;
		}
		else
		{
			/* str does need to be truncated */
			/*
			 * keep first (max-3) characters of str, erase
			 * remainder and add ellipsis ("...").
			 */
			str.erase(max-3, str.size()-max+3);
			str += "...";
			return str;
		}
	}
}

/******************************************************************************
 * ExpandString()
 *
 * Takes a string str and an integer min as argument, and returns a
 * string based on str that has length no less than min.
 *
 * If str has length greater than or equal to min, str is returned.
 * If str has length less than min, the string returned has str
 * padded with enough trailing spaces to bring its length to min.
 *
 * Author : Gareth Thompson
 */
string ExpandString(string str, int min)
{
	if (testmode) cout << "entering ExpandString(" << str << ", " << min << ")\n";
	int spaces = min - str.size();
	if (testmode) cout << "spaces = " << spaces << "\n";
	while (spaces > 0)
	{
		str += ' ';
		spaces--;
		if (testmode) cout << "spaces = " << spaces << "\n";
	}
	return str;
}

/******************************************************************************
 * ResizeString()
 *
 * Takes a string str and integers min and max as argument, and returns a
 * string based on str that has length between min and max.
 *
 * If min > max, no such string exists and a blank string "" is returned.
 * If max <= 3, str cannot be effectively truncated at the
 * maximum length, and a blank string is returned.
 *
 * If min <= max, and max > 3, then:
 * - If str has length less than min, it is padded with trailing spaces
 *   to bring its length up to min.
 * - If str has length greater than max, it is truncated at a
 *   length of max. (The string returned has the first (max-3)
 *   characters of str, followed by an ellipsis "...")
 *
 * Author : Gareth Thompson
 */
string ResizeString(string str, int min, int max)
{
	if (testmode) cout << "entering ResizeString(" << str << ", " << min << ", " << max << ")\n";
	if (min > max || max <= 3)
	{
		return "";
	}
	/* Resize string to required length */
	str = TruncateString(str, max);
	str = ExpandString(str, min);
	return str;
}
