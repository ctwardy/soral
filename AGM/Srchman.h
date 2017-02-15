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
 * Search_manager.h
 *
 * Class structure for the seach manager interface. This object can then be used
 * to access all of the data about areas, resources and assignements in a safe and
 * consistant method
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 02/04/00 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#ifndef _Srchman_h_
#define _Srchman_h_
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
#define MENU_MASK		 0xFF00
#define MENU_OPTION_MASK 0x00FF
class BigArea;
class Resources;
class InputFile;
class Assignment;
class Menu;
class SearchManager
{
	public:
		enum
		{
			MAIN_MENU,
			AREA_MENU,
			RESOURCE_MENU,
			ASSIGNMENT_MENU,
			SAVE_MENU,
			CORRECTION_MENU,
			MENU_COUNT
		}
		menu;
	public:
		SearchManager(void);
		~SearchManager(void);
		void LoadAreas(string areas_filename);
		void LoadResources(string resources_filename);
		void PrintMap(void);
		bool LoadAssignments(string assignemt_filename);
		// newly added functions for Gareth
		double GetHoursRemaining(int resource_num);
		double GetESW(int resource_num);
		double getSpeed(int resource_num);
		bool   AnyHoursRemaining(void);
		bool   AreThereHoursRemaining(int ResourceNum);

		void   DeleteAllAssignments(void);
		bool   AddAssignment(int resource_num, const Assignment& the_assignment);
		vector<Assignment> GetAssignments(int resource_num);
		double GetEffectiveSweepRate(int resource_num);
		vector<int> GetResourceNumList(void);
		void   OutputResourceAssignments(void);
		void   OutputResourceAssignments(ostream& out);
		void   OutputAreas(void);
		void   OutputAreas(ostream& out);
		void   OutputAllPOAs(void);
		void   ViewAllAssignments(void);
		void   ViewAllAssignmentsTable(void);
		vector<int> GetAreaNumList(void);
		bool  UpdatePOA(int area_number, float newPOA);
		void  UpdateAllPOAs(void);
		float GetPOA(int area_number);
		float GetPden(int area_number);
		float GetSize(int area_number);
		void MenuManager(void);
		void copyright(void);
		void CopyrightMini(void);
		bool CalcOptimalAssignment(void);
		bool CalcOptimalAssignmentNoCorrFacts(void);
		bool CalcOptimalAssignmentCharnCoop(int resourceNum);
		bool useSORAL(void);
		void test(void);			// testing
		void SearchAndPrint(int resourceNum);	// functions
	private:
		BigArea* big_area;				// map object with defined search areas
		Resources* resources;			// contains SRU information
		InputFile* input_file;			// used for taking in input from data files
		Menu* current_menu;
		int compResNum;				//Resource Number that function gtPSR uses when comparing the PSR of areas
		/* Pointer to member function type used by sortList function */
		typedef bool (SearchManager::*COMPARE) (const int&, const int&);
		/* Comparison functions used with sortList algorithm */
		bool gtPden(const int& areaNumA, const int& areaNumB);
		bool gtPSR(const int& areaNumA, const int& areaNumB);
		void sortList(vector<int>& theList, COMPARE compare);
		double getPSRCorrFacts(int resourceNum, int areaNum);
		bool assignSRUs(int areaNum, double coverage);

		//string* main_menu_options[];
		//string resources_menu_options[];		// list of strings for menus
		//string area_menu_options[];
};

#endif



