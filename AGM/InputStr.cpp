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
 * InputStr.cpp
 *
 * Utility for obtaining a string (which may contain whitespace)
 * from standard input.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 08/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 20/04/01 |  2  | Declaration moved to global.h -
 *     |          |     | Changed #include "InputString.h" to
 *     |          |     | #include "global.h".  Now uses StripWhite().
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 2.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include "global.h"

using namespace std;


/******************************************************************************
 * GetInputString()
 *
 * Obtains an input string (which may contain whitespace) from
 * an input stream and returns it as a string object.
 * All leading and trailing whitespace is removed.
 *
 * Author : Gareth Thompson
 */

string GetInputString(istream& in)
{
	if (testmode) cout << "entering GetInputString()\n";

	char inChar = in.get();
	string inStr = "";

	/* Ignore any leading whitespace */
	while (isspace(inChar))
	{
		inChar = in.get();
	}

	/* Read characters up to newline into string */
	while (inChar != '\n')
	{
		inStr += inChar;
		inChar = in.get();
	}

	/* Remove trailing whitespace */
	inStr = StripWhite(inStr);

	return inStr;

}
