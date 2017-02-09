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
 * error_man.cpp
 *
 * Handles simple error logging and feadback
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 21/04/00 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include "Err_mngr.h"
#include "global.h"
#include <fstream>
#include <stdio.h>
#include <time.h>

using namespace std;

/******************************************************************************
 * ErrorManager()
 *
 * Michael Eldridge
 *
 * Defualt constructor that stamps the file with a time stamp.
 */

ErrorManager::ErrorManager(void)
{
	FILE *output;

	output = fopen("error.log", "a+");

	struct tm *newtime;
	time_t long_time;
	time( &long_time );
	newtime = localtime( &long_time );

	fprintf(output, "\n\n**********************************************************************\n");
	fprintf(output, "%s" , asctime(newtime));
	fprintf(output, "**********************************************************************");

	fclose(output);
}

/******************************************************************************
 * PostError()
 *
 * Handles any simple errors that are posted by the system
 *
 * Author : Michael Eldridge
 *
 * Parameters : level of the error and a text string to explain the error
 */

bool ErrorManager::PostError(Error_level level, string text_msg, string error_pos)
{
	FILE *output;

	output = fopen("error.log", "a+");

	fprintf(output, "\n\nUser msg \n%s", text_msg.c_str());
	fprintf(output, "\nComment msg \n%s", error_pos.c_str());

	fclose(output);

	// handle the error

	switch(level)
	{
		case WARNING:
			{
				cerr << endl << "WARNING : " << text_msg << endl;
				return false;
			}
			break;

		case WARNING_OPTION:
			{
				cerr << endl << "WARNING : " << text_msg << endl;
				string s = "Do you wish to continue?";
				if (GetResponce(s))
				{
					return true;
				}
				else
				{
					cerr << "Program Halting..." << endl;
					exit(1);
				}
			}
			break;

		case HALT:
			{
				cerr << endl << "ERROR : " << text_msg << endl;
				cerr << "Program Halting..." << endl;
				exit(1);
			}
			break;

		case COMMAND_LINE_ERROR:
			{
				cerr << endl << "ERROR : " << text_msg << endl;
				cerr << endl << "Program Usage" << endl;
				cerr <<	"=============" << endl;
				cerr << "Program Mode" << endl << "------------" << endl;
				cerr << "Interactive Mode < no tag > - Allows the user to interact with the search data" << endl;
				cerr << "Batch Mode       <--batch > - Takes in data files and produces a best" << endl;
				cerr << "                             search allocation table" << endl;
				cerr << endl << "Batch Mode Options" << endl << "------------------" << endl;
				cerr << "Advice	<--advice> - Takes data files for areas and resources, " << endl;
				cerr << "                    prints suggested assignments" << endl;
				cerr << "Auto	< --auto > - Takes data files for areas & resources, makes assignments." << endl;
				cerr << "                    Updates POAs. Displays assignments and new POAs." << endl;
				cerr << "File <--autofile> - Reads files for areas, resources and writes file for" << endl;
				cerr << "                    allocations (uses SORAL) and updated areas (new POAs)." << endl;
				cerr << "Run	< --run  > - Takes data files for areas, resources and allocations " << endl;
				cerr << "                     and returns the assignments and new POA's" << endl;
				cerr << endl << "File Name Tags" << endl << "--------------" << endl;
				cerr << "-A  - name of file with the map area details" << endl;
				cerr << "-R  - name of file containing list of Search and Rescue units available" << endl;
				cerr << "-S  - name of file with a list of Search and Rescue unit allocations" << endl;
				cerr << "Example: AGMSAR --batch --auto -Aarea.dat -Rresource.dat" << endl;
				exit(1);
			}
			break;

		default:
				return false;
			break;
	}
	return false;
}
