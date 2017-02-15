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
 * Search_manager.cpp
 *
 * Creates the interface for access to search and rescue data
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 02/04/00 |  1  | Created.
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 19/01/03 | 1.5 | Added useSORAL to integrate with SORAL.
 *-----+----------+-----+-----------------------------------------------------
 * crt | 29/01/03 | 1.6 | Fixed useSORAL to use ESR properly.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.7 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <iostream>
#include <string>
#include <vector>
#include "Srchman.h"
#include "global.h"
#include "Resource.h"
#include "InputFil.h"
#include "Areas.h"
#include "menu.h"
#include "math.h"
#include "Err_mngr.h"
#include "Assignmt.h"
#include "DataLimt.h"
#include "../SORAL/C++/Allocatn.h"
#include "../SORAL/C++/containr.h"
#include "../SORAL/C++/Alloc-CC.h"

#ifdef WIN32
#include <conio.h>
#endif

using namespace std;

/******************************************************************************
 * SearchManager()
 *
 * Base Constructor
 *
 * Author : Michael Eldridge
 *
 * void
 */

SearchManager::SearchManager(void)
{
	big_area = new BigArea();
	resources = new Resources();
	input_file = new InputFile();
}

/******************************************************************************
 * ~SearchManager()
 *
 * Base destructor
 *
 * Author : Michael Eldridge
 *
 * Parameters : void
 */

SearchManager::~SearchManager(void)
{
	delete big_area;
	delete resources;
	delete input_file;
}

/******************************************************************************
 * LoadAreas()
 *
 * Loads in the data for all search areas from a data file
 *
 * Author : Michael Eldridge
 *
 * Parameters : area_filename is the name of the file to load data from
 */

void SearchManager::LoadAreas(string areas_filename)
{
	big_area->loadAreas(areas_filename);
}

/******************************************************************************
 * LoadResources()
 *
 * Loads in the data for all Search and Rescue units from data file
 *
 * Author : Michael Eldridge
 *
 * Parameters : resources_filename is the name of the file to load data from
 */

void SearchManager::LoadResources(string resources_filename)
{
	resources->loadSRUs(resources_filename);
}

/******************************************************************************
 * PrintMap()
 *
 * Prints out the ascii character map of the current data
 *
 * Author : Michael Eldridge
 *
 * Parameters : void
 */

void SearchManager::PrintMap(void)
{
	big_area->printmap();
}




/******************************************************************************
 * LoadAssignments()
 *
 * Obtains assignments from a datafile and stores them in resources.
 *
 * If a file with the specified filename cannot be opened,
 * a warning is posted.
 *
 * If the file can be opened, each line is read from the
 * file in turn.  If this line is of the correct format,
 * the specified Area and Resource both exist, the number of resource-hours
 * is positive and the Resource has sufficient Resource-hours remaining to
 * accept an assignment with that number of Resource-hours, the assignment
 * is stored.
 *
 * If the specified Resource or Area do not exist, the resource-hours are negative (or 0),
 * or the resource has insufficient Resource-hours remaining to take the assignment,
 * an error is posted and no assignment is added.
 *
 * Returns true if 1 or more assignments stored, false otherwise.
 *
 * Author : Gareth Thompson
 *
 * Parameters : filename is the name of the file containing assignment data
 */

bool SearchManager::LoadAssignments(string filename)
{
	InputFile in;
	string record;

	if (testmode) cout << "Loading assignments from file " << filename << "..." << endl;

	if (!in.open(filename))
	{
		error_manager->PostError(WARNING_OPTION, "File "+filename+" could not be opened.  No assignments loaded.", "SearchManager::LoadAssignments() - file could not be opened.");
		return false;
	}

	bool added = false;  //	no assignments have been added

	while (in.getRecord(record))
	{
		/* Tokenise record read from file at commas */
		vector<string> data = Tokenise(record, ',');

		/* Strip leading and trailing whitespace from each token */
		data = StripWhite(data);

		if (testmode)
		{
			cout << "SPLIT RECORD: ";
			PrintStringVector(data);
		}

		/*
		 * Having extracted the pieces of data from the record, we now create a new
		 * assignment using this data.
		 */
		if (data.size() != 3)
		{
			/* Incorrect number of tokens in this record */
			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - This line does not have 3 pieces of data specified.  Assignment ignored.", "SearchManager::LoadAssignments() - Less or more than 3 comma-separated tokens  on line of file.");
		}
		else
		{
			/* Correct number of tokens in this record */

			/* Check if first piece of data is a valid Resource Number */
			if (!IsInt(data[0]))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Resource Number "+data[0]+" is not a valid integer.  Assignment ignored.", "SearchManager::LoadAssignments() - data[0] does not contain a valid integer.");
				continue;
			}

			int resourceNum = atoi(data[0].c_str());
			if (!resources->isSRU(resourceNum))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" -  There is no SRU with Resource Number "+data[0]+".  Assignment could not be added.", "SearchManager::LoadAssignments() - data[0] does not contain a valid Resource Number.");
				continue;
			}

			/* Check if second piece of data is a valid Area Number */
			if (!IsInt(data[1]))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Area Number "+data[1]+" is not a valid integer.  Assignment ignored.", "SearchManager::LoadAssignments() - data[1] does not contain a valid integer.");
				continue;
			}

			int areaNum = atoi(data[1].c_str());
			if (!big_area->isArea(areaNum))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" -  There is no Area with Area Number "+data[1]+".  Assignment could not be added.", "SearchManager::LoadAssignments() - data[1] does not contain a valid Area Number.");
				continue;
			}

			/* Check if third piece of data is a valid number of Resource Hours */
			if (!IsFloat(data[2]))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Resource Hours "+data[2]+" is not a valid floating-point number.  Assignment ignored.", "SearchManager::LoadAssignments() - data[2] does not contain a valid floating-point number.");
				continue;
			}

			double resourceHours = atof(data[2].c_str());
			if (resourceHours <= 0.0)
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Resource Hours "+data[2]+" is not positive.  Assignment could not be added.", "SearchManager::LoadAssignments() - data[2] contains a value that is negative or 0.");
				continue;
			}

			/* Assignment should now be added */
			if (!resources->addAssignment(resourceNum, Assignment(areaNum, resourceHours)))
			{
				/* Insufficient Resource-hours available to add Assignment */
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - SRU "+data[0]+" does not have sufficient Resource-hours remaining to accept Assignment.  Assignment could not be added.", "SearchManager::LoadAssignments() - resources->addAssignment(resourceNum, Assignment(areaNum, resourceHours)) returned false.");
			}
			else
			{
				added = true;
			}

		}
	}

	in.close();

	return added;
}


/******************************************************************************
 * Menu()
 *
 * Creates and operates the menu system for interactive mode
 *
 * Author : Michael Eldridge
 *
 * Parameters : void
 */

void SearchManager::MenuManager(void)
{
	if (testmode) cout << "Started menus" << endl;

	Menu *menus[MENU_COUNT];

	if (testmode) cout << "Creating each of the menu options" << endl;

	if (testmode) cout << "Main menu" << endl;
	menus[MAIN_MENU] = new MainMenu(10);
	if (testmode) cout << "Area menu" << endl;
	menus[AREA_MENU] = new AreaMenu(8);
	if (testmode) cout << "Resource Menu" << endl;
	menus[RESOURCE_MENU] = new ResourceMenu(9);
	if (testmode) cout << "Assignment menu" << endl;
	menus[ASSIGNMENT_MENU] = new AssignmentMenu(4);
	if (testmode) cout << "Save menu" << endl;
	menus[SAVE_MENU] = new SaveMenu(5);
	if (testmode) cout << "Correction menu" << endl;
	menus[CORRECTION_MENU] = new CorrectionMenu(5);

	current_menu = menus[MAIN_MENU];

	int option;

	while (1)
	{
		if (testmode) cout << "Printing titles" << endl;
		current_menu->PrintTitle();
		if (testmode) cout << "Printing options" << endl;
		current_menu->PrintOptions();
		if (testmode) cout << "Selecting a menu options" << endl;
		option = current_menu->ExecuteOption();


		switch(current_menu->GetMenuType())
		{
			case MAIN_MENU:
			{
				switch (option)
				{
					case 0:		// exit
						{
							copyright();
							delaykey("\n\nPress enter to exit AGM SAR");
							exit(0);

						}
						break;

					case 1:		// Resource Properties
						{
							current_menu = menus[RESOURCE_MENU];
						}
						break;

					case 2:		// Save Current State
						{
							current_menu = menus[SAVE_MENU];
						}
						break;

					case 3:		// Map Area Properties
						{
							current_menu = menus[AREA_MENU];
						}
						break;

					case 4:		// Assignment Properties
						{
							current_menu = menus[ASSIGNMENT_MENU];
						}
						break;

					case 5:		// View Current Resource Assignments
						{
							ViewAllAssignmentsTable();
						}
						break;

					case 6:		// Request Resource Allocation Advice
						{
							BigArea new_big_area;
							new_big_area = *big_area;

							CalcOptimalAssignment();

							resources->outputAllAssignments(cout);

							*big_area = new_big_area;
						}
						break;

					case 7:		// Update POAs using current Resource Allocation
						{
							UpdateAllPOAs();
						}
						break;

					case 8:		// Update POAs using current Resource Allocation
					{
							BigArea new_big_area;
							new_big_area = *big_area;

							useSORAL();

							resources->outputAllAssignments(cout);

							*big_area = new_big_area;
					}
					break;

					case 9:		// display big copyright notice
						{
							copyright();
							delaykey("\n\n Press enter when done reading");
						}
						break;
				}
			}
			break;

			case AREA:
			{
				switch(option)
				{
					case 0:		current_menu = menus[MAIN_MENU];		break;

					case 1:
						{
							big_area->MenuModifyArea();
						}
						break;

					case 2:		big_area->MenuNewArea();				break;

					case 3:
					{
						int area_number;
						bool test = true;
						string s = "Enter the number of the area you wish to delete : ";
						area_number = GetValidInputInteger(s, "Invalid input", DataLimits::areaNum_min, DataLimits::areaNum_max);

						vector<int> SRUs = resources->getResourceNumList();

						if (big_area->isArea(area_number))
						{
							vector<int>::iterator current;

							for (current = SRUs.begin(); current != SRUs.end() ; current++)
							{
								vector<Assignment> ass_list = resources->getAssignments(*current);
								vector<Assignment>::iterator assignment;

								for (assignment = ass_list.begin() ; assignment != ass_list.end() ; assignment++)
								{
									if (assignment->getAreaNum() == area_number)
									{
										test = false;
										break;
									}
								}
							}

							if (test)
							{
								string s = "Are you sure you want to delete Area "+ConvertToStr(area_number)+"?";
								if (GetResponce(s))
								{
									big_area->MenuDeleteArea(area_number);
								}
							}
							else
							{
								string s1 = "You have existing assignments to this area.\nPlease remove these and then delete the area.";
								string s2 = "SearchManager::MenuManager() Deleting an area failed";

								error_manager->PostError(WARNING, s1, s2);
							}
						}
						else
						{
							string s1 = "Area is not a defined area";
							string s2 = "SearchManager::MenuManager() deleting an area";

							error_manager->PostError(WARNING, s1, s2);
						}
					}
					break;
					case 4:		big_area->MenuView();					break;
					case 5:		big_area->ViewAllAreas();				break;
					case 6:		big_area->MenuLoad();					break;

					case 7:
						{
							string s = "Are you sure you wish to delete ALL areas?";

							if (GetResponce(s))
							{
								big_area->deleteAllAreas();
							}
						}
						break;
				}
			}
			break;

			case RESOURCE:
			{
				switch (option)
				{
					case 0:
						{
							current_menu = menus[MAIN_MENU];
						}
						break;

					case 1:
						{
							resources->userEnterSRU();
						}
						break;

					case 2:
						{
							string file;
							cout << endl << "Enter file name : ";
							file = GetInputString(cin);
							LoadResources(file);
						}
						break;

					case 3:
						{
							resources->outputAllSRUs(cout);
							int id;
							string s = "Enter SRU to delete : ";
							id = GetValidInputInteger(s,"Invalid input", DataLimits::resourceNum_min, DataLimits::resourceNum_max);
							if (resources->isSRU(id))
							{
								string s = "Are you sure you wish to remove this resource permenantly?";

								if (GetResponce(s))
								{
									resources->deleteSRU(id);
								}
							}
							else
							{
								string e1 = "That resource number does not exist";
								string e2 = "SearchManager::MenuManager() Resource menu delete resource";
								error_manager->PostError(WARNING, e1, e2);
							}
						}
						break;

					case 4:
						{
							string s = "Are you sure you wish to delete ALL resources permenantly?";

							if (GetResponce(s))
							{
								resources->deleteAllSRUs();
							}
						}
						break;

					case 5:
						{
							resources->outputAllSRUs(cout);
							int id;
							string s = "Enter SRU to modify : ";
							id = GetValidInputInteger(s, "Invalid resource index", DataLimits::resourceNum_min, DataLimits::resourceNum_max);

							s = "Are you sure you wish to modify this resource?";

							if (resources->isSRU(id))
							{
								if (GetResponce(s))
								{
									resources->userModifySRU(id);
								}
							}
							else
							{
								cerr << "There is no SRU with that Resource Number\n";
							}
						}
						break;

					case 6:
						{
							resources->viewAllSRUs();
							int id;
							string s = "Enter SRU to view : ";
							id = GetValidInputInteger(s, "Invalid reosurce index", DataLimits::resourceNum_min, DataLimits::resourceNum_max);

							if (resources->isSRU(id))
							{
								resources->viewSRU(id);
							}
							else
							{
								string s = "SearchManager::MenuManager() an invalid resource index was specified while trying to view an SRU";
								error_manager->PostError(WARNING, "That is not a valid resource index", s);
							}
						}
						break;

					case 7:
						{
							resources->viewAllSRUs();
						}
						break;

					case 8:
						{
							current_menu = menus[CORRECTION_MENU];
						}
						break;
				}
			}
			break;

			case SAVE_MENU:
			{
				switch (option)
				{
					case 0:		// go to the main menu
						{
							current_menu = menus[MAIN_MENU];
						}
						break;

					case 1:		// Save current assignment details
						{
							ofstream ass_file;
							cout << "Please enter a file name to save the assignments as : ";
							string name = GetInputString(cin);

							ass_file.open(name.c_str());
							resources->outputAllAssignments(ass_file);
							ass_file.close();
						}
						break;

					case 2:		// Save current area details
						{
							ofstream area_file;
							cout << "Please enter a file name to save the assignments as : ";
							string name = GetInputString(cin);

							area_file.open(name.c_str());
							big_area->OutputAllAreas(area_file);
							area_file.close();
						}
						break;

					case 3:		// Save current resource details
						{
							ofstream res_file;
							cout << "Please enter a file name to save the resources as : ";
							string name = GetInputString(cin);

							res_file.open(name.c_str());
							resources->outputAllSRUs(res_file);
							res_file.close();
						}
						break;

					case 4:		// 	Save all current details
						{
							cout << "Files will be saved as <filename>_res.dat, <filename>_area.dat and <filename>_ass.dat" << endl;
							cout << "Please enter a file name to save the files as : ";
							string name = GetInputString(cin);

							string ass_file, area_file, res_file;

							ass_file = name + "_ass.dat";
							area_file = name + "_area.dat";
							res_file = name + "_res.dat";

							ofstream ass;
							ofstream res;
							ofstream area;

							ass.open(ass_file.c_str());
							resources->outputAllAssignments(ass);
							ass.close();

							area.open(area_file.c_str());
							big_area->OutputAllAreas(area);
							area.close();

							res.open(res_file.c_str());
							resources->outputAllSRUs(res);
							res.close();
						}
						break;
				}
			}
			break;

			case ASSIGNMENT_MENU:
				{
					switch(option)
					{
						case 0:		// go to the main menu
							{
								current_menu = menus[MAIN_MENU];
							}
							break;

						case 1:		// add assignment
							{
								int resource_index, area_index;
								double hours;

								string s = "Please enter the index of the resource to be allocated : ";
								resource_index = GetValidInputInteger(s, "Invalid reource index", DataLimits::resourceNum_min, DataLimits::resourceNum_max);

								if (!resources->isSRU(resource_index))
								{
									error_manager->PostError(WARNING, "That is not a valid resource index", "SearchManager::MenuManager() An invaild resource index was specified in add Assignment");
									break;
								}

								resources->viewAssignments(resource_index);

								cout << "\n";
								hours = GetValidInputFloat("Number of hours to assign: ", "Invalid Entry", 0);

								if (resources->getHoursRemaining(resource_index) < hours)
								{
									error_manager->PostError(WARNING, "There are not enough hours left for that assignment", "SearchManager::MenuManager() Tried to assign more hours than were available a unit");
									break;
								}

								s = "Which area index would you like to assign it to : ";
								area_index = GetValidInputInteger(s, "Invalid area number", DataLimits::areaNum_min, DataLimits::areaNum_max);

								if (big_area->isArea(area_index))
								{
									Assignment assignment(area_index, hours);
									resources->addAssignment(resource_index, assignment);
								}
								else
								{
									error_manager->PostError(WARNING, "That is not a valid area number", "SearchManager::MenuManager() An incorrect area number was specified when adding an Assignment");
								}
							}
							break;

						case 2:		// delete assignment
							{
								int resource_index;
								//char responce;

								string s = "Please enter the index of the resource to be de-allocated : ";
								resource_index = GetValidInputInteger(s, "Invaliod resource index", DataLimits::resourceNum_min, DataLimits::resourceNum_max);

								if (!resources->isSRU(resource_index))
								{
									error_manager->PostError(WARNING, "That is not a valid resource index", "SearchManager::MenuManager() while deleteing an assignment, an invaild resource index was specified");
									break;
								}

								resources->viewAssignments(resource_index);

								s = "Are you sure you wish to remove all these assignments?";

								if (GetResponce(s))
								{
									resources->deleteAssignments(resource_index);
								}
							}
							break;

						case 3:		//load assignments from file
							{
								cout << "\nEnter file name: ";
								string filename = GetInputString(cin);

								LoadAssignments(filename);
							}
							break;
						}
				}
				break;

			case CORRECTION_MENU:
				{
					switch(option)
					{
						case 0:
							{
								current_menu = menus[RESOURCE_MENU];
							}
							break;

						case 1:		// View Correction factors for an SRU
							{
								int resource_index;

								string s = "Please enter the index of the resource to be viewed : ";
								resource_index = GetValidInputInteger(s, "Invalid resource index", DataLimits::resourceNum_min, DataLimits::resourceNum_max);

								if (!resources->isSRU(resource_index))
								{
									error_manager->PostError(WARNING, "That is not a valid resource index", "SearchManager::MenuManager() invaild resource index was specified for viewing of correction factors");
									break;
								}

								resources->viewCorrectionFactors(resource_index);
							}
							break;

						case 2:		// Enter a correction factor for an SRU
							{
								int resourceNum = GetValidInputInteger("Enter the Resource Number of the SRU: ", "Invalid entry!");
								resources->userEnterCorrectionFactor(resourceNum);
							}
							break;

						case 3:		// Delete a correction factor for an SRU
							{
								int resourceNum = GetValidInputInteger("Enter the Resource Number of the SRU: ", "Invalid entry!");
								resources->userDeleteCorrectionFactor(resourceNum);
							}
							break;

						case 4:		// Delete all correction factors for an SRU
							{
								int resourceNum = GetValidInputInteger("Enter the Resource Number of the SRU: ", "Invalid entry!");
								resources->deleteCorrectionFactors(resourceNum);
							}
							break;
					}
				}
				break;
		}
	}
}

/******************************************************************************
 * GetHoursRemaining()
 *
 * Michael Eldridge
 *
 * Find the number of hours of searching remaining for a unit
 */

double SearchManager::GetHoursRemaining(int resource_num)
{
	if (resources->isSRU(resource_num))
	{
		return resources->getHoursRemaining(resource_num);
	}
	else
	{
		return -1;		// this is to show no unit in that resource num existed
	}
}

/******************************************************************************
 * AreThereHoursRemaining()
 *
 * Michael Eldridge
 *
 * Find the number of hours of searching remaining for a unit
 */

bool SearchManager::AreThereHoursRemaining(int resource_num)
{
	return resources->hoursRemaining(resource_num);
}

/******************************************************************************
 * GetESW()
 *
 * Michael Eldridge
 *
 * Get the estimated sweep width of a uint if it exists
 */

double SearchManager::GetESW(int resource_num)
{
	if (resources->isSRU(resource_num))
	{
		return resources->getESW(resource_num);
	}
	else
	{
		return -1;		// this is to show no uint in that resource num existed
	}
}

/******************************************************************************
 * getSpeed()
 *
 * Michael Eldridge
 *
 * Get the speed of a SNR unit if it exists
 */

double SearchManager::getSpeed(int resource_num)
{
	if (resources->isSRU(resource_num))
	{
		return resources->getSpeed(resource_num);
	}
	else
	{
		return -1;		// this is to show no uint in that resource num existed
	}
}

/******************************************************************************
 * AnyHoursRemaining()
 *
 * Michael Eldridge
 *
 * See whether there are any searcher hours remaining
 */

bool SearchManager::AnyHoursRemaining(void)
{
	return resources->anyHoursRemaining();
}

/******************************************************************************
 * DeleteAllAssignments()
 *
 * Michael Eldridge
 *
 * Remove all SRU from there current assignemts
 */

void SearchManager::DeleteAllAssignments(void)
{
	resources->deleteAllAssignments();
}

/******************************************************************************
 * AddAssignment()
 *
 * Michael Eldridge
 *
 * Set a unit to a SNR assignment
 */

bool SearchManager::AddAssignment(int resource_num, const Assignment& the_assignment)
{
	if (resources->isSRU(resource_num))
	{
		if (testmode) cout << "Resource NUM " << resource_num << " Assigned " << the_assignment.getResourceHours() << "Hours" << endl;

		return resources->addAssignment(resource_num, the_assignment);
	}
	else
	{
		return false;		// unit didn't exist
	}
}

/******************************************************************************
 * GetAssignments()
 *
 * Michael Eldridge
 *
 * Get the list of assignments for a particular unit
 */

vector<Assignment> SearchManager::GetAssignments(int resource_num)
{
	if (resources->isSRU(resource_num))
	{
		return resources->getAssignments(resource_num);
	}
	else
	{
		vector<Assignment> empty_assignments;
		return empty_assignments;		// unit didn't exist
	}
}

/******************************************************************************
 * GetAreaNumList()
 *
 * Michael Eldridge
 *
 * Get the list of valid area numbers
 */

vector<int> SearchManager::GetAreaNumList(void)
{
	return big_area->getAreaNumList();
}

/******************************************************************************
 * UpdatePOA()
 *
 * Michael Eldridge
 *
 * Update the POA of an Area
 */

bool SearchManager::UpdatePOA(int area_number, float newPOA)
{
	if (big_area->isArea(area_number))
	{
		if (newPOA <= 100 && newPOA >= 0)
		{
			big_area->updatePOA(area_number, newPOA);
			return true;
		}
	}
	return false;
}

/******************************************************************************
 * GetPOA()
 *
 * Michael Eldridge
 *
 * Read the POA of an Area
 */

float SearchManager::GetPOA(int area_number)
{
	if (big_area->isArea(area_number))
	{
		return big_area->getPOA(area_number);
	}
	return -1;
}

/******************************************************************************
 * GetPden()
 *
 * Michael Eldridge
 *
 * Find the probability density of an area
 */

float SearchManager::GetPden(int area_number)
{
	if (big_area->isArea(area_number))
	{
		return big_area->getPden(area_number);
	}
	return -1;
}
/******************************************************************************
 * GetSize()
 *
 * Michael Eldridge
 *
 * Find the size of an area
 */

float SearchManager::GetSize(int area_number)
{
	if (big_area->isArea(area_number))
	{
		return big_area->getSize(area_number);
	}
	return -1;
}

/******************************************************************************
 * GetEffectiveSweepRate()
 *
 * Michael Eldridge
 *
 * Will return the effect sweep rate of a particular resource
 */

double SearchManager::GetEffectiveSweepRate(int resource_num)
{
	if (resources->isSRU(resource_num))
	{
		return resources->getEffectiveSweepRate(resource_num);
	}
	else
	{
		return -1;		// this is to show no uint in that resource num existed
	}
}

/******************************************************************************
 * GetResourceNumList()
 *
 * Michael Eldridge
 *
 * Returns a list of all valid resources currently loaded
 */

vector<int> SearchManager::GetResourceNumList(void)
{
	return resources->getResourceNumList();
}

/******************************************************************************
 * OutputResourceAssignemnts()
 *
 * Michael Eldridge
 *
 * Output all the resources assignments to stdout
 */

void SearchManager::OutputResourceAssignments(void)
{
	resources->outputAllAssignments(cout);
}

// Added ASO 21/1/03 to enable autofile mode of AGM
void SearchManager::OutputResourceAssignments(ostream& out)
{
	resources->outputAllAssignments(out);
}

/******************************************************************************
 * OutputAreas()
 *
 * Andre Oboler
 *
 * Output all Areas through the search manager
 */

void SearchManager::OutputAreas(void)
{
	big_area->OutputAllAreas(cout);
}

void SearchManager::OutputAreas(ostream& out)
{
	big_area->OutputAllAreas(out);
}


/******************************************************************************
 * OutputAllPOAs()
 *
 * Michael Eldridge
 *
 * Output all the area POA's to std out
 */

void SearchManager::OutputAllPOAs(void)
{
	big_area->OutputAllAreas(cout);
}

/******************************************************************************
 * ViewAllAssignments()
 *
 * Michael Eldridge
 *
 * Views all the current assignments in table format
 */

void SearchManager::ViewAllAssignmentsTable(void)
{
	resources->viewAllAssignments();
}

/******************************************************************************
 * ViewAllAssignments()
 *
 * Michael Eldridge
 *
 * Views all the assignments in file format
 */

void SearchManager::ViewAllAssignments(void)
{
	resources->outputAllAssignments(cout);
}

/******************************************************************************
 * UpdateAllPOAs()
 *
 * Updates POAs for a search that uses the current Assignments stored in
 * resources.  The update of POAs accounts for correction factors for
 * terrain and vegetation in each Area, and assumes that all searches
 * are unsuccessful.
 *
 * If there are no SRUs present, a warning is posted.  A warning is also
 * posted for each SRU that has hours unassigned for searching, and each
 * SRU assigned to search Rest of World (area number -1).
 *
 * Author : Gareth Thompson
 */

void SearchManager::UpdateAllPOAs(void)
{
	if (testmode) cout << "entering SearchManager::UpdateAllPOAs()\n";

	/* Obtain List of Resources */
	vector<int> SRUList = resources->getResourceNumList();

	if (testmode)
	{
		cout << "List of Resources: \n";
		PrintIntVector(SRUList);
	}

	/* Check if there are SRUs present */
	if (SRUList.size() == 0)
	{
		/* No SRUs present, so no searching is performed */
		error_manager->PostError(WARNING, "There are no SRUs stored.  No searching occurs and no change is made to areas' POA values.", "SearchManager::UpdateAllPOAs() - getResourceNumList() returned a vector of size 0.");
		return;
	}

	/* Calculate results of searches for each SRU in turn */
	vector<int>::iterator currentSRU;
	for (currentSRU = SRUList.begin(); currentSRU != SRUList.end(); currentSRU++)
	{
		/* Check if this SRU has resource-hours remaining to assign */
		if (resources->hoursRemaining(*currentSRU))
		{
			error_manager->PostError(WARNING, "SRU "+ConvertToStr(*currentSRU)+" has Resource-hours that were not assigned for searching.", "SearchManager::UpdateAllPOAs() - resources->hoursRemaining(*currentSRU) returned true");
		}

		/* Obtain List of Assignments for this SRU */
		vector<Assignment> assignList = resources->getAssignments(*currentSRU);

		/* Update POA for each assignment in turn */
		vector<Assignment>::iterator currentAssignment;
		for (currentAssignment = assignList.begin(); currentAssignment != assignList.end(); currentAssignment++)
		{
			if (testmode)
			{
				cout << "Assignment is: \n";
				cout << "SRU: " << *currentSRU << "\n";
				cout << "Area: " << currentAssignment->getAreaNum() << "\n";
				cout << "Resource-hours: " << currentAssignment->getResourceHours() << "\n";
			}

			int areaNum = currentAssignment->getAreaNum();

			if (testmode) cout << "Area number: " << areaNum << "\n";

			/* Area should exist */
			if (!big_area->isArea(areaNum))
			{
				/* Should never be executed, but include error-checking code in case */
				error_manager->PostError(WARNING, "SRU "+ConvertToStr(*currentSRU)+" is assigned to search non-existent Area "+ConvertToStr(areaNum)+".  Assignment ignored.", "SearchManager::UpdateAllPOAs() - big_area->isArea(areaNum) returned false.  An Assignment has been stored for an area that does not exist.");
				continue;
			}

			/* Check if Area to search is Rest of World. */
			if (areaNum == -1)
			{
				/* For assignments to Rest of World, produce a warning and continue as normal. */
				error_manager->PostError(WARNING, "SRU "+ConvertToStr(*currentSRU)+" is assigned to search Rest of World (Area number -1).", "SearchManager::UpdateAllPOAs() - areaNum is -1.");
			}

			/* Calculate POD for this Search, taking correction factors for terrain and vegetation into account */
			double areaEffectivelySwept = resources->getEffectiveSweepRate(*currentSRU, big_area->getTerrain(areaNum), big_area->getVegetation(areaNum)) *
						      currentAssignment->getResourceHours();

			if (testmode) cout << "Area effectively swept: " << areaEffectivelySwept << "\n";

			double size = big_area->getSize(areaNum);

			/* Size should not be equal to 0 */
			if (size == 0)
			{
				/* Should never be executed, but include error-checking code in case */
				error_manager->PostError(WARNING, "Size of Area "+ConvertToStr(areaNum)+" is 0, making calculations impossible.  Assignment of Resource "+ConvertToStr(*currentSRU)+" to this area is ignored.", "SearchManager::UpdateAllPOAs() - big_area->getSize() returned 0.  The size of an area has been stored as 0.");
				continue;
			}

			double coverage = areaEffectivelySwept / size;

			if (testmode) cout << "Coverage: " << coverage << "\n";

			double POD = 1.0 - exp(-1 * coverage);

			if (testmode) cout << "POD: " << POD << "\n";

			/* Calculate new POA for Area after this search */
			double POA = (1-POD) * big_area->getPOA(areaNum);

			if (testmode) cout << "New POA: " << POA << "\n";

			/* New POA for Area should be stored */
			if (!big_area->updatePOA(areaNum, POA))
			{
				/* Should never be executed, but include error-checking code in case */
				error_manager->PostError(WARNING, "Miscellaneous error when storing new POA "+ConvertToStr(POA)+" for Area Number "+ConvertToStr(areaNum)+".  POA may no longer be correct.", "SearchManager::UpdateAllPOAs() - big_area->updatePOA(areaNum, POA) returned false for valid areaNum and POA.");
				continue;
			}
		}
	}
}



/******************************************************************************
 * CalcOptimalAssignment()
 *
 * If resources contains exactly one SRU, CalcOptimalAssignmentCharnCoop()
 * is called to find the optimal allocation of that SRU, taking correction
 * factors into account.  If resources contains multiple SRUs,
 * CalcOptimalAssignmentNoCorrFacts() is called to find the optimal allocation
 * of those SRUs, ignoring correction factors.
 *
 * The value returned is that returned by the function called.
 *
 * Author : Gareth Thompson
 */

bool SearchManager::CalcOptimalAssignment(void)
{
	if (testmode) cout << "entering SearchManager::CalcOptimalAssignment()\n";

	vector<int> resourceList = resources->getResourceNumList();

	if (resourceList.size() == 1)
	{
		return (CalcOptimalAssignmentCharnCoop(resourceList[0]));
	}
	else
	{
		return (CalcOptimalAssignmentNoCorrFacts());
	}

}

/**
 * Added 19/1/03 to integrate with SORAL library
 *
 * 29/1/03 crt: fixed to use ESR as ESR, not ESW.
 *
 */
bool SearchManager::useSORAL(void)
{

	int i,j;
	int areaNumber; // Note: this is the number NOT the index.
   int resourceNumber, areaIndex, resourceIndex;
	int num_res = resources->getNumResources();
	int num_areas = big_area->count();
	valarray<double> availableHours(num_res);
	valarray<double> POC(num_areas);
	//resources->getResourceNumList()
	vector<int>::iterator ResIter;
	vector<int>::iterator AreaIter;
	Array2D effectiveness(num_areas, num_res);
	//Array2D& effectiveness = *effectivenessTemp;
	ActiveAreasIterator* activeAreas;
	ResourceIterator* activeRes;
	double time;


	/****************************
	 *
	 *	Make a list of hours available
	 *
	 ****************************/

	vector<int> tempVectorRes=resources->getResourceNumList();

    int resIndex = 0;
	for(ResIter=tempVectorRes.begin(); ResIter != tempVectorRes.end(); ResIter++)
	{
		if(testmode==true)
		{
			cout << "\nResources and Hours Exported to SORAL\n";
			cout << "availableHours: Res(" << *ResIter << ")  Hours(" << resources->getHoursRemaining(*ResIter) << ")\n";
		}
		availableHours[resIndex++] = resources->getHoursRemaining(*ResIter);
	}



	if(testmode==true)
	{
		cout << "availableHours Imported to SORAL: \n";
		cout << "*";
		PrintDoubleValArray(availableHours);
		cout << "\n\n";
	}



	/****************************
	 *
	 *	Make effectiveness matrix
	 *
	 ****************************/

	// Note: do not normalise before using SORAL!

	vector<int> tempVectorArea=big_area->getAreaNumList();

	// Remove any areas with negative AreaNumbers eg home base and rest of world.
	for(AreaIter=tempVectorArea.begin();AreaIter != tempVectorArea.end(); AreaIter++)
	{
		if(*AreaIter<0)
		{
			tempVectorArea.erase(AreaIter);
			num_areas--;
		}
	}


	if(testmode==true)
	{
		cout << "\nAreas\n";
		PrintIntVector(tempVectorArea);
		cout << "\nResources\n";
		PrintIntVector(tempVectorRes);
	}
	int tempTerr;
	int tempVeg;
	double tempESR;    // Added by crt.
	//double tempESW;  // Commented out by crt. Not needed.
	double speed;
	double areaSize;
	double tempEffectiveness;

	// Step 1. Get effectiveness = ESW * speed [* corrFactor] / areaSize
	for(j=0; j<num_res; j++)
	{
		for(i=0; i<num_areas; i++)
		{
			// resource, terrain, veg
			areaNumber=tempVectorArea[i];
			resourceNumber=tempVectorRes[j];
			tempTerr=big_area->getTerrain(areaNumber);
			tempVeg=big_area->getVegetation(areaNumber);

			// Note getEffectiveSweepRate returns in km^2/hr (assuming standard input files)
			tempESR=resources->getEffectiveSweepRate(resourceNumber, tempTerr, tempVeg);


			if(testmode==true)
			{
				cout <<"\n Area: " << areaNumber << "  Resource: " << resourceNumber;
				cout << "  Terrain: " << tempTerr << "  Vegetation: " << tempVeg;
				cout <<"  ** ESR "<< tempESR <<" **\n"; // crt changed to ESR
			}
			areaSize=big_area->getSize(areaNumber);
			tempEffectiveness= (tempESR) /areaSize;

			effectiveness[i][j]=tempEffectiveness;
		}
	}
	if(testmode==true)
	{
		cout << "Effectiveness Array2D\n";
		effectiveness.print();
	}
	// effectiveness
	/****************************
	 *
	 *	Make POC vector
    * aka POA vector
	 *
	 ****************************/
	//[TODO]
	// POC
	for(i=0; i<num_areas; i++)
	{
		double tempPOA;
		areaNumber=tempVectorArea[i];
		tempPOA=big_area->getPOA(areaNumber);
		tempPOA=tempPOA/100;
		POC[i] = tempPOA;
	}
	if(testmode==true)
	{
		cout << "\n POC = POA\n";
		PrintDoubleValArray(POC);
	}

	/****************************
	 *
	 *	Make the allocation object
	 *      (FINALLY!)
	 *
	 ****************************/

	 CharnesCooper theAllocation(num_res, num_areas, effectiveness, availableHours, POC);
	 //Washburn theAllocation(num_res, num_areas, effectiveness, availableHours, POC);


	 // Causes errors
	 //cout << theAllocation.getCoverage(0) << " <- Coverage of 1 \n";

	/****************************
	 *
	 *	Update AGMs allocations
	 *  to mirror what SORAL said
	 *
	 ****************************/

	 /* Note: Soral uses the index of the resources and variables passed in...
	  * it does not even know their "numbers".
	  * before using ANY "current" from an iterator, convert it back to its number.
	  * eg areaNumber=big_area->getAreaNumList()[activeAreas->get()];
	  * where activeAreas is a SORAL iterator.
	  */

	activeAreas= new ActiveAreasIterator(theAllocation);


	i=0;
	if(testmode==true)
	{
		cout << " \n This " << i <<"th Active Area is: Area " << activeAreas->getCurrentActiveAreaNum();
		cout << "\n";
	}


	while(!(activeAreas->atEnd()))
	{

		areaIndex=activeAreas->getCurrentActiveAreaNum();
		areaNumber=tempVectorArea[areaIndex];
		activeRes= new ResourceIterator(theAllocation, areaIndex); // theAllocation, resourceNumber
		ResourceAssignment resAssign( **activeRes );
		resourceIndex=resAssign.getResourceNum();
		resourceNumber=tempVectorRes[resourceIndex];
		time=resAssign.getTime();
		Assignment* tempAssign = new Assignment(areaNumber, time);
		resources->addAssignment(resourceNumber, *tempAssign);

		// ASO 23/1/03
		// This line seems to be tricky. Windows wants it as
		// "(*activeAreas)++" and linux as "*activeAreas++"
		//
		// [TODO]
		// crt: if it's a problem, just use a = a + 1.....
		++(*activeAreas);

		//testing
		if(testmode==true)
		{
			i++;
			cout << " \n This " << i <<"th Active Area is: Area " << activeAreas->getCurrentActiveAreaNum();
			cout << "\n";
		}

		delete activeRes; // clean up memory
	}

	return true;
}

/******************************************************************************
 * CalcOptimalAssignmentNoCorrFacts()
 *
 * Calculates an optimal assignment of the (multiple) SRUs in resources to
 * search the areas in big_area, ignoring any correction factors for terrain
 * and vegetation (the algorithm assumes that each SRU has a fixed Effective
 * Sweep Rate for all Areas).
 *
 * If resources contains at least one SRU with hours available for searching
 * and a positive Effective Sweep Rate (product of ESW [Sweep Width] and Speed),
 * and big_area contains at least one Area with a non-zero Pden (Probability
 * density), any current assignments are deleted, the optimal allocation is
 * calculated and stored, and true is returned.
 *
 * If any of the above conditions are not met, an appropriate error is posted
 * and false is returned.
 *
 * Author : Gareth Thompson
 */

bool SearchManager::CalcOptimalAssignmentNoCorrFacts(void)
{
	if (testmode) cout << "entering SearchManager::CalcOptimalAssignmentNoCorrFacts()\n";

	vector<int>::iterator current;

	/* Clear current assignments */
	resources->deleteAllAssignments();

	/*
	 * Check that there is at least one SRU with hours available for searching
	 * and a positive Effective Sweep Rate.
	 */
	vector<int> resourceList = resources->getResourceNumList();

	if (resourceList.size() == 0)
	{
		error_manager->PostError(WARNING, "No SRUs are stored, so no assignments can be made.", "SearchManager::CalcOptimalAssignmentNoCorrFacts() - resources->getResourceNumList() returned an empty vector.");
		return false;
	}

	bool resourceToSearch = false;
	for (current = resourceList.begin(); current != resourceList.end(); current++)
	{
		if (resources->getEffectiveSweepRate(*current) > 0 && resources->getHoursRemaining(*current) > 0)
		{
			resourceToSearch = true;
			break;
		}
	}

	if (!resourceToSearch)
	{
		error_manager->PostError(WARNING, "There are no SRUs with Hours Available for searching, and positive ESW (Sweep Width) and Speed.  No SRUs can do any effective searching, so no sensible allocation can be made.  No assignments set.", "SearchManager::CalcOptimalAssignmentNoCorrFacts() - For every SRU, either resources->getEffectiveSweepRate(*current) or resources->getHoursRemaining(*current) returned 0.");
		return false;
	}

	/* Obtain a list of areas */
	vector<int> areaList = big_area->getAreaNumList();

	if (testmode)
	{
		cout << "List of areas:\n";
		PrintIntVector(areaList);
		cout << "\n";
	}

	/* Remove Rest of World (area number -1) from list, if present */
	for (current = areaList.begin(); current != areaList.end(); current++)
	{
		if (testmode)
		{
			int temp;
			temp = *current;
			cout << "current: " << temp << "\t";
		}

		if ((*current) == -1)
		{
			areaList.erase(current);
			break;
		}
	}

	if (testmode)
	{
		cout << "List of areas, with Rest of World removed:\n";
		PrintIntVector(areaList);
		cout << "\n";
	}

	/* Check that there is at least one Area available for searching with a positive Pden */
	if (areaList.size() == 0)
	{
		error_manager->PostError(WARNING, "There are no searchable areas.   No assignments can be made.  [NOTE: Rest of World is not a searchable area.]", "SearchManager::CalcOptimalAssignmentNoCorrFacts() - No areas are present in areaList after Rest of World has been removed.");
		return false;
	}

	bool areaToSearch = false;
	for (current = areaList.begin(); current != areaList.end(); current++)
	{
		if (big_area->getPden(*current) > 0)
		{
			if (testmode) cout << "Area " << *current << " has a nonzero Pden of: " << big_area->getPden(*current) << "\n";
			areaToSearch = true;
			break;
		}
	}

	if (!areaToSearch)
	{
		error_manager->PostError(WARNING, "There are no Areas with positive Pden (Probability Density) values.  No useful allocation can be found.  No assignments set.", "SearchManager::CalcOptimalAssignmentsNoCorrFacts() - big_area->getPden(*current) returned 0 or less for all valid current.");
		return false;
	}

	/* Sort areaList into descending order by Pden */
	sortList(areaList, &SearchManager::gtPden);

	if (testmode)
	{
		cout << "Areas in Pden order (with Rest of World removed):\n";
		PrintIntVector(areaList);
		cout << "\n";
	}

	double pdenMax;  /* Maximum Pden of Areas */
	double pden2;  /* 2nd highest Pden of Areas */
	vector<int>::iterator lastArea;  /* Last area in vector with equal-highest Pden */
	double totalSize;  /* Total size of Areas with equal-highest Pden */

	/* Initialise above data variables */
	lastArea = areaList.begin();
	pdenMax = big_area->getPden(*lastArea);
	totalSize = big_area->getSize(*lastArea);

	while (lastArea < areaList.end()-1 && FloatEqual(big_area->getPden(*(lastArea+1)), pdenMax))
	{
		lastArea++;
		totalSize += big_area->getSize(*lastArea);
	}

	if (lastArea < areaList.end() - 1)
	{
		/* All areas do not have equal Pden.  2nd highest Pden is next in list. */
		pden2 = big_area->getPden(*(lastArea+1));
	}


	/* Continue to make assignments until no SRUs have Resource-hours remaining to assign. */
	while (resources->anyHoursRemaining())
	{
		if (testmode)
		{
			cout << "Last Area in vector to search: " << *lastArea << "\n";
			cout << "Maximum Pden: " << pdenMax << "\n";
			cout << "2nd highest Pden: " << pden2 << "\n";
			cout << "Total size of areas to search: " << totalSize << endl;
		}

		double coverageActual;		//Actual coverage to search with for this iteration

		if (lastArea == areaList.end()-1 || pden2 == 0.0)
		{
			/*
			 * Areas before (and including) lastArea have equal Pden, and there are
			 * either no more areas, or all following areas have Pden 0.0.  It is
			 * therefore impossible to drive the Pden of areas at pdenMax down to pden2,
			 * so the remaining Resource-Hours are spread across the areas before (and
			 * including) lastArea to obtain the highest possible uniform coverage.
			 */
			coverageActual = resources->getAreaEffectivelySweptRemaining() / totalSize;
		}
		else
		{
			/*
			 * All Areas do not have equal Pden.  Those Areas with the
			 * highest Pden are to be searched with the coverage necessary
			 * to drive pdenMax down to pden2.  (Or the maximum coverage
			 * that can be achieved with the given SRUs, if that is lower).
			 */

			/* Calculate POD necessary to drive pdenMax down to pden2 */
			double POD = 1.0 - pden2 / pdenMax;

			if (testmode) cout << "POD: " << POD << endl;

			/* Calculate necessary coverage to achieve this POD */
			double coverageNeeded = -1 * log(1.0 - POD);

			if (testmode) cout << "Coverage Needed: " << coverageNeeded << endl;

			/* Calculate maximum coverage that can be achieved with remaining resources */
			double coverageAvailable = resources->getAreaEffectivelySweptRemaining() / totalSize;

			if (testmode) cout << "Coverage Available: " << coverageAvailable << endl;

			/* Calculate the actual coverage to use (minimum of coverageNeeded and coverageActual) */
			if (coverageNeeded < coverageAvailable)
			{
				coverageActual = coverageNeeded;
			}
			else
			{
				coverageActual = coverageAvailable;
			}
		}


		if (testmode) cout << "Coverage to use: " << coverageActual << endl;

		/* Assign SRUs to search each Area with the required coverage */
		vector<int>::iterator areaToSearch;
		for (areaToSearch = areaList.begin(); areaToSearch <= lastArea; areaToSearch++)
		{
			/* Assignment should be successful */
			if (!assignSRUs((*areaToSearch), coverageActual))
			{
				error_manager->PostError(WARNING, "Miscellaneous error when adding assignments.  Some assignments may not have been added correctly.", "SearchManager::assignSRUs() - assignSRUs() returned false when sufficient resource-hours were available for assignments.");
				return false;
			}
		}

		if (testmode) resources->viewAllAssignments();

		/* Update required data variables for the next iteration */
		pdenMax = pden2;

		while (lastArea < areaList.end()-1 && FloatEqual(big_area->getPden(*(lastArea+1)), pdenMax))
		{
			lastArea++;
			totalSize += big_area->getSize(*lastArea);
		}

		if (lastArea < areaList.end() - 1)
		{
			/* All areas do not have equal Pden.  2nd highest Pden is next in list. */
			pden2 = big_area->getPden(*(lastArea+1));
		}

	}
	return true;

}






/******************************************************************************
 * assignSRUs()
 *
 * Adds assignments to SRUs so that the specified area will be searched with the
 * specified coverage.  Any correction factors for terrain and vegetation
 * are ignored.
 *
 * If the specified area exists and sufficient resource-hours are available
 * (to achieve the desired coverage), these assignments are made and true is
 * returned.
 *
 * If the Area does not exist, no assignments are made and false is returned.
 *
 * If insufficient resource-hours are available, all remaining resource-hours
 * are assigned to search that area and false is returned.
 *
 * Author : Gareth Thompson
 */

bool SearchManager::assignSRUs(int areaNum, double coverage)
{
	if (testmode) cout << "entering AssignSRUs(" << areaNum << ", " << coverage << ")\n";

	/* Check if Area exists */
	if (!big_area->isArea(areaNum)) return false;

	/* If required coverage is zero, no assignments are necessary */
	if (coverage == 0.0) return true;

	/* Calculate the Area Effectively Swept to achieve required coverage */
	double areaToEffectivelySweep = coverage * big_area->getSize(areaNum);

	/* Get list of Resource Numbers available */
	vector<int> resourceList = resources->getResourceNumList();

	vector<int>::iterator current;

	/*
	 * Continue to assign resources until the areaEffectivelySwept is reduced to 0 or
	 * there are no more SRUs to give assignments to.
	 */
	for (current = resourceList.begin(); current != resourceList.end(); current++)
	{
		if (resources->hoursRemaining(*current))
		{
			/* This SRU has further Resource-hours available for searching.  It can be assigned to search this area. */

			/* Calculate the maximum area that this SRU can effectively sweep */
			double maxAreaEffecSweep = resources->getEffectiveSweepRate(*current) * resources->getHoursRemaining(*current);

			if (FloatLess(maxAreaEffecSweep, areaToEffectivelySweep))
			{
				/* This SRU cannot sweep all the required area. Assign all its hours to sweep this area. */
				resources->addAssignment((*current), Assignment(areaNum, resources->getHoursRemaining(*current)));

				/* Reduce areaToEffectivelySweep by the amount that has been swept */
				areaToEffectivelySweep -= maxAreaEffecSweep;
			}
			else
			{
				/* This SRU can sweep all the required area. Assign sufficient Resource Hours to do so. */
				double hoursToSweep = areaToEffectivelySweep / resources->getEffectiveSweepRate(*current);
				resources->addAssignment((*current), Assignment(areaNum, hoursToSweep));

				/* No more assignments are necessary */
				return true;
			}
		}
	}

	/* areaToEffectivelySweep was not reduced to zero - insufficient resource-hours were available */
	return false;
}



/******************************************************************************
 * CalcOptimalAssignmentCharnCoop()
 *
 * Calculates the optimal assignment of one SRU to search multiple areas
 * using the Charnes-Cooper algorithm.  Correction factors (which modify the
 * Effective Sweep Rate of the SRU in each area depending upon the terrain
 * and vegetation) are taken into account by this algorithm.
 *
 * If Resources has an SRU with the specified Resource Number,
 * and there are Areas (other than Rest of World) to search,
 * the current assignments for that SRU are deleted, the optimal
 * allocation (assuming that only that SRU is available) is
 * calculated and stored, and true is returned.
 *
 * If Resources does not have an SRU with the specified Resource
 * Number or there are no areas to search, no calculations
 * are performed, an error is posted and false is returned.
 *
 * If the SRU has a PSR of 0 in every area, no sensible allocation can be
 * made, so an error is posted and false is returned.
 *
 * Note that repeated application of this algorithm for different
 * SRUs will not result in an optimal allocation for the complete set
 * of SRUs.
 *
 * Author : Gareth Thompson
 */

bool SearchManager::CalcOptimalAssignmentCharnCoop(int resourceNum)
{
	if (testmode) cout << "entering CalcOptimalAssignmentCharnCoop()\n";

	vector<int>::iterator current;

	/* Check if SRU Exists */
	if (!resources->isSRU(resourceNum))
	{
		error_manager->PostError(WARNING, "There is no SRU with Resource Number "+ConvertToStr(resourceNum)+".  No assignments could be set.", "SearchManager::CalcOptimalAssignmentCharnCoop() - resources->isSRU(resourceNum) returned false");
		return false;
	}

	/* Assignments for SRU should be deleted */
	if (!resources->deleteAssignments(resourceNum))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error when deleting current assignments for SRU"+ConvertToStr(resourceNum)+".  New assignments could not be set.", "SearchManager::CalcOptimalAssignmentsCharnCoop() - resources->deleteAssignments(resourceNum) returned false for valid resourceNum.");
		return false;
	}

	/* Obtain a list of areas */
	vector<int> areaList = big_area->getAreaNumList();

	if (testmode)
	{
		cout << "List of areas:\n";
		PrintIntVector(areaList);
		cout << "\n";
	}

	/* Remove Rest of World (area number -1) from list, if present */
	for (current = areaList.begin(); current != areaList.end(); current++)
	{
		if (testmode) cout << "current: " << *current << "\t";

		if ((*current) == -1)
		{
			areaList.erase(current);
			break;
		}
	}

	if (testmode)
	{
		cout << "List of areas, with Rest of World removed:\n";
		PrintIntVector(areaList);
		cout << "\n";
	}

	/* Check if there are no areas to search */
	if (areaList.size() == 0)
	{
		error_manager->PostError(WARNING, "There are no searchable areas.   No assignments can be made.  [NOTE: Rest of World is not a searchable area.]", "SearchManager::CalcOptimalAssignmentCharnCoop() - No areas are present in areaList after Rest of World has been removed.");
		return false;
	}

	/* Check that SRU has a positive PSR in at least one area */
	bool areaToSearch = false;
	for (current = areaList.begin(); current != areaList.end(); current++)
	{
		if (getPSRCorrFacts(resourceNum, *current) > 0.0)
		{
			if (testmode) cout << "SRU " << resourceNum << " has a nonzero PSR in area " << (*current) << ".  PSR is " << getPSRCorrFacts(resourceNum, *current) << endl;
			areaToSearch = true;
			break;
		}
	}

	if (testmode) cout << "Area to search: " << testmode << endl;

	if (!areaToSearch)
	{
		error_manager->PostError(WARNING, "SRU "+ConvertToStr(resourceNum)+" does not have a positive PSR (Probable Success Rate) in any area.  No useful allocation can be found.  No assignments set.", "SearchManager::CalcOptimalAssignmentsCharnCoop() - getPSRCorrFacts(resourceNum, *current) returned a value of 0 or less for all valid current.");
		return false;
	}

	/* Sort list of areas into descending order of PSR for this SRU */
	compResNum = resourceNum;	//Compare PSRs for specified Resource Number
	sortList(areaList, &SearchManager::gtPSR);

	if (testmode)
	{
		cout << "List of areas, sorted in PSR order for Resource " << resourceNum << ":\n";
		PrintIntVector(areaList);
		cout << "\n";
	}

	double PSRmax;		//Maximum PSR of areas
	double PSR2;		//2nd highest PSR of areas
	vector<int>::iterator lastArea;		//Last area in areaList that has equal highest PSR

	/* Initialise above variables */
	lastArea = areaList.begin();
	PSRmax = getPSRCorrFacts(resourceNum, *lastArea);

	while (lastArea < areaList.end()-1 && FloatEqual(getPSRCorrFacts(resourceNum, *(lastArea+1)), PSRmax))
	{
		lastArea++;
		if (testmode) cout << "Last Area incremented to: " << *lastArea << "\n";
	}

	if (lastArea < (areaList.end() - 1))
	{
		/* All areas do not have equal PSR.  2nd highest PSR is next in list. */
		PSR2 = getPSRCorrFacts(resourceNum, *(lastArea+1));
		if (testmode) cout << "All areas do not have equal PSR.  2nd highest is: " << PSR2 << "\n";
	}

	/* Continue to make Assignments until SRU has no Resource-hours remaining to assign. */
	while (resources->hoursRemaining(resourceNum))
	{
		if (testmode)
		{
			cout << "Last Area to search: " << *lastArea << "\n";
			cout << "Maximum PSR: " << PSRmax << "\n";
			cout << "2nd highest PSR: " << PSR2 << "\n";
		}

		if (lastArea == areaList.end()-1)
		{
			/*
			 * SRU has equal PSR in all areas.  The remaining Resources hours are split between them in
			 * such a way that the PSRs for all areas are driven down to the same level.  Each Area is
			 * searched with Resource hours proportional to its Size divided by Effective Sweep Rate.
			 */
			double totalHoursAvailable = resources->getHoursRemaining(resourceNum);
			double totalSizeOverESR = 0;

			if (testmode)
			{
				cout << "Equal PSR in all areas.  Making final allocation.\n";
				cout << "Total hours available: " << totalHoursAvailable << "\n";
			}

			for (current = areaList.begin(); current != areaList.end(); current++)
			{
				totalSizeOverESR += big_area->getSize(*current) /
						    resources->getEffectiveSweepRate(resourceNum,
										     big_area->getTerrain(*current),
										     big_area->getVegetation(*current));
			}

			if (testmode) cout << "Total Size/ESR = " << totalSizeOverESR << "\n";

			for (current = areaList.begin(); current != areaList.end(); current++)
			{
				double sizeOverESR = big_area->getSize(*current) /
						     resources->getEffectiveSweepRate(resourceNum,
										      big_area->getTerrain(*current),
										      big_area->getVegetation(*current));

				if (testmode) cout << "Area " << *current << ": Size/ESR = " << sizeOverESR << "\n";

				double proportion = sizeOverESR / totalSizeOverESR;

				if (testmode) cout << "Proportion for Area " << *current << " is: " << proportion << "\n";

				double hoursToAssign = proportion * totalHoursAvailable;

				if (testmode) cout << "Hours to assign for Area " << *current << " is " << hoursToAssign << "\n";

				/* Assignment should be added successfully */
				if (!resources->addAssignment(resourceNum, Assignment(*current, hoursToAssign)))
				{
					/* Should never be executed, but include error-checking code in case */
					error_manager->PostError(WARNING, "Miscellaneous error when adding Assignments.  Some Assignments may not have been stored correctly.", "SearchManager::CalcOptimalAssignmentsCharnCoop() - resources->addAssignment() returns false for a valid Resource Number and an allowed Assignment.");
					return false;
				}
			}

			/* There should now be no Resource hours remaining. */
			if (resources->hoursRemaining(resourceNum))
			{
				/* Should never be executed, but include error-checking code in case */
				error_manager->PostError(WARNING, "Miscellaneous error when adding Assignments.  All Resource hours for SRU may not have been used.", "SearchManager::CalcOptimalAssignmentsCharnCoop() - resources->hoursRemaining(resourceNum) returned true when all resource hours have been used.");
				return false;
			}

			/* All resource hours are now used. */
			if (testmode) cout << "Assignments complete...exiting loop\n";
			break;
		}


		/*
		 * The SRU does not have equal PSR in all areas.  The areas with PSRmax are now driven down to PSR2, or
		 * are driven down as far as possible if there are insufficient Resource Hours remaining to drive them
		 * down to PSR2.
		 */

		/*
		 * Calculate hours needed to drive PSRmax down to PSR2, unless PSR2 is 0
		 * (in which case an infinite number of hours are needed)
		 */
		double POD, coverageNeeded, hoursNeeded;
		if (PSR2 != 0.0)
		{
			/* Calculate POD necessary to drive PSRmax down to PSR2 */
			POD = 1 - PSR2 / PSRmax;

			if (testmode) cout << "POD: " << POD << "\n";

			/* Calculate necessary coverage to achieve this POD */
			coverageNeeded = -1 * log(1.0 - POD);

			if (testmode) cout << "Coverage Needed: " << coverageNeeded << "\n";

			/* Calculate Number of Resource Hours required to obtain this coverage for all areas with PSRmax. */
			hoursNeeded = 0;
			for (current = areaList.begin(); current <= lastArea; current++)
			{
				/* Add hours required to sweep current area with given coverage */
				hoursNeeded += coverageNeeded * big_area->getSize(*current) /
					       resources->getEffectiveSweepRate(resourceNum, big_area->getTerrain(*current), big_area->getVegetation(*current));
			}

			if (testmode) cout << "Hours needed: " << hoursNeeded << "\n";
		}


		/*
		 * Check if number of Resource Hours available is less than or equal to that necessary to obtain
		 * desired coverage. Note that a PSR2 value of 0 means that an infinite number of hours is needed,
		 * so the Resource Hours available is always less than that necessary.
		 */
		if (PSR2 == 0.0 || !FloatLess(hoursNeeded, resources->getHoursRemaining(resourceNum)))
		{
			/*
			 * Number of Resource Hours available is less than or equal to that necessary to achieve
			 * desired coverage.  The remaining resource-hours are assigned in such a way that all
			 * areas that currently have PSRmax have the same final PSR.  Each Area is searched with
			 * Resource hours proportional to its size divided by Effective Sweep Rate.
			 */

			if (testmode) cout << "Insufficient resource hours available.  Remainder to be distributed between areas with PSRmax.\n";

			double totalHoursAvailable = resources->getHoursRemaining(resourceNum);
			double totalSizeOverESR = 0;
			for (current = areaList.begin(); current <= lastArea; current++)
			{
				totalSizeOverESR += big_area->getSize(*current) /
						    resources->getEffectiveSweepRate(resourceNum,
										     big_area->getTerrain(*current),
										     big_area->getVegetation(*current));
			}

			if (testmode) cout << "Total Size/ESR = " << totalSizeOverESR << "\n";

			for (current = areaList.begin(); current <= lastArea; current++)
			{
				double sizeOverESR = big_area->getSize(*current) /
						     resources->getEffectiveSweepRate(resourceNum,
										      big_area->getTerrain(*current),
										      big_area->getVegetation(*current));

				if (testmode) cout << "Area " << *current << ": Size/ESR = " << sizeOverESR << "\n";

				double proportion = sizeOverESR / totalSizeOverESR;

				if (testmode) cout << "Proportion for Area " << *current << " is: " << proportion << "\n";

				double hoursToAssign = proportion * totalHoursAvailable;

				if (testmode) cout << "Hours to assign for Area " << *current << " is " << hoursToAssign << "\n";

				/* Assignment should be added successfully */
				if (!resources->addAssignment(resourceNum, Assignment(*current, hoursToAssign)))
				{
					/* Should never be executed, but include error-checking code in case */
					error_manager->PostError(WARNING, "Miscellaneous error when adding Assignments.  Some Assignments may not have been stored correctly.", "SearchManager::CalcOptimalAssignmentsCharnCoop() - resources->addAssignment() returns false for a valid Resource Number and an allowed Assignment.");
					return false;
				}
			}

			/* There should now be no Resource hours remaining. */
			if (resources->hoursRemaining(resourceNum))
			{
				/* Should never be executed, but include error-checking code in case */
				error_manager->PostError(WARNING, "Miscellaneous error when adding Assignments.  All Resource hours for SRU may not have been used.", "SearchManager::CalcOptimalAssignmentsCharnCoop() - resources->hoursRemaining(resourceNum) returned true when all resource hours have been used.");
				return false;
			}

			/* All resource hours are now used. */
			if (testmode) cout << "Assignments complete...exiting loop\n";
			break;
		}

		/*
		 * More Resource Hours are available than necessary to achieve desired coverage.  Sufficient Resource-hours
		 * are assigned to each Area with PSRmax to achieve the desired coverage (and drive their PSR values down
		 * to PSR2).
		 */
		for (current = areaList.begin(); current <= lastArea; current++)
		{
			double hoursToAssign = coverageNeeded * big_area->getSize(*current) /
					       resources->getEffectiveSweepRate(resourceNum,
										big_area->getTerrain(*current),
										big_area->getVegetation(*current));

			if (testmode) cout << "Hours needed for Area " << *current << ": " << hoursToAssign << "\n";

			/* Assignment should now be made */
			if (!resources->addAssignment(resourceNum, Assignment(*current, hoursToAssign)))
			{
				/* Should never be executed, but include error-checking code in case */
				error_manager->PostError(WARNING, "Miscellaneous error when adding Assignments.  Some Assignments may not have been stored correctly.", "SearchManager::CalcOptimalAssignmentsCharnCoop() - resources->addAssignment() returns false for a valid Resource Number and an allowed Assignment.");
				return false;
			}
		}

		/* Update lastArea, PSRmax and PSR2 for next iteration */
		PSRmax = PSR2;

		while (lastArea < areaList.end()-1 && FloatEqual(getPSRCorrFacts(resourceNum, *(lastArea+1)), PSRmax))
		{
			lastArea++;
			if (testmode) cout << "Last Area incremented to: " << *lastArea << "\n";
		}

		if (lastArea < (areaList.end() - 1))
		{
			/* All areas do not have equal PSR.  2nd highest PSR is next in list. */
			PSR2 = getPSRCorrFacts(resourceNum, *(lastArea+1));
			if (testmode) cout << "All areas do not have equal PSR.  2nd highest is: " << PSR2 << "\n";
		}
	}

	return true;
}




/******************************************************************************
 * gtPden()
 *
 * Comparison function used with sortList function.
 * Returns true if the area with Area Number areaNumA has a greater
 * Pden than that with areaNumB.
 *
 * Returns false if the above conditions are not met, or if
 * either Area does not exist.
 *
 * Author : Gareth Thompson
 */

bool SearchManager::gtPden(const int& areaNumA, const int& areaNumB)
{
	if (testmode) cout << "entering SearchManager::gtPden(areaNumA, areaNumB)\n";

	if (!big_area->isArea(areaNumA) || !big_area->isArea(areaNumB))
	{
		return false;
	}

	/* Determine Pden for each area */
	double pdenA = big_area->getPden(areaNumA);
	double pdenB = big_area->getPden(areaNumB);

	return (pdenA > pdenB);
}



/******************************************************************************
 * gtPSR()
 *
 * Comparison function used with sortList function.
 * Returns true if the PSR of the SRU with Resource Number compResNum
 * has a higher PSR (Probable Success Rate) in the Area with Area
 * Number areaNumA than in the Area with Area Number areaNumB.
 * (Correction factors are taken into account in this comparison).
 *
 * Note that compResNum is a data member of SearchManager which
 * should be set to the required value before calling gtPSR.
 *
 * PSR is the product of the Pden of the Area with the Effective Sweep
 * Rate of the SRU in that area (taking correction factors for terrain
 * and vegetation into account).
 *
 * Returns false if the above condition is not met, or if the specified
 * SRU or Areas do not exist.
 *
 * Author : Gareth Thompson
 */

bool SearchManager::gtPSR(const int& areaNumA, const int& areaNumB)
{
	if (testmode) cout << "entering SearchManager::gtPSR(areaNumA, areaNumB)\n";

	if (!resources->isSRU(compResNum) || !big_area->isArea(areaNumA) || !big_area->isArea(areaNumB))
	{
		return false;
	}

	/* Determine PSR of SRU in each area */
	double PSRa = getPSRCorrFacts(compResNum, areaNumA);
	double PSRb = getPSRCorrFacts(compResNum, areaNumB);

	if (testmode)
	{
		cout << "PSRa: " << PSRa << ", PSRb: " << PSRb << endl;
	}

	return (PSRa > PSRb);
}




/******************************************************************************
 * sortList()
 *
 * Sorts theList into the order specified by the SearchManager
 * member function pointed to by compare().  The relative
 * order of equal elements in the sorted list is undefined.
 *
 * The standard sort() function cannot be used for some sorting
 * tasks within SearchManager because the keys for the integers
 * being sorted (which determine the relative order of these
 * integers) are specified within the big_area and resources
 * objects (which are not accessible to sort()).  An example is
 * sorting Area Numbers into Pden order, where the Pden values
 * are specified in big_area.
 *
 * If theList is initially empty, no sorting is performed!
 *
 * PRECONDITIONS:
 * If a should be placed before b in the sorted list, compare(a,b)
 * returns true and compare(b,a) returns false.
 * If a and b are equal (either can be placed first) compare(a,b)
 * and compare(b,a) both return true or both return false.
 *
 * Author : Gareth Thompson
 */

void SearchManager::sortList(vector<int>& theList, COMPARE compare)
{
	if (testmode)
	{
		cout << "entering sortList((";
		PrintIntVector(theList);
		cout << "), ?)\n";
	}

	/* If list has size less than 2, it is already sorted */
	if (theList.size() < 2) return;

	/* Sort list using selection sort */
	vector<int>::iterator i, j, next;
	for (i = theList.begin(); i<theList.end()-1; i++)
	{
		/* Find element that must be placed in position i */
		next = i;
		for (j=i+1; j<theList.end(); j++)
		{
			/* Call member function, via pointer, to make comparison */
			if ((this->*compare)(*j, *next))
			{
				next = j;
			}
		}

		/* Place next value in position i (swap elements at next and i) */
		int temp = *i;
		*i = *next;
		*next = temp;

		if (testmode)
		{
			cout << "List: ";
			PrintIntVector(theList);
			cout << "\n";
		}

	}
}



/******************************************************************************
 * getPSRCorrFacts()
 *
 * Returns the PSR (Probable Success Rate) (% / hour) for the SRU with the
 * specified Resource Number, in the area with the specified Area Number,
 * taking correction factors for terrain and vegetation into account.
 *
 * If the SRU and Area both exist, the PSR is returned.  This is the product
 * of the Pden (Probability density) of the area and the Effective Sweep
 * Rate of the SRU, with the terrain and vegetation in the given area.
 *
 * If either SRU or Area do not exist, the return value is undefined.
 *
 * Author : Gareth Thompson
 */

double SearchManager::getPSRCorrFacts(int resourceNum, int areaNum)
{
	if (testmode) cout << "entering SearchManager::getPSRCorrFacts(" << resourceNum << ", " << areaNum << ")\n";

	if (resources->isSRU(resourceNum) && big_area->isArea(areaNum))
	{
		/* Return PSR value */
		return (big_area->getPden(areaNum) * resources->getEffectiveSweepRate(resourceNum,
										      big_area->getTerrain(areaNum),
										      big_area->getVegetation(areaNum)));
	}
	else
	{
		/* SRU or Area does not exist */
		return -1.0;	//undefined return value
	}
}


/******************************************************************************
 * copyright() / CopyrightMini()
 *
 * Displays a (c) notice to stdout
 *
 * Version:
 * Created 2003-01-12.  Modified 2008-02-17 due to a change in the license
 * (now available under GPL).
 *
 * Parameters : void
 *
 * Authors : Andre Oboler, Gareth Thompson
 */

void SearchManager::copyright(void)
{
	CopyrightMini();

	if(GetResponce("\nMore?")==true)
	{
		cout << "This software was originally developed in 2001 for the subject CSE3301 in the\n";
		cout << "School of Computer Science and Software Engineering, Monash University,\n";
		cout <<	"Australia. The authors wish to thank their supervisor (and co-ordinator\n";
		cout << "of the SARbayes project) Dr Charles Twardy.\n";
		cout << "\n";
		cout << "This version, which was created in 2003 and updated in 2008, uses the open source search and rescue\n";
		cout << "library SORAL (SARBayes Optimal Research Allocation Library).  SORAL was\n";
		cout << "developed by Charles Twardy, David Albrecht, Andre Oboler, Gareth Thompson,\n";
		cout << "Michael Eldridge & others. SORAL is Copyright (C) the authors & Monash University.\n";
		cout << "You can find out more about SORAL and other search projects at the SARBayes\n";
		cout << "web site: http://www.sarbayes.org\n";
	}

	return;
}

void SearchManager::CopyrightMini(void)
{
		cout << "-- AGM SAR --\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "Copyright (C) 2001-2008 AGM, a team comprising Andre Oboler, Gareth\n";
		cout << "Thompson and Michael Eldridge.\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "AGM SAR is free software: you can redistribute it and/or modify\n";
		cout << "it under the terms of the GNU General Public License version 3,\n";
		cout << "as published by the Free Software Foundation. However, this\n";
		cout << "notice must be retained.\n";
		cout << "\n";
		cout << "AGM SAR uses the SORAL library, available separately under the GNU\n";
		cout << "General Public License, and distributed here in compliance with\n";
		cout << "that license.\n";
		cout << "\n";
		cout << "AGM SAR is distributed in the hope that it will be useful,\n";
		cout << "but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
		cout << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Use is at your\n";
		cout << "own risk. See the GNU General Public License for more details.\n";
		cout << "\n";
		cout << "You should have received a copy of the GNU General Public License\n";
		cout << "along with AGM SAR (see license.txt).  If not, see\n";
		cout << "<http://www.gnu.org/licenses/>.\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "\n";
}
