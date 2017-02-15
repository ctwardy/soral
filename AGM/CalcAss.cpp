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
 * CalcAss.cpp
 *
 * Functions for calculating and storing the optimal assignment
 * of Resources for the next sortie.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 23/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <vector>
#include "global.h"
#include "math.h"
#include "Srchman.h"
#include "Assignmt.h"
using namespace std;

/******************************************************************************
 * CalcOptimalAssignment()
 *
 * Calculates the optimal assignment of the SRUs in the Resources
 * part of the SearchManager object for searching the Areas
 * in the BigArea part of the SearchManager object, and stores
 * these assignments.  Any current assignments are first deleted.
 *
 * Author : Gareth Thompson
 */
void CalcOptimalAssignment(SearchManager* searchMan)
{
	if (testmode) cout << "entering calcOptimalAssignment()\n";
	/* Clear current assignment */
	searchMan->DeleteAllAssignments();

	/* Obtain a list of areas in descending order of Pden */
	vector<int> areaList = DescendingPdenList(searchMan);
	if (testmode)
	{
		cout << "Areas in Pden order:\n";
		PrintIntVector(areaList);
		cout << "\n";
	}
	/* Remove Rest of World (area number -1) from list, if present */
	vector<int>::iterator current = areaList.begin();
	while (current != areaList.end())
	{
		if (*current == -1)
		{
			areaList.erase(current);
			break;
		}
		current++;
	}
	if (testmode)
	{
		cout << "Areas in Pden order, with Rest of World removed:\n";
		PrintIntVector(areaList);
		cout << "\n";
	}
	/* If no Areas are present in list, no assignments can be made */
	if (areaList.size() == 0) return;

	double pdenMax;  /* Maximum Pden of Areas */
	double pden2;  /* 2nd highest Pden of Areas */
	vector<int>::iterator lastArea;  /* Last area in vector with equal-highest Pden */
	double totalSize;  /* Total size of Areas with equal-highest Pden */
	/* Initialise above data variables */
	lastArea = areaList.begin();
	pdenMax = searchMan->GetPden(*lastArea);
	totalSize = searchMan->GetSize(*lastArea);
	while (lastArea < areaList.end()-1 && FloatEqual(searchMan->GetPden(*(lastArea+1)), pdenMax))
	{
		lastArea++;
		totalSize += searchMan->GetSize(*lastArea);
	}
	if (lastArea < areaList.end() - 1)
	{
		/* All areas do not have equal Pden.  2nd highest Pden is next in list. */
		pden2 = searchMan->GetPden(*(lastArea+1));
	}

	double coverageActual;
	/*
	 * Continue to assign SRUs until no SRUs have resource-hours
	 * remaining for searching.
	 */
	while (searchMan->AnyHoursRemaining())
	{
		//searchMan->ViewAllAssignmentsTable();
		//cout << "Hours reaining -> " << searchMan->AnyHoursRemaining() << endl;
		/*if (testmode)
		{
			cout << "Last Area in vector to search: " << *lastArea << "\n";
			cout << "Maximum Pden: " << pdenMax << "\n";
			cout << "2nd highest Pden: " << pden2 << "\n";
			cout << "Total size of areas to search: " << totalSize << endl;
		}*/
		if (lastArea == areaList.end()-1)
		{
			/*
			 * All Areas have equal Pden and are to be searched with
			 * equal coverage.  The actual coverage is the maximum that
			 * can be achieved with the given SRUs.
			 */
			coverageActual = AreaEffectivelySweptRemaining(searchMan) / totalSize;
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
			double coverageAvailable = AreaEffectivelySweptRemaining(searchMan) / totalSize;
			if (testmode) cout << "Coverage Available: " << coverageAvailable << endl;
			/* Calculate the actual coverage to use */
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
			AssignSRUs(searchMan, (*areaToSearch), coverageActual);
		}
		//function not available from SearchManager
		//if (testmode) searchMan->ViewAllAssignments();
		/* Update required data variables for the next iteration */
		pdenMax = pden2;
		while (lastArea < areaList.end()-1 && FloatEqual(searchMan->GetPden(*(lastArea+1)), pdenMax))
		{
			lastArea++;
			totalSize += searchMan->GetSize(*lastArea);
		}
		if (lastArea < areaList.end() - 1)
		{
			/* All areas do not have equal Pden.  2nd highest Pden is next in list. */
			pden2 = searchMan->GetPden(*(lastArea+1));
		}
	}
}


/******************************************************************************
 * DescendingPdenList()
 *
 * Returns a vector containing the Area numbers from the
 * BigArea part of the SearchManager object in descending
 * order by the probability density of those areas.
 *
 * Author : Gareth Thompson
 */
vector<int> DescendingPdenList(SearchManager* searchMan)
{
	if (testmode) cout << "entering descendingPdenList()\n";
	/* Obtain list of Area numbers */
	vector<int> list = searchMan->GetAreaNumList();
	/* If list has size less than 2, it is already sorted */
	if (list.size() < 2)
	{
		return list;
	}
	/* Sort list by probability density: selection sort */
	vector<int>::iterator i, j, max;
	for (i = list.begin(); i<list.end()-1; i++)
	{
		/* Find maximum value from i to end of vector */
		max = i;
		for (j=i+1; j<list.end(); j++)
		{
			if (searchMan->GetPden(*j) > searchMan->GetPden(*max))
			{
				max = j;
			}
		}
		/* Place maximum value in next closest position to start of vector */
		Swap(i, max);
		if (testmode)
		{
			cout << "List: ";
			PrintIntVector(list);
			cout << "\n";
		}
	}
	return list;
}

/******************************************************************************
 * Swap()
 *
 * Swaps the values pointed to by two vector<int>::iterator objects.
 * It is assumed that both point to valid locations within a vector.
 *
 * Author : Gareth Thompson
 */
void Swap(vector<int>::iterator a, vector<int>::iterator b)
{
	if (testmode) cout << "entering Swap()\n";
	int temp = *a;
	*a = *b;
	*b = temp;
}

/******************************************************************************
 * AreaEffectivelySweptRemaining()
 *
 * Returns the maximum Area Effectively Swept that can be achieved with
 * the unassigned parts of the Resources in the SearchManager argument.
 *
 * Author : Gareth Thompson
 */
double AreaEffectivelySweptRemaining(SearchManager* searchMan)
{
	if (testmode) cout << "entering AreaEffectivelySweptRemaining()\n";
	vector<int> resourcesList = searchMan->GetResourceNumList();
	double areaEffecSweptRem = 0.0;
	vector<int>::iterator current;
	for (current = resourcesList.begin(); current != resourcesList.end(); current++)
	{
		/*
		 * Area effectively swept remaining for a resource is the product
		 * of its Effective Sweep Rate and Resource Hours Remaining.
		 */
		areaEffecSweptRem += searchMan->GetEffectiveSweepRate(*current) *
				     searchMan->GetHoursRemaining(*current);
	}
	return areaEffecSweptRem;
}

/******************************************************************************
 * AssignSRUs()
 *
 *
 * Assigns SRUs to search the area with the specified area number using the
 * given coverage.  Returns true if the assignment is successful; false if
 * there are insufficient resource-hours available to achieve this coverage.
 *
 * Author : Gareth Thompson
 */
bool AssignSRUs(SearchManager* searchMan, int areaNum, double coverage)
{
	if (testmode) cout << "entering AssignSRUs(" << "?, " << areaNum << ", " << coverage << ")\n";
	/* Calculate the Area Effectively Swept to achieve required coverage */
	double areaToEffectivelySweep = coverage * searchMan->GetSize(areaNum);
	/* Get list of Resource Numbers available */
	vector<int> resourceList = searchMan->GetResourceNumList();
	vector<int>::iterator current = resourceList.begin();
	/*
	 * Continue to assign resources until the
	 * areaEffectivelySwept is reduced to 0 or
	 * there are no more SRUs to give assignments to.
	 */
	while (FloatLess(0.0, areaToEffectivelySweep) && current != resourceList.end())
	{
		if (searchMan->AreThereHoursRemaining(*current))
		{
			/*
			 * This SRU has further Resource-hours available for
			 * searching.  It can be assigned to search this area.
			 */

			/* Calculate the maximum area that this SRU can effectively sweep */
			double maxAreaEffecSweep = searchMan->GetEffectiveSweepRate(*current) *
						   searchMan->GetHoursRemaining(*current);

			if (FloatLess(maxAreaEffecSweep, areaToEffectivelySweep))
			{
				/*
				 * This SRU cannot sweep all the required area.
				 * Assign all its hours to sweep this area.
				 */
				searchMan->AddAssignment((*current), Assignment(areaNum, searchMan->GetHoursRemaining(*current)));
				/* Reduce areaToEffectivelySweep by the amount that has been swept */
				areaToEffectivelySweep -= maxAreaEffecSweep;
			}
			else
			{
				/*
				 * This SRU can sweep all the required area.
				 * Assign sufficient Resource Hours to do so.
				 */
				double hoursToSweep = areaToEffectivelySweep / searchMan->GetEffectiveSweepRate(*current);
				searchMan->AddAssignment((*current), Assignment(areaNum, hoursToSweep));
				/* areaToEffectivelySweep is now reduced to 0 */
				areaToEffectivelySweep = 0.0;
			}
		}

		/* The next SRU in the list will be assigned in the next iteration */
		current++;
	}
	/* Assignment is successful if areaToEffectivelySweep is reduced to 0 */
	return FloatEqual(areaToEffectivelySweep, 0.0);
}
