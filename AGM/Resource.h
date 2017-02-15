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
 * Resource.h
 *
 * Resources stores details of all available SRUs (including
 * the areas that they are allocated to search in the next
 * sortie).  It is possible to add, delete, modify and view SRUs;\
 * modify, view and clear their allocation to areas; and add and
 * delete Correction factors which modify their Effective Sweep
 * Rate according to the terrain and vegetation present.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 02/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 21/04/01 |  2  | Updated.  Major changes in functionality for stage
 *     |          |     | 2.  Type of POD changed to double.
 *----------------------------------------------------------------------------
 * GT  | 27/04/01 |  3  | Updated.  Now stores assignments using class
 *     |          |     | Assignment.
 *----------------------------------------------------------------------------
 * GT  | 07/05/01 |  4  | Updated.  Now stores only one assignments to each
 *     |          |     | Area for each SRU.  Does not store assignments
 *     |          |     | with Resource Hours 0.
 *----------------------------------------------------------------------------
 * GT  | 25/05/01 |  5  | Updated.  Now handles correction factors.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 5.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#ifndef _Resource_h_
#define _Resource_h_
#define UNSPECIFIED -1.0	// Correction factor has not been specified
#define NOCORRECTION 0		// Correction factor should not be taken into account when calculating effective sweep rate
#include <vector>
#include "Assignmt.h"
#include "DataLimt.h"

using namespace std;

class Resources
{
	private:
		/*
		 * SRU (Search and Rescue Unit) is a single record containing the
		 * Resource Number, Resource Type, POD, ESW, Speed and Resource-Hours
		 * available for that SRU.  It also stores assignments for the SRU,
		 * and correction factors (which adjust its effective sweeping rate
		 * for different combination of terrain and vegetation).
		 */
		class SRU
		{
		public:
			/*
			 * Constructor to create a new, valid SRU.
			 * All numeric data members are initialised to minimum
			 * values.
			 * myResourceType is initially blank.
			 * myAssignments begins empty (by default).
			 * All correction factors are initially set to UNSPECIFIED.
			 *
			 * A constructor with arguments to specify initial values is
			 * NOT provided - this ensures that the "set" functions, which
			 * check the data passed to them, are used to enter data
			 * into SRUs.
			 */
			SRU(void)
			: myResourceNum(DataLimits::resourceNum_min),
			  myResourceType(""),
			  myPOD(DataLimits::POD_min),
			  myESW(DataLimits::ESW_min),
			  mySpeed(DataLimits::speed_min),
			  myHoursAvail(DataLimits::hoursAvailable_min)
			{
				int terrain, vegetation;
				for (terrain=DataLimits::terrain_min; terrain<=DataLimits::terrain_max; terrain++)
				{
					for (vegetation=DataLimits::vegetation_min; vegetation<=DataLimits::vegetation_max; vegetation++)
					{
						myCorrectionFactors[terrain][vegetation] = UNSPECIFIED;
					}
				}
			}
			inline int getResourceNum(void) const { return myResourceNum; }
			bool setResourceNum(int resourceNum);
			inline string getResourceType(void) const { return myResourceType; }
			// All strings are considered to be valid Resource Types
			inline bool setResourceType(const string& resourceType) { myResourceType = resourceType;  return true; }
			inline double getPOD(void) const { return myPOD; }
			bool setPOD(double POD);
			inline double getESW(void) const { return myESW; }
			bool setESW(double ESW);
			inline double getSpeed(void) const { return mySpeed; }
			bool setSpeed(double speed);
			inline int getHoursAvail(void) const	{ return myHoursAvail; }
			bool setHoursAvail(int hoursAvail);

			inline static const bool isValidCorrectionFactor(double factor) { return (factor>=DataLimits::correctionFactor_min && factor<=DataLimits::correctionFactor_max); }
			bool isCorrectionFactorSet(int terrain, int vegetation);
			bool setCorrectionFactor(int terrain, int vegetation, double factor);
			double getCorrectionFactor(int terrain, int vegetation);
			bool deleteCorrectionFactor(int terrain, int vegetation);
			void deleteCorrectionFactors(void);
			void viewCorrectionFactors(void);
			inline vector<Assignment> getAssignments(void) const	{ return myAssignments; }
			bool addAssignment(const Assignment& theAssignment);
			bool deleteAssignment(int areaNum);
			inline void deleteAssignments(void) { myAssignments.clear(); }
			void sortAssignAreaNum(void);
			double getHoursRemaining(void);
			bool hoursRemaining(void);
			double getHoursAssigned(void);
			double getEffectiveSweepRate(int terrain = NOCORRECTION, int vegetation = NOCORRECTION);
			string getSRUString(void);
			/*
			 * Predicate < object for comparing SRUs by Resource Number.
			 * If sru_lt is an SRU::ltResNum object, then
			 * sru_lt(sru1, sru2) will return true if sru1's Resource Number
			 * is less than sru2's Resource Number.
			 */
			class ltResNum
			{
				public:
					inline bool operator() (const SRU& sru1, const SRU& sru2) const
					{ return sru1.getResourceNum() < sru2.getResourceNum(); }
			};
		private:
			int myResourceNum;
			string myResourceType;
			double myPOD;
			double myESW; /* Effective Sweep Width (m) */
			double mySpeed; /* Speed (km/h) */
			int myHoursAvail;
			/*
			 * myCorrectionFactors[x][y], DataLimits::terrain_min<=x<=DataLimits::terrain_max,
			 * DataLimits::vegetation_min<=y<=DataLimits::vegetation_max,
			 * is the correction factor for terrain type x and vegetation type y.
			 *
			 * myCorrectionFactors[x][0] is reserved for a default correction factor for terrain
			 * type x; myCorrectionFactors[0][y] is reserved for a default correction factor for
			 * vegetation type y.  (Default correction factors for terrain/vegetation not
			 * currently implemented.)
			 *
			 * NOTE: It is assumed here that DataLimits::terrain_min, DataLimits::terrain_max,
			 * DataLimits::vegetation_min and DataLimits::vegetation_max are all positive
			 * integers.
			 */
			double myCorrectionFactors[DataLimits::terrain_max + 1][DataLimits::vegetation_max + 1];
			vector<Assignment> myAssignments;
		};
	public:
		/* Default constructor is sufficient */
		/*
		 * Returns true if an SRU with the specified Resource
		 * Number is present in SRUlist, false otherwise.
		 */
		inline bool isSRU(int resourceNum) { return (findSRU(resourceNum) != SRUlist.end()); }
		vector<int> getResourceNumList(void);
		bool loadSRUs(string filename);
		bool deleteSRU(int resourceNum);
		inline void deleteAllSRUs(void) { SRUlist.clear(); }
		bool userEnterSRU(void);
		bool userModifySRU(int resourceNum);
		void viewSRU(int resourceNum);
		void viewAllSRUs(void);
		void outputAllSRUs(ostream& out);
		bool userEnterCorrectionFactor(int resourceNum);
		bool userDeleteCorrectionFactor(int resourceNum);
		bool deleteCorrectionFactors(int resourceNum);
		void viewCorrectionFactors(int resourceNum);
		bool addAssignment(int resourceNum, const Assignment& theAssignment);
		bool deleteAssignment(int resourceNum, int areaNum);
		bool deleteAssignments(int resourceNum);
		vector<Assignment> getAssignments(int resourceNum);
		void viewAssignments(int resourceNum);
		int getNumResources(void);
		void deleteAllAssignments(void);
		void viewAllAssignments(void);
		void outputAllAssignments(ostream& out);
		double getHoursRemaining(int resourceNum);
		double getESW(int resourceNum);
		double getSpeed(int resourceNum);
		double getCorrectionFactor(int resourceNum, int terrain, int vegetation);
		double getEffectiveSweepRate(int resourceNum, int terrain = NOCORRECTION, int vegetation = NOCORRECTION);
		bool hoursRemaining(int resourceNum);
		bool anyHoursRemaining(void);
		double getAreaEffectivelySweptRemaining(void);
		bool menu(void);  /* menu function for users */
		void test(void);   /* testing function */
	private:
		/*
		 * Finds the SRU with a specified Resource Number.
		 * If an SRU with the specified Resource Number is
		 * present, findSRU() returns an iterator to the
		 * first SRU in the SRUlist which has that Resource Number.
		 * If an SRU with the specified Resource Number is not
		 * present, findSRU() returns an iterator equal to SRUlist.end().
		 */
		vector<SRU>::iterator findSRU(int resourceNum);
		void sortResNum(void);
		bool addSRU(const SRU& sru);
	private:
		vector<SRU> SRUlist;
};
#endif
