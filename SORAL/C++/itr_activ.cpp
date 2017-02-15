/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file itr_activ.cpp
 *  \brief itr_activ.cpp Implementation of active areas iterator.
 *
 * Specific implementation of active areas iterator: an iterator that
 * iterates through all the areas which have resources assigned to them.
 * (In a search with many areas, this will be a small percentage of 
 * the total number of areas.)
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 05/12/01 |  1  | Created.                                            
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 25/02/02 |  2  | Modifications (bug fixing).
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 10/12/02 |  3  | Re-written to meet new specs
 *-----+----------+-----+-----------------------------------------------------
 * crt | 10mar03  |  4  | Cleaned after code review. Removed get(), cleaned
 *     |          |     | comments, replaced "-1" with enum from .h. (cvs 1.6)
 *-----+----------+-----+-----------------------------------------------------
 * crt | 11mar03  |  5  | Added cmnts abt functions not implemented.
 *-----+----------+-----+-----------------------------------------------------
 * crt | 18apr03  |  6  | Added destructor. Bug spotted by GT.
 *-----+----------+-----+-----------------------------------------------------
 * crt | 01may03  |  7  | Operator* returns object, not pointer
 *-----+----------+-----+-----------------------------------------------------
 * \endverbatim
 */

//===========================================================================//
// Written by Michael Eldridge, Gareth Thompson, & Andre Oboler              //
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

/**** ActiveAreasIterator() **************************************************/
/// From an allocation create an object to iterate over assigned (active) areas
/**
 * Constructor that takes an allocation (could be any sub type) 
 * and then allows the user to iterates over ONLY the areas which have
 * any resources assigned to them. (And all of those.)
 *
 * The new object begins with the first active area in this allocation.
 *
 * NOTE: Unlike the other iterators, this one only returns the area number
 *
 * WARNING: Does not check to make sure it got passed a proper allocation.
 * 
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 */

ActiveAreasIterator::ActiveAreasIterator(const Allocation& p_allocation) 
  :	myAllocation(p_allocation)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating an active area iterator (ActiveAreasIterator::ActiveAreasIterator)" << endl;
	#endif
	
	current=myAllocation.firstArea();

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished creating an active area iterator (ActiveAreasIterator::ActiveAreasIterator)" << endl;
	#endif
}

/**** ~ActiveAreasIterator() *************************************************/
/// Destructor: clean up memory allocated in "current".
/**
 * Author: Charles Twardy 18apr03, for bug spotted by GT.
 */
ActiveAreasIterator::~ActiveAreasIterator()
{
  delete current;
}

/**** operator++() **********************************************************/
/// Increments the iterator to the next active (ie assigned) area. 
/**
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 */

void ActiveAreasIterator::operator++(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Incrementing an active area iterator (ActiveAreasIterator::operator++)" << endl;
	#endif

	// If at end of list, remain there
	if (atEnd())
	{
		return;
	}

	// Otherwise move to next item or end of list
   int currAreaNum = current->getActiveAreaNum();
	ActiveArea* temp = myAllocation.nextArea(currAreaNum);
	delete current;
	current = temp;

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished incrementing an active area iterator (ActiveAreasIterator::operator++)" << endl;
	#endif
}

/**** operator*() **********************************************************/
/// Returns the object pointed to by this iterator.
/**
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 */

ActiveArea ActiveAreasIterator::operator*(void) const
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Returning the active area pointed to by the iterator (ActiveAreasIterator::operator*)" << endl;
	#endif
	
	if (atEnd())
	{
		cerr << "Warning: There is no current active area. " 
			 << "Returning 0." << endl;
		// Perhaps throw an exception warning here.
		return ActiveArea(0);
	}

	return ActiveArea (current->getActiveAreaNum());
}

/**** atEnd() **************************************************************/
/// Checks to see whether the iterator is at the end of the list.
/**
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 */
bool ActiveAreasIterator::atEnd(void) const
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Checking to see if the iterator is at the end (Iterator::atEnd)" << endl;
	#endif

	if (current==NULL)
	{
		return true;
	}
	return false;
}


