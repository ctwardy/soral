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
 * test_smn.cpp
 *
 * test() function for testing SearchManager's private functions
 *
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 28/05/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <iostream>
#include <string>
#include "Srchman.h"
#include "Resource.h"
#include "Areas.h"
#include "global.h"
using namespace std;
/******************************************************************************
 * SearchAndPrint()
 *
 * Prints the PSRs for all areas for the specified Resource Number, Updates
 * POAs using the assignments currently stored, and then prints the PSRs
 * again.
 *
 * Author : Gareth Thompson
 */
void SearchManager::SearchAndPrint(int resourceNum)
{
        if (testmode) cout << "entering SearchAndPrint()\n";
	cout << "\nOriginal PSR values are:\n";
	vector<int> areaList = big_area->getAreaNumList();
	vector<int>::iterator current;
	for (current = areaList.begin(); current != areaList.end(); current++)
	{
		double Pden = big_area->getPden(*current);
		double ESR = resources->getEffectiveSweepRate(resourceNum, big_area->getTerrain(*current), big_area->getVegetation(*current));
		double PSR = Pden * ESR;
		cout << "Area Num: " << *current << "\t\tPden: " << Pden << "   \t\tESR: " << ESR << "  \t\tPSR: " << PSR << "\n";
	}
	UpdateAllPOAs();
	cout << "\nResulting PSR values are:" << "\n";
	areaList = big_area->getAreaNumList();
	for (current = areaList.begin(); current != areaList.end(); current++)
	{
		double Pden = big_area->getPden(*current);
		double ESR = resources->getEffectiveSweepRate(resourceNum, big_area->getTerrain(*current), big_area->getVegetation(*current));
		double PSR = Pden * ESR;
		cout << "Area Num: " << *current << "\t\tPden: " << Pden << "   \t\tESR: " << ESR << "  \t\tPSR: " << PSR << "\n";
	}
	cout << "\n";
}


/******************************************************************************
 * test()
 *
 * Tests functions of SearchManager that are not externally accessible.
 *
 * Author : Gareth Thompson
 */
void SearchManager::test(void)
{
        if (testmode) cout << "entering SearchManager::test()\n";
	cout << "Does getPSRCorrFacts() correctly return the PSR for a resource / area combination?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rs3.dat");
	LoadAreas("test_ar1.dat");
	if (testmode)
	{
		cout << "getPSRCorrFacts(1, 6): " << getPSRCorrFacts(1, 6) << "\n";
		cout << "getPSRCorrFacts(7, 3): " << getPSRCorrFacts(7, 3) << "\n";
	}
	if (FloatEqual(getPSRCorrFacts(1, 6), 0.00075625) && FloatEqual(getPSRCorrFacts(7, 3), 0.003))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does gtPSR(a,b) return true if SRU has greater PSR in area a than area b?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rs3.dat");
	LoadAreas("test_ar1.dat");
	if ((compResNum = 4) && gtPSR(3, 1) && (compResNum = 7) && gtPSR(1, 5) && (compResNum = 4) && gtPSR(1, 5))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does gtPSR(a,b) return false if SRU has PSR in area a less than or equal to that in area b?...";
	if ((compResNum = 4) && !gtPSR(1, 3) && (compResNum = 7) && !gtPSR(5, 1) && (compResNum = 4) && !gtPSR(5, 1)  &&
	    (compResNum = 1) && !gtPSR(1,5) && (compResNum = 1) && !gtPSR(1,1))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does gtPSR(a,b) return false if SRU compResNum or Areas a/b do not exist?...";
	if ((compResNum = 10) && !gtPSR(1, 1) && (compResNum = 1) && !gtPSR(10, 1) && (compResNum = 1) && !gtPSR(1, 10))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	/* Testing gtPDen() */
	cout << "Does gtPden(a,b) return true if Area a has greater Pden than area b?...";
	if (gtPden(5, 1) && gtPden(5, 3))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does gtPDen(a,b) return false if Area a had Pden less than or equal to Area b?...";
	if (!gtPden(1, 5) && !gtPden(3, 5) && !gtPden(1, 1))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does gtPDen(a,b) return false if either Area does not exist?...";
	if (!gtPden(1, 10) && !gtPden(10, 1))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	/* Testing sortList() */
	cout << "Does sortList correctly sort a vector of integers using gtPSR?...\n";
	vector<int> list;
	list.push_back(1);
	list.push_back(3);
	list.push_back(5);
	list.push_back(6);
	cout << "Output should be:\n";
	cout << "5*1*6*3*\n";
	cout << "Output is:\n";
	compResNum = 1;
	sortList(list, &SearchManager::gtPSR);
	PrintIntVector(list);
	cout << "\n";
	cout << "Output should be:\n";
	cout << "1*6*3*5*\n";
	cout << "Output is:\n";
	compResNum = 7;
	sortList(list, &SearchManager::gtPSR);
	PrintIntVector(list);
	cout << "\n";
	cout << "Does sortList correctly sort a vector of integers using gtPDen?...\n";
	cout << "Output should be:\n";
	cout << "6*5*1*3*\n";
	cout << "Output is:\n";
	sortList(list, &SearchManager::gtPden);
	PrintIntVector(list);
	cout << "\n";
	/* Testing CalculateOptimalAssignmentCharnCoop() */
	cout << "Does CalcOptimalAssignmentCharnCoop() produce an appropriate error message if the Resource to be used does not exist?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rs1.dat");
	LoadAreas("test_ar1.dat");
	cerr << "An error message should state that Resource 10 does not exist.\n";
	CalcOptimalAssignmentCharnCoop(10);
	cout << "Does CalcOptimalAssignmentCharnCoop() produce an appropriate error message if there are no areas to search?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rs1.dat");
	LoadAreas("test_ar2.dat");
	cerr << "An error message should state that there are no areas to search.\n";
	CalcOptimalAssignmentCharnCoop(1);
	cout << "Does CalcOptimalAssignmentCharnCoop() produce an error message if resource has a PSR of 0 in all areas?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsU.dat");
	LoadAreas("test_ar3.dat");
	cerr << "An error message should state that the SRU does not have a positive PSR in any area.\n";
	CalcOptimalAssignmentCharnCoop(1);
	cout << "Does CalcOptimalAssignmentCharnCoop() correctly split resource hours between SRUs if all have equal PSR?..." << endl;
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsQ.dat");
	LoadAreas("test_ar4.dat");
	CalcOptimalAssignmentCharnCoop(1);
	cout << "\nExpected Allocation is: \n";
	cout << "AREA NUMBER: -2\t\tRESOURCE HOURS: 36.36\n";
	cout << "AREA NUMBER: 1\t\tRESOURCE HOURS:  290.91\n";
	cout << "AREA NUMBER: 3\t\tRESOURCE HOURS:  72.73\n";
	cout << "AREA NUMBER: 5\t\tRESOURCE HOURS:  18.18\n";
	cout << "AREA NUMBER: 6\t\tRESOURCE HOURS:  581.82\n";
	cout << "\nActual allocation is: \n";
	resources->viewAssignments(1);
	SearchAndPrint(1);
	cout << "Does CalcOptimalAssignmentCharnCoop() correctly split resource hours between SRUs if there is insufficient time to drive PSRmax down to PSR2?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsR.dat");
	LoadAreas("test_ar5.dat");
	CalcOptimalAssignmentCharnCoop(2);
	cout << "\nExpected Allocation is: \n";
	cout << "AREA NUMBER: 1\t\tRESOURCE HOURS: 1.00\n";
	cout << "AREA NUMBER: 10\t\tRESOURCE HOURS: 2.00\n";
	cout << "\nActual allocation is: \n";
	resources->viewAssignments(2);
	SearchAndPrint(2);
	cout << "Does CalcOptimalAssignmentCharnCoop() correctly split resource hours between SRUs if PSR2 is 0?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsQ.dat");
	LoadAreas("test_ar7.dat");
	CalcOptimalAssignmentCharnCoop(1);
	cout << "\nExpected Allocation is: \n";
	cout << "AREA NUMBER: -2\t\tRESOURCE HOURS: 36.36\n";
	cout << "AREA NUMBER: 1\t\tRESOURCE HOURS:  290.91\n";
	cout << "AREA NUMBER: 3\t\tRESOURCE HOURS:  72.73\n";
	cout << "AREA NUMBER: 5\t\tRESOURCE HOURS:  18.18\n";
	cout << "AREA NUMBER: 6\t\tRESOURCE HOURS:  581.82\n";
	cout << "\nActual allocation is: \n";
	resources->viewAssignments(1);
	SearchAndPrint(1);
	cout << "Does CalcOptimalAssignmentCharnCoop() corectly assign resource hours for sample.area example?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsS.dat");
	LoadAreas("test_ar6.dat");
	cout << "\nExpected Allocation is: \n";
	cout << "AREA NUMBER: 1\t\tRESOURCE HOURS: 1.03\n";
	cout << "AREA NUMBER: 2\t\tRESOURCE HOURS: 0.92\n";
	cout << "AREA NUMBER: 3\t\tRESOURCE HOURS: 1.60\n";
	cout << "AREA NUMBER: 4\t\tRESOURCE HOURS: 1.84\n";
	cout << "AREA NUMBER: 5\t\tRESOURCE HOURS: 2.75\n";
	cout << "AREA NUMBER: 6\t\tRESOURCE HOURS: 1.86\n";
	CalcOptimalAssignment();
	cout << "Output from other algorithm is:\n";
	resources->viewAssignments(3);
	CalcOptimalAssignmentCharnCoop(3);
	cout << "\nActual allocation is: \n";
	resources->viewAssignments(3);
	SearchAndPrint(3);
	cout << "Does CalCOptimalAssignmentCharnCoop() correctly assign the resources in a general case?...\n";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsT.dat");
	LoadAreas("test_ar8.dat");
	cout << "\nExpected Allocation is: \n";
	cout << "AREA NUMBER: 1\t\tRESOURCE HOURS: 13.71\n";
	cout << "AREA NUMBER: 3\t\tRESOURCE HOURS: 13.71\n";
	cout << "AREA NUMBER: 10\t\tRESOURCE HOURS: 22.58\n";
	CalcOptimalAssignmentCharnCoop(3);
	cout << "\nActual allocation is: \n";
	resources->viewAssignments(3);
	SearchAndPrint(3);

	/* Testing CalcOptimalAssignmentNoCorrFacts() */
	cout << "Does CalcOptimalAssignmentNoCorrFacts() produce an error message if there are no SRUs?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadAreas("test_ar8.dat");
	CalcOptimalAssignmentNoCorrFacts();

	cout << "Does CalcOptimalAssignmentNoCorrFacts() produce an error message if there are no SRUs with positive Hours Available and Effective Sweep Rate?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsV.dat");
	LoadAreas("test_ar8.dat");
	CalcOptimalAssignmentNoCorrFacts();
	cout << "Does CalcOptimalAssignmentNoCorrFacts() produce an error message if there are no Areas to search?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rs1.dat");
	LoadAreas("test_ar2.dat");
	CalcOptimalAssignmentNoCorrFacts();

	cout << "Does CalcOptimalAssignmentNoCorrFacts produce an error message if there are no Areas with Pden greater than 0?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rs1.dat");
	LoadAreas("test_ar9.dat");
	CalcOptimalAssignmentNoCorrFacts();

	cout << "Does CalcOptimalAssignmentNoCorrFacts() correctly split resource hours between SRUs if there is insufficient time to drive pdenMax down to pden2?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsW.dat");
	LoadAreas("test_arA.dat");
	CalcOptimalAssignmentNoCorrFacts();
	cout << "\nExpected Allocation is: \n";
	cout << "AREA NUM: 1	RESOURCE 1: 10 hrs,	RESOURCE 2: 38.33 hrs" << "\n";
	cout << "AREA NUM: 2	RESOURCE 2: 11.67 hrs" << "\n";
	cout << "\nActual allocation is: \n";
	resources->viewAllAssignments();
	cout << "Does CalcOptimalAssignmentCharnCoop() correctly split resource hours between SRUs if PSR2 is 0?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsX.dat");
	LoadAreas("test_arB.dat");
	CalcOptimalAssignmentNoCorrFacts();
	cout << "\nExpected Allocation is: \n";
	cout << "AREA NUM: 1	RESOURCE 1: 100.00 hrs,	RESOURCE 2: 383.33 hrs" << "\n";
	cout << "AREA NUM: 2	RESOURCE 2: 116.67 hrs" << "\n";
	cout << "\nActual allocation is: \n";
	resources->viewAllAssignments();
	/* Testing UpdateAllPOAs() */
	cout << "Does UpdateAllPOAs produce an error message if there are no SRUs?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	UpdateAllPOAs();
	cout << "Does UpdateAllPOAs produce warnings if SRUs have resource-hours that have not been used?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsX.dat");
	LoadAreas("test_arB.dat");
	resources->addAssignment(1, Assignment(1, 100));
	resources->addAssignment(2, Assignment(1, 250));
	cerr << "An error message should be posted because SRU 2 has Resource-hours remaining\n";
	UpdateAllPOAs();
	cout << "Does UpdateAllPOAs produce a warnings if an Area does not exist?...\n";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsX.dat");
	LoadAreas("test_arB.dat");
	resources->addAssignment(1, Assignment(1, 100));
	resources->addAssignment(2, Assignment(20, 250));
	cerr << "An error message should be posted because SRU 2 is assigned to area 20, which doesn't exist.\n";
	UpdateAllPOAs();
	cout << "Does UpdateAllPOAs produce a warnings if an Area has a size of 0?...\n";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsX.dat");
	LoadAreas("test_arC.dat");
	resources->addAssignment(1, Assignment(1, 100));
	resources->addAssignment(2, Assignment(2, 250));
	cerr << "An error message should be posted because SRU 2 is assigned to area 2, which has a size of 0.\n";
	UpdateAllPOAs();
	cout << "Does UpdateAllPOAs produce a warnings if an SRU is assigned to search Rest of World?...\n";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rsX.dat");
	LoadAreas("test_arC.dat");
	resources->addAssignment(1, Assignment(-1, 100));
	cerr << "An error message should be posted because SRU 1 is assigned to search Rest of World.\n";
	UpdateAllPOAs();
	/* Testing Load Assignments() */
	cout << "Does LoadAssignments() work correctly?...";
	resources->deleteAllSRUs();
	big_area->deleteAllAreas();
	LoadResources("test_rs1.dat");
	LoadAreas("test_ar3.dat");
	LoadAssignments("test_as1.dat");
	resources->viewAllAssignments();
	cout << "Does LoadAssignments() crash if file does not exist?...";
	LoadAssignments("non-existentfile.dat");
}
