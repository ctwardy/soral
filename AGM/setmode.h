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
 * setmode.h
 *
 * Interprets the input from the user and decides which mode to run in
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 09/04/01 |  1  | Created.
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 2x/01/03 |  2  | Added BATCH_AUTOFILE and BATCH_AUTO_SORAL
 * crt | 24/01/03 |     | for testing it with the SORAL library.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 2.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include <iostream>
#include "Err_mngr.h"

using namespace std;

class SearchManager;

typedef enum			// program modes
{
	INTERACTIVE,
	BATCH_ADVICE,
	BATCH_RUN,
	BATCH_AUTO,
	BATCH_AUTOFILE,
	BATCH_AUTO_SORAL,
	ERROR
} Program_mode;

typedef enum			// data file tag types
{
	AREA,
	RESOURCE,
	ASSIGN
} Tag;

class SetupMode : public ErrorManager
{
	public:

		SetupMode(void) {}
		~SetupMode(void) {}

		Program_mode SetMode(int argc, char *argv[], SearchManager* sm);
		Program_mode FindMode(int argc, char *argv[]);
		Program_mode FindSubmode(int argc, char *argv[]);

		string	GetTag(Tag tag, int argc, char *argv[]);

		void HandleError(int local_error_id) { cout << "ERROR thrown back" << endl; }
};
