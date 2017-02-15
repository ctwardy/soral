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
 * delay.cpp
 *
 * Gets:	a string
 * Returns: a char
 * promps user with string, and waits until user press a key
 * The key pressed is then returned
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * AO  | 07/04/00 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <iostream>
#include <string>
//#include <conio.h>
#include "Srchman.h"
using namespace std;
char delaykey(string prompts)
{
	char response='~';
	cout << "\n";
	cout << prompts;
	cout << "\n";
	while (response == '~')
	{
		response=getchar();
		/* Under Windows this take letters till user presses enter,
		   but will only return the first one.
		   The documentation suggests this should only take 1 char
		   hopefully under linux it does this.
		   Either way it will compile and work after a fasion.
		*/
	}
	fflush(stdin);
	return response;
}
