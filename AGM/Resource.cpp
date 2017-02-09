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
 *----------------------------------------------------------------------------
 * GT  | 21/04/01 |  2  | Updated.  Major changes in functionality for stage
 *     |          |     | 2.  Type of POD changed to double.  Many functions
 *     |          |     | modified to better interact with user.
 *----------------------------------------------------------------------------
 * GT  | 27/04/01 |  3  | Updated.  Now stores assignments using class
 *     |          |     | Assignment.
 *----------------------------------------------------------------------------
 * GT  | 07/05/01 |  4  | Updated.  Now stores only one assignment to each
 *     |          |     | Area for each SRU.  Does not store assignments
 *     |          |     | with Resource Hours 0.
 *----------------------------------------------------------------------------
 * GT  | 25/05/01 |  5  | Updated.  Now handles correction factors.
 *----------------------------------------------------------------------------
 * GT  | 28/05/01 |  6  | Updated.  Error handling and input/output fixed.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 6.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */


//#include <string>
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
 * getResourceNumList()
 *
 * Returns a vector<int> containing the set of Resource
 * Numbers of SRUs in SRUlist, in ascending order.
 * Because all functions of Resources access SRUs via
 * Resource Number, this list is needed to enable external
 * parts of the program to access the SRUs that are
 * stored in this Resources object.
 * Note that the number of SRUs is equal to the size of
 * this list.
 *
 * Author : Gareth Thompson
 */

vector<int> Resources::getResourceNumList(void)
{
	if (testmode) cout << "entering Resources::getResourceNumList()\n";

	/* Sort SRUlist into ascending order by Resource Number */
	sortResNum();

	vector<int> list;
	vector<SRU>::iterator current;

	for (current = SRUlist.begin(); current != SRUlist.end(); current++)
	{
		list.push_back(current->getResourceNum());
	}

	return list;

}



/******************************************************************************
 * loadSRUs()
 *
 * Obtains SRUs from a datafile with a specified filename
 * and appends them to SRUlist.
 *
 * If a file with the specified filename cannot be opened,
 * a warning is posted.
 *
 * If the file can be opened, each record is read from the
 * file in turn.  If this record is of the correct format,
 * and there is no existing SRU with the specified Resource
 * Number, an SRU with the given data is appended to SRUlist.
 *
 * If an SRU with the specified Resource Number already exists,
 * a warning is posted and no SRU is added.
 *
 * If the data read is of the incorrect format, all or part of
 * the data is ignored, a warning is posted and no SRU is added.
 *
 * Returns true if 1 or more SRUs are added to SRUlist,
 * false otherwise.
 *
 * Author : Gareth Thompson
 */

bool Resources::loadSRUs(string filename)
{
	if (testmode) cout << "entering Resources::loadSRUs(" << filename << ")\n";

	InputFile in;
	string record;

	if (!in.open(filename))
	{
		error_manager->PostError(WARNING_OPTION, "File "+filename+" could not be opened.  No Resources data loaded.",  "Resources::loadSRUs() - File could not be opened");
		return false;
	}

	bool added = false;  //	no SRUs have been added

	while (in.getRecord(record))
	{
		if (testmode) cout << "LINE: " << in.lastRecLine() << " RECORD: " << record << endl;

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
		 * Having extracted the pieces of data from the
		 * record, we now create a new SRU in SRUlist
		 * using this data.
		 */
		if (data.size() != 7)
		{
			/* Incorrect number of tokens in this record */
			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - This line does not have 7 pieces of data specified.  SRU ignored.", "Resources::loadSRUs() - Less or more than 7 comma-separated tokens  on line of file.");
		}
		else
		{
			/* Correct number of tokens in this record. */

			/* Create new SRU object to insert into SRUlist */
			SRU sruTemp;

			/* Check if first piece of data is a valid Resource Number */
			if (!IsInt(data[0]))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Resource Number "+data[0]+" is not a valid integer.  SRU ignored.", "Resources::loadSRUs() - data[0] does not contain a valid integer.");
				continue;
			}

			int resourceNum = atoi(data[0].c_str());
			if (!sruTemp.setResourceNum(resourceNum))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Resource Number "+data[0]+" is not between "+ConvertToStr((int)DataLimits::resourceNum_min)+" and "+ConvertToStr((int)DataLimits::resourceNum_max)+".  SRU ignored.", "Resources::loadSRUs() - data[0] does not contain a valid Resource Number.");
				continue;
			}

			/* No checking necessary for Resource Type */
			sruTemp.setResourceType(data[1]);

			/* Check if third piece of data is a valid POD */
			if (!IsFloat(data[2]))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - POD "+data[2]+" is not a valid floating point number.  SRU ignored.", "Resources::loadSRUs() - data[2] does not contain a valid floating point number.");
				continue;
			}

			double POD = atof(data[2].c_str());
			if (!sruTemp.setPOD(POD))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - POD "+data[2]+" is not between "+ConvertToStr(DataLimits::POD_min)+" and "+ConvertToStr(DataLimits::POD_max)+".  SRU ignored.", "Resources::loadSRUs() - data[2] does not contain a valid POD.");
				continue;
			}

			/* Check if fourth piece of data is a valid ESW */
			if (!IsFloat(data[3]))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - ESW "+data[3]+" is not a valid floating point number.  SRU ignored.", "Resources::loadSRUs() - data[3] does not contain a valid floating point number.");
				continue;
			}

			double ESW = atof(data[3].c_str());
			if (!sruTemp.setESW(ESW))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - ESW "+data[3]+" is not between "+ConvertToStr(DataLimits::ESW_min)+" and "+ConvertToStr(DataLimits::ESW_max)+".  SRU ignored.", "Resources::loadSRUs() - data[3] does not contain a valid ESW.");
				continue;
			}

			/* Check if fifth piece of data is a valid Speed */
			if (!IsFloat(data[4]))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Speed "+data[4]+" is not a valid floating point number.  SRU ignored.", "Resources::loadSRUs() - data[4] does not contain a valid floating point number.");
				continue;
			}

			double speed = atof(data[4].c_str());
			if (!sruTemp.setSpeed(speed))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Speed "+data[4]+" is not between "+ConvertToStr(DataLimits::speed_min)+" and "+ConvertToStr(DataLimits::speed_max)+".  SRU ignored.", "Resources::loadSRUs() - data[4] does not contain a valid Speed.");
				continue;
			}

			/* Check if sixth piece of data is a valid number of Hours Available */
			if (!IsInt(data[5]))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Hours Available "+data[5]+" is not a valid integer.  SRU ignored.", "Resources::loadSRUs() - data[5] does not contain a valid integer.");
				continue;
			}

			int hoursAvail = atoi(data[5].c_str());
			if (!sruTemp.setHoursAvail(hoursAvail))
			{
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Hours Available "+data[5]+" is not between "+ConvertToStr((int)DataLimits::hoursAvailable_min)+" and "+ConvertToStr((int)DataLimits::hoursAvailable_max)+".  SRU ignored.", "Resources::loadSRUs() - data[5] does not contain a valid Hours Available value.");
				continue;
			}

			/* Check if SRU can be added */
			if (!addSRU(sruTemp))
			{
				/* SRU could not be added because there is already an SRU with the specified Resource Number. */
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - An SRU with Resource Number "+ConvertToStr(resourceNum)+" already exists.  SRU ignored.", "Resources::loadSRUs() - addSRU(sruTemp) returned false; SRU could not be added.");
				continue;
			}

			added = true;		//SRU added

			/* Obtain iterator which points to this SRU */
			vector<SRU>::iterator SRUiter = findSRU(resourceNum);

			/* Now add correction factors */

			/* Check that correction factor string has leading/trailing brackets, and remove them */
			string correctionString;
			if (data[6][0] == '(' && data[6][data[6].size()-1] == ')')
			{
				correctionString = data[6].substr(1, data[6].size()-2);
				if (testmode) cout << "Correction factor string: " << correctionString << "\n";
			}
			else
			{
				/* Correction factor string does not have leading/trailing brackets */
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Correction factors string is not correctly parenthesised.  All correction factors for this SRU ignored.", "Resources::loadSRUs() - data[6] does not have leading and trailing brackets.");
				continue;
			}

			if (testmode) cout << "Correction factor string: " << correctionString << "\n";

			/* Tokenise correction factor string at '(' to obtain a separate string for each correction factor. */
			vector<string> correctionData = Tokenise(correctionString, '(');

			if (testmode)
			{
				cout << "Split Correction factor string: ";
				PrintStringVector(correctionData);
			}

			/* Strip leading and trailing whitespace from each token */
			correctionData = StripWhite(correctionData);

			/* Check if first element (the part of the correction String before the first '(') is blank */
			if (correctionData[0].size() != 0)
			{
				/* First element is an error */
				error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Correction factor "+correctionData[0]+" does not have a leading bracket.  Correction factor ignored.", "Resources::loadSRUs() - correctionsData[0] is not blank");
			}

			/* Ignore first element */
			correctionData.erase(correctionData.begin());

			if (testmode)
			{
				cout << "Correction factor string without first element: ";
				PrintStringVector(correctionData);
			}

			/* Add each correction factor to SRU in turn */
			vector<string>::iterator current;
			for (current = correctionData.begin(); current != correctionData.end(); current++)
			{
				/* Check that correction factor also has a trailing bracket, and remove it */
				string correctionFactor;
				if ((*current)[current->size()-1] == ')')
				{
					correctionFactor = current->substr(0, current->size()-1);
				}
				else
				{
					error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Correction factor ("+(*current)+" does not have a trailing bracket.  Correction factor ignored.", "Resources::loadSRUs() - (*current)[current->size()-1] is not ')'");
					continue;
				}

				/*
				 * Tokenise correctionFactor at '/' to obtain separate terrain/vegetation/factor
				 * values for this correction factor.
				 */
				vector<string> correctionNumbers = Tokenise(correctionFactor, '/');

				if (testmode)
				{
					cout << "Data for correction factor: ";
					PrintStringVector(correctionNumbers);
				}

				/* Strip leading/trailing whitespace from each number */
				correctionNumbers = StripWhite(correctionNumbers);

				/* Check that we have correct number of pieces of data for this correction factor (3). */
				if (correctionNumbers.size() != 3)
				{
					error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Correction factor ("+(*current)+" does not have 3 pieces of data.  Correction factor ignored.", "Resources::loadSRUs() - Less or more than 3 / separated tokens in a correction factor.");
					continue;
				}

				/* Check that first piece of data for this correction factor is a valid terrain value. */
				if (!IsInt(correctionNumbers[0]))
				{
					error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Terrain "+correctionNumbers[0]+" for correction factor ("+(*current)+" is not a valid integer.  Correction factor ignored.", "Resources::loadSRUs() - correctionNumbers[0] is not a valid integer.");
					continue;
				}

				int terrain = atoi(correctionNumbers[0].c_str());
				if (!DataLimits::isValidTerrain(terrain))
				{
					error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Terrain "+correctionNumbers[0]+" for Correction factor ("+(*current)+" is not between "+ConvertToStr((int)DataLimits::terrain_min)+" and "+ConvertToStr((int)DataLimits::terrain_max)+".  Correction factor ignored.", "Resources::loadSRUs() - correctionNumbers[0] does not contain a valid terrain value.");
					continue;
				}

				/* Check that second piece of data for correction factor is a valid vegetation value. */
				if (!IsInt(correctionNumbers[1]))
				{
					error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Vegetation "+correctionNumbers[1]+" for correction factor ("+(*current)+" is not a valid integer.  Correction factor ignored.", "Resources::loadSRUs() - correctionNumbers[1] is not a valid integer.");
					continue;
				}

				int vegetation = atoi(correctionNumbers[1].c_str());
				if (!DataLimits::isValidVegetation(vegetation))
				{
					error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Vegetation "+correctionNumbers[1]+" for Correction factor ("+(*current)+" is not between "+ConvertToStr((int)DataLimits::vegetation_min)+" and "+ConvertToStr((int)DataLimits::vegetation_max)+".  Correction Factor ignored.", "Resources::loadSRUs() - correctionNumbers[1] does not contain a valid vegetation value.");
					continue;
				}

				/* Check that third piece of data for correction factor is a valid correction factor value. */
				if (!IsFloat(correctionNumbers[2]))
				{
					error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Factor "+correctionNumbers[2]+" for correction factor ("+(*current)+" is not a valid floating point number.  Correction factor ignored.", "Resources::loadSRUs() - correctionNumbers[2] is not a valid floating point number.");
					continue;
				}

				double factor = atof(correctionNumbers[2].c_str());
				if (!SRU::isValidCorrectionFactor(factor))
				{
					error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Factor "+correctionNumbers[2]+" for Correction factor ("+(*current)+" is not between "+ConvertToStr(DataLimits::correctionFactor_min)+" and "+ConvertToStr(DataLimits::correctionFactor_max)+".  Correction Factor ignored.", "Resources::loadSRUs() - correctionNumbers[2] does not contain a valid correction factor value.");
					continue;
				}

				/*
				 * Check that a correction factor has not already been loaded
				 * for this combination of terrain and vegetation.
				 */
				if (SRUiter->isCorrectionFactorSet(terrain, vegetation))
				{
					error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Duplicate correction factors specified for terrain = "+correctionNumbers[0]+" and vegetation = "+correctionNumbers[1]+".  Second correction factor ignored.", "Resources::loadSRUs() - isCorrectionFactorSet(terrain, vegetation) returns true for specified terrain and vegetation values");
					continue;
				}

				/* Correction factor is correct and should be stored */
				if (!SRUiter->setCorrectionFactor(terrain, vegetation, factor))
				{
					/* Should never be executed, but include error-checking code in case */
					error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Miscellaneous error with correction factor ("+(*current)+".  Correction factor could not be loaded.", "Resources::loadSRUs() - SRUiter->setCorrectionFactor(terrain, vegetation, factor) returned false for valid values of terrain/vegetation/factor.");
				}
			}

		}

	}

	in.close();

	if (testmode) cout << "Data loaded from file." << "\n";

	return added;
}


/******************************************************************************
 * addSRU()
 *
 * Adds the specified SRU to SRUlist.
 *
 * If an SRU with the same Resource Number is not present in SRUlist, sru
 * is added and true is returned.
 *
 * If an SRU with the same Resource Number is already present, sru is
 * not added and false is returned.
 *
 * Author : Gareth Thompson
 */

bool Resources::addSRU(const SRU& sru)
{
	if (testmode) cout << "entering Resources::addSRU()\n";

	if (isSRU(sru.getResourceNum()))
	{
		return false;
	}
	else
	{
		SRUlist.push_back(sru);
		return true;
	}
}

/******************************************************************************
 * deleteSRU()
 *
 * Removes the SRU with the specified Resource Number from SRUlist.
 *
 * If an SRU with the specified Resource Number exists, it is deleted and
 * true is returned.
 *
 * Otherwise, an error is posted and false is returned.
 *
 * Author : Gareth Thompson
 */

bool Resources::deleteSRU(int resourceNum)
{
	if (testmode) cout << "entering Resources::deleteSRU(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter == SRUlist.end())
	{
		/* SRU with specified Resource Number is not present */
		error_manager->PostError(WARNING, "There is no SRU with Resource Number "+ConvertToStr(resourceNum)+".  SRU could was not deleted.", "Resources::deleteSRU() - findSRU(resourceNum) returned SRUlist.end()");
		return false;
	}
	else
	{
		/* SRU with specified Resource Number is present. */
		SRUlist.erase(SRUiter);
		return true;
	}
}



/******************************************************************************
 * userEnterSRU()
 *
 * Allows the user to specify details of a new SRU via standard input.
 *
 * If the user selects an unused Resource Number, they are then prompted
 * to enter the remaining data, the SRU is added to SRUlist,
 * and true is returned.
 * If any piece of data entered is invalid, the user is re-prompted to
 * enter that data.
 *
 * If the user selects a Resource Number which is already used, no data is
 * accepted, no SRU is added, an error is posted and false is returned.
 *
 * Author : Gareth Thompson
 */

bool Resources::userEnterSRU(void)
{
	if (testmode) cout << "entering Resources::userEnterSRU()\n";

	cout << "Please enter the details for the new SRU:\n\n";

	/* Create SRU object to add to SRUlist */
	SRU sruTemp;

	/* Get and check resource Number */
	int resourceNum = GetValidInputInteger("Resource Number (integer "+ConvertToStr((int)DataLimits::resourceNum_min)+" to "+ConvertToStr((int)DataLimits::resourceNum_max)+"): ", "Invalid entry!", DataLimits::resourceNum_min, DataLimits::resourceNum_max);

	/* Resource number is correct and should be stored */
	if (!sruTemp.setResourceNum(resourceNum))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error with resource Number "+ConvertToStr(resourceNum)+".  SRU could not be added.", "Resources::userEnterSRU() - setResourceNum(resourceNum) returned false for valid resourceNum");
		return false;
	}

	/* Check if an SRU with this Resource Number exists */
	if (isSRU(resourceNum))
	{
		error_manager->PostError(WARNING, "An SRU with Resource Number "+ConvertToStr(resourceNum)+" already exists.  SRU could not be added.", "Resource::userEnterSRU() - isSRU(resourceNum) returned true");
		return false;
	}

	/* No checking necessary for Resource Type */
	cout << "Resource Type (text string): ";
	sruTemp.setResourceType(GetInputString(cin));

	/* Get and check POD */
	double POD = GetValidInputFloat("POD (floating point number "+ConvertToStr(DataLimits::POD_min)+" to "+ConvertToStr(DataLimits::POD_max)+")% : ", "Invalid entry!", DataLimits::POD_min, DataLimits::POD_max);

	/* POD is correct and should be stored */
	if (!sruTemp.setPOD(POD))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error with POD "+ConvertToStr(POD)+".  SRU could not be added.", "Resources::userEnterSRU() - setPOD(POD) returned false for valid POD");
		return false;
	}

	/* Get and check ESW */
	double ESW = GetValidInputFloat("ESW (floating point number "+ConvertToStr(DataLimits::ESW_min)+" to "+ConvertToStr(DataLimits::ESW_max)+")m : ", "Invalid entry!", DataLimits::ESW_min, DataLimits::ESW_max);

	/* ESW is correct and should be stored */
	if (!sruTemp.setESW(ESW))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error with ESW "+ConvertToStr(ESW)+".  SRU could not be added.", "Resources::userEnterSRU() - setESW(ESW) returned false for valid ESW");
		return false;
	}

	/* Get and check Speed */
	double speed = GetValidInputFloat("Speed (floating point number "+ConvertToStr(DataLimits::speed_min)+" to "+ConvertToStr(DataLimits::speed_max)+")km/hr : ", "Invalid entry!", DataLimits::speed_min, DataLimits::speed_max);

	/* Speed is correct and should be stored */
	if (!sruTemp.setSpeed(speed))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error with Speed "+ConvertToStr(speed)+".  SRU could not be added.", "Resources::userEnterSRU() - setSpeed(speed) returned false for valid speed");
		return false;
	}

	/* Get and check Hours Available */
	int hoursAvail = GetValidInputInteger("Resource-hours Available (integer "+ConvertToStr((int)DataLimits::hoursAvailable_min)+" to "+ConvertToStr((int)DataLimits::hoursAvailable_max)+"): ", "Invalid entry!", DataLimits::hoursAvailable_min, DataLimits::hoursAvailable_max);

	/* Hours Available is correct and should be stored */
	if (!sruTemp.setHoursAvail(hoursAvail))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error with Resource-Hours Available "+ConvertToStr(hoursAvail)+".  SRU could not be added.", "Resources::userEnterSRU() - setHoursAvail(hoursAvail) returned false for valid hoursAvail");
		return false;
	}

	/* SRU should now be added */
	if (!addSRU(sruTemp))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error when adding SRU.  SRU not added.", "Resources::userEnterSRU() - addSRU(sruTemp) returned false for sruTemp with a unique Resource Number");
		return false;
	}

	return true;
}


/******************************************************************************
 * userModifySRU()
 *
 * Allows the user to modify details of an  SRU with a specified Resource
 * Number.
 *
 * If an SRU with the specified Resource Number exists, the user is prompted
 * for the new details, the SRU is modified and true is returned.
 * If any piece of data is invalid (including if the Resource Number
 * specified is already used by another SRU), the user is reprompted to
 * enter that data.
 *
 * If there is no SRU with the specified Resource Number, no data is accepted,
 * no modification is made, an error is posted and and true is returned.
 *
 * Author : Gareth Thompson
 */

bool Resources::userModifySRU(int resourceNum)
{
	if (testmode) cout << "entering Resources::userModifySRU(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter == SRUlist.end())
	{
		/* SRU with specified Resource Number is not present */
		error_manager->PostError(WARNING, "There is no SRU with Resource Number "+ConvertToStr(resourceNum)+".  SRU could not be modified.", "Resources::userModifySRU() - findSRU(resourceNum) returned SRUlist.end()");
		return false;
	}

	/* Get and check resource Number */
	int newResourceNum;
	do
	{
		newResourceNum = GetValidInputInteger("New Resource Number (integer "+ConvertToStr((int)DataLimits::resourceNum_min)+" to "+ConvertToStr((int)DataLimits::resourceNum_max)+"): ", "Invalid entry!", DataLimits::resourceNum_min, DataLimits::resourceNum_max);

		if (newResourceNum != resourceNum && isSRU(newResourceNum))
		{
			/* Attempting to change Resource Number to that of another existing SRU */
			cout << "There is already an SRU with Resource Number " << newResourceNum << "\n";
		}

	} while (newResourceNum != resourceNum && isSRU(newResourceNum));


	/* Resource number is correct and should be stored */
	if (!SRUiter->setResourceNum(newResourceNum))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error with resource Number "+ConvertToStr(newResourceNum)+".  SRU could not be correctly modified.", "Resources::userModifySRU() - setResourceNum(newResourceNum) returned false for valid newResourceNum");
		return false;
	}

	/* No checking necessary for Resource Type */
	cout << "New Resource Type (text string) : ";
	SRUiter->setResourceType(GetInputString(cin));

	/* Get and check POD */
	double POD = GetValidInputFloat("New POD (floating point number "+ConvertToStr(DataLimits::POD_min)+" to "+ConvertToStr(DataLimits::POD_max)+")% : ", "Invalid entry!", DataLimits::POD_min, DataLimits::POD_max);

	/* POD is correct and should be stored */
	if (!SRUiter->setPOD(POD))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error with POD "+ConvertToStr(POD)+".  SRU could not be correctly modified.", "Resources::userModifySRU() - setPOD(POD) returned false for valid POD");
		return false;
	}

	/* Get and check ESW */
	double ESW = GetValidInputFloat("New ESW (floating point number "+ConvertToStr(DataLimits::ESW_min)+" to "+ConvertToStr(DataLimits::ESW_max)+")m : ", "Invalid entry!", DataLimits::ESW_min, DataLimits::ESW_max);

	/* ESW is correct and should be stored */
	if (!SRUiter->setESW(ESW))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error with ESW "+ConvertToStr(ESW)+".  SRU could not correctly modified.", "Resources::userModifySRU() - setESW(ESW) returned false for valid ESW");
		return false;
	}

	/* Get and check Speed */
	double speed = GetValidInputFloat("New Speed (floating point number "+ConvertToStr(DataLimits::speed_min)+" to "+ConvertToStr(DataLimits::speed_max)+")km/hr : ", "Invalid entry!", DataLimits::speed_min, DataLimits::speed_max);

	/* Speed is correct and should be stored */
	if (!SRUiter->setSpeed(speed))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error with Speed "+ConvertToStr(speed)+".  SRU could not be correctly modified.", "Resources::userModifySRU() - setSpeed(speed) returned false for valid speed");
		return false;
	}

	/* Get and check Hours Available */
	int hoursAvail = GetValidInputInteger("New Resource-hours Available (integer "+ConvertToStr((int)DataLimits::hoursAvailable_min)+" to "+ConvertToStr((int)DataLimits::hoursAvailable_max)+"): ", "Invalid entry!", DataLimits::hoursAvailable_min, DataLimits::hoursAvailable_max);

	/* Hours Available is correct and should be stored */
	if (!SRUiter->setHoursAvail(hoursAvail))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error with Resource-Hours Available "+ConvertToStr(hoursAvail)+".  SRU could not be correctly modified.", "Resources::userModifySRU() - setHoursAvail(hoursAvail) returned false for valid hoursAvail");
		return false;
	}

	return true;
}



/******************************************************************************
 * viewSRU()
 *
 * Prints the details of an SRU with a specified Resource Number to standard
 * output.  An error is posted if there is no SRU with that Resource Number.
 *
 * Author : Gareth Thompson
 */

void Resources::viewSRU(int resourceNum)
{
	if (testmode) cout << "entering Resources::viewSRU(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter == SRUlist.end())
	{
		/* SRU with specified Resource Number is not present. */
		error_manager->PostError(WARNING, "There is no SRU with Resource Number "+ConvertToStr(resourceNum)+".  SRU could not be viewed.", "Resources::viewSRU() - findSRU(resourceNum) returned SRUlist.end()");
	}
	else
	{
		/* SRU with specified Resource Number is present. */
		cout << "Resource Type:  " << SRUiter->getResourceType() << "\n";
		printf("POD: %.2f%%\n", SRUiter->getPOD());
		printf("ESW: %.2fm\n", SRUiter->getESW());
		printf("Speed: %.2fkm/h\n", SRUiter->getSpeed());
		cout << "Resource-hours available:  " << SRUiter->getHoursAvail() << endl;
	}
}


/******************************************************************************
 * viewAllSRUs()
 *
 * Prints details of all SRUs to standard output in a
 * table form.
 *
 * Author : Gareth Thompson
 */

void Resources::viewAllSRUs(void)
{
	if (testmode) cout << "entering Resources::viewAllSRUs()\n";

	/* Output headings for table */
	cout << " Num   Type                               POD      ESW    Speed     Hours\n";
	cout << "                                          (%)      (m)   (km/h)     Avail\n";
	cout << "\n";

	/* Sort SRUs by Resource Number */
	sortResNum();

	/* Output details of each SRU */
	vector<SRU>::iterator current;
	for (current = SRUlist.begin(); current != SRUlist.end(); current++)
	{
		printf("%4d   ", current->getResourceNum());
		cout << ResizeString(current->getResourceType(), 30, 30) << "   ";
		printf("%5.1f   ", current->getPOD());
		printf("%6.1f   ", current->getESW());
		printf("%6.1f    ", current->getSpeed());
		printf("%6d\n", current->getHoursAvail());
	}
}


/******************************************************************************
 * outputAllSRUs()
 *
 * Outputs all SRUs (in ascending order by Resource Number)
 * to an output stream in the Resources file format.  This
 * is useful for output to files.
 *
 * Author : Gareth Thompson
 */

void Resources::outputAllSRUs(ostream& out)
{
	if (testmode) cout << "entering Resources::outputAllSRUs()\n";

	sortResNum();

	vector<SRU>::iterator SRUCurrent;

	for (SRUCurrent = SRUlist.begin(); SRUCurrent != SRUlist.end(); SRUCurrent++)
	{
		out << SRUCurrent->getSRUString() << "\n";
	}
}


/******************************************************************************
 * Resources::userEnterCorrectionFactor()
 *
 * Allows the user to enter a correction factor for the specified SRU.
 *
 * If the specified SRU exists, the user is prompted for terrain, vegetation
 * and correction factor, the result is stored (overwriting any
 * previous correction factor) and true is returned.
 * If any piece of data entered is invalid, the user is re-prompted to
 * enter that data.
 *
 * If there is no SRU with the specified Resource Number, no data is accepted,
 * no correction factor is set, an error is posted, and false is returned.
 *
 * Author : Gareth Thompson
 */

bool Resources::userEnterCorrectionFactor(int resourceNum)
{
	if (testmode) cout << "entering Resources::userEnterCorrectionFactor(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter == SRUlist.end())
	{
		/* SRU with specified Resource Number is not present */
		error_manager->PostError(WARNING, "There is no SRU with Resource Number "+ConvertToStr(resourceNum)+".  Correction factor could not be entered.", "Resources::userEnterCorrectionFactor() - findSRU(resourceNum) returned SRUlist.end()");
		return false;
	}

	int terrain = GetValidInputInteger("Terrain value (integer "+ConvertToStr((int)DataLimits::terrain_min)+" to "+ConvertToStr((int)DataLimits::terrain_max)+") : ", "Invalid entry!", DataLimits::terrain_min, DataLimits::terrain_max);

	int vegetation = GetValidInputInteger("Vegetation value (integer "+ConvertToStr((int)DataLimits::vegetation_min)+" to "+ConvertToStr((int)DataLimits::vegetation_max)+") : ", "Invalid entry!", DataLimits::vegetation_min, DataLimits::vegetation_max);

	double factor = GetValidInputFloat("Factor (floating point number "+ConvertToStr(DataLimits::correctionFactor_min)+" to "+ConvertToStr(DataLimits::correctionFactor_max)+") : ", "Invalid entry!", DataLimits::correctionFactor_min, DataLimits::correctionFactor_max);

	/* Correction Factor should now be set */
	if (!SRUiter->setCorrectionFactor(terrain, vegetation, factor))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error when adding correction factor.  Correction factor not set.", "Resources::userEnterCorrectionFactor() - setCorrectionFactor(terrain, vegetation, factor) returned false for valid terrain / vegetation / factor");
		return false;
	}

	return true;
}



/******************************************************************************
 * Resources::userDeleteCorrectionFactor()
 *
 * Allows the user to delete a correction factor for the specified SRU.
 *
 * If the specified SRU exists, the user is prompted for terrain and vegetation
 * values.  If any piece of data is invalid, the user is re-prompted to enter
 * that data.
 *
 * If the SRU has a correction factor for that combination of terrain and
 * vegetation, it is deleted and true is returned.  Otherwise, no change is
 * made, an error is posted and false is returned.
 *
 * If the specified SRU does not exist, no data is accepted, no change is made,
 * an error is posted and false is returned.
 *
 * Author : Gareth Thompson
 */

bool Resources::userDeleteCorrectionFactor(int resourceNum)
{
	if (testmode) cout << "entering Resources::userDeleteCorrectionFactor(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter == SRUlist.end())
	{
		/* SRU with specified Resource Number is not present */
		error_manager->PostError(WARNING, "There is no SRU with Resource Number "+ConvertToStr(resourceNum)+".  Correction factor could not be deleted.", "Resources::userDeleteCorrectionFactor() - findSRU(resourceNum) returned SRUlist.end()");
		return false;
	}

	int terrain = GetValidInputInteger("Terrain value (integer "+ConvertToStr((int)DataLimits::terrain_min)+" to "+ConvertToStr((int)DataLimits::terrain_max)+") : ", "Invalid entry!", DataLimits::terrain_min, DataLimits::terrain_max);

	int vegetation = GetValidInputInteger("Vegetation value (integer "+ConvertToStr((int)DataLimits::vegetation_min)+" to "+ConvertToStr((int)DataLimits::vegetation_max)+") : ", "Invalid entry!", DataLimits::vegetation_min, DataLimits::vegetation_max);

	if (!SRUiter->isCorrectionFactorSet(terrain, vegetation))
	{
		/* There is no current correction factor to delete */
		error_manager->PostError(WARNING, "SRU "+ConvertToStr(resourceNum)+" does not have a correction factor for terrain = "+ConvertToStr(terrain)+" and vegetation = "+ConvertToStr(vegetation)+".  Correction factor could not be deleted.", "Resources::userDeleteCorrectionFactor() - isCorrectionFactorSet(terrain, vegetation) returned false");
		return false;
	}

	/* Correction Factor should now be deleted */
	if (!SRUiter->deleteCorrectionFactor(terrain, vegetation))
	{
		/* Should never be executed, but include error-checking code in case */
		error_manager->PostError(WARNING, "Miscellaneous error when deleting correction factor.  Correction factor not deleted.", "Resources::userDeleteCorrectionFactor() - deleteCorrectionFactor(terrain, vegetation) returned false when a correction factor was initially set for those terrain / vegetation values");
		return false;
	}

	return true;
}


/******************************************************************************
 * Resources::deleteCorrectionFactors()
 *
 * Allows the user to delete all correction factor for the specified SRU.
 * If the specified SRU exists, its correction factors are all deleted
 * and true is returned.
 *
 * If the SRU does not exist, no change is made, an error is posted, and false
 * is returned.
 *
 * Author : Gareth Thompson
 */

bool Resources::deleteCorrectionFactors(int resourceNum)
{
	if (testmode) cout << "entering Resources::deleteCorrectionFactors(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter == SRUlist.end())
	{
		/* SRU with specified Resource Number is not present */
		error_manager->PostError(WARNING, "There is no SRU with Resource Number "+ConvertToStr(resourceNum)+".  Correction factors could not be deleted.", "Resources::userDeleteCorrectionFactors() - findSRU(resourceNum) returned SRUlist.end()");
		return false;
	}

	SRUiter->deleteCorrectionFactors();
	return true;
}






/******************************************************************************
 * Resources::viewCorrectionFactors()
 *
 * Prints the correction factors for the SRU with the
 * specified Resource Number.
 * If the SRU exists, its correction factors are printed
 * to standard output in table form.
 * If the SRU does not exist, an error is posted.
 *
 * Author : Gareth Thompson
 */

void Resources::viewCorrectionFactors(int resourceNum)
{
	if (testmode) cout << "entering Resources::viewCorrectionFactors(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter != SRUlist.end())
	{
		/* SRU with specified Resource Number is present */
		SRUiter->viewCorrectionFactors();
	}
	else
	{
		/* SRU with specified Resource Number is not present. */
		error_manager->PostError(WARNING, "There is no SRU with Resource Number "+ConvertToStr(resourceNum)+". Correction Factors could not be viewed.", "Resources::viewCorrectionFactors() - findSRU(resourceNum) returned SRUlist.end()");
	}
}





/******************************************************************************
 * Resources::addAssignment()
 *
 * Adds theAssignment to the assignments of the SRU with the specified
 * Resource Number.
 *
 * If an SRU with the specified Resource Number exists, and
 * theAssignment.getResourceHours() is non-negative and not greater than the
 * number of resource-hours remaining for the SRU, theAssignment is added
 * to those for that SRU and true is returned.
 *
 * Otherwise, it is not possible for the SRU to have the assignment:
 * theAssignment is not added, and false is returned.
 *
 * Author : Gareth Thompson
 */

bool Resources::addAssignment(int resourceNum, const Assignment& theAssignment)
{
	if (testmode) cout << "entering Resources::addAssignment(" << resourceNum << ", " << theAssignment.getAreaNum() << ")\n";
	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter != SRUlist.end())
	{
		/* SRU with specified Resource Number is present */
		return SRUiter->addAssignment(theAssignment);
	}
	else
	{
		/* SRU with specified Resource Number is not present. */
		return false;
	}
}


/******************************************************************************
 * Resources::deleteAssignment()
 *
 * Removes the assignment with the specified Area Number from the
 * SRU with the specified Resource Number.
 *
 * If an SRU with the specified Resource Number exists, and has
 * an assignment with the specified Area Number, it is deleted and
 * true is returned.
 *
 * If the SRU does not exist, or has no assignment with the specified
 * Area Number, no change is made and false is returned.
 *
 * Author : Gareth Thompson
 */

bool Resources::deleteAssignment(int resourceNum, int areaNum)
{
	if (testmode) cout << "entering Resources::deleteAssignment(" << resourceNum << ", " << areaNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter == SRUlist.end())
	{
		/* SRU with specified Resource Number is not present. */
		return false;
	}
	else
	{
		/* SRU with specified Resource Number is present. */
		return SRUiter->deleteAssignment(areaNum);
	}
}






/******************************************************************************
 * Resources::deleteAssignments()
 *
 * Deletes all Assignments for the SRU with the specified Resource Number.
 *
 * If an SRU with the specified Resource Number exists, its assignments are
 * deleted and true is returned.
 *
 * Otherwise, false is returned.
 *
 * Author : Gareth Thompson
 */

bool Resources::deleteAssignments(int resourceNum)
{
	if (testmode) cout << "entering Resources::deleteAssignments(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter != SRUlist.end())
	{
		/* SRU with specified Resource Number is present */
		SRUiter->deleteAssignments();
		return true;
	}
	else
	{
		/* SRU with specified Resource Number is not present. */
		return false;
	}
}





/******************************************************************************
 * Resources::getAssignments()
 *
 * Returns a vector<Assignment> containing the assignments
 * for the SRU with the specified Resource Number.
 *
 * If an SRU with the specified Resource Number does not
 * exist, the return value is undefined.
 *
 * Author : Gareth Thompson
 */

vector<Assignment> Resources::getAssignments(int resourceNum)
{
	if (testmode) cout << "entering Resources::getAssignments(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter != SRUlist.end())
	{
		/* SRU with specified Resource Number is present */
		return SRUiter->getAssignments();
	}
	else
	{
		/* SRU with specified Resource Number is not present. */
		vector<Assignment> empty_assignments;
		return empty_assignments;  //undefined return value
	}
}


/******************************************************************************
 * viewAssignments()
 *
 * Prints the assignments for the SRU with the specified Resource Number to
 * standard output.  An error is posted if there is no SRU with the specified
 * Resource Number.
 *
 * Author : Gareth Thompson
 */

void Resources::viewAssignments(int resourceNum)
{
	if (testmode) cout << "entering Resources::viewAssignments(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter == SRUlist.end())
	{
		/* SRU with specified Resource Number is not present. */
		error_manager->PostError(WARNING, "There is no SRU with Resource Number "+ConvertToStr(resourceNum)+". Assignments could not be viewed.", "Resources::viewAssignments() - findSRU(resourceNum) returned SRUlist.end()");
	}
	else
	{
		/* SRU with specified Resource Number is present. */
		/* Sort Assignments into ascending order by Area Number, and print. */
		SRUiter->sortAssignAreaNum();
		vector<Assignment> temp;
		temp = getAssignments(resourceNum);
		PrintAssignmentVector(temp);
	}
}



/******************************************************************************
 * deleteAllAssignments()
 *
 * Deletes the assignments for every SRU in SRUlist.
 *
 * Author : Gareth Thompson
 */

void Resources::deleteAllAssignments(void)
{
	if (testmode) cout << "entering Resources::deleteAllAssignments()\n";

	vector<SRU>::iterator current;

	for (current = SRUlist.begin(); current != SRUlist.end(); current++)
	{
		current->deleteAssignments();
	}
}



/******************************************************************************
 * viewAllAssignments()
 *
 * Prints the assignments of SRUs to areas (for searching)
 * to standard output in a table form, that is useful for
 * users to view.
 *
 * SRUs are sorted into ascending order by Resource Number.
 * Their Assignments are sorted into ascending order by
 * Area Number.
 *
 * Author : Gareth Thompson
 */

void Resources::viewAllAssignments(void)
{
	if (testmode) cout << "entering Resources::viewAllAssignments()\n";

	/* Output headings for table */
	cout << " Res     Hours       Hours     Area          Hours\n";
	cout << " Num     Avail        Used      Num       Assigned\n";
	cout << "==================================================\n";

	/* Sort SRUs by Resource Number */
	sortResNum();

	/* Output details of each SRU */
	vector<SRU>::iterator current;
	for (current = SRUlist.begin(); current != SRUlist.end(); current++)
	{
		printf("%4d    ", current->getResourceNum());
		printf("%6d   ", current->getHoursAvail());
		printf("%9.2f     ", current->getHoursAssigned());

		/* Output the assignments for the SRU */
		current->sortAssignAreaNum();
		vector<Assignment> assignments = current->getAssignments();

		if (assignments.size() == 0)
		{
			/* No assignments - output dashes */
			cout << "   -            -\n";
		}
		else
		{
			/* Output first assignment on current line */
			printf("%4d      ", assignments[0].getAreaNum());
			printf("%9.2f\n", assignments[0].getResourceHours());

			/* Output any remaining assignments on following lines */
			int i;
			for (i=1; i<assignments.size(); i++)
			{
				printf("                               %4d      ", assignments[i].getAreaNum());
				printf("%9.2f\n", assignments[i].getResourceHours());
			}
		}

		/* Output line separating SRUs */
		cout << "==================================================\n";

	}
}


/******************************************************************************
 * outputAllAssignments()
 *
 * Outputs all assignments to an output stream in the
 * Assignment file format.  This is useful for output
 * to files.
 *
 * Assignments are sorted into ascending order by Resource
 * Number and then Area Number.
 *
 * Author : Gareth Thompson
 */

void Resources::outputAllAssignments(ostream& out)
{
	if (testmode) cout << "entering Resources::outputAllAssignments()\n";

	/* Sort SRUs by Resource Number */
	sortResNum();

	vector<SRU>::iterator SRUCurrent;
	for (SRUCurrent = SRUlist.begin(); SRUCurrent != SRUlist.end(); SRUCurrent++)
	{
		/* Sort Assignments by Area Number */
		SRUCurrent->sortAssignAreaNum();

		vector<Assignment> assignments = SRUCurrent->getAssignments();

		vector<Assignment>::iterator assCurrent;
		for (assCurrent = assignments.begin(); assCurrent != assignments.end(); assCurrent++)
		{
			out << SRUCurrent->getResourceNum() << ", ";
			out << assCurrent->getAreaNum() << ", ";

			/* Output Resource Hours with 2 digits after decimal point */
			char str[20];
			sprintf(str, "%-9.2f", assCurrent->getResourceHours());
			out << str << "\n";
		}
	}
}



/******************************************************************************
 * getHoursRemaining()
 *
 * Returns the number of resource-hours available for the SRU
 * with the specified Resource Number that have not yet been
 * assigned for searching.
 *
 * This value may be slightly negative, because of the
 * non-zero floating-point precision defined by FloatLess().
 * (It is possible to assign more hours to a resource than
 * are available, provided that the assignments do not exceed
 * the hours available by more than the defined precision.)
 *
 * The return value is undefined if there is no SRU with the
 * specified Resource Number.
 *
 * It is best to call hoursRemaining() first to check that there
 * are hours remaining, before calling getHoursRemaining to
 * determine the actual number remaining.
 *
 * Author : Gareth Thompson
 */

double Resources::getHoursRemaining(int resourceNum)
{
	if (testmode) cout << "entering Resources::getHoursRemaining(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter != SRUlist.end())
	{
		/* SRU with specified Resource Number is present */
		return SRUiter->getHoursRemaining();
	}
	else
	{
		/* SRU with specified Resource Number is not present. */
		return 0.0;  //undefined return value
	}
}


/******************************************************************************
 * Resources::getESW()
 *
 * Returns the ESW of the SRU with the specified Resource Number (IGNORING
 * CORRECTION FACTORS).
 *
 * The return value is undefined if there is no SRU with the
 * specified Resource Number.
 *
 * Author : Gareth Thompson
 */

double Resources::getESW(int resourceNum)
{
	if (testmode) cout << "entering Resources::getESW(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter != SRUlist.end())
	{
		/* SRU with specified Resource Number is present */
		return SRUiter->getESW();
	}
	else
	{
		/* SRU with specified Resource Number is not present. */
		return 0.0;  //undefined return value
	}
}


int Resources::getNumResources(void)
{
	return SRUlist.size();
}

/******************************************************************************
 * Resources::getSpeed()
 *
 * Returns the Speed of the SRU with the specified Resource Number (IGNORING
 * CORRECTION FACTORS).
 *
 * The return value is undefined if there is no SRU with the
 * specified Resource Number.
 *
 * Author : Gareth Thompson
 */

double Resources::getSpeed(int resourceNum)
{
	if (testmode) cout << "entering Resources::getSpeed(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter != SRUlist.end())
	{
		/* SRU with specified Resource Number is present */
		return  SRUiter->getSpeed();
	}
	else
	{
		/* SRU with specified Resource Number is not present. */
		return 0.0;
	}
}



/******************************************************************************
 * Resources::getCorrectionFactor()
 *
 * Returns the Correction Factor for the SRU with the specified Resource
 * Number, in an area with the specified terrain and vegetation.
 *
 * If the SRU exists, and the terrain and vegetation values are
 * valid the correction factor for the SRU is returned:
 * - If a correction factor has been defined for this combination
 *   of terrain and vegetation values, it is returned.
 * - Otherwise, default correction factor 1.0 is returned.
 *
 * If there is no SRU with the specified Resource Number, or the
 * terrain/vegetation values are invalid, the return value is undefined.
 *
 * Author : Gareth Thompson
 */

double Resources::getCorrectionFactor(int resourceNum, int terrain, int vegetation)
{
	if (testmode) cout << "entering Resources::getCorrectionFactor(" << resourceNum << ", " << terrain << ", " << vegetation << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter != SRUlist.end())
	{
		/* SRU with specified Resource Number is present */
		return  SRUiter->getCorrectionFactor(terrain, vegetation);
	}
	else
	{
		/* SRU with specified Resource Number is not present. */
		return -1.0;   //undefined return value
	}

}





/******************************************************************************
 * Resources::getEffectiveSweepRate()
 *
 * Returns the Effective Sweep Rate of the SRU with the
 * specified Resource Number (in km^2/hr).
 *
 * If an SRU with the specified Resource Number exists, its Effective Sweep
 * Rate is returned:
 * - If terrain and vegetation arguments are given, and they are valid values
 *   the effective sweep rate of the SRU for that combination of terrain and
 *   vegetation is returned.  (This is the product of ESW, speed, and the
 *   correction factor for that terrain.)
 *   If the SRU does not have a correction factor for that combination of
 *   vegetation and terrain, it is assued to be 1.
 * - If terrain and vegetation arguments are not given, or either is an
 *   invalid value, then the effective sweep rate of the SRU, ignoring
 *   correction factors, is returned.  This is the product of ESW and speed.
 *
 *
 * If an SRU with the specified Resource Number does not exist, the return
 * value is undefined.
 *
 * Author : Gareth Thompson
 */

double Resources::getEffectiveSweepRate(int resourceNum, int terrain, int vegetation)
{
	if (testmode) cout << "entering Resources::getEffectiveSweepRate(" << resourceNum << ", " << terrain << ", " << vegetation << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter != SRUlist.end())
	{
		/* SRU with specified Resource Number is present */
		return  SRUiter->getEffectiveSweepRate(terrain, vegetation);
	}
	else
	{
		/* SRU with specified Resource Number is not present. */
		return 0.0;  //undefined return value
	}
}




/******************************************************************************
 * Resources::hoursRemaining()
 *
 * Returns true if an SRU with the specified Resource
 * Number exists and has resource-hours that have not yet
 * been assigned for searching.
 *
 * Returns false if an SRU with the specified Resource Number
 * does not exist or does not have resource-hours remaining
 * to be assigned.
 *
 * Author : Gareth Thompson
 */

bool Resources::hoursRemaining(int resourceNum)
{
	if (testmode) cout << "entering Resources::hoursRemaining(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = findSRU(resourceNum);

	if (SRUiter != SRUlist.end())
	{
		/* SRU with specified Resource Number is present */
		return  SRUiter->hoursRemaining();
	}
	else
	{
		/* SRU with specified Resource Number is not present. */
		return false;
	}
}


/******************************************************************************
 * anyHoursRemaining()
 *
 * Returns true if there any SRUs in SRUlist which have
 * Resource-hours available that have not yet been assigned
 * for searching.  Otherwise, returns false.
 *
 * Author : Gareth Thompson
 */

bool Resources::anyHoursRemaining(void)
{
	if (testmode) cout << "entering Resources::anyHoursRemaining()\n";

	vector<SRU>::iterator current;

	for (current = SRUlist.begin(); current != SRUlist.end(); current++)
	{
		if (current->hoursRemaining())
		{
			return true;
		}
	}

	return false;
}






/******************************************************************************
 * getAreaEffectivelySweptRemaining()
 *
 * Returns the maximum Area Effectively Swept that can be achieved with the
 * Resource-hours that are available but that have not yet been assigned
 * to SRUs (ignoring correction factors for vegetation and terrain).
 *
 * The Area Effectively Swept Remaining for a given SRU is the product of
 * its Effective Sweep Rate (here, correction factors are ignored) and
 * hours remaining for searching.  The value returned by this function is
 * the sum of the Area Effectively Swept Remaining values for all SRUs.
 *
 * Author : Gareth Thompson
 */

double Resources::getAreaEffectivelySweptRemaining(void)
{
	if (testmode) cout << "entering Resources::getAreaEffectivelySweptRemaining()\n";

	double areaEffecSweptRem = 0.0;
	vector<SRU>::iterator current;

	for (current = SRUlist.begin(); current != SRUlist.end(); current++)
	{
		areaEffecSweptRem += current->getEffectiveSweepRate() * current->getHoursRemaining();
	}

	return areaEffecSweptRem;
}



/******************************************************************************
 * menu()
 *
 * Menu which provides users with options for modifying
 * the SRUs stored in this Resources object.
 *
 * Returns true if any SRUs are modified.
 * Returns false if no SRUs are modified.
 *
 * Author : Gareth Thompson
 */

bool Resources::menu(void)
{
	if (testmode) cout << "entering Resources::menu()\n";

	int choice;
	bool modified = false;  // no SRUs have been modified

	const int maxchoice = 11;

	do
	{
		cout << "\n";
		cout << "********************" << endl;
		cout << "** Resources Menu **" << endl;
		cout << "********************" << endl;
		cout << "1. Enter a new SRU\n";
		cout << "2. Load SRUs from a file\n";
		cout << "3. Delete an SRU\n";
		cout << "4. Delete all current SRUs\n";
		cout << "5. Modify details of an SRU\n";
		cout << "6. View details of an SRU\n";
		cout << "7. View details of all SRUs\n";
		cout << "8. View Correction factors for an SRU\n";
		cout << "9. Enter a correction factor for an SRU\n";
		cout << "10. Delete a correction factor for an SRU\n";
		cout << "11. Delete all correction factors for an SRU\n";
		cout << "0. Main Menu" << endl;

		if (testmode) cout << "MODIFIED: " << modified << "\n\n";

		do
		{
			cout << "\nChoice: ";
			cin >> choice;

			if (choice < 0 || choice > maxchoice)
			{
				cout << "Invalid choice.  Please enter 1-7 or 0!" << endl;
			}
		} while (choice < 0 || choice > maxchoice);

		if (choice == 1)  /* Enter a new SRU */
		{
			if (userEnterSRU()) modified = true;
		}
		else if (choice == 2)  /* Load SRUs from a file */
		{
			string filename;
			cout << "Enter filename to load SRUs from: ";

			filename = GetInputString(cin);

			if (loadSRUs(filename)) modified = true;
		}
		else if (choice == 3)  /* Delete an SRU */
		{
			int resourceNum;
			cout << "Enter the Resource Number for the SRU: ";
			cin >> resourceNum;

			if (deleteSRU(resourceNum)) modified = true;
		}
		else if (choice == 4) /* Delete all current SRUs */
		{
			/* Only delete SRUs if there are some present,
			 * so that we know if a modification has
			 * been made.
			 */
			if (SRUlist.size() != 0)
			{
				deleteAllSRUs();
				modified = true;
			}
		}
		else if (choice == 5) /* Modify details of an SRU */
		{
			int resourceNum;
			cout << "Enter the Resource Number for the SRU: ";
			cin >> resourceNum;

			if (userModifySRU(resourceNum)) modified = true;
		}
		else if (choice == 6) /* View details of an SRU */
		{
			int resourceNum;
			cout << "Enter the Resource Number for the SRU: ";
			cin >> resourceNum;

			viewSRU(resourceNum);
		}
		else if (choice == 7) /* View details of all SRU */
		{
			viewAllSRUs();
		}
		else if (choice == 8)
		{
			int resourceNum;
			bool success;
			do
			{
				cout << "Enter the Resource Number for the SRU: ";
				success = GetInputInteger(cin, resourceNum);

				if (!success) cout << "Invalid entry!\n";

			} while (!success);

			cout << "\n";
			viewCorrectionFactors(resourceNum);
		}
		else if (choice == 9)
		{
			int resourceNum = GetValidInputInteger("Enter the Resource Number of the SRU: ", "Invalid entry!");

			userEnterCorrectionFactor(resourceNum);
		}
		else if (choice == 10)
		{
			int resourceNum = GetValidInputInteger("Enter the Resource Number of the SRU: ", "Invalid entry!");

			userDeleteCorrectionFactor(resourceNum);
		}
		else if (choice == 11)
		{
			int resourceNum = GetValidInputInteger("Enter the Resource Number of the SRU: ", "Invalid entry!");

			deleteCorrectionFactors(resourceNum);
		}
	} while (choice != 0);

	return modified;
}


/******************************************************************************
 * findSRU()
 *
 * Finds the SRU with a specified Resource Number.
 * If an SRU with the specified Resource Number is
 * present, findSRU() returns an iterator to the
 * first SRU in the SRUlist which has that Resource Number.
 * If an SRU with the specified Resource Number is not
 * present, findSRU() returns an iterator equal to SRUlist.end().
 *
 * Author : Gareth Thompson
 */

vector<Resources::SRU>::iterator Resources::findSRU(int resourceNum)
{
	if (testmode) cout << "entering Resources::findSRU(" << resourceNum << ")\n";

	vector<SRU>::iterator SRUiter = SRUlist.begin();

	while (SRUiter != SRUlist.end())
	{
		if (SRUiter->getResourceNum() == resourceNum)
		{
			return SRUiter;
		}

		SRUiter++;
	}

	return SRUiter;
}


/******************************************************************************
 * sortResNum()
 *
 * Sorts SRUlist into ascending order by Resource Number.
 *
 * Author : Gareth Thompson
 */

void Resources::sortResNum(void)
{
	if (testmode) cout << "entering Resources::sortResNum()\n";

	/*
	 * ltResNum compares SRUs using Resource Number.
	 * The standard sort() function sorts SRUs using
	 * ltResNum to compare SRUs.
	 */
	sort(SRUlist.begin(), SRUlist.end(), SRU::ltResNum());
}
