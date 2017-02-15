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
 * Assignmt.h
 * [NOTE: There is no Assignmt.cpp]
 *
 * Assignment is a simple data structure for storing a single
 * search assignment.  It stores the area to be searched and
 * the number of resource-hours to search for.
 *
 * No error checking of these values is provided by Assignment.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 22/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 07/05/01 |  2  | Updated.  ltAreaNum provided for comparisons.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 2.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#ifndef Assignmt_h
#define Assignmt_h
using namespace std;
class Assignment
{
	public:
		/*
		 * Constructor to create new Assignment, specifying
		 * data values.
		 */
		Assignment(int areaNum, double resourceHours)
		: myAreaNum(areaNum), myResourceHours(resourceHours)
		{}
		/*
		 * Constructor to create new Assignment, initialising
		 * data values to 0.
		 */
		Assignment(void)
		: myAreaNum(0), myResourceHours(0)
		{}
		inline int getAreaNum(void) const { return myAreaNum; }
		inline void setAreaNum(int areaNum) { myAreaNum = areaNum; }
		inline double getResourceHours(void) const { return myResourceHours; }
		inline void setResourceHours(double resourceHours) { myResourceHours = resourceHours; }
		/*
		 * Predicate < object for comparing Assignments by Area
		 * Number.  If assign_lt is a ltAreaNum object, then
		 * assign_lt(assignment1, assignment2) will return true
		 * if assignment1's Area Number is less than assignment2's
		 * Area Number.
		 */
		class ltAreaNum
		{
			public:
				inline bool operator() (const Assignment& assignment1, const Assignment& assignment2) const
				{ return assignment1.getAreaNum() < assignment2.getAreaNum(); }
		};
	private:
		int myAreaNum;  /* Area to search */
		double myResourceHours;  /* Resource hours to search for */
};
#endif
