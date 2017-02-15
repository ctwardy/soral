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
 * test_inf.cpp
 *
 * test() function for testing InputFile's private functions
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 07/04/01 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <iostream>
#include <string>
#include "InputFil.h"
#include "global.h"
using namespace std;
/******************************************************************************
 * test()
 *
 * Tests InputFile's private functions
 *
 * Author : Gareth Thompson
 */
void InputFile::test(void)
{
        if (testmode) cout << "entering InputFile::test()\n";
	/* Testing isRecord() */
	string line;
	cout << "Is a string of whitespace recognised as a record?...";
	line = "   		   ";
	if (isRecord(line))
	{
		cout << "Yes.  FAILURE." << endl;
	}
	else
	{
		cout << "No.  SUCCESS." << endl;
	}
	cout << "Is a string beginning with # recognised as a record?...";
	line ="   		# Text";
	if (isRecord(line))
	{
		cout << "Yes.  FAILURE." << endl;
	}
	else
	{
		cout << "No.  SUCCESS." << endl;
	}

	cout << "Is a string beginning with % recognised as a record?...";
	line ="   		% Text";
	if (isRecord(line))
	{
		cout << "Yes.  FAILURE." << endl;
	}
	else
	{
		cout << "No.  SUCCESS." << endl;
	}
	cout << "Is a string beginning with another character recognised as a record?...";
	line ="   		Text";
	if (isRecord(line))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  SUCCESS." << endl;
	}
}
