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
 * ConToStr.cpp
 *
 * Specialisations of ConvertToStr() functionf for converting
 * certain type of variables to strings.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 27/05/01 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include <string>
#include <sstream>
#include <cstdio>
#include "global.h"

using namespace std;

/******************************************************************************
 * ConvertToStr<double>()
 *
 * Takes a double and returns the representation of it,
 * using the %.2f conversion of sprintf, as a string.
 *
 * Author : Gareth Thompson
 */

string ConvertToStr(double d)
{
	if (testmode) cout << "entering ConvertToStr(" << d << ")\n";

	char temp[100];   //Enough characters to hold any double


	sprintf(temp, "%.2f", d);
	string str = temp;
	return str;
}

/******************************************************************************
 * ConvertToStr<int>()
 *
 * Takes a double and returns the representation of it,
 * using the %.2f conversion of sprintf, as a string.
 *
 * Author : Gareth Thompson
 */

/*string ConvertToStr(int d)
{
	if (testmode) cout << "entering ConvertToStr(" << d << ")\n";

	char temp[100];   //Enough characters to hold any int

	sprintf(temp, "%.2f", d);
	string str = temp;
	return str;
}*/

