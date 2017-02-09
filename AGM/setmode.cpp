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
 * setmode.cpp
 *
 * Interprets the input from the user and decides which mode to run in
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 09/04/01 |  1  | Created.
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 2x/01/03 |  2  | Added --autofile
 *-----+----------+-----+-----------------------------------------------------
 * crt | 24/01/03 |  3  | Added --soral so I could test w/o clobbering.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 3.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include "setmode.h"
#include "Srchman.h"
#include "Err_mngr.h"
#include "global.h"
#include <string>
#include <fstream>


using namespace std;

/******************************************************************************
 * FindSubmode()
 *
 * Michael Eldridge
 *
 * Searchs for a sub mode selection when it has been determined that we are
 * running in batch mode
 */

Program_mode SetupMode::FindSubmode(int argc, char *argv[])
{
	string s;
	string advice = "--advice";
	string run = "--run";
	string auto_mode = "--auto";
	string autofile_mode = "--autofile";
	string soral_mode = "--soral";         // use SORAL

	for (int i = 0 ; i < argc ; i++)
	{
		s = argv[i];
		if (s[0] == '-')
		{
			if (s == advice)
			{
				return BATCH_ADVICE;
			}
			if (s == run)
			{
				return BATCH_RUN;
			}
			if (s == auto_mode)
			{
				return BATCH_AUTO;
			}
			if (s == autofile_mode)
			{
				return BATCH_AUTOFILE;
			}
			if (s == soral_mode)
			{
				return BATCH_AUTO_SORAL;
			}
		}
	}
	return ERROR;
}

/******************************************************************************
 * FindMode()
 *
 * Michael Eldridge
 *
 * Determines the mode entered in from the command line
 */

Program_mode SetupMode::FindMode(int argc, char *argv[])
{
	string s;
	string batch = "--batch";

	if (testmode) cout << "FindMode values" << endl;
	for (int i = 0 ; i < argc ; i++)
	{
		s = argv[i];
		if (testmode) cout << s << endl;
		if (s[0] == '-')
		{
			if (s == batch)
			{
				return FindSubmode(argc, argv);
			}
		}
	}
	return INTERACTIVE;
}

/******************************************************************************
 * GetTag()
 *
 * Michael Eldridge
 *
 * Searches for file name tags
 */

string SetupMode::GetTag(Tag tag, int argc, char *argv[])
{
	string s;

	for (int i = 0 ; i < argc ; i++)
	{
		s = argv[i];
		if (s[0] == '-')
		{
			if (tag == AREA && s[1] == 'A')
			{
				if (s == "-A")
				{
					error_manager->PostError(COMMAND_LINE_ERROR, "Incorrect number of type parameters specified", "The program could not determine how to run from the parameters specified");
				}
				string temp(s, 2, string::npos);
				return temp;
			}
			if (tag == RESOURCE && s[1] == 'R')
			{
				if (s == "-R")
				{
					error_manager->PostError(COMMAND_LINE_ERROR, "Incorrect number of type parameters specified", "The program could not determine how to run from the parameters specified");
				}
				string temp(s, 2, string::npos);
				return temp;
			}
			if (tag == ASSIGN && s[1] == 'S')
			{
				if (s == "-S")
				{
					error_manager->PostError(COMMAND_LINE_ERROR, "Incorrect number of type parameters specified", "The program could not determine how to run from the parameters specified");
				}
				string temp(s, 2, string::npos);
				return temp;
			}
		}
	}
	return "ERROR";
}

/******************************************************************************
 * SetMode()
 *
 * Michael Eldridge
 *
 * Sets the actual mode of the program and loads any data files
 */

Program_mode SetupMode::SetMode(int argc, char *argv[], SearchManager* sm)
{
	string area_file, resource_file, assign_file;
	area_file = GetTag(AREA, argc, argv);
	resource_file = GetTag(RESOURCE, argc, argv);
	assign_file = GetTag(ASSIGN, argc, argv);

	switch(FindMode(argc, argv))
	{
		case INTERACTIVE:
			{
				if (testmode) cout << "MODE : INTERACTIVE" << endl;
				if (testmode) cout << "Is there an area file??" << endl;
				if (area_file != "ERROR")
				{
					cout << "area specified" << endl;
					sm->LoadAreas(area_file);
				}
				if (testmode) cout << "Is there a resource file" << endl;
				if (resource_file != "ERROR")
				{
					cout << "resources specified" << endl;
					sm->LoadResources(resource_file);
				}
				if (testmode) cout << "is there an assignment file" << endl;
				if (assign_file != "ERROR")
				{
					cout << "assignments specified" << endl;
					sm->LoadAssignments(assign_file);
				}
				if (testmode) cout << "return INTERACTIVE MODE" << endl;
				return Program_mode(INTERACTIVE);
			}
			break;

		case BATCH_ADVICE:
			{
				if (testmode) cout << "MODE : ADVICE ";
				if (area_file == "ERROR" || resource_file == "ERROR")
				{
					cerr << "Error : One or more files were not specified" << endl;
					return Program_mode(ERROR);
				}
				if (testmode) cout << area_file << " " << resource_file << endl;
				sm->LoadAreas(area_file);
				sm->LoadResources(resource_file);
				return Program_mode(BATCH_ADVICE);
			}
			break;

		case BATCH_AUTO:
			{
				if (testmode) cout << "MODE : AUTO " << endl;
				if (area_file == "ERROR" || resource_file == "ERROR")
				{
					cerr << "Error : One or more files were not specified" << endl;
					return Program_mode(ERROR);
				}
				if (testmode) cout << area_file << " " << resource_file << endl;
				sm->LoadAreas(area_file);
				sm->LoadResources(resource_file);
				return Program_mode(BATCH_AUTO);

			}
			break;

		case BATCH_AUTOFILE:
			{
				if (testmode) cout << "MODE : AUTOFILE " << endl;
				if (area_file == "ERROR" || resource_file == "ERROR" || assign_file == "ERROR")
				{
					cerr << "Error : One or more files were not specified" << endl;
					return Program_mode(ERROR);
				}
				if (testmode) cout << "Area file: " << area_file << "  Resource file: " << resource_file << "  Write assignments to: " << assign_file << endl;

				// Load data
				sm->LoadAreas(area_file);
				sm->LoadResources(resource_file);

				// Now update
				sm->useSORAL(); // get advice
				sm->UpdateAllPOAs(); // use the advice

				// Now record to file

				ofstream ass_file;
				ofstream area_fileStream;

				ass_file.open(assign_file.c_str());
				sm->OutputResourceAssignments(ass_file);
				ass_file.close();

				area_fileStream.open(area_file.c_str());
				sm->OutputAreas(area_fileStream);
				area_fileStream.close();

				return Program_mode(BATCH_AUTOFILE);
			}
			break;


		// crt 24Jan03: copied BATCH_AUTOFILE for soral but
		//              BATCH_AUTO for output because BATCH_AUTOFILE
		//              clobbers the input files.
		//   It would be better to change BATCH_AUTOFILE, but that
        //   would break Andre's GUI so I'll let him do it.

		//	ASO - reviewed 3/2/02. This function is undocumented...
		//  a note needs to be added to error manager to show
		// that it exists and how to use it. ie for printing
		// when the user enters --batch and no other paramaters.
		case BATCH_AUTO_SORAL:
			{
				if (testmode) cout << "MODE : AUTO_SORAL " << endl;
				if (area_file == "ERROR" || resource_file == "ERROR")
				{
					cerr << "Error : One or more files were not specified" << endl;
					return Program_mode(ERROR);
				}
				if (testmode) cout << "Area file: " << area_file << "  Resource file: " << resource_file << "  Write assignments to: " << assign_file << endl;

				// Load data
				sm->LoadAreas(area_file);
				sm->LoadResources(resource_file);

				// Now update
				sm->useSORAL(); // get advice
				sm->UpdateAllPOAs(); // use the advice

				return Program_mode(BATCH_AUTO_SORAL);
			}
			break;


		case BATCH_RUN:
			{
				if (testmode) cout << "MODE : RUN " << endl;
				if (area_file == "ERROR" || resource_file == "ERROR" || assign_file == "ERROR")
				{
					cerr << "Error : One or more files were not specified" << endl;
					return Program_mode(ERROR);
				}
				if (testmode) cout << area_file << " " << resource_file << " " << assign_file << endl;
				sm->LoadAreas(area_file);
				sm->LoadResources(resource_file);
				sm->LoadAssignments(assign_file);
				return Program_mode(BATCH_RUN);
			}
			break;

		case ERROR:
			{
				error_manager->PostError(COMMAND_LINE_ERROR, "Incorrect number of type parameters specified", "The program could not determine how to run from the parameters specified");
			}
			break;
	}
	return Program_mode(ERROR);
}

