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
 * error_man.h
 *
 * Handles error managerment
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 09/04/01 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#ifndef _err_mngr_h_
#define _err_mngr_h_
#include <iostream>
#include <string>
using namespace std;
typedef enum			// program modes
{
	WARNING,
	WARNING_OPTION,
	HALT,
	COMMAND_LINE_ERROR
} Error_level;
class ErrorManager
{
	public:
		ErrorManager(void);
		~ErrorManager(void) {}
		bool PostError(Error_level level, string text_msg, string error_pos);
	private:
};
static ErrorManager* error_manager;
#endif
