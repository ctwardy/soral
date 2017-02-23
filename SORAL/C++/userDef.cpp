/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file userDef.cpp
 *  \brief userDef.cpp Contains the UserDef Class's functions.
 * 
 * Contains the UserDef class's functions.
 * UserDef is the allocation class that allows the user to set their own 
 * allocations. Anything can be converted to UserDef via the Allocation
 * copy constructor plus the iterators for that other allocation.
 * That feature lets users tweak an automated allocation to take account
 * of human factors not known to the algorithm.
 *
 * NOTE: The movement functions are ordered <em>fromArea</em>, 
 * <em>toArea</em>, <em>resource</em>, <em>amount</em>. 
 * While the order resource, amount, fromArea, toArea may make more 
 * intuitive sense, the order used is consistent with the array 
 * structure[area][resource]. That is, in a function call, anything 
 * representing an area goes before the thing representing a resource.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 26/12/02 |  1  | Created from Charnes-Cooper                         
 *-----+----------+-----+-----------------------------------------------------
 * crt | 13jan03  |  2  | Finished changing 'home base' from 0 to -1.
 *     |          |     | Documentation, some error-checking.
 *-----+----------+-----+-----------------------------------------------------
 * aso | 12mar03  |  3  | Movd some debug info into #ifdef _ALLOCATION_TESTMODE
 *     |          |     | controled section.
 *-----+----------+-----+-----------------------------------------------------
 * aso | 23mar03  |  4  | Made lots of things const.
 *-----+----------+-----+-----------------------------------------------------
 * aso | 30mar03  |  5  | Made copy ctor use allocations copy ctor
 *-----+----------+-----+-----------------------------------------------------
 * crt |  6apr03  |  6  | Now uses UNALLOCATED_AREA rather than -1.
 *     |          |     | Filename changed to UserDef (not userDef)
 *     |          |     | Doxygen comments added. Added error-trapping to
 *     |          |     | the accessor functions to trap bogus input. Bugfix.
 *-----+----------+-----+-----------------------------------------------------
 * crt | 18apr03  |  7  | Simplified and debugged constructor.
 *-----+----------+-----+-----------------------------------------------------
 * \endverbatim
 */

//===========================================================================//
// Written by Andre Oboler                               http://sarbayes.org //
//---------------------------------------------------------------------------//
// The SORAL implementation is free software, but it is Copyright (C)        //
// 2001-2003 the authors and Monash University (the SARBayes project).       //
// It is distributed under the terms of the GNU General Public License.      //
// See the file COPYING for copying permission.                              //
//                                                                           //
// If those licencing arrangements are not satisfactory, please contact us!  //
// We are willing to offer alternative arrangements, if the need should arise//
//                                                                           //
// THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED OR //
// IMPLIED.  ANY USE IS AT YOUR OWN RISK.                                    //
//                                                                           //
// Permission is hereby granted to use or copy this program for any purpose, //
// provided the above notices are retained on all copies.  Permission to     //
// modify the code and to distribute modified code is granted, provided the  //
// above notices are retained, in accordance with the GNU GPL.               //
//===========================================================================//

#include "UserDef.h"
#include <iostream> // ASO 29/11/02 C++ standard is not iostream.h

using namespace std; // ASO 29/11/02 needed: iostream declares functions in std


// Constructors (and Destructors)

/**** UserDef() constructor **************************************************/
/// Make a user-defined allocn: ie an empty allocn matrix of the correct size
/**
 * The from-scratch constructor.
 * Makes a user-defined allocation: an empty allocation matrix of the right
 * size. The user may fill this with the methods of UserDef.
 *
 */
UserDef::UserDef(const int p_no_resources, 
					  const int p_no_areas, 
					  const Array2D& p_effectiveness,
					  const valarray<double> p_available, 
					  const valarray<double> p_POC) :
  Allocation(p_no_resources, p_no_areas, p_effectiveness, p_available, p_POC),
  myAssignments(p_no_areas, p_no_resources),
  myUnallocatedResources(myEndurance)

{
	//memset(myAssignments, 0, (sizeof(double)*p_no_areas * p_no_resources));	

	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating a User-Defined search object (UserDef::UserDef)" << endl;
	#endif
}

/**** UserDef() constructor *************************************************/
/// Create a UserDef Allocation from an existing allocation (of another type)
/**
 * Makes a user-defined allocation from an existing allocation (of any type).
 * The user may then modify this allocation.
 * 18apr03: crt simplified & debugged
 * 01may03: crt even further simplified thx to njh
 */
UserDef::UserDef(Allocation& oldAllocation)
 :	Allocation(oldAllocation), 
    myAssignments(myNumAreas, myNumResources),
    myUnallocatedResources(myEndurance)
{
#ifdef _ALLOCATION_TESTMODE
    cout << "Creating a User-Defined search object (UserDef::UserDef(Allocation &oldAllocation))" << endl;
#endif

	ActiveAreasIterator activeAreas(oldAllocation);

	//While there are still areas with assignments
	while(!(activeAreas.atEnd()))
	{		
	    ActiveArea       area(*activeAreas); 
		int              areaIndex (area.getActiveAreaNum());
		ResourceIterator resItr(oldAllocation, areaIndex);

		while (!(resItr.atEnd()))
		{
			ResourceAssignment resAssign (*resItr);
			int                resIndex  (resAssign.getResourceNum());
			double             time      (resAssign.getTime());
			myAssignments[areaIndex][resIndex] = time;
			++resItr; //increment
		}

		++activeAreas; //incriment
	}

}

/**** ~UserDef() ************************/
/// Empty destructor for UserDef
UserDef::~UserDef()
{

}

/**** calcAllocation() *******************************************************/
/// In UserDef, calcAllocation does nothing.
/**
 * UserDef provides "calcAllocaton" just to keep the coding standard.
 * Since the allocation "algorithm" for UserDef is wired through the 
 * keyboard (ie, it's the user), this routine does nothing. 
 */
void UserDef::calcAllocation(void)
{
	//Does nothing.
}

/**** isValidArea() ********************************************************/
/// Checks to see the chosen area is valid.
/**
 * Helper function that checks to see that the chosen area is valid. 
 * It does not consider the UNALLOCATED_AREA to be valid, so you must
 * check for that separately in some of the move functions.
 *
 * This function makes code a little clearer and easier to change.
 *
 * crt
 */
bool UserDef::isValidArea(const int area) const
{
  return (area>=0 && area < myNumAreas);
}

/**** isValidResource() *****************************************************/
/// Checks to see the chosen resource is valid.
/**
 * Helper function that checks to see that the chosen resource is valid. 
 * Just cleans up other code a little to have this.
 *
 * crt
 */
bool UserDef::isValidResource(const int resource) const
{
  return (resource>=0 && resource < myNumResources);
}


/***************************************************************************/
/// Moves an amount of a resource between areas
/**
 * Moves <em>amount</em> of <em>resource</em> from <em>fromArea</em> 
 * to <em>toArea</em>. 
 * This is the basic movement code, all other movement code should call this to
 * ensure the range checking only needs to be coded once and changed once if 
 * the specs change.
 *
 * Author: Andre Oboler (ASO)
 *
 */

void UserDef::move(const int fromArea, 
						 const int toArea, 
						 const int resource, 
						 const double amount)
{
	// Do some basic checking

  if(!isValidResource(resource))
	{
		// [TODO ASO] Possibly throw execption here.
		// Error is resource out of range.
		return;
	}
	
	if(!isValidArea(fromArea) && fromArea != UNALLOCATED_AREA)
	{
		// \todo Possibly throw "area out of range" execption here.
		return;
	}

	if(!isValidArea(toArea) && toArea != UNALLOCATED_AREA)
	{
		// \todo Possibly throw "area out of range" execption here.
		return;
	}

	if(amount < 0)
	{
		// \todo Possibly throw "negative amount to transfer" execption here.
		return;
	}


	if (fromArea==toArea)  // Silly request wd cause errors if UNALLOCATED_AREA.
	  {                    // crt 13jan03 added
		 return;
	  }

	// Final check, do we have enough resource available to meet the transfer 
   // quota, if moving from the unallocated pool
	if (fromArea==UNALLOCATED_AREA)
	{
		if(myUnallocatedResources[resource]-amount < 0)
		{
			// \todo [gt] Possibly throw "insuf. resources" exception here.
			return;
		}
	}
	else // If moving from another area
	{

		if(myAssignments[fromArea][resource]-amount < 0)
		{
			// \todo [ASO] Possibly throw execption here.
			// Error is amount to transfer is more than the amount available.
			return;
		}
	}

	if (fromArea==UNALLOCATED_AREA) // If moving out of the unallocated pool
	{
	  myUnallocatedResources[resource]=myUnallocatedResources[resource]-amount;		
		myAssignments[toArea][resource]=myAssignments[toArea][resource]+amount;
	}
	else if (toArea==UNALLOCATED_AREA) // If moving to the unallocated pool
	{
	  myAssignments[fromArea][resource]=myAssignments[fromArea][resource]-amount;
	  myUnallocatedResources[resource]=myUnallocatedResources[resource]+amount;		
	}
	else // If moving between areas
	{
		myAssignments[fromArea][resource]=myAssignments[fromArea][resource]-amount;
		myAssignments[toArea][resource]=myAssignments[toArea][resource]+amount;
	}

	forceRecalc = true; // We've changed something. Better tell the calc fns.
	return; // Success.

}

/**************************************************************************/
/// Moves an amount of a resource between areas
/**
 * Move all of this resource from <em>fromArea</em>  to <em>toArea</em>.
 *
 * Author: Andre Oboler (ASO)
 */

void UserDef::move(const int fromArea, 
						 const int toArea, 
						 const int resource)
{
		move(fromArea, toArea, resource, myAssignments[fromArea][resource]);
	return;
}

/***************************************************************************/
/// Assign some of this resource from unallocated pool to area <em>toArea</em>
/**
 * Assign some of a resource to the specified area.
 * Move a resource from the unallocated area to another area.
 *
 * Author: Andre Oboler (ASO)
 *
 */
 
void UserDef::add(const int toArea, const int resource, const double amount)
{
	move(UNALLOCATED_AREA, toArea, resource, amount);
	return;
}

/***************************************************************************/
/// Assign whatever remains of this resource to area <em>toArea</em>
/**
 * Assign whatever remains (unallocated) of this resource to the requested
 * area. Specifically, moves all of a resource from UNALLOCATED_AREA to 
 * another area.
 *
 * Author: Andre Oboler (ASO)
 *
 */
void UserDef::add(const int toArea, const int resource)
{
	move(UNALLOCATED_AREA, toArea, resource, myUnallocatedResources[resource]);
	return;
}

/**************************************************************************/
/// Remove part of this resource (to the unallocated pool)
/**
 * Unassigns a specified amount of the specified resource. That is,
 * moves some of a resource from an area back to the UNALLOCATED_AREA.
 *
 * Author: Andre Oboler (ASO)
 *
 */

void UserDef::remove(const int fromArea, const int resource, const double amount)
{
	move(fromArea, UNALLOCATED_AREA, resource, amount);
	return;
}

/**************************************************************************/
/// Remove all of this resource (to the unallocated pool)
/**
 * Unassign all of a resource from the specified area. That is, 
 * move all of a resource from a specified area to UNALLOCATED_AREA
 *
 * Author: Andre Oboler (ASO)
 *
 */

void UserDef::remove(const int fromArea, const int resource)
{
	move(fromArea, UNALLOCATED_AREA, resource, myAssignments[fromArea][resource]);
	return;
}


/***************************************************************************/
/// Unassigns <em>all</em> of a resource, making it unallocated.
/**
 * Unassigns <em>all</em> of a resource.
 *
 * Moves all instances of a resource to the unallocated area.
 *
 * Author: Andre Oboler (ASO)
 *
 */
void UserDef::clearResource(const int resource)
{	
	int tempArea;			

	for (tempArea=0; tempArea<myNumAreas ; tempArea++)
	{				
		if (myAssignments[tempArea][resource] > 0)
		{
			// If resources are present, move them to the unallocated pool.
			remove (tempArea, resource);			
		}				
	}
	return;
}

/***************************************************************************/
/// Unassigns all resources in an area
/**
 * Unassigns <em>all</em> resources in <em>area</em>. 
 * Specifically, it moves all resources in <em>area</em> to 
 * UNALLOCATED_AREA.
 *
 * Note: This code could use the first area and next area function 
 * but that adds extra overhead (in calling the functions) for 
 * no apparent again.
 *
 * Author: Andre Oboler (ASO)
 *
 */

void UserDef::clearArea(const int area)
{	
	int tempRes;			

	// crt 13jan03: Added trap. What if someone tried to clear unallocated?
   // crt  6apr03: Modified to use isValidArea
	if (!isValidArea(area))
	  {
		 return;
	  }

	for (tempRes=0; tempRes<myNumResources ; tempRes++)
	{				
		if (myAssignments[area][tempRes] > 0)
		{
			// If resources are present, move them to the unallocated pool.
			remove (area, tempRes);		
		}				
	}
	return;
}

/***************************************************************************/
/// Clears all existing allocations.
/**
 * Clears all existing allocations, moving all resources in all areas
 * back to the unallocated pool.
 *
 * Author: Andre Oboler (ASO)
 *
 */
void UserDef::clearAll()
{	
	int tempArea;			
	int tempRes;			

	for (tempArea=0; tempArea<myNumAreas ; tempArea++)
	{				
		for (tempRes=0; tempRes<myNumResources ; tempRes++)
		{				

			if (myAssignments[tempArea][tempRes] > 0)
			{
				// If resources are present, move them to the unallocated pool.
				remove (tempArea, tempRes);
			}
		}				
	}

	return;
}


/***************************************************************************/
/// Returns the area number of the first area in this allocation
/**
 * Returns the area number of the first area in this allocation. 
 *
 * If the allocation is empty, returns NULL.
 *
 * Author: Andre Oboler (ASO)
 */
		
 ActiveArea* UserDef::firstArea(void) const
 {
	int i=0;
	int j=0;
	
	// Find index of first non zero cell in myAssignments
	
	for(i=0; i<myNumAreas; i++)
	{
		for (j=0; j<myNumResources; j++)
		{
			if (myAssignments[i][j]!=0)
			{
				return new ActiveArea(i);
			}
		}
	}
	
	// If no resource was found
	return NULL;
 }

/***************************************************************************/
 /// Returns the first AreaAssignment for a given resource.
/**
 * Returns the first AreaAssignment (an area and a time) for a given resource.
 * 
 * If this resource is not assigned to any area, returns NULL.
 * 
 * If the resource is invalid, returns NULL. 
 * \todo It should throw an exception if the resource is invalid.
 *
 * Author: Andre Oboler (ASO)
 */

 AreaAssignment* UserDef::firstArea(const int resource) const
 {
	 if (!isValidResource(resource))
	 {
		// \todo Throw "resource out of range" exception?
		return NULL;
	 } 

	 int area;		
	// Find index of first non zero area for this resource
	for(area=0; area<myNumAreas; area++)
	{
			if (myAssignments[area][resource]!=0)
			{
				return new AreaAssignment(area, myAssignments[area][resource]);;
			}
	}
	
		
	//If no resource was found
	return NULL; 
	
 }

/***************************************************************************/
 /// Given an area number, returns the next area with an assignment
/**
 * Given an area number, returns the next area that has something assigned to 
 * it in this set of allocations.
 *
 * If there is no following area has resources assigned to it,
 * the function returns NULL.
 * 
 * NOTE: This function searches by AREA, that is, it searches through all 
 * resources in area N before trying area N+1. Etc.
 *
 * \todo: Throw exception on invalid input.
 *
 * Author: Andre Oboler (ASO)
 */

ActiveArea* UserDef::nextArea(const int currentArea) const
{
  if (!isValidArea(currentArea))
	 {
		/// \todo Throw exception here.
		return NULL;
	 }

  int tempArea;
  int tempResource;			
  
  // Across 1 step
  for (tempArea=currentArea+1; tempArea<myNumAreas ; tempArea++)
	 {				
		// step down to bottom looking for a non zero cell
		for(tempResource=0; tempResource<myNumResources; tempResource++)
		  {						
			 if (myAssignments[tempArea][tempResource] > 0)
				{
				  // Return the area with a non zero resource allocation
				  // We do not care about which resource is here.
				  return new ActiveArea(tempArea);
				}
		  }				
	 }
  
  // No more areas with assignments
  return NULL;
}

/***************************************************************************/
/// Given a resource and area, returns next AreaAssignment for this resource.
/**
 * Given a resource and an area, returns the next area (and time) that 
 * <em>this resource</em> is assigned to.
 *
 * If there are no more areas or if the resource is not assigned to any 
 * more areas, returns NULL.
 *
 * \todo: Throw exception on invalid input
 *
 * Author: Andre Oboler (ASO)
 */
AreaAssignment* UserDef::nextArea(const int resource, 
											 const int currentArea) const
{
  if (!isValidArea(currentArea) || !isValidResource(resource))
	 {
		/// \todo Throw exception here.
		return NULL;
	 }


  int tempArea;			
  
  // Across 1 step
  for (tempArea=currentArea+1; tempArea<myNumAreas ; tempArea++)
	 {				
		if (myAssignments[tempArea][resource] > 0)
		  {
			 // Return the area with a nonzero resource allocation
			 return new AreaAssignment(tempArea,myAssignments[tempArea][resource]);
		  }				
	 }
  
  // No more areas with assignments of this resource
  return NULL; 
}


/**************************************************************************/
/// Given an area, returns the first resource assigned there.
/**
 * Given an area, it returns the first resource assigned to that 
 * area (returned as a ResourceAssignment with the resource and time). 
 *
 * If there are no resources, it returns NULL.
 *
 * \todo: Throw exception on invalid input
 *
 * Author: Andre Oboler (ASO)
 */

ResourceAssignment* UserDef::firstRes(const int area) const
{
  if (!isValidArea(area))
	 {
		/// \todo Throw exception here.
		return NULL;
	 }

  int tempResource;			
  
  // step down to bottom looking for a non zero cell
  for(tempResource=0; tempResource<myNumResources; tempResource++)
	 {						
		if (myAssignments[area][tempResource] > 0)
		  {
			 // Return the resource with a non zero allocation
			 // We know the area (passed in) and only return the resource and time
			 return new ResourceAssignment(tempResource, myAssignments[area][tempResource]);
		  }
	 }				
  
  // No more resources assigned to this area
  return NULL;
  
}	

/***************************************************************************/
/// Given a resource & area, returns the next resource assigned there
/**
 * Given a resource and an area, it returns 
 * the next resource assigned to that area (as a ResourceAssignment).
 *
 * If there are no next resources, it returns NULL.
 *
 * \todo: Throw exception on invalid input.
 *
 * Author: Andre Oboler (ASO)
 */

ResourceAssignment* UserDef::nextRes(const int area, 
												 const int currentResource) const
{
  if (!isValidArea(area) || !isValidResource(currentResource))
	 {
		/// \todo Throw exception here.
		return NULL;
	 }

  int tempResource;			
  // step down to bottom looking for a non zero cell
  for(tempResource=currentResource+1; tempResource<myNumResources; tempResource++)
	 {						
		if (myAssignments[area][tempResource] > 0)
		  {
			 // Return the resource (and time) with a non zero allocation
			 // (We already know the area, as it was passed in.)
			 return new ResourceAssignment(tempResource, myAssignments[area][tempResource]);
		  }
	 }				
  
  // No more areas with assignments
  return NULL;
}
	
		
		
