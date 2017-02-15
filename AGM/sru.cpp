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
 * Resource.cpp
 *
 * Resources stores details of all available SRUs (including their assignments
 * to search areas).  It is possible to add, delete, modify and view SRUs;
 * add, view and clear assignments to areas; and add and delete correction
 * factors.  Resources also provides necessary data about the SRUs stored to
 * other modules in the program.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 02/04/01 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
*/
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "Err_mngr.h"
#include "InputFil.h"
#include "Assignmt.h"
#include "Resource.h"
using namespace std;
/******************************************************************************
 * Resources::SRU::setResourceNum()
 *
 * If the integer argument is a valid Resource Number,
 * sets myResourceNum to this value and returns true.
 *
 * Otherwise, leaves myResourceNum unmodified and returns
 * false.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::setResourceNum(int resourceNum)
{
	if (testmode) cout << "entering Resources::SRU::setResourceNum(" << resourceNum << ")\n";
	if (resourceNum >= DataLimits::resourceNum_min &&
	    resourceNum <= DataLimits::resourceNum_max)
	{
		/* Resource Number valid */
		myResourceNum = resourceNum;
		return true;
	}
	else
	{
		/* Resource Number invalid */
		return false;
	}
}

/******************************************************************************
 * Resources::SRU::setPOD()
 *
 * If the double argument is a valid POD, sets myPOD to this
 * value and returns true.
 *
 * Otherwise, leaves myPOD unmodified and returns false.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::setPOD(double POD)
{
	if (testmode) cout << "entering Resources::SRU::setPOD(" << POD << ")\n";
	if (POD >= DataLimits::POD_min &&
	    POD <= DataLimits::POD_max)
	{
		/* POD valid */
		myPOD = POD;
		return true;
	}
	else
	{
		/* POD invalid */
		return false;
	}
}

/******************************************************************************
 * Resources::SRU::setESW()
 *
 * If the double argument is a valid ESW, sets myESW to this
 * value and returns true.
 *
 * Otherwise, leaves myESW unmodified and returns false.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::setESW(double ESW)
{
	if (testmode) cout << "entering Resources::SRU::setESW(" << ESW << ")\n";
	if (ESW >= DataLimits::ESW_min &&
	    ESW <= DataLimits::ESW_max)
	{
		/* ESW valid */
		myESW = ESW;
		return true;
	}
	else
	{
		/* ESW invalid */
		return false;
	}
}

/******************************************************************************
 * Resources::SRU::setSpeed()
 *
 * If the double argument is a valid Speed, sets mySpeed to this
 * value and returns true.
 *
 * Otherwise, leaves mySpeed unmodified and returns false.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::setSpeed(double speed)
{
	if (testmode) cout << "entering Resources::SRU::setSpeed(" << speed << ")\n";
	if (speed >= DataLimits::speed_min &&
	    speed <= DataLimits::speed_max)
	{
		/* Speed valid */
		mySpeed = speed;
		return true;
	}
	else
	{
		/* Speed invalid */
		return false;
	}
}

/******************************************************************************
 * Resources::SRU::setHoursAvail()
 *
 * If the integer argument is a valid value for hours available,
 * sets myHoursAvailable to this value and returns true.
 *
 * Otherwise, leaves myHoursAvailable unmodified and returns false.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::setHoursAvail(int hoursAvail)
{
	if (testmode) cout << "entering Resources::SRU::setHoursAvail(" << hoursAvail << ")\n";
	if (hoursAvail >= DataLimits::hoursAvailable_min &&
	    hoursAvail <= DataLimits::hoursAvailable_max)
	{
		/* Hours available valid */
		myHoursAvail = hoursAvail;
		return true;
	}
	else
	{
		/* Hours available invalid */
		return false;
	}
}

/******************************************************************************
 * Resources::SRU::isCorrectionFactorSet()
 *
 * Returns true if the terrain and vegetation values are valid
 * and a correction factor has been set for the specified
 * combination of vegetation and terrain.
 *
 * Otherwise, returns false.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::isCorrectionFactorSet(int terrain, int vegetation)
{
	if (testmode) cout << "entering Resources::SRU::isCorrectionFactorSet(" << terrain << ", " << vegetation << ")\n";
	if (DataLimits::isValidTerrain(terrain) && DataLimits::isValidVegetation(vegetation))
	{
		/*
		 * If the value stored for the specified combination of
		 * terrain and vegetation is equal to UNSPECIFIED then a
		 * correction factor has not been set.
		 */
		if (testmode) printf("Correction factor: %.20f, Unspecified value: %.20f", myCorrectionFactors[terrain][vegetation], UNSPECIFIED);
		return (!(myCorrectionFactors[terrain][vegetation] == UNSPECIFIED));
	}
	else
	{
		/* terrain and/or vegetation values are invalid */
		return false;
	}
}

/******************************************************************************
 * Resources::SRU::setCorrectionFactor()
 *
 * Sets the correction factor for this SRU for the specified terrain and vegetation.
 *
 * If terrain and vegetation values are valid (within the limits specified in
 * class DataLimits), and the correction factor is in the required range (also
 * specified in class DataLimits) then the correction factor is set and true is
 * returned.
 *
 * If terrain and/or vegetation values are invalid, or the correction factor is not
 * in the desired range, the correction factor cannot be set, and false is returned.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::setCorrectionFactor(int terrain, int vegetation, double factor)
{
	if (testmode) cout << "entering Resources::SRU::setCorrectionFactor(" << terrain << ", " << vegetation << ", " << factor << ")\n";
	if (!DataLimits::isValidTerrain(terrain) || !DataLimits::isValidVegetation(vegetation))
	{
		/* terrain and/or vegetation values are invalid */
		return false;
	}
	else
	{
		if (isValidCorrectionFactor(factor))
		{
			/* Correction factor is valid */
			myCorrectionFactors[terrain][vegetation] = factor;
			return true;
		}
		else
		{
			/* Correction factor is invalid */
			return false;
		}
	}
}

/******************************************************************************
 * Resources::SRU::getCorrectionFactor()
 *
 * Returns the correction factor for this SRU for the specified
 * terrain and vegetation.
 *
 * If the terrain and vegetation values are valid then the relevant
 * correction factor is returned:
 * - If a correction factor has been defined for this combination
 *   of terrain and vegetation values, it is returned.
 * - Otherwise, default correction factor 1.0 is returned.
 *
 * If the terrain and/or vegetation valuea are invalid, no such correction
 * factor exists and the return value is undefined.
 *
 * Author : Gareth Thompson
 */
double Resources::SRU::getCorrectionFactor(int terrain, int vegetation)
{
	if (testmode) cout << "entering Resources::SRU::getCorrectionFactor(" << terrain << ", " << vegetation << ")\n";
	if (DataLimits::isValidTerrain(terrain) && DataLimits::isValidVegetation(vegetation))
	{
		if (isCorrectionFactorSet(terrain, vegetation))
		{
			/* Correction factor has been specified */
			if (testmode) cout << "Correction factor specified.\n";
			return myCorrectionFactors[terrain][vegetation];
		}
		else
		{
			/* Correction factor has not been specified */
			if (testmode) cout << "Correction factor not specified.\n";
			return 1.0;
		}
	}
	else
	{
		/* terrain and/or vegetation values are invalid */
		return -1.0;  //undefined return value
	}
}

/******************************************************************************
 * Resources::SRU::deleteCorrectionFactor()
 *
 * Deletes the correction factor for this SRU for the specified terrain
 * and vegetation.
 *
 * If the terrain and vegetation values are valid and a correction factor
 * is set for that combination of terrain and vegetation, the correction
 * factor is deleted and true is returned.
 *
 * Otherwise, false is returned.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::deleteCorrectionFactor(int terrain, int vegetation)
{
	if (testmode) cout << "entering Resources::SRU::deleteCorrectionFactor(" << terrain << ", " << vegetation << ")\n";
	if (isCorrectionFactorSet(terrain, vegetation))
	{
		/*
		 * A correction factor has been set.  Delete
		 * it by indicating that the correction factor
		 * is now UNSPECFIED.
		 */
		myCorrectionFactors[terrain][vegetation] = UNSPECIFIED;
		return true;
	}
	else
	{
		/* No correction factor is set */
		return false;
	}
}

/******************************************************************************
 * Resources::SRU::deleteCorrectionFactors()
 *
 * Deletes all correction factors for this SRU.
 *
 * Author : Gareth Thompson
 */
void Resources::SRU::deleteCorrectionFactors(void)
{
	if (testmode) cout << "entering Resources::SRU::deleteCorrectionFactors()\n";
	int terrain, vegetation;
	/*
	 * Delete correction factor for each possible
	 * combination of terrain and vegetation.
	 */
	for (terrain=DataLimits::terrain_min; terrain<=DataLimits::terrain_max; terrain++)
	{
		for (vegetation=DataLimits::vegetation_min; vegetation<=DataLimits::vegetation_max; vegetation++)
		{
			deleteCorrectionFactor(terrain, vegetation);
		}
	}
}

/******************************************************************************
 * Resources::SRU::viewCorrectionFactors()
 *
 * Prints all correction factors for this SRU, in a table, to standard output.
 *
 * Author : Gareth Thompson
 */
void Resources::SRU::viewCorrectionFactors(void)
{
	if (testmode) cout << "entering Resources::SRU::viewCorrectionFactors()\n";
	/* Output headings for table */
	cout << "Terrain   Vegetation     Correction\n";
	cout << "		           Factor\n";
	cout << "===================================\n";
	/* Output all correction factors that have been specified */
	int terrain, vegetation;
	for (terrain=DataLimits::terrain_min; terrain<=DataLimits::terrain_max; terrain++)
	{
		for (vegetation=DataLimits::vegetation_min; vegetation<=DataLimits::vegetation_max; vegetation++)
		{
			if (isCorrectionFactorSet(terrain, vegetation))
			{
				printf("  %3d          ", terrain);
				printf("%1d            ", vegetation);
				printf("%6.3f\n", getCorrectionFactor(terrain, vegetation));
			}
		}
	}
}

/******************************************************************************
 * Resources::SRU::addAssignment()
 *
 * Adds theAssignment to myAssignments.
 *
 * If theAssignment.getResourceHours() is non-negative, and not greater than the
 * Resource-hours remaining for this SRU (according to the precision defined
 * by FloatLess()), theAssignment is added to myAssignments and true is
 * returned.
 *
 * The following rules are followed when adding Assignments:
 * - Adding an Assignment with Resource Hours equal to 0 (according to the
 *   precision defined in FloatEqual()) does not change myAssignments.
 * - If the SRU already has an Assignment with the Area Number of the new
 *   Assignment, the Resource Hours of the new Assignment are added to those
 *   of the old Assignment. The data is stored as one Assignment, rather than
 *   two.
 *
 * If theAssignment.getResourceHours() is negative, or greater than the
 * resource-hours remaining for the SRU, the assignment is not added and
 * false is returned.
 *
 * NOTE: addAssignment does not provide a check to ensure that the area
 *       number is valid.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::addAssignment(const Assignment& theAssignment)
{
	if (testmode) cout << "entering Resources::SRU::addAssignment()\n";
	if (testmode)
	{
		double hoursRem = getHoursRemaining();
		double hoursAssign = theAssignment.getResourceHours();
		printf("Resource hours remaining: %.20f\n", hoursRem);
		printf("Resource hours to assign: %.20f\n", hoursAssign);
	}
	if (theAssignment.getResourceHours() < 0)
	{
		/* Resource hours negative - assignment cannot be added */
		return false;
	}
	if (FloatEqual(theAssignment.getResourceHours(), 0))
        {
	        /* Assignment has Resource Hours of 0, so no modification is made. */
	        return true;
	}
	if (FloatLess(getHoursRemaining(), theAssignment.getResourceHours()))
	{
		/* Insufficient resource hours available for assignment - assignment cannot be added */
		if (testmode) cout << "Assignment impossible\n";
		return false;
	}
	/* Check if SRU already has an Assignment with that Area Number */
	vector<Assignment>::iterator current;
	for (current = myAssignments.begin(); current != myAssignments.end(); current++)
	{
	        if (current->getAreaNum() == theAssignment.getAreaNum())
		{
		        current->setResourceHours(current->getResourceHours()+theAssignment.getResourceHours());
			return true;
		}
	}
	/* None of the special cases apply - add the assignment */
	myAssignments.push_back(theAssignment);
	return true;
}

/******************************************************************************
 * Resources::SRU::deleteAssignment()
 *
 * Deletes the assignment with the specified Area Number from the SRU.
 * (Note that an SRU should only ever have one assignment with the
 * specified area number.)
 *
 * If the SRU has an assignment with the specified area number, it is
 * deleted and true is returned.  Otherwise, no change is made and false
 * is returned.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::deleteAssignment(int areaNum)
{
	if (testmode) cout << "entering Resources::SRU::deleteAssignment(" << areaNum << ")\n";
	/* Search for an assignment with the specified area number */
	vector<Assignment>::iterator current;
	for (current = myAssignments.begin(); current != myAssignments.end(); current++)
	{
		if (current->getAreaNum() == areaNum)
		{
			/* SRU has an assignment with specified area number: delete it. */
			myAssignments.erase(current);
			return true;
		}
	}
	/* SRU does not have an assignment with the specified area number */
	return false;
}


/******************************************************************************
 * Resources::SRU::sortAssignAreaNum()
 *
 * Sorts the Assignments for this SRU into ascending order
 * by Area Number.  If getAssignments() is then called,
 * the vector<Assignment> returned will be sorted into
 * ascending order by Area Number.
 *
 * Author : Gareth Thompson
 */
void Resources::SRU::sortAssignAreaNum(void)
{
	if (testmode) cout << "entering Resources::SRU::sortAssignAreaNum()\n";
	/*
	 * ltAreaNum compares Assignments using Area Number.
	 * The standard sort() function sorts Assignments
	 * using ltAreaNum to compare Assignments.
	 */
	sort(myAssignments.begin(), myAssignments.end(), Assignment::ltAreaNum());
}

/******************************************************************************
 * Resources::SRU::getHoursRemaining()
 *
 * Returns the number of resource-hours available for this SRU
 * that have not yet been assigned for searching.
 *
 * This value may be slightly negative, because of the
 * non-zero floating-point precision defined by FloatLess().
 * (It is possible to assign more hours to a resource than
 * are available, provided that the assignments do not exceed
 * the hours available by more than the defined precision.)
 *
 * It is best to call hoursRemaining() first to check that there
 * are hours remaining, before calling getHoursRemaining to
 * determine the actual number remaining.
 *
 * Author : Gareth Thompson
 */
double Resources::SRU::getHoursRemaining(void)
{
	if (testmode) cout << "entering Resources::SRU::getHoursRemaining()\n";
	return (getHoursAvail() - getHoursAssigned());
}

/******************************************************************************
 * Resources::SRU::hoursRemaining()
 *
 * Returns true if there are resource-hours available for this
 * SRU that have not yet been assigned for searching.
 *
 * If the Resource Hours remaining for this SRU are greater
 * than 0 (according to the precision defined by FloatLess)
 * true is returned.  Otherwise, false is returned.
 *
 * Author : Gareth Thompson
 */
bool Resources::SRU::hoursRemaining(void)
{
	if (testmode) cout << "entering Resources::SRU::anyHoursRemaining()\n";
	return (FloatLess(0.0, getHoursRemaining()));
}

/******************************************************************************
 * getHoursAssigned()
 *
 * Returns the number of resource-hours for this SRU that
 * have been assigned for searching.
 *
 * Author : Gareth Thompson
 */
double Resources::SRU::getHoursAssigned(void)
{
	if (testmode) cout << "entering Resources::SRU::getHoursAssigned()\n";
	double resHours = 0.0;
	vector<Assignment>::iterator current;
	for (current = myAssignments.begin(); current != myAssignments.end(); current++)
	{
		resHours += current->getResourceHours();
	}
	return resHours;
}

/******************************************************************************
 * getEffectiveSweepRate()
 *
 * Returns the effective Sweep Rate for this SRU (km^2/hr).
 *
 * If terrain and vegetation arguments are given, and they are valid values
 * the effective sweep rate of the SRU for that combination of terrain and
 * vegetation is returned.  (This is the product of ESW, speed, and the
 * correction factor for that terrain.)
 * If the SRU does not have a correction factor for that combination of
 * vegetation and terrain, it is assumed to be 1.
 *
 * If terrain and vegetation arguments are not given, or either is an
 * invalid value, then the effective sweep rate of the SRU, ignoring
 * correction factors, is returned.  This is the product of ESW and speed.
 *
 * Author : Gareth Thompson
 */
double Resources::SRU::getEffectiveSweepRate(int terrain, int vegetation)
{
	if (testmode) cout << "entering Resources::SRU::getEffectiveSweepRate" << terrain << ", " << vegetation << ")\n";
	if (DataLimits::isValidTerrain(terrain) && DataLimits::isValidVegetation(vegetation))
	{
		/*
		 * Valid terrain and vegetation specified.  Return Effective
		 * Sweep Rate, using correction factors, in km^2/hr.
		 */
		return myESW * mySpeed * getCorrectionFactor(terrain, vegetation) / 1000;
	}
	else
	{
		/*
		 * terrain and vegetation values have not been specified or
		 * are invalid.  Return Effective Sweep Rate, ignoring
		 * correction factors, in km^2/hr.
		 */
		return myESW * mySpeed/1000;
	}
}

/******************************************************************************
 * getSRUString()
 *
 * Returns the data stored for this SRU as a string,
 * in the format:
 * [Resource number], [Resource Type], [POD], [ESW], [Speed], [Resource-hours available], [correction table]
 *
 * where [correction table] is of the form:
 * ( ([terrain1]/[vegetation1]/[correction_factor1]) ([terrain2]/[vegetation2]/[correction_factor2]) ... )
 *
 * Author : Gareth Thompson
 */
string Resources::SRU::getSRUString(void)
{
	if (testmode) cout << "entering getSRUString()\n";
	char tempStr[20];  //temporary storage for producing formatted output
	std::ostringstream ostr; //12/1/03 ASO changed from ostrstream ostr; to std::ostringstream for gcc 3.1.1 compliance
	ostr << myResourceNum << ", " << myResourceType << ", ";
	/*
	 * Output POD, ESW and Speed with 2 digits after
	 * decimal point.
	 */
	sprintf(tempStr, "%.2f", myPOD);
	ostr << tempStr << ", ";
	sprintf(tempStr, "%.2f", myESW);
	ostr << tempStr << ", ";
	sprintf(tempStr, "%.2f", mySpeed);
	ostr << tempStr << ", ";
	ostr << myHoursAvail << ", ";
	/* Include all correction factors that have been specified */
	ostr << "( ";
	int terrain, vegetation;
	for (terrain=DataLimits::terrain_min; terrain<=DataLimits::terrain_max; terrain++)
	{
		for (vegetation=DataLimits::vegetation_min; vegetation<=DataLimits::vegetation_max; vegetation++)
		{
			if (isCorrectionFactorSet(terrain, vegetation))
			{
				ostr << "(" << terrain << "/" << vegetation << "/";
				sprintf(tempStr, "%.3f", getCorrectionFactor(terrain, vegetation));
				ostr << tempStr << ") ";
			}
		}
	}
	ostr << ")";
	/* Null-terminate ostr */
	ostr << '\0';
	if (testmode) cout << "SRU String is: " << ostr.str();
	return ostr.str();
}
