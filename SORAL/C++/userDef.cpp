/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file UserDef.cpp
 *  \brief UserDef.cpp Contains the UserDef Class's functions.
 * 
 * Contains the UserDef Class's functions.
 * UserDef is the allocation class that allows the user to set their own allocations.
 * Other childen of allocation should be able to convert to type UserDef so the user
 * can tweak the automatic allocation suggestions (to take account of human factors 
 * not known to the algorithm).
 *
 * NOTE: The movement functions are ordered fromArea, toArea, resource, amount.
 * While the order resource, amount, fromArea, toArea may make more intuitive sense,
 * the order used is consistent with the array structure[area][resource].
 * That is, in a function call, anything representing an area goes before the
 * thing representing a resource.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 26/12/02 |  1  | Created from Charnes-Cooper                         
 *-----+----------+-----+-----------------------------------------------------
 * crt | 13jan02  |  2  | Finished changing 'home base' from 0 to -1.
 *     |          |     | Documentation, some error-checking.
 *----------------------------------------------------------------------------
 * \endverbatim
 */

/********************
 * WORK IN PROGRESS *
 ********************
 * [TODO] ASO 30/12/02 - should not be using area zero but some other 
 * array of length numResource. Where this array lives is still to be decided
 * This change affect parts of this file.
 */
/// \todo [Is this still a to-do or did I just do it???] 
/// Don't use area 0 but an array of length numResource.

#include "Allocatn.h"
#include <iostream> // ASO 29/11/02 changed to iostream from iostream.h to meet the C++ standard

using namespace std; // ASO 29/11/02 needed as iostream declares function in std.

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// Create a user-defined allocation... ie an empty allocation matrix of the correct size
UserDef::UserDef(int p_no_resources, int p_no_areas, const Array2D& p_effectiveness,
		const vector<double>& p_available, const vector<double>& p_POC)
:	Allocation(p_no_resources, p_no_areas, p_effectiveness, p_available, p_POC),
	myAssignments(p_no_areas, p_no_resources)
	
{
	//memset(myAssignments, 0, (sizeof(double) * p_no_areas * p_no_resources)); 			

	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating a User-Defined search object (UserDef::UserDef)" << endl;
	#endif
}
/// Create a UserDef Allocation from an existing allocation (of another type)
UserDef::UserDef(Allocation& oldAllocation)
:	Allocation(oldAllocation.myNumResources, oldAllocation.myNumAreas, 
			   oldAllocation.myEffectiveness,
			   oldAllocation.myAvailable, oldAllocation.myPOC),	
	myAssignments(oldAllocation.myNumAreas, oldAllocation.myNumResources)	
{
	//memset(myAssignments, 0, (sizeof(double) * p_no_areas * p_no_resources)); 			

	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating a User-Defined search object (UserDef::UserDef(Allocation *oldAllocation))" << endl;
	#endif


	int tempArea;
	int tempResource;			
	ResourceAssignment *tempResourceAssignment;

	// Setting up the first entry using the "firstArea" function
	// Step 1: Get the data
	tempArea=oldAllocation.firstArea(); // first area
	tempResourceAssignment=oldAllocation.firstRes(tempArea); // resource / time pair
	tempResource=tempResourceAssignment->getResourceNum(); // First resource
	// Step 2: Store it
	myAssignments.value[tempArea][tempResource]=tempResourceAssignment->getTime();


	// Now use nextRes to get each value for this first area
	while (tempResourceAssignment != NULL)
	{
		// Step 1: Get the data
		tempResourceAssignment=oldAllocation.nextRes(tempArea, tempResource); // resource / time pair
		if (tempResourceAssignment != NULL)
		{
			tempResource=tempResourceAssignment->getResourceNum(); // First resource

			// Step 2: Store it
			myAssignments.value[tempArea][tempResource]=tempResourceAssignment->getTime();
		}

	}
	
	// move through the rest of the areas using nextArea
	for (;tempArea!=-1; tempArea=nextArea(tempArea)) // note use of sentinal value -1
	{
		tempResourceAssignment=oldAllocation.firstRes(tempArea); // resource / time pair
		
		// If there is a first allocation to this area, copy it over
		if (tempResourceAssignment != NULL)
		{
			tempResource=tempResourceAssignment->getResourceNum(); // First resource
			// Step 2: Store it
			myAssignments.value[tempArea][tempResource]=tempResourceAssignment->getTime();
		}

		// If there are more, copy them over too
		while (tempResourceAssignment != NULL)
		{
			// Step 1: Get the data
			tempResourceAssignment=oldAllocation.nextRes(tempArea, tempResource); // resource / time pair
			
			// If there is another get it
			if (tempResourceAssignment != NULL)
			{
				tempResource=tempResourceAssignment->getResourceNum(); // First resource

				// Step 2: Store it
				myAssignments.value[tempArea][tempResource]=tempResourceAssignment->getTime();
			}

		}

	}

	// No more areas with assignments
}

/// use default destructor
UserDef::~UserDef()
{

}


/// Moves an amount of a resource between areas
/***************************************************************************/
/**
 * move()
 *
 * Moves <em>amount</em> of <em>resource</em> from <em>fromArea</em> 
 * to <em>toArea</em>. 
 * This is the basic movement code, all other movement code should call this to
 * ensure the range checking only needs to be coded once and changed once if 
 * the specs change.
 *
 * Author: Andre Oboler (ASO)
 *
 */

void UserDef::move(int fromArea, int toArea, int resource, double amount)
{
	// Do some basic checking

	if(resource<0 || resource >= myNumResources)
	{
		// [TODO ASO] Possibly throw execption here.
		// Error is resource out of range.
		return;
	}
	
	// -1 is legal becuase it represents the unallocated pool
	if(fromArea<-1 || fromArea >= myNumAreas)
	{
		// [TODO ASO] Possibly throw execption here.
		// Error is from area out of range.
		return;
	}

	// -1 is legal becuase it represents the unallocated pool
	if(toArea < -1 || toArea >= myNumAreas)
	{
		// [TODO ASO] Possibly throw execption here.
		// Error is to area out of range.
		return;
	}

	if(amount < 0)
	{
		// [TODO ASO] Possibly throw execption here.
		// Error is amount to transfer is negetive.
		return;
	}


	if (fromArea==toArea)  // Silly request.  (crt 13jan02 added)
	  {
		 return;
	  }

	// Final check, do we have enough resource available to meet the transfer quota
	// If moving from the unallocated pool
	if (fromArea==-1)
	{
		if(myAvailable[resource]-amount < 0)
		{
			return;
		}
	}
	else // If moving from another area
	{

		if(myAssignments.value[fromArea][resource]-amount < 0)
		{
			// [TODO ASO] Possibly throw execption here.
			// Error is amount to transfer is more than the amount available.
			return;
		}
	}

	if (fromArea==-1) // If moving out of the unallocated pool
	{
		myAvailable[resource]=myAvailable[resource]-amount;		
		myAssignments.value[toArea][resource]=myAssignments.value[toArea][resource]+amount;
	}
	else if (toArea==-1) // If moving to the unallocated pool
	{
		myAssignments.value[fromArea][resource]=myAssignments.value[fromArea][resource]-amount;
		myAvailable[resource]=myAvailable[resource]+amount;		
	}
	else // If moving between areas
	{
		myAssignments.value[fromArea][resource]=myAssignments.value[fromArea][resource]-amount;
		myAssignments.value[toArea][resource]=myAssignments.value[toArea][resource]+amount;
	}
	return; // Success.

}

/// Moves an amount of a resource between areas
/***************************************************************************/
/** 
 * Move ()
 *
 * Move all of this resource that has been found in <em>fromArea</em>
 * to <em>toArea</em>
 *
 * Author: Andre Oboler (ASO)
 */

void UserDef::move(int fromArea, int toArea, int resource)
{
		move( fromArea, toArea, resource, myAssignments.value[fromArea][resource]);
	return;
}

/// Assign an amount of this resource (from the unallocated pool) to area <em>toArea</em>
/***************************************************************************/
/**
 * Add()
 *
 * Move a resource from area -1 (unallocated) to another area.
 *
 * Author: Andre Oboler (ASO)
 *
 */
 
void UserDef::add(int toArea, int resource, double amount)
{
	move(-1, toArea, resource, amount);
	return;
}

// Assign whatever is left (at the unallocated pool) of this resource to area <em>toArea</em>
/***************************************************************************/
/**
 * Add()
 *
 * Move a resource from area -1 (unallocated) to another area.
 *
 * Author: Andre Oboler (ASO)
 *
 */
void UserDef::add(int toArea, int resource)
{
	move(-1, toArea, resource, myAssignments.value[0][resource]);
	return;
}

/// remove part of this resource (to the unallocated pool)
/**************************************************************************/
/**
 * delete()
 *
 * Move a resource from an area to area -1 (unallocated).
 *
 * Author: Andre Oboler (ASO)
 *
 */

void UserDef::remove(int fromArea, int resource, double amount)
{
	move(fromArea, -1, resource, amount);
	return;
}

/// remove all of this resource to unallocated
/**************************************************************************/
/**
 * delete()
 *
 * Move all of a resource from an area to unallocated
 *
 * Author: Andre Oboler (ASO)
 *
 */

void UserDef::remove(int fromArea, int resource)
{
	move(fromArea, -1, resource, myAssignments.value[fromArea][resource]);
	return;
}


/// Moves all instances of a resource to area -1 (unallocated).
/***************************************************************************/
/**
 * clearResource()
 *
 * Moves all instances of a resource to area -1 (unallocated).
 *
 * Author: Andre Oboler (ASO)
 *
 */
void UserDef::clearResource(int resource)
{	
	int tempArea;			

	// NB: Start from area zero as area -1 is the unallocated pool
	for (tempArea=0; tempArea<myNumAreas ; tempArea++)
	{				
		if (myAssignments.value[tempArea][resource] > 0)
		{
			// If resources are present, move them to the unallocated pool.
			remove (tempArea, resource);			
		}				
	}
	return;
}

/// Moves all resources in an area to unallocated
/***************************************************************************/
/**
 * clearArea()
 *
 * Moves all resources in an area to area -1 (unallocated).
 *
 * Note: This code could use the first area and next area function but this adds
 * extra overhead (in calling the functions) for no apparent again.
 *
 * Author: Andre Oboler (ASO)
 *
 */

void UserDef::clearArea(int area)
{	
	int tempRes;			

	// crt 13jan03: Added trap. What if someone tried to clear unallocated?
   //              This would try to index area[-1]. Oops. So just return.
	if (area<0)
	  {
		 return;
	  }

	for (tempRes=0; tempRes<myNumResources ; tempRes++)
	{				
		if (myAssignments.value[area][tempRes] > 0)
		{
			// If resources are present, move them to the unallocated pool.
			remove (area, tempRes);		
		}				
	}
	return;
}

/// Moves all resources to unallocated, i.e. empties all allocations.
/***************************************************************************/
/**
 * clearAll()
 *
 * Moves all resources to unallocated, i.e. empties all allocations.
 *
 * Author: Andre Oboler (ASO)
 *
 */
void UserDef::clearAll()
{	
	int tempArea;			
	int tempRes;			

	// NB: Start from area zero as area -1 is the unallocated pool
	for (tempArea=0; tempArea<myNumAreas ; tempArea++)
	{				
		for (tempRes=0; tempRes<myNumResources ; tempRes++)
		{				

			if (myAssignments.value[tempArea][tempRes] > 0)
			{
				// If resources are present, move them to the unallocated pool.
				remove (tempArea, tempRes);
			}
		}				
	}

	return;
}


/// Returns the area number of the first area in this allocation
/***************************************************************************/
/**
 * firstArea()
 *
 * Returns the area number of the first area in this allocation. 
 *
 * If the allocation is empty, returns -1
 * 
 * \todo It would be better if UserDef::firstArea threw an exception
 *       rather than returning -1. Esp. if -1 is the unallocated area.
 *
 * Author: Andre Oboler (ASO)
 */
		
 int UserDef::firstArea(void)
 {
	int i;
	int j;
	
	// Find index of first non zero cell in myAssignments
	for(i=0; i<myNumAreas; i++);
	{
		for (j=0; j< myNumResources; j++)
		{
			if (myAssignments.value[i][j]!=0)
			{
				return i;
			}
		}
	}
	
	// If no resource was found
		return -1;
 }

 /// Returns the first AreaAssignment for a given resource.
/***************************************************************************/
/**
 * firstArea()
 *
 * Returns the first AreaAssignment (an area and a time) for a given resource.
 * 
 * If the resource does not exist in this allocation an area assignment of
 * area -1 for time 0 is returned.
 * 
 * \todo It would be better if firstArea(int resource) threw an exception.
 *
 * Author: Andre Oboler (ASO)
 */

 AreaAssignment* UserDef::firstArea(int resource)
 {
	 	 
	 int i;		

	// Find index of first non zero area for this resource
	for(i=0; i<myNumAreas; i++);
	{
			if (myAssignments.value[i][resource]!=0)
			{
				return new AreaAssignment(resource, myAssignments.value[i][resource]);;
			}
	}
	
		
	//Check in case this resource not assigned to any areas
		return NULL; 
	
 }

 /// Given an area number, returns the next area with an assignment
/***************************************************************************/
/**
 * nextArea()
 *
 * Given an area number, returns the next area that has something assigned to 
 * it in this set of allocations.
 *
 * If there is no other area with an allocation of resources greater than 0, 
 * the function returns -1. 
 * NOTE: This function searches by AREA, that is, it searches through all area N 
 * and all resources before searching through area N+1 and all resources... etc.
 *
 * \todo: It would be better if nextArea() threw exceptions.
 *
 * Author: Andre Oboler (ASO)
 */

		int UserDef::nextArea(int area)
		{
			int tempArea;
			int tempResource;			


			// Across 1 step
			for (tempArea=area+1; tempArea<myNumAreas ; tempArea++)
			{				
				// step down to bottom looking for a non zero cell
				for(tempResource=0; tempResource<myNumResources; tempResource++)
				{						
					if (myAssignments.value[tempArea][tempResource] > 0)
					{
						// Return the area with a non zero resource allocation
						// We do not care about which resourse is here.
						return tempArea;
					}
				}				
			}
			
			// No more areas with assignments
			return -1;
		}

/// Given a resource and an area, returns the next AreaAssignment for this resource.
/***************************************************************************/
/**
 * nextArea()
 *
 * Given a resource and an area, 
 * returns the next area (and time) for  <em>this resource</em>.
 *
 * If there are no more areas or the resource is not assigned to any more areas
 * returns an area of -1 for time 0
 *
 * \todo: It would be better if nextArea(int resource, int area) threw exceptions
 *
 * Author: Andre Oboler (ASO)
 */
		AreaAssignment* UserDef::nextArea(int resource, int area) // params: What we are talking about, where we are now (in that order)
		{
			int tempArea;			

			// Across 1 step
			for (tempArea=area+1; tempArea<myNumAreas ; tempArea++)
			{				
				if (myAssignments.value[tempArea][resource] > 0)
				{
					// Return the area with a non zero resource allocation
					// We do not care about which resourse is here.
					return new AreaAssignment(tempArea,myAssignments.value[tempArea][resource]);
				}				
			}
			
			// No more areas with assignments of this resource
			return NULL; 
		}
		

/// Given an area, it returns the first resource assigned there, as ResourceAssignment.
/**************************************************************************/
/**
 * firstRes()
 *
 * Given an area, it returns the first resource assigned to that 
 * area (returned as a ResourceAssignment with the resource and time). 
 *
 * If there are no resources, it returns an assingnment of resource -1 for time 0.
 *
 * \todo: It would be better if (guess what?) firstRes() threw exceptions
 *
 * Author: Andre Oboler (ASO)
 */

	ResourceAssignment* UserDef::firstRes(int area)
	{
		int tempResource;			

		// step down to bottom looking for a non zero cell
		for(tempResource=0; tempResource<myNumResources; tempResource++)
		{						
			if (myAssignments.value[area][tempResource] > 0)
			{
				// Return the resource with a non zero allocation
				// We know the area (passed in) and only return the resource and time
				
				return new ResourceAssignment(tempResource, myAssignments.value[area][tempResource]);
			}
		}				
			
		// No more resources assigned to this area
		return NULL;

	}	

/// Given a resource and an area, it returns the next resource assigned there, as a ResourceAssignment.
/***************************************************************************/
/**
 * nextRes()
 *
 * Given a resource and an area, it returns 
 * the next resource assigned to that area (as a ResourceAssignment).
 *
 * If there are no next resources, it returns an assingnment of resource -1 for time 0.
 * This is a sentinal value.
 *
 * \todo: This one should perhaps NOT throw an exception.
 * Or return a "warning" exception "No more resources"
 *
 * Author: Andre Oboler (ASO)
 */

	ResourceAssignment* UserDef::nextRes(int Area, int Resource) // params: What we are talking about, where we are now (in that order)
	{
		
		int tempResource;			
		// step down to bottom looking for a non zero cell
		for(tempResource=Resource+1; tempResource<myNumResources; tempResource++)
		{						
			if (myAssignments.value[Area][tempResource] > 0)
			{
				// Return the resource (and time) with a non zero allocation
				// We already know the area as it was passed in (so no need to return this to the user)
				return new ResourceAssignment(tempResource, myAssignments.value[Area][tempResource]);
			}
		}				
		
		// No more areas with assignments
		return NULL;
	}
	
		
		
/*****************************************************************************/
/* calcAllocationUserDef()
 * 
 * There is no Calc allocation for userdef.
 */

