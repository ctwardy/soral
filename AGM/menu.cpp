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
 * menu.cpp
 *
 * Controls the menu system used for the interactive mode
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 13/05/00 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 5.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <iostream>
#include <string>
#include <vector>
//#include "Resource.h"
//#include "InputFil.h"
//#include "Areas.h"
//#include "Srchman.h"
#include "menu.h"
#include "global.h"
using namespace std;
/******************************************************************************
 * ExecuteOption()
 *
 * Michael Eldridge
 *
 * Determines whether an entered menu option os valid and returns it for use
 */
int Menu::ExecuteOption(void)
{
	int input;
	while (1)
	{
		cout << "Please enter an option : ";
		GetInputInteger(cin, input);
		if (input >= 0 && input <= size - 1)
		{
			break;
		}
		else
		{
			cout << endl << "Invalid option" << endl;
			PrintOptions();
		}
	}
	return input;
}
/******************************************************************************
 * PrintTitle()
 *
 * Michael Eldridge
 *
 * Print out the title for a menu
 */
void Menu::PrintTitle(void)
{
	int counter = 0;
	string main_title = "AGM Search and Rescue ";
	int star_length, spacing;
	cout << endl;
	if (title.length() < main_title.length())
	{
		star_length = main_title.length() + 8;
	}
	else
	{
		star_length = title.length() + 8;
	}
	// title
	for (counter = 0 ; counter < star_length ; counter++)
	{
		cout << "*";
	}
	cout << endl;
	if (title.length() < main_title.length())
	{
		cout << "*** " << main_title << " ***" << endl;
		spacing = (main_title.length() - title.length()) / 2;
		cout << "*** ";
		for (counter = 0 ; counter < spacing ; counter++)
		{
			cout << " ";
		}
		cout << title;
		for (counter = 0 ; counter < spacing ; counter++)
		{
			cout << " ";
		}
		if ((main_title.length() - title.length()) % 2)
		{
			cout << " ";
		}
		cout << " ***" << endl;
	}
	else
	{
		cout << "*** " << title << " ***" << endl;
		spacing = (title.length() - main_title.length()) / 2;
		cout << "*** ";
		for (counter = 0 ; counter < spacing ; counter++)
		{
			cout << " ";
		}
		cout << main_title;
		for (counter = 0 ; counter < spacing ; counter++)
		{
			cout << " ";
		}
		if ((title.length() - main_title.length()) % 2)
		{
			cout << " ";
		}
		cout << " ***" << endl;
	}
	for (counter = 0 ; counter < star_length ; counter++)
	{
		cout << "*";
	}
	cout << endl << endl;
}

/******************************************************************************
 * AreaMenu()
 *
 * Michael Eldridge
 *
 * Constructor for the area menu which sets up all the menu strings
 */
AreaMenu::AreaMenu(int p_size)
: Menu("Area Menu", p_size)
{
	menu_type = AREA;
	menu_options[0] = "Back to Main Menu";
	menu_options[1] = "Modify an Area";
	menu_options[2] = "Add a new Area";
	menu_options[3] = "Delete an Area";
	menu_options[4] = "View an Area";
	menu_options[5] = "View all Areas";
	menu_options[6] = "Load Areas from file";
	menu_options[7] = "Delete ALL Areas";
}
/******************************************************************************
 * PrintOptions()
 *
 * Michael Eldridge
 *
 * Print out all the menu options for this menu
 */
void AreaMenu::PrintOptions(void)
{
	for (int i = 1 ; i < size ; i++)
	{
		cout << "[" << i << "] " << menu_options[i] << endl;
	}
	cout << endl << "[0] " << menu_options[0] << endl;
}
/******************************************************************************
 * ResourceMenu()
 *
 * Michael Eldridge
 *
 * Constructor for the resources menu which sets up all the menu strings
 */
ResourceMenu::ResourceMenu(int p_size)
: Menu("Resource Menu", p_size)
{
	if (testmode) cout << "Constructing resource menu" << endl;
	menu_type = RESOURCE;
	menu_options[0] = "Back to Main Menu";
	menu_options[1] = "Enter a new SRU";
	menu_options[2] = "Load SRUs from a file";
	menu_options[3] = "Delete an SRU";
	menu_options[4] = "Delete all current SRUs";
	menu_options[5] = "Modify details of an SRU";
	menu_options[6] = "View details of an SRU";
	menu_options[7] = "View details of all SRUs";
	menu_options[8] = "Adjust correction factors";
	if (testmode) cout << "Finished constructing" << endl;
}
/******************************************************************************
 * PrintOptions()
 *
 * Michael Eldridge
 *
 * Print out all the menu options for this menu
 */
void ResourceMenu::PrintOptions(void)
{
	for (int i = 1 ; i < size ; i++)
	{
		cout << "[" << i << "] " << menu_options[i] << endl;
	}
	cout << endl << "[0] " << menu_options[0] << endl;
}
/******************************************************************************
 * MainMenu()
 *
 * Michael Eldridge
 *
 * Constructor for the main menu which sets up all the menu strings
 */
MainMenu::MainMenu(int p_size)
: Menu("Main Menu", p_size)
{
	menu_type = MAIN;
	menu_options[0] = "Exit";
	menu_options[1] = "Resource Properties";
	menu_options[2] = "Save Project";
	menu_options[3] = "Map Area Properties";
	menu_options[4] = "Assignment Adjustments";
	menu_options[5] = "View Current Resource Assignments";
	menu_options[6] = "Request Resource Allocation Advice";
	menu_options[7] = "Update POAs using current Resource Allocation";
	menu_options[8] = "Suggest with SORAL";
	menu_options[9] = "About AGM SAR";
}
/******************************************************************************
 * PrintOptions()
 *
 * Michael Eldridge
 *
 * Print out all the menu options for this menu
 */
void MainMenu::PrintOptions(void)
{
	for (int i = 1 ; i < size ; i++)
	{
		cout << "[" << i << "] " << menu_options[i] << endl;
	}
	cout << endl << "[0] " << menu_options[0] << endl;
}
/******************************************************************************
 * AssignmentMenu()
 *
 * Michael Eldridge
 *
 * Constructor for the main menu which sets up all the menu strings
 */
AssignmentMenu::AssignmentMenu(int p_size)
: Menu("Assignment Menu", p_size)
{
	menu_type = ASSIGNMENT;
	menu_options[0] = "Back to Main Menu";
	menu_options[1] = "Add Assignment";
	menu_options[2] = "Delete Assignment";
	menu_options[3] = "Load Assignments from a file";
}
/******************************************************************************
 * PrintOptions()
 *
 * Michael Eldridge
 *
 * Print out all the menu options for this menu
 */
void AssignmentMenu::PrintOptions(void)
{
	for (int i = 1 ; i < size ; i++)
	{
		cout << "[" << i << "] " << menu_options[i] << endl;
	}
	cout << endl << "[0] " << menu_options[0] << endl;
}
/******************************************************************************
 * SaveMenu()
 *
 * Michael Eldridge
 *
 * Constructor for the main menu which sets up all the menu strings
 */
SaveMenu::SaveMenu(int p_size)
: Menu("Save Menu", p_size)
{
	menu_type = SAVE;
	menu_options[0] = "Back to Main Menu";
	menu_options[1] = "Save current assignment details";
	menu_options[2] = "Save current area details";
	menu_options[3] = "Save current resources details";
	menu_options[4] = "Save all current details";
}
/******************************************************************************
 * PrintOptions()
 *
 * Michael Eldridge
 *
 * Print out all the menu options for this menu
 */
void SaveMenu::PrintOptions(void)
{
	for (int i = 1 ; i < size ; i++)
	{
		cout << "[" << i << "] " << menu_options[i] << endl;
	}
	cout << endl << "[0] " << menu_options[0] << endl;
}

/******************************************************************************
 * CorrectionMenu()
 *
 * Michael Eldridge
 *
 * Constructor for the main menu which sets up all the menu strings
 */
CorrectionMenu::CorrectionMenu(int p_size)
: Menu("Correction Factors Menu", p_size)
{
	menu_type = CORRECTION;
	menu_options[0] = "Back to Resources Menu";
	menu_options[1] = "View Correction factors for an SRU";
	menu_options[2] = "Enter a correction factor for an SRU";
	menu_options[3] = "Delete a correction factor for an SRU";
	menu_options[4] = "Delete all correction factors for an SRU";
}
/******************************************************************************
 * PrintOptions()
 *
 * Michael Eldridge
 *
 * Print out all the menu options for this menu
 */
void CorrectionMenu::PrintOptions(void)
{
	for (int i = 1 ; i < size ; i++)
	{
		cout << "[" << i << "] " << menu_options[i] << endl;
	}
	cout << endl << "[0] " << menu_options[0] << endl;
}
