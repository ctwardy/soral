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
 * Sandr.cpp
 *
 * Holds the main function for the s&r research project
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 02/04/00 |  1  | Created.
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 2x/01/03 |  2  | Added BATCH_AUTOFILE case
 *-----+----------+-----+-----------------------------------------------------
 * crt | 24/01/03 |  3  | Added BATCH_AUTO_SORAL case. Remove later or merge.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 3.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <iostream>
#include <string>
#include "Srchman.h"
#include "Err_mngr.h"
#include "setmode.h"
#include "global.h"

#ifdef WIN32
#include <conio.h>
#endif
#include <time.h>
using namespace std;
bool testmode = false;
/* Function maintained by: Michael Eldridge */
int main(int argc, char* argv[])
{
	SetupMode setup;
	SearchManager* search_manager = new SearchManager();
	switch (setup.SetMode(argc, argv, search_manager))
	{
		case INTERACTIVE:
			{
				if (testmode) cout << "Starting the menu manager" << endl;
				search_manager->CopyrightMini();
				search_manager->MenuManager();
			}
			break;
		case BATCH_ADVICE:
			{
				// take in areas and resources
				search_manager->CalcOptimalAssignment();
				search_manager->UpdateAllPOAs();
				cout << "<ASSIGN>" << endl;
				search_manager->ViewAllAssignments();
				cout << "</ASSIGN>" << endl;
				cout << "<POA>" << endl;
				search_manager->OutputAllPOAs();
				cout << "</POA>" << endl;
			}
			break;
		case BATCH_RUN:
			{
				// take in areas and resources and assignments
				search_manager->UpdateAllPOAs();
				cout << "<ASSIGN>" << endl;
				search_manager->ViewAllAssignments();
				cout << "</ASSIGN>" << endl;
				cout << "<POA>" << endl;
				search_manager->OutputAllPOAs();
				cout << "</POA>" << endl;
			}
			break;
		case BATCH_AUTO:
			{
				// take in areas and resources
				search_manager->CalcOptimalAssignment();
				search_manager->UpdateAllPOAs();
				cout << "<ASSIGN>" << endl;
				search_manager->ViewAllAssignments();
				cout << "</ASSIGN>" << endl;
				cout << "<POA>" << endl;
				search_manager->OutputAllPOAs();
				cout << "</POA>" << endl;
			}
			break;
		case BATCH_AUTOFILE:
			{
				// All done in "set mode", nothing to do here.
			}
			break;
	   case BATCH_AUTO_SORAL:
		  {
			 // The work is already done. Print to stdout
				cout << "<ASSIGN>" << endl;
				search_manager->ViewAllAssignments();
				cout << "</ASSIGN>" << endl;
				cout << "<POA>" << endl;
				search_manager->OutputAllPOAs();
				cout << "</POA>" << endl;
		  }
	   case ERROR:
		  {
				cerr << "ERROR" << endl;
		  }
	}
#ifdef WIN32
	getch();
#endif
	return 0;
}
