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
 * ChkType.cpp
 *
 * Functions for checking if data stored in string variables is of
 * a specific type.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 06/05/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 25/05/01 |  2  | Updated.  Now tests if values are in required range
 *     |          |     | for ints / doubles.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 2.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include <string>
#include <climits>
#include <cfloat>
#include <cerrno>
#include "global.h"

using namespace std;


/******************************************************************************
 * IsInt()
 *
 * Takes a string as argument and returns true if that string
 * represents a valid integer.
 *
 * A valid integer is one that is between the minimum and
 * maximum allowed values for a variable of type int and which
 * matches the regular expression:
 * ('+'|'-')?[0-9]+
 * (A possible sign, followed by one or more digits)
 * (Note that the string may not contain whitespace)
 *
 * Author : Gareth Thompson
 */

bool IsInt(string str)
{
	if (testmode) cout << "entering IsInt(" << str << ")\n";

	/*
	 * Check if string is between minimum and maximum
	 * allowed values for an int.
	 *

	/*
	 * Make errno not equal to ERANGE so that we can test if atoi sets
	 * it to ERANGE
	 */
	errno = !ERANGE;

	if (testmode) cout << "BEFORE Range checking --> ERRNO: " << errno << "\tE" << "RANGE: " << ERANGE << endl;

	atoi(str.c_str());

	if (testmode) cout << "AFTER Range checking --> ERRNO: " << errno << "\tE" << "RANGE: " << ERANGE << endl;

	/*
	 * If atoi sets errno = ERANGE, then the size of the integer value
	 * of the string is too large to store in an int variable).
	 */
	if (errno == ERANGE)
	{
		if (testmode) cout << str << " cannot be represented as an integer variable.\n";
		return false;
	}

	/* Lexical analysis performed using Finite Automaton */
	enum State {S1, S2, S3};

	enum State currentState = S1;
	int pos = 0;

	while (pos < str.size())
	{
		if (currentState == S1)
		{
			switch (str[pos])
			{
				case '+':
				case '-':
				{
					currentState = S2;
					break;
				}

				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					currentState = S3;
					break;
				}

				default:
				{
					return false;
				}
			}
		}
		else if (currentState == S2)
		{
			switch (str[pos])
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					currentState = S3;
					break;
				}

				default:
				{
					return false;
				}
			}
		}
		else if (currentState == S3)
		{
			switch (str[pos])
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					currentState = S3;
					break;
				}

				default:
				{
					return false;
				}
			}
		}

		pos++;
	}

	return (currentState == S3);
}




/******************************************************************************
 * IsFloat()
 *
 * Takes a string as argument and returns true if that string
 * represents a valid floating point number.
 *
 * A valid floating point number is one that is no longer than
 * FLOATMAXCHARS in length and which matches the regular expression:
 * ('+'|'-')?(([0-9]+.[0-9]*)|(.[0-9]+))
 * (A possible sign, followed by a string of one or more digits,
 *  possibly containing a single decimal point)
 * (Note that the string may not contain whitespace)
 *
 * Author : Gareth Thompson
 */

bool IsFloat(string str)
{
	if (testmode) cout << "entering IsFloat(" << str << ")\n";

	/* Check if string is more than FLOATMAXCHARS characters long. */
	if (str.size() > FLOATMAXCHARS)
	{
		if (testmode) cout << str << " is too long to represent as a floating point value.\n";
		return false;
	}

	/* Lexical analysis performed using Finite Automaton */
	enum State {S1, S2, S3, S4, S5};

	enum State currentState = S1;
	int pos = 0;

	while (pos < str.size())
	{
		if (currentState == S1)
		{
			switch (str[pos])
			{
				case '+':
				case '-':
				{
					currentState = S2;
					break;
				}

				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					currentState = S4;
					break;
				}

				case '.':
				{
					currentState = S3;
					break;
				}

				default:
				{
					return false;
				}
			}
		}
		else if (currentState == S2)
		{
			switch (str[pos])
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					currentState = S4;
					break;
				}

				case '.':
				{
					currentState = S3;
					break;
				}

				default:
				{
					return false;
				}
			}
		}
		else if (currentState == S3)
		{
			switch (str[pos])
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					currentState = S5;
					break;
				}

				default:
				{
					return false;
				}
			}
		}
		else if (currentState == S4)
		{
			switch (str[pos])
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					currentState = S4;
					break;
				}

				case '.':
				{
					currentState = S5;
					break;
				}

				default:
				{
					return false;
				}
			}
		}
		else if (currentState == S5)
		{
			switch (str[pos])
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					currentState = S5;
					break;
				}

				default:
				{
					return false;
				}
			}
		}

		pos++;
	}

	return (currentState == S4 || currentState == S5);
}
