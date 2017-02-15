/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file UserDef.h
 *  \brief UserDef.h Create a user-defined (manual) allocation.
 *
 *
 * Allows the user to create their own allocations (including by
 * modifying existing allocations) and then evaluating them.
 *
 * Author: Andre Oboler
 *
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+---------+-----+-----------------------------------------------------
 * Who |   When  | Ver | What
 *-----+---------+-----+-----------------------------------------------------
 * crt | 04mar03 |  1  | Created file from userDef stuff in
 *     |         |     | old Allocatn.h
 *-----+---------+-----+-----------------------------------------------------
 * crt | 04mar03 |  2  | Changed name from userDef to UserDef.  
 *     |         |     | Added UNALLOCATED_AREA so we don't use -1.
 *     |         |     | Added helper functions isValidArea, isValidResource.
 *-----+---------+-----+-----------------------------------------------------
 * \endverbatim
 */

//============================================================================//
// Written by Andre Oboler                               http://sarbayes.org  //
//----------------------------------------------------------------------------//
// The SORAL implementation is free software, but it is Copyright (C)         //
// 2001-2003 the authors and Monash University (the SARBayes project).        //
// It is distributed under the terms of the GNU General Public License.       //
// See the file COPYING for copying permission.                               //
//                                                                            //
// If those licencing arrangements are not satisfactory, please contact us!   //
// We are willing to offer alternative arrangements, if the need should arise.//
//                                                                            //
// THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED OR  //
// IMPLIED.  ANY USE IS AT YOUR OWN RISK.                                     //
//                                                                            //
// Permission is hereby granted to use or copy this program for any purpose,  //
// provided the above notices are retained on all copies.  Permission to      //
// modify the code and to distribute modified code is granted, provided the   //
// above notices are retained, in accordance with the GNU GPL.                //
//============================================================================//


#ifndef _UserDef_h_
#define _UserDef_h_

#include "Allocatn.h"
#include <vector>
#include <math.h>
#include "containr.h"
#include "Array2D.h"
#include <valarray>

using namespace std;
enum {UNALLOCATED_AREA = -1}; // Keeps track of resources not yet allocated.

/// The user-defined Allocation class. User may create his own allocation here.
/*****************************************************************************/
/**
 * UserDef:
 *
 * Allocation class for user-specified allocations. This class allows the user
 * to create an allocation from scratch, or to import an existing allocation 
 * and tweak it. This class is needed because search managers will almost 
 * always be aware of more constraints than the current program can handle.
 *
 * Note: The calcAllocation function does nothing in UserDef.
 *
 * Author : Andre Oboler
 */

class UserDef : public Allocation
{
	// Constructors.
	
	public:
		UserDef(const int p_no_resources, const int p_no_areas, const Array2D& p_effectiveness,
			const valarray<double> p_available, const valarray<double> p_POC);

		UserDef(const UserDef &p_allocation);
		UserDef(Allocation& oldAllocation);

		~UserDef();

	// Allocation Functions.

	protected:

	public:
		void clearAll();
		void clearArea(const int area);
		void calcAllocation(void);
		void clearResource(const int resource);
		void remove(const int fromArea, const int resource, const double amount);
		void remove(const int fromArea, const int resource);
		void add(const int toArea, const int resource, const double amount);
		void add(const int toArea, const int resource);
		void move(const int fromArea, const int toArea, const int resource);
		void move(const int fromArea, const int toArea, const int resource, const double amount);
		//ASO 23mar03 \todo Add: bool haveUnallocatedResources();
		//ASO 23mar03 \todo Add: valarray<double> getUnallocatedResources(); 

	// Functions.


	// Added by ASO 5/12/02
	protected:
		ActiveArea* firstArea(void) const;
		ActiveArea* nextArea(const int currentArea) const;
		AreaAssignment* firstArea(const int resource) const;
		AreaAssignment* nextArea(const int resource, const int currentArea) const; 
		ResourceAssignment* firstRes(const int area) const;
		ResourceAssignment* nextRes(const int area, const int currentResource) const; 

	// Test functions
	public:
		//Removed ASO 17/12/02 void SetTableValue(int p_x, int p_y, int p_value);
		//Removed - ASO 17/12/02 void PrintTable(void);

	// Utility functions. \todo Why is assignment here?
	private:
		UserDef &operator=(const UserDef &p_allocation);
		bool isValidArea(const int area) const;
		bool isValidResource(const int resource) const;

	// Member variables

	private:
		/// The set of assignments, stored as a simple matrix.
		Array2D myAssignments;

		/// myUnallocatedResources stores the number of unallocated hours for 
		/// each resource. As hours are assigned this value must be adjusted.
		valarray<double> myUnallocatedResources;


	// Friend Classes.
	// ASO 9/12/02
	// note could make friend _functions_ rather than _class_ to achieve 
   // better coupling. For ex.: iterators get access only to the 2 functions 
	// they need (a first and a next)

	public:
		//friend class Iterator;
		/// So that the AreaIterator can access the first and next functions
		friend class AreaIterator;
		/// So that the ResourceIterator can access the first and next functions
		friend class ResourceIterator;
		/// So that the ActiveAreasIterator can access the first and next fnctns
		friend class ActiveAreasIterator;
};
#endif
