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
 * ASO | 28/11/02 |  3  | Iterator class removed, previously inherited functions 
 *     |          |     | added to this and other iterator like classes
 *----------------------------------------------------------------------------
 * ASO | 10/12/02 |  5  | Re-written for new iterator design
 *----------------------------------------------------------------------------
 * \endverbatim
 */

#include "Allocatn.h"
#include "containr.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

/*****************************************************************************************
 * AreaIterator
 *
 * Base constructor for the iterator. Requires a pointer to the CharnesCooper object which 
 * the iterator is to operate on.
 *
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 * 
 */

//Altered by Gareth Thompson 24-2-2002
//myAssignments has been moved to the CharnesCooper class, so these iterators
//are now specific to that class
/// From an allocation and resource create an object to iterate over the areas using the resource
		/**
		 * Constructor that takes an allocation (could be any sub type) 
		 * and a resource number and then allows the user to iterates over 
		 * all areas that have that resource allocated to them 
		 * (and how long they are there for)
		 */
AreaIterator::AreaIterator(Allocation& p_allocation, int tempResource)
//AreaIterator::AreaIterator(CharnesCooper *p_allocation, int p_area_no)
:	myAllocation(p_allocation)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating an area iterator (AreaIterator::AreaIterator)" << endl;
	#endif
	
	resource = tempResource; 
	current=myAllocation.firstArea(resource);
	

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished creating an area iterator (AreaIterator::AreaIterator)" << endl;
	#endif
}

/// use default destructor
/***********************************************************************************/
/**
 * ~AreaIterator
 *
 * Reclaims the memory used by the iterator. As no memory is assigned, this function is 
 * empty.
 *
 * Author : Michael Eldridge
 * 
 */

AreaIterator::~AreaIterator()
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Destroying an area iterator (AreaIterator::~AreaIterator)" << endl;
	#endif
}

/// Increments the iterator to the next resource assigned to this area. 
/***********************************************************************************/
/**
 * operator++
 *
 * Increments the iterator to the next resource assigned to this area. 
 *
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 * 
 */

void AreaIterator::operator++(void)
{
	int areaNumber;
	#ifdef _ALLOCATION_TESTMODE
		cout << "Incrementing an area iterator (AreaIterator::operator++)" << endl;
	#endif

		// If at end of list, remain there
	if (current == NULL)
	{
		return;
	}

	// Other wise move to next item or end of list
	AreaAssignment* temp;
	areaNumber=current->getAreaNum();
	cout << areaNumber;
	temp=myAllocation.nextArea(resource, areaNumber);
	delete current;
	current=temp;

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished incrementing an area iterator (AreaIterator::operator++)" << endl;
	#endif
}



/// Returns the object pointed to by this iterator.
/*************************************************************************************/
/**
 * operator*
 *
 * Returns the object pointed to by this iterator.
 *
 *
 * Author : Andre Oboler (ASO)
 * 
 */

//Altered by Gareth Thompson 24-2-2002, to avoid returning a reference to a local variable
AreaAssignment* AreaIterator::get(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Returning the area pointed to by the iterator (AreaIterator::operator())" << endl;
	#endif
	
		// check if pointing to a valid object and warn in testing mode (but continue)
	if (current == NULL)
	{
		#ifdef _ALLOCATION_TESTMODE
		cout << "Warning: There is no current area assignment" << endl;
		#endif
		// Perhaps throw an exception warning here.
	}
	// Note current will ALWAYS be a valid address, although it may be area -1 for time 0
	// if there is no allocation to dereference (i.e. there were none to start with or you 
	// moved past the last one.
	return current;
}

/// Returns the object pointed to by this iterator.
/*************************************************************************************/
/**
 * operator*()
 *
 * Returns the object pointed to by this iterator.
 *
 * An alias for get
 *
 */

AreaAssignment* AreaIterator::operator*(void)
{
	return get();
}

/// Checks to see whether the iterator is at the end of the list.  
/*************************************************************************************/
/**
 * atEnd
 *
 * Checks to see whether the iterator is at the end of the list.  
 *
 * Author : Michael Eldridge
 * 
 */

bool AreaIterator::atEnd(void)
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

