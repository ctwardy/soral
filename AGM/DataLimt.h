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
 * DataLimt.h
 *
 * Defines the upper and lower limits for all pieces of
 * data in the SAR program.
 *
 * Because terrain and vegetation values must be used by both
 * Areas and SRUs (when storing correction factors), functions for
 * testing if integers are valid terrain/vegetation values are also
 * defined here (for other pieces of data, the "set" functions of
 * the respective classes perform these checks).
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 26/05/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#ifndef _datalimt_h_
#define _datalimt_h_

#include <climits>
#include "global.h"

using namespace std;

class DataLimits
{
public:
	// Function to test if an integer is a valid terrain value
	inline static bool isValidTerrain(int terrain)
	{ return (terrain>=terrain_min && terrain<=terrain_max); }

	// Function to test if an integer is a valid vegetation value
	inline static bool isValidVegetation(int vegetation)
	{ return (vegetation>=vegetation_min && vegetation<=vegetation_max); }

	enum { areaNum_min = -2, areaNum_max = 100 };
	enum { travelTime_min = 0, travelTime_max = INT_MAX };
	enum { altitude_min = INT_MIN, altitude_max = INT_MAX };
	enum { terrain_min = 1, terrain_max = 100 };
	enum { vegetation_min = 1, vegetation_max = 3};
	enum { hoursAvailable_min = 0, hoursAvailable_max = INT_MAX };
	enum { resourceNum_min = 0, resourceNum_max = INT_MAX };

	static const double POA_min;
	static const double POA_max;

	static const double POD_min;
	static const double POD_max;

	static const double ESW_min;
	static const double ESW_max;

	static const double speed_min;
	static const double speed_max;

	static const double correctionFactor_min;
	static const double correctionFactor_max;

private:
	/* Constructor private - you can't create objects of this class. */
	DataLimits();
};

#endif
