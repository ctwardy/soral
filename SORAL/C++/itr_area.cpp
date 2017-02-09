/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file itr_area.cpp
 *  \brief itr_area.cpp Implementation of area iterator
 *
 *
 * Specific implementation of area iterator. Implements all of the standard
 * iterator operators but specfically for the area/resource structure of this
 * library.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+---------+-----+-----------------------------------------------------
 * Who |   When  | Ver | What
 *-----+---------+-----+-----------------------------------------------------
 * ME  | 05dec01 |  1  | Created.
 *-----+---------+-----+-----------------------------------------------------
 * GT  | 25feb02 |  2  | Modifications (bug fixing).
 *-----+---------+-----+-----------------------------------------------------
 * ASO | 28nov02 |  3  | Iterator class removed, previously inherited functions
 *     |         |     | added to this and other iterator like classes
 *-----+---------+-----+-----------------------------------------------------
 * ASO | 10dec03 |  5  | Re-written for new iterator design
 *-----+---------+-----+-----------------------------------------------------
 * crt | 06mar03 | 5.5 | Cleaned. Changed to myArea, myResource. Compiles.
 *     |         |     | Still needs another going-over. (cvs 1.5)
 *-----+---------+-----+-----------------------------------------------------
 * crt | 10mar03 |  6  | More cleaning. Mostly OK. (cvs 1.6)
 *-----+---------+-----+-----------------------------------------------------
 * crt | 11mar03 |  7  | Added cmnts abt functions not implemented.
 *-----+---------+-----+-----------------------------------------------------
 * crt | 18apr03 |  8  | Added destructor. Bug spotted by GT. Fixed doc.
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

/**** AreaIterator() *********************************************************/
/// Create an iterator over the areas for that resource
/**
 * Constructor that takes an allocation (could be any sub type) and a 
 * resource number and creates an iterator over all areas that have that 
 * resource allocated to them, returning AreaAssignments.
 * It begins with the first area to which that resource has been assigned, 
 * as implemented by the specific allocation type being called.
 */
AreaIterator::AreaIterator(const Allocation& p_allocation, const int p_resource_num)
  :  myAllocation(p_allocation),
	 myResource(p_resource_num)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating an area iterator (AreaIterator::AreaIterator)" << endl;
	#endif

	current=myAllocation.firstArea(myResource);


	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished creating an area iterator (AreaIterator::AreaIterator)" << endl;
	#endif
}

/**** ~AreaIterator() *************************************************/
/// Destructor: clean up memory allocated in "current".
/**
 * Author: Charles Twardy 18apr03, for bug spotted by GT.
 */
AreaIterator::~AreaIterator()
{
  delete current;
}

/**** operator++() ***********************************************************/
/// Increments the iterator to the next area for this resource.
/**
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 */

void AreaIterator::operator++(void)
{
#ifdef _ALLOCATION_TESTMODE
  cout << "Incrementing an area iterator (AreaIterator::operator++)" << endl;
#endif

   if (atEnd())
	{
		return;
	}

	// Otherwise move to next item or end of list
	int areaNumber = current->getAreaNum();
	AreaAssignment* temp = myAllocation.nextArea(myResource, areaNumber);
	delete current;
	current=temp;

#ifdef _ALLOCATION_TESTMODE
	cout << "Finished incrementing an area iterator (AreaIterator::operator++)" 
		  << endl;
#endif
}



/// Returns the object pointed to by this iterator.
/**** operator*() ***********************************************************/
/**
 * Author : Andre Oboler (ASO)
 */

AreaAssignment AreaIterator::operator*(void) const
{
#ifdef _ALLOCATION_TESTMODE
  cout << "Returning the area pointed to by the iterator (AreaIterator::operator())" << endl;
#endif

		// check if pointing to a valid object and warn (but continue)
	if (atEnd())
	{
		cerr << "Warning: There is no current area assignment. " 
			 << "Returning (0,0)." << endl;
		// Perhaps throw an exception warning here.
		return AreaAssignment(0,0);
	}

	return AreaAssignment (*current);
}


/**** atEnd() **************************************************************/
/// Checks to see whether the iterator is at the end of the list.
/**
 * Author : Michael Eldridge
 */

bool AreaIterator::atEnd(void) const
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

