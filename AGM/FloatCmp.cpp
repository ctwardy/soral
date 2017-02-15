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
 * FloatCmp.cpp
 *
 * Utilities for comparing floating point numbers to a given
 * precision.  (PRECISION is defined in global.h).
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 24/04/01 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include "global.h"
#include <stdio.h>
#include <cmath>
using namespace std;

/******************************************************************************
 * FloatEqual()
 *
 * Determines if two floating point numbers are equal.  Floating
 * point numbers are defined to be equal if they differ by less
 * than PRECISION.
 *
 * Author : Gareth Thompson
 */
bool FloatEqual(double num1, double num2)
{
	if (testmode) cout << "entering FloatEqual(" << num1 << ", " << num2 << ")\n";
	double diff = fabs(num1 - num2);
	if (testmode)
	{
		cout << "Difference between values ";
		printf("%f, %f gives %f\n", num1, num2 ,diff);
	}
	return (diff < PRECISION);
}

/******************************************************************************
 * FloatLess()
 *
 * Determines if the first floating point argument is less
 * than the second by more than PRECISION (floating point numbers
 * are defined to be equal if they differ by less than PRECISION).
 *
 * Author : Gareth Thompson
 */
bool FloatLess(double num1, double num2)
{
	if (testmode) cout << "entering FloatLess(" << num1 << ", " << num2 << ")\n";
	return ( (num1 < num2) && !FloatEqual(num1, num2) );
}
