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
 * Areas.cpp
 *
 *  Display Map showing POAs. Provide and Update POA values. Store Areas data.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * AO  | 02/04/00 |  1  | Created.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "InputFil.h"
#include "math.h"
#include "Areas.h"
using namespace std;
/******************************************************************************
 * setNumber()
 *
 * Set the area number of the area
 *
 * Author : Andre Oboler
 *
 */
bool BigArea::Area::setNumber(int newnumber)
{
	number=newnumber;
	return true;
}
/******************************************************************************
 * setLocation()
 *
 * Set the location of an Area
 *
 * Author : Andre Oboler
 */
bool BigArea::Area::setLocation(UTM newlocation)
{
	location=newlocation;
	return true;
}
/******************************************************************************
 * DumpArea()
 *
 * Set the location of an Area
 *
 * Author : Andre Oboler
 */
/*
string BigArea::Area::DumpArea(void)
{
	string temp;
	int in;
	// ASO 12/1/03 lines below changed from being "ostrstream ostrN;" to "std::ostringstream ostrN;" to be GCC 3.1.1 compliant
	std::ostringstream ostr1; // Change back to one ostream object soon as I work out how to clear this buffer !
	std::ostringstream ostr2;
	std::ostringstream ostr3;
	std::ostringstream ostr4;
	std::ostringstream ostr5;
	std::ostringstream ostr6;
	ostr1 << number << '\0';
	temp += ostr1.str();
	temp+=", (";
	temp+= location.x;
	temp+= "/";
	temp+= location.y;
	temp+= "), (";
	for (in=0; in< boundaries.size(); in++)
	{
		temp+= "(";
		temp+= boundaries[in].x;
		temp+= "/";
		temp+= boundaries[in].y;
		temp+= ")";
	}
	temp +="), ";
	ostr2 << traveltime << '\0';
	temp += ostr2.str();
	temp +=", ";
	ostr3 << altitude << '\0';
	temp += ostr3.str();
	temp +=", ";
	ostr4 << terrain << '\0';
	temp += ostr4.str();
	temp +=", ";
	ostr5 << vegetation << '\0';
	temp += ostr5.str();
	temp +=", ";
	ostr6 << POA << '\0';
	temp += ostr6.str();
	temp +="\n";
	// Null-terminate temp
	temp << '\0';
	return ostr.str();
	return temp;
}
*/
// New go 21/1/03
string BigArea::Area::DumpArea(void)
{
	string temp;
	int in;
	// ASO 12/1/03 lines below changed from being "ostrstream ostrN;" to "std::ostringstream ostrN;" to be GCC 3.1.1 compliant
	std::ostringstream ostr; // Change back to one ostream object soon as I work out how to clear this buffer !
	std::ostringstream ostr2;
	std::ostringstream ostr3;
	std::ostringstream ostr4;
	std::ostringstream ostr5;
	std::ostringstream ostr6;
	ostr << number << ", (" << location.x << "/" << location.y << "), (";
	for (in=0; in< boundaries.size(); in++)
	{
		ostr << "(" << boundaries[in].x << "/" << boundaries[in].y << ")";
	}
	ostr << "), " << traveltime << ", " << altitude << ", " << terrain;
	ostr << ", " << vegetation << ", " << POA << "\n";
	/* Null-terminate ostr */
	ostr << '\0';
	return ostr.str();
}
/******************************************************************************
 * setTravelTime()
 *
 * Set the location of an Area
 *
 * Author : Andre Oboler
 */
bool BigArea::Area::setTraveltime(int newTravelTime)
{
	if (newTravelTime >= 0)
	{
		traveltime=newTravelTime;
		return true;
	}
	return false; // can not travel back in time !
}
/******************************************************************************
 * setBoundaries
 *
 * Takes:   String containing an arbitrary amount of UTMs
 * Returns: Bool
 * Does:	Splits string into UTMs and stores in a UTM vector called
 *          Boundaries inside area.
 *
 * Author : Andre Oboler
 */
bool BigArea::Area::setBoundaries(string boundariesString)
{
/*   The following code should run at O(2N+3) where N is an x or y co-ordinate.*/
	int pos=0; // possition of start of word in temp string
	int k=0; // possition in boundariesString
	int i=0; // UTM number in list
	int bracket=0; // count of open brackets
	UTMtype temp;
	boundaries.clear();
	while(k < boundariesString.size())
			{
				if (boundariesString[k] == '(')
				{
					bracket++;
					if (bracket>1) // ie not first opening bracket
					{
						pos=k+1; //start of new 4 digits is here
					}
				}
				else if (boundariesString[k] == ')')
				{
					bracket--;
					if (bracket>0) // ie not last closing bracket
					{
						temp.y = boundariesString.substr(pos, 4);
						boundaries.push_back(temp);
					}
					i++; // incement to next UTM location index
				}
				else if (boundariesString[k] == '/')
				{
					temp.x=boundariesString.substr(pos, 4);
					pos=k+1;
				}
				else if (boundariesString[k] == '\n')
				{
					// Exit with fatal error, or return false
					// and 1 level up crashes with error.
					return false;
				}
				else if (boundariesString[k] == ' ')
				{
					// ignore
				}
				else
				{
					//valid charactor
				}
				k++;
			}
			return true;
}
/******************************************************************************
 * setAltitude()
 *
 * Set the altitude of an Area
 *
 * Author : Andre Oboler
 */
bool BigArea::Area::setAltitude(int newaltitude)
{
	altitude=newaltitude;
	return true;
}
/******************************************************************************
 * setSize()
 *
 * Set the overall size of an Area
 *
 * Author : Andre Oboler
 */
bool BigArea::Area::setSize(float newSize)
{
	size=newSize;
	return true;
}
/******************************************************************************
 * setTerrain()
 *
 * Set the terrain type of an Area
 *
 * Author : Andre Oboler
 */
bool BigArea::Area::setTerrain(int newterrain)
{
	terrain=newterrain;
	return true;
}
/******************************************************************************
 * setVegetation()
 *
 * Set the vegitation type of an Area
 *
 * Author : Andre Oboler
 */
bool BigArea::Area::setVegetation(int newvegetation)
{
	vegetation=newvegetation;
	return true;
}
/******************************************************************************
 * setPOA()
 *
 * Set the POA of an Area
 *
 * Author : Andre Oboler
 */
bool BigArea::Area::setPOA(float newPOA)
{
	POA=newPOA;
	return true;
}
