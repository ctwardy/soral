/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file itr_res.cpp
 *  \brief itr_res.cpp Implementation of resource iterator.
 * 
 *
 * Specific implementation of resource iterator. Implements all of the 
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
 * GT  | 02/02/02 |  2  | Fixed bug: now works correctly when myAllocation->myNumResources
 *     |          |     | is not equal to myAllocation->myNumAreas.
 *----------------------------------------------------------------------------
 * GT  | 25/02/02 |  3  | Modifications (bug fixing).
 *----------------------------------------------------------------------------
 * ASO | 10/12/02 |  4  | Updated after removing contain base class
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
 * ResourceIterator
 *
 * Base constructor for the iterator. Requires a pointer to the Allocation object which 
 * the iterator is to operate on.
 *
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 * 
 */

//Altered by Gareth Thompson 24-2-2002
//myAssignments has been moved to the CharnesCooper class, so these iterators
//are now specific to that class

// ASO 29/11/02 Lines below swapped
ResourceIterator::ResourceIterator(Allocation& p_allocation, int tempArea)
//ResourceIterator::ResourceIterator(CharnesCooper *p_allocation, int p_resource_no)
:	myAllocation(p_allocation)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating a resource iterator (ResourceIterator::ResourceIterator)" << endl;
	#endif

	area=tempArea;
	current=myAllocation.firstRes(area);


	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished creating a resource iterator (ResourceIterator::ResourceIterator)" << endl;
	#endif
}

/*****************************************************************************************
 * ~ResourceIterator
 *
 * Reclaims the memory used by the iterator. As no memory is assigned, this function is 
 * empty.
 *
 * Author : Michael Eldridge
 * 
 */

/// use default destructor		
ResourceIterator::~ResourceIterator()
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Destroying a resource iterator (AreaIterator::~ResourceIterator)" << endl;
	#endif
}

/*****************************************************************************************
 * operator++
 *
 * Increments the iterator to the next resource assigned to this area. 
 *
 * Author : Michael Eldridge
 * Rewritten: Andre Oboler (ASO)
 * 
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

	// Other wise move to next item or end of list
	ResourceAssignment* temp;
	temp=myAllocation.nextRes(area,current->getResourceNum());
	delete current;
	current=temp;

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished incrementing a resource iterator (ResourceIterator::operator++)" << endl;
	#endif
}

/*****************************************************************************************
 * operator*
 *
 * Returns the object pointed to by this iterator.
 *
 * Rewritten: Andre Oboler (ASO)
 * 
 */

//Altered by Gareth Thompson 24-2-2002, to avoid returning a reference to a local variable
ResourceAssignment *ResourceIterator::get(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Returning the resource pointed to by the iterator (ResourceIterator::operator())" << endl;
	#endif

	// check if pointing to a valid object and warn in testing mode (but continue)
	if (current == NULL)
	{
		#ifdef _ALLOCATION_TESTMODE
		cout << "Warning: There is no current resource assignment" << endl;
		#endif
		// Perhaps throw an exception warning here.
	}
	// Note current will ALWAYS be a valid address, although it may be resource -1 for time 0
	// if there is no allocation to dereference (i.e. there were none to start with or you 
	// moved past the last one.
	return current;
}



/*****************************************************************************************
 * operator*()
 *
 * Returns the object pointed to by this iterator.
 *
 * An alias for get
 *
 */
ResourceAssignment *ResourceIterator::operator*(void)
{
	return get();
}

/*****************************************************************************************
 * atEnd
 *
 * Checks to see whether the iterator is at the end of the list.
 * Returns true if at end
 *
 * Author : Andre Oboler
 * 
 */

bool ResourceIterator::atEnd(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Checking to see if the iterator is at the end (Iterator::atEnd)" << endl;
	#endif

	if (current == NULL)
	{
		return true;
	}

	return false;

}
