/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file itr_assn.cpp
 *  \brief itr_assn.cpp Implementation of assigned areas iterator.
 *
 * Specific implementation of assigned areas iterator. Implements all of the 
 * standard iterator operators but specfically for the area/resource structure 
 * of this library.  
 *
 * <b><u>Version History</u></b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 05/12/01 |  1  | Created.                                            
 *----------------------------------------------------------------------------
 * GT  | 25/02/02 |  2  | Modifications (bug fixing).
 *----------------------------------------------------------------------------
 * ASO | 10/12/02 |  3  | Re-written to meet new specs
 *----------------------------------------------------------------------------
 * \endverbatim
 */

#include "Allocatn.h"
#include "containr.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

//Altered by Gareth Thompson 24-2-2002
//myAssignments has been moved to the CharnesCooper class, so these iterators
//are now specific to that class

// ASO 29/11/02 Lines below swapped back.
/// constructor that takes an allocation (could be any sub type) and then iterates over it

/// From an allocation create an object to iterate over the areas with an allocation of resources
/*****************************************************************/
/**
 * Constructor that takes an allocation (could be any sub type) 
 * and then allows the user to iterates over 
 * all areas that have one or more resource allocated to them.
 *
 * NOTE: Unlike the other iterators, this one only returns the area number
 *
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 */

ActiveAreasIterator::ActiveAreasIterator(Allocation& p_allocation) 
//ActiveAreasIterator::ActiveAreasIterator(CharnesCooper *p_allocation) 
:	myAllocation(p_allocation)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating an assigned area iterator (ActiveAreasIterator::ActiveAreasIterator)" << endl;
	#endif
	
	current=myAllocation.firstArea();

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished creating an assigned area iterator (ActiveAreasIterator::ActiveAreasIterator)" << endl;
	#endif
}


/// use default destructor 
/******************************************************************************/
/** 
 * ~ActiveAreasIterator
 *
 * Reclaims the memory used by the iterator. As no memory is assigned, this function is 
 * empty.
 *
 * Author : Michael Eldridge
 * 
 */

ActiveAreasIterator::~ActiveAreasIterator()
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Destroying an assigned area iterator (AreaIterator::~ActiveAreasIterator)" << endl;
	#endif
}

/// Increments the iterator to the next assigned area. 
/*********************************************************************************/
/** perator++
 *
 * Increments the iterator to the next assigned area. 
 *
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 * 
 */

void ActiveAreasIterator::operator++(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Incrementing an assigned area iterator (ActiveAreasIterator::operator++)" << endl;
	#endif

	// If at end of list, remain there
	if (current == -1)
	{
		return;
	}

	// Other wise move to next item or end of list
		
	current=myAllocation.nextArea(current);
	
	

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished incrementing an assigned area iterator (ActiveAreasIterator::operator++)" << endl;
	#endif
}

/// Returns the object pointed to by this iterator.
/*************************************************************************************/
/**
 * get
 *
 * Returns the object pointed to by this iterator.
 *
 * Note : At the moment the iterator will not go off the end of the list.
 *
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 * 
 */


// Or perhaps it should be: ActiveArea *ActiveAreasIterator::get(void)
int ActiveAreasIterator::get(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Returning the assigned area pointed to by the iterator (ActiveAreasIterator::operator())" << endl;
	#endif
	
	return current;
}

/// Checks to see whether the iterator is at the end of the list.
/************************************************************************************/
/**
 * atEnd
 *
 * Checks to see whether the iterator is at the end of the list.  
 *
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 * 
 */
bool ActiveAreasIterator::atEnd(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Checking to see if the iterator is at the end (Iterator::atEnd)" << endl;
	#endif

	if (current==-1)
	{
		return true;
	}
	return false;
}

/// Returns the object pointed to by this iterator.
/************************************************************************************/
/**
 * operator*()
 *
 * Returns the object pointed to by this iterator.
 *
 * An alias for get
 *
 */

int ActiveAreasIterator::operator*(void)
{
	return get();
}
