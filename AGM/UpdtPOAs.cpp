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
 * UpdtPOA.cpp
 *
 * Functions for calculating the new POA values using the current
 * assignment of SRUs to Areas.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 27/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.7 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include <vector>
#include "global.h"
#include "math.h"
#include "Assignmt.h"
#include "Srchman.h"

using namespace std;


/******************************************************************************
 * UpdateAllPOAs()
 *
 * Updates the POA values for each Area in the BigArea part of
 * the SearchManager object, using the current assignment of
 * SRUs in the Resources part of the SearchManager object.
 * (The update of POAs assumes that all searches are unsuccessful.)
 *
 * Author : Gareth Thompson
 */

void UpdateAllPOAs(SearchManager* searchMan)
{
	if (testmode) cout << "entering UpdtPOAs()\n";

	/* Obtain List of Resources */
	vector<int> SRUList = searchMan->GetResourceNumList();

	if (testmode) PrintIntVector(SRUList);

	/* Calculate results of searches for each SRU in turn */
	vector<int>::iterator currentSRU;
	for (currentSRU = SRUList.begin(); currentSRU != SRUList.end(); currentSRU++)
	{
		/* Obtain List of Assignments for this SRU */
		vector<Assignment> assignList = searchMan->GetAssignments(*currentSRU);

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

			/* Calculate POD for this Search */
			double areaEffectivelySwept = searchMan->GetEffectiveSweepRate(*currentSRU) *
						      currentAssignment->getResourceHours();

			if (testmode) cout << "Area effectively swept: " << areaEffectivelySwept << "\n";

			double coverage = areaEffectivelySwept /
					  searchMan->GetSize(currentAssignment->getAreaNum());

			if (testmode) cout << "Coverage: " << coverage << "\n";

			double POD = 1.0 - exp(-1 * coverage);

			if (testmode) cout << "POD: " << POD << "\n";

			/* Calculate new POA for Area after this search */
			double POA = (1-POD) * searchMan->GetPOA(currentAssignment->getAreaNum());

			if (testmode) cout << "New POA: " << POA << "\n";

			/* Store new POA for Area */
			searchMan->UpdatePOA(currentAssignment->getAreaNum(), POA);
		}
	}
}
