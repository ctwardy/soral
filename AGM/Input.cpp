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
 * Input.cpp
 *
 * Utilities for obtaining input from input streams in
 * a reliable manner.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 08/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 20/04/01 |  2  | Updated.  Declaration moved to global.h. Now uses
 *     |          |     | StripWhite().
 *----------------------------------------------------------------------------
 * GT  | 09/05/01 |  3  | Updated.  GetInputInteger and GetInputFloat
 *     |          |     | added.
 *----------------------------------------------------------------------------
 * GT  | 25/05/01 |  4  | Updated.  GetValidInputInteger and
 *     |          |     | GetValidInputFloat added.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 4.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <climits>
#include <cerrno>
#include "global.h"

using namespace std;


/******************************************************************************
 * GetInputString()
 *
 * Reads characters from the specified input stream up to the
 * first newline that occurs after a non-whitespace character.
 * All leading and trailing whitespace is removed and the result
 * returned as a string object.
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



/******************************************************************************
 * GetInputInteger()
 *
 * Obtains an integer from an input stream.
 *
 * Reads characters from the specified input stream up to the
 * first newline that occurs after a non-whitespace character.
 * All leading and trailing whitespace is removed.
 * If the resulting input is a valid integer (it must have the
 * form of an integer and must be between the minimum and maximum
 * allowed values for an integer), i is set to the value of the
 * integer and true is returned.  Otherwise, i is unchanged and
 * false is returned.
 *
 * This function enables integer input without causing errors
 * if the input string is not an integer.
 *
 * Author : Gareth Thompson
 */

bool GetInputInteger(istream& in, int& i)
{
	if (testmode) cout << "entering GetInputInteger()\n";

	string str = GetInputString(in);

	if (IsInt(str))
	{
		i = atoi(str.c_str());
		return true;
	}
	else
	{
		return false;
	}
}


/******************************************************************************
 * GetValidInputInteger()
 *
 * Obtains a valid integer from standard input.
 *
 * The string prompt is displayed, and the user prompted to enter data.
 * If the data is a valid integer between min and max (inclusive),
 * the integer entered is returned.  The default values of min and max
 * are INT_MIN and INT_MAX respectively, so that any value that can be
 * stored in an int is accepted.
 * If the input is invalid, the string errorMsg is printed, then the string
 * prompt is printed and the user is again prompted to enter data.  This
 * process continues until the user enters valid data.
 *
 * This function enables integer input without causing errors
 * if the input string is not an integer.
 *
 * PRECONDITION: max >= min
 * (If max < min, user can never enter a valid value and becomes stuck in
 * an infinite loop.)
 *
 * Author : Gareth Thompson
 */

int GetValidInputInteger(string prompt, string errorMsg, int min, int max)
{
	if (testmode) cout << "entering GetValidInputInteger()\n";

	int i;
	bool success;

	do
	{
		cout << prompt;
		success = GetInputInteger(cin, i);

		if (!success || i < min || i > max)
		{
			cout << errorMsg << "\n";
		}

	} while (!success || i < min || i > max);

	return i;
}






/******************************************************************************
 * GetInputFloat()
 *
 * Obtains a floating-point number from an input stream.
 *
 * Reads characters from the specified input stream up to the
 * first newline that occurs after a non-whitespace character.
 * All leading and trailing whitespace is removed.
 * If the resulting input is a valid floating-point number, d
 * is set to that floating-point number and true is returned.
 * Otherwise, d is unchanged and false is returned.
 *
 * This function enables floating-point number input without
 * causing errors if the input string is not a floating-point
 * number.
 *
 * Author : Gareth Thompson
 */

bool GetInputFloat(istream& in, double& d)
{
	if (testmode) cout << "entering GetInputFloat()\n";

	string str = GetInputString(in);

	if (IsFloat(str))
	{
		d = atof(str.c_str());
		return true;
	}
	else
	{
		return false;
	}
}




/******************************************************************************
 * GetValidInputFloat()
 *
 * Obtains a valid integer from standard input.
 *
 * The string prompt is displayed, and the user prompted to enter data.
 * If the data is a valid floating point number between min and max
 * (inclusive), the float entered is returned.  The default values of min
 * and max are FLOATMINVAL and FLOATMAXVAL respectively.  These allow all
 * valid floating-point numbers to be input.  (If a floating point number
 * that is input as a string is not between these values, it must have
 * more than FLOATMAXCHARS characters and is therefore not a valid floating
 * point number.)
 * If the input is invalid, the string errorMsg is printed, then the string
 * prompt is printed and the user is again prompted to enter data.  This
 * process continues until the user enters valid data.
 *
 * This function enables floating point number input without causing errors
 * if the input string is not a floating point number.
 *
 * PRECONDITION: max >= min
 * (If max < min, user can never enter a valid value and becomes stuck in
 * an infinite loop.)
 *
 * Author : Gareth Thompson
 */

double GetValidInputFloat(string prompt, string errorMsg, double min, double max)
{
	if (testmode) cout << "entering GetValidInputFloat()\n";

	double d;
	bool success;

	do
	{
		cout << prompt;
		success = GetInputFloat(cin, d);

		if (!success || d < min || d > max)
		{
			cout << errorMsg << "\n";
		}

	} while (!success || d < min || d > max);

	return d;
}

/******************************************************************************
 * GetResponce()
 *
 * Michael Eldridge
 *
 * Gets a yes or no responce from standard input.
 */

bool GetResponce(string input)
{
	cout << input << " (y/n) : ";
	string s = GetInputString(cin);

	while (1)
	{
		if (s.size() == 1)
		{
			if (s[0] == 'y' || s[0] == 'Y')
			{
				return true;
			}
			else if (s[0] == 'n' || s[0] == 'N')
			{
				return false;
			}
		}
		cout << "That is not a valid option." << endl;
		cout << input << " (y/n) : ";
		s = GetInputString(cin);
	}
	return true;
}
