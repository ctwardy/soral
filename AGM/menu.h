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
 * menu.h *
 * Controls the menu system used for the interactive mode
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 13/05/00 |  1  | Created.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <iostream>
#include <string>
using namespace std;
typedef enum
{
	MAIN,
	AREA,
	RESOURCE,
	ASSIGNMENT,
	SAVE,
	CORRECTION
}
MenuType;
/******************************************************************************
 * Menu
 *
 * Michael Eldridge
 *
 * The main menu class which controls the menu options
 */
class Menu
{
	public:
		Menu(string p_title, int p_size) : title(p_title), size(p_size) {}
		virtual ~Menu(void) {}
		virtual void PrintOptions(void) = 0;
		int ExecuteOption(void);
		void PrintTitle(void);
		MenuType GetMenuType(void) { return menu_type; }
	protected:
		MenuType menu_type;
		string title;
		int size;
	private:
};
/******************************************************************************
 * AreaMenu
 *
 * Michael Eldridge
 *
 * Controls the display and functionallity of the area's menu
 */
class AreaMenu : public Menu
{
	public:
		AreaMenu(int p_size);
		~AreaMenu(void) {}
		void PrintOptions(void);
	private:
		string menu_options[8];
};
/******************************************************************************
 * ResourceMenu
 *
 * Michael Eldridge
 *
 * Controls the display and functionallity of the resource's menu
 */
class ResourceMenu : public Menu
{
	public:
		ResourceMenu(int p_size);
		~ResourceMenu(void) {}
		void PrintOptions(void);
	private:
		string menu_options[9];
};
/******************************************************************************
 * MainMenu
 *
 * Michael Eldridge
 *
 * Controls the display and functionallity of the main menu
 */
class MainMenu : public Menu
{
	public:
		MainMenu(int p_size);
		~MainMenu(void) {}
		void PrintOptions(void);
	private:
		string menu_options[10];
};

/******************************************************************************
 * AssignmentMenu
 *
 * Michael Eldridge
 *
 * Controls the display and functionallity of the assignment menu
 */
class AssignmentMenu : public Menu
{
	public:
		AssignmentMenu(int p_size);
		~AssignmentMenu(void) {}
		void PrintOptions(void);
	private:
		string menu_options[4];
};
/******************************************************************************
 * SaveMenu
 *
 * Michael Eldridge
 *
 * Controls the display and functionallity of the save menu
 */
class SaveMenu : public Menu
{
	public:
		SaveMenu(int p_size);
		~SaveMenu(void) {}
		void PrintOptions(void);
	private:
		string menu_options[5];
};
/******************************************************************************
 * CorrectionMenu
 *
 * Michael Eldridge
 *
 * Controls the display and functionallity of the correction menu
 */
class CorrectionMenu : public Menu
{
	public:
		CorrectionMenu(int p_size);
		~CorrectionMenu(void) {}
		void PrintOptions(void);
	private:
		string menu_options[5];
};
