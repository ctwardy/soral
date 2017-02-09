/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file itr_res.cpp
 *  \brief itr_res.cpp Implementation of resource iterator.
 *
 *
 * Specific implementation of resource iterator. See Allocatn.h for
 * description of ResourceIterator class. Implements the standard
 * iterator operators.
 *
 * Author : Michael Eldridge
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+---------+-----+-----------------------------------------------------
 * Who |   When  | Ver | What
 *-----+---------+-----+-----------------------------------------------------
 * ME  | 05dec01 |  1  | Created.
 *-----+---------+-----+-----------------------------------------------------
 * GT  | 02feb02 |  2  | Fixed bug: now works correctly when 
 *     |         |     | myAllocation->myNumResources is not equal to 
 *     |         |     | myAllocation->myNumAreas.
 *-----+---------+-----+-----------------------------------------------------
 * GT  | 25feb02 |  3  | Modifications (bug fixing).
 *-----+---------+-----+-----------------------------------------------------
 * ASO | 10dec02 |  4  | Updated after removing container base class
 *-----+---------+-----+-----------------------------------------------------
 * ASO | 10dec02 |  5  | Re-written for new iterator design
 *-----+---------+-----+-----------------------------------------------------
 * crt | 10mar03 |  6  | Cleaned after code review. Removed get(), cleaned
 *     |         |     | comments, replaced "-1" with enum from .h. (cvs 1.5)
 *-----+---------+-----+-----------------------------------------------------
 * crt | 11mar03 |  7  | Added cmnts abt functions not implemented.
 *-----+---------+-----+-----------------------------------------------------
 * crt | 18apr03 |  8  | Added destructor. Bug spotted by GT.
 *-----+---------+-----+-----------------------------------------------------
 * crt | 01may03 |  9  | Operator* returns object, not pointer
 *-----+---------+-----+-----------------------------------------------------
 * \endverbatim
 */

//===========================================================================//
// Written by Michael Eldridge, Gareth Thompason, and Andre Oboler           //
//                                                       http://sarbayes.org //
//---------------------------------------------------------------------------//
// The SORAL implementation is free software, but it is Copyright (C)        //
// 2001-2003 the authors and Monash University (the SARBayes project).       //
// It is distributed under the terms of the GNU General Public License.      //
// See the file COPYING for copying permission.                              //
//                                                                           //
// If those licencing arrangements are not satisfactory, please contact us!  //
// We are willing to offer alternative arrangements if the need should arise.//
//                                                                           //
// THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED OR //
// IMPLIED.  ANY USE IS AT YOUR OWN RISK.                                    //
//                                                                           //
// Permission is hereby granted to use or copy this program for any purpose, //
// provided the above notices are retained on all copies.  Permission to     //
// modify the code and to distribute modified code is granted, provided the  //
// above notices are retained, in accordance with the GNU GPL.               //
//===========================================================================//

#include "Allocatn.h"
#include "containr.h"
#include <iostream>
#include <cstdlib>

using namespace std;

/**** ResourceIterator() *****************************************************/
/// Frm an allocation & an area, make an iterator for resources assigned there
/**
 * Constructor that takes an allocation (could be any sub type)
 * and an area number and finds the first resource assigned to that
 * area in this allocation. Uses whatever definition of "first"
 * the allocation defined when it implemented firstRes(area).
 *
 */
ResourceIterator::ResourceIterator(const Allocation& p_allocation, const int p_area_num)
  :	myAllocation(p_allocation),
		myArea(p_area_num)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating a resource iterator (ResourceIterator::ResourceIterator)" << endl;
	#endif

	current=myAllocation.firstRes(myArea);


	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished creating a resource iterator (ResourceIterator::ResourceIterator)" << endl;
	#endif
}

/**** ~ResourceIterator() *************************************************/
/// Destructor: clean up memory allocated in "current".
/**
 * Author: Charles Twardy 18apr03, for bug spotted by GT.
 */
ResourceIterator::~ResourceIterator()
{
  delete current;
}


/**** operator++() **********************************************************/
/// Increments the iterator to the next resource assigned to this area.
/**
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 */

void ResourceIterator::operator++(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Incrementing a resource iterator (ResourceIterator::operator++)" << endl;
	#endif

	// If at end of list, remain there
	if (current == NULL)
	{
		return;
	}

	// Otherwise move to next item or end of list
	ResourceAssignment* temp;
	temp=myAllocation.nextRes(myArea,current->getResourceNum());
	delete current;
	current=temp;

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished incrementing a resource iterator (ResourceIterator::operator++)" << endl;
	#endif
}

/**** operator*() ***********************************************************/
/// Returns the object pointed to by this iterator.
/**
 * Rewritten: Andre Oboler (ASO)
 */

ResourceAssignment ResourceIterator::operator*(void) const
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Returning the resource pointed to by the iterator (ResourceIterator::operator*())" << endl;
	#endif

	if (atEnd())
	{
		cerr << "Warning: There is no current resource assignment. " 
			 << "Returning (0,0)." << endl;
		// Perhaps throw an exception warning here.
		return ResourceAssignment(0,0);
	}

	return ResourceAssignment (current->getResourceNum(), 
							   current->getTime()         );

}

/**** atEnd() **************************************************************/
/// Returns true iff the iterator is at the end of the list.
/**
 * Author : Andre Oboler
 */

bool ResourceIterator::atEnd(void) const
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Checking to see if the iterator is at the end (ResourceIterator::atEnd)" << endl;
	#endif

	if (current == NULL)
	{
		return true;
	}

	return false;

}
