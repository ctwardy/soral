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
 * Output.cpp
 *
 * Functions for printing data.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 06/05/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 24/05/01 |  2  | Updated.  PrintStringVector() added.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 2.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <stdio.h>
#include "Assignmt.h"
#include "global.h"

using namespace std;


/******************************************************************************
 * PrintAssignmentVector()
 *
 * Prints the contents of a vector<Assignment> to standard output.
 * Each Assignment (Area Number and Resource Hours) is printed on
 * a separate line.
 *
 * Author : Gareth Thompson
 */

void PrintAssignmentVector(vector<Assignment>& theVector)
{
	if (testmode) cout << "entering PrintAssignmentVector()\n";


	vector<Assignment>::iterator current;

	for (current = theVector.begin(); current != theVector.end(); current++)
	{
		printf("AREA NUMBER: %4d      ", current->getAreaNum());
		printf("RESOURCE HOURS: %9.2f\n", current->getResourceHours());
	}
}


/******************************************************************************
 * PrintIntVector()
 *
 * Prints a list of the values in a vector<int> to standard output,
 * with pairs of integers separated by '*'.
 * ('*' will also be printed after the last integer.)
 *
 * Author : Gareth Thompson
 */

void PrintIntVector(vector<int>& theVector)
{
	if (testmode) cout << "entering PrintIntVector()\n";

	vector<int>::iterator current;

	for (current = theVector.begin(); current != theVector.end(); current++)
	{
		cout << *current << "*";
	}
}

/******************************************************************************
 * PrintDoubleVector()
 *
 * Prints a list of the values in a vector<double> to standard output,
 * with pairs separated by '*'.
 * ('*' will also be printed after the last double.)
 *
 * Author : Andre Oboler
 * Addapted from Gareth's PrintIntVector()
 */

void PrintDoubleVector(vector<double>& theVector)
{
	if (testmode) cout << "entering PrintIntVector()\n";

	vector<double>::iterator current;

	for (current = theVector.begin(); current != theVector.end(); current++)
	{
		cout << *current << "*";
	}
}


/******************************************************************************
 * PrintStringVector()
 *
 * Prints a list of the values in a vector<string> to standard output,
 * with pairs of strings separated by '*'.
 * ('*' will also be printed after the last string.)
 *
 * Author : Gareth Thompson
 */

void PrintStringVector(vector<string>& theVector)
{

	if (testmode) cout << "entering PrintStringVector()\n";

	vector<string>::iterator current;

	for (current = theVector.begin(); current != theVector.end(); current++)
	{
		cout << *current << "*";
	}
}

