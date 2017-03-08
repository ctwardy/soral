/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file Alloc-CC.cpp
 *  \brief Alloc-CC.cpp contains the CharnesCooper specific allocation code
 *
 * Implements a specific allocation object which uses the Charnes Cooper 
 * allocation method. See the header file for more information about the
 * algorithm. 
 *
 * Contains calcAllocation() and the functions used by the iterators
 * for moving over allocations. Currently stores its allocation in 
 * an Array2D object.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 05/12/01 |  1  | Created.
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 12/01/01 |  2  | Modified.
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 02/02/02 |  3  | Modified.
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 25/02/02 |  4  | Minor modifications.
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 5/12/02  |  5  | New functions added
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 9/12/02  |  6  | New functions from 5 altered and completed
 *-----+----------+-----+-----------------------------------------------------
 * ASO | ?/02/03  |  7  | Andre replaced selection sort with quicksort cvs 1.7
 *-----+----------+-----+-----------------------------------------------------
 * crt | 04mar03  |  8  | Merged in cc-alloc.cpp and removed that. (cvs 1.10)
 *-----+----------+-----+-----------------------------------------------------
 * crt | 28mar03  |  9  | Privatization. Reprotection. Other changes.
 *-----+----------+-----+-----------------------------------------------------
 * \endverbatim
 */

//============================================================================//
// Written by Gareth Thompson and Andre Oboler            http://sarbayes.org //
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

#include "Alloc-CC.h"
#include <iostream> // ASO 29/11/02 changed from iostream.h to meet the C++ standard
#include "memory.h"

using namespace std; // ASO 29/11/02 needed as iostream declares function in std.

/*************************************************************************/
/// Constructor calls calcAllocation and uses Array2D to store allocation.
/**
 * Constructor for the Charnes Cooper allocation object. (File description 
 * and header file description have more information about the algorithm.)
 *
 * Author : Michael Eldridge
 * 
 */
 
 
 extern "C" CharnesCooper* newCharnesCooper(const int p_no_resources, 
						  const int p_no_areas, 
						  const Array2D& p_effectiveness,
						  const double p_available[], 
						  const double p_POC[]) {
    						  
    cout << "POCs in:  0:" << p_POC[0] << 
        ", 1: " << p_POC[1] <<
        ", 2: " << p_POC[2] <<
        ", 3: " << p_POC[3] <<
        endl;
    						  
    						  
    CharnesCooper* obj = new CharnesCooper(p_no_resources, p_no_areas, p_effectiveness, 
        toValArray(p_no_resources, p_available), toValArray(p_no_areas, p_POC));
    
    
    // debug that correct parameters arrived
     cout << "endurances: 0:" << obj->getEndurance(0) << endl;
    cout << "POCs out: 0:" << obj->getPOC_debug_only(0) << 
        ", 1: " << obj->getPOC_debug_only(1) <<
        ", 2: " << obj->getPOC_debug_only(2) <<
        ", 3: " << obj->getPOC_debug_only(3) <<
        endl;

    
    return obj;
}


CharnesCooper::CharnesCooper(const int p_no_resources, 
									  const int p_no_areas, 
									  const Array2D& p_effectiveness,
									  const valarray<double> p_endurance, 
									  const valarray<double> p_POC)
  :Allocation(p_no_resources, p_no_areas, p_effectiveness, p_endurance, p_POC),
	myAssignments(p_no_areas, p_no_resources),
	myAvailable(p_endurance[0])
{
#ifdef _ALLOCATION_TESTMODE
   cout << "Creating a Charnes Cooper allocation (CharnesCooper::CharnesCooper)" << endl;
#endif
	calcAllocation();
}





// crt 5mar03: removed do-nothing destructor so now it uses the default.

/*************************************************************************/
/// Returns the area number of the first area in this allocation.
/**
 * Returns the area number of the first area in this allocation.
 *
 * If the allocation is empty, returns NULL.
 * \todo: It would be better if it threw an exception
 *
 * Author: Andre Oboler (ASO)
 */

ActiveArea* CharnesCooper::firstArea(void) const
{
  int i;
  int j;

  // Find index of first non zero cell in myAssignments
  for(i=0; i < myNumAreas; i++)
  {
    for (j=0; j < myNumResources; j++)
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

 /// Returns the area number of the first area in this allocation.
/***************************************************************************/
/**
 * Returns the first AreaAssignment (an area and a time) that a given
 * resource was assigned to.
 *
 * If the resource does not exist in this allocation, it returns NULL.
 *
 * \todo: It would be better if it threw an exception
 *
 * Author: Andre Oboler (ASO)
 */

AreaAssignment* CharnesCooper::firstArea(const int resource) const
{
  // Find index of first non zero area for this resource
  for(int i=0; i<myNumAreas; i++)
  {
    if (myAssignments[i][resource]!=0)
    {
      return new AreaAssignment(i, myAssignments[i][resource]);
    }
  }

  //Check in case this resource not assigned to any areas
  return NULL;
}

/// Given an area number, returns the next area that has something assigned to it
/****************************************************************************/
/**
 * Given an area number, returns the next area that has something assigned to
 * it in this set of allocations.
 *
 * If there is no other area with an allocation of resources greater than 0,
 * the function returns NULL.
 * NOTE: This function searches by AREA: ie it searches through all of area N
 * and all resources before searching through area N+1 and all resources. Etc.
 *
 * \todo: It would be better if it threw exceptions?
 *
 * Author: Andre Oboler (ASO)
 */

ActiveArea* CharnesCooper::nextArea(const int currentArea) const
{
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
	return new ActiveArea(tempArea);
      }
    }
  }

  // No more areas with assignments
  return NULL;
}

 /// Given a resource and an area number, returns the next area to which this resource is assigned.
/****************************************************************************/
/**
 * Given a resource and an area number, returns the next area 
 * (returned as an AreaAssignment of area and time) to which 
 * <em>this</em> resource is assigned.
 *
 * If this resource is not assigned to any more areas,
 * the function returns NULL.
 *
 * \todo: It would be better if it threw exceptions or enum NO_MORE_AREAS?
 *
 * Author: Andre Oboler (ASO)
 */

AreaAssignment* CharnesCooper::nextArea(const int resource, 
										const int currentArea) const
{
  int tempArea;

  // Across 1 step
  for (tempArea=currentArea+1; tempArea<myNumAreas ; tempArea++)
  {
    if (myAssignments[tempArea][resource] > 0)
    {
      // Return the area with a non zero resource allocation
      return new AreaAssignment(tempArea, 
										  myAssignments[tempArea][resource]);
    }
  }

  // No more areas with assignments of this resource
  return NULL;
}


/// Given an area, it returns the first resource assigned to that area
/****************************************************************************/
/**
 * Given an area, it returns the first resource assigned to that
 * area (returned as a ResourceAssignment with the resource and time).
 *
 * If there are no resources, it returns NULL
 *
 * \todo: It would be better if it through exceptions, or used enums.
 *
 * Author: Andre Oboler (ASO)
 */

ResourceAssignment* CharnesCooper::firstRes(const int area) const
{
  int tempResource;

  // step down to bottom looking for a non zero cell
  for(tempResource=0; tempResource<myNumResources; tempResource++)
  {
    if (myAssignments[area][tempResource] > 0)
    {
       // Return the resource with a non zero allocation
       // We know the area (passed in) and only return the resource and time

      return new ResourceAssignment(tempResource,
				    myAssignments[area][tempResource]);
    }
  }

  // No more resources assigned to this area
  return NULL;
}

/// Given a resource and an area, it returns the next ResourceAssignment for that area
/****************************************************************************/
/**
 * Given a resource and an area, it returns
 * the next resource assigned to that area (as a ResourceAssignment).
 *
 * If there are no next resources, it returns NULL.
 *
 * \todo: Perhaps we should NOT suggest that this one throw an exception.
 * Maybe return a "warning" exception: "No more resources"
 *
 * Author: Andre Oboler (ASO)
 */

ResourceAssignment* CharnesCooper::nextRes(const int area, 
										   const int currentResource) const
{

  int tempResource;
  // step down to bottom looking for a non zero cell
  for(tempResource=currentResource+1; tempResource<myNumResources; tempResource++)
  {
    if (myAssignments[area][tempResource] > 0)
    {
      // Return the resource (and time) with a nonzero allocation
      // We already know the area, as it was passed in (so no need
      // to return this to the user)
      return new ResourceAssignment(tempResource,
				    myAssignments[area][tempResource]);
    }
  }

  // No more areas with assignments
  return NULL;
}

/// Top level of quickSort algorithm. The recursive part is in qSort.
/************************************************************************/
/** 
 * Sorts a list of ints (which are the index numbers of a set of areas)
 * into decending order by their area's PSR values.
 * 
 * Reminder: Quicksort is on average O(n log n), but in the worst case
 * will be O(n^2). The worst case is when the list is already sorted.
 * So... DO NOT use this function additional times just to "ensure" the list 
 * is ordered.
 */
void CharnesCooper::quickSort(int items[], int arraySize)
{
  qSort(items, 0, arraySize - 1);
}

/// Recursive part of quickSort algorithm.
void CharnesCooper::qSort(int items[], int left, int right)
{
  int initialLeft, initialRight;
  int pivot;

  initialLeft = left;
  initialRight = right;
  pivot = items[left];
  
  
  while (left < right)
  {
    while ((calcInitialPSR(0, items[right]) <= calcInitialPSR(0, pivot)) && (left < right))
	{
      right--;
	}
    if (left != right)
    {
	  items[left] = items[right];
      left++;
    }
    while (calcInitialPSR(0, items[left]) >= calcInitialPSR(0, pivot) && (left < right))
	{	  
      left++;
	}

    if (left != right)
    {
	  items[right] = items[left];
      right--;
    }
  }
  items[left] = pivot;
  pivot = left;
  left = initialLeft;
  right = initialRight;
  if (left < pivot)
    qSort(items, left, pivot-1);
  if (right > pivot)
    qSort(items, pivot+1, right);
}

/// Calculate the allocation using the Charnes Cooper algorithm
/***************************************************************************/
/**
 * calcAllocationCharnesCooper()
 *
 * Note: Charnes Cooper only uses 1 resource
 *
 * Uses the Charnes-Cooper algorithm to calculate the optimal assignment of
 * resource 0 to the set of areas. The remaining search endurance 
 * (time the resource is still available for) is stored in myAvailable.
 *
 *
 * This set of assignments is stored in myAssignments.
 *
 * If resource 0 is useless (for every area, either POC is
 * zero, or its effectiveness in that area is zero), no
 * allocation is made (resource 0 is assigned to each area
 * for 0 hours).
 *
 * Author: Gareth Thompson
 */

void CharnesCooper::calcAllocation()
{
  #ifdef _ALLOCATION_TESTMODE
    cout << "Entering CharnesCooper::calcAllocation()" << endl;
  #endif

  int j;

  /* Delete any current assignments for resource 0 */
  for (j=0; j<myNumAreas; j++)
  {
    myAssignments[j][0] = 0.0;
  }

  /*
   * If resource 0 is useless (for every area, PSR is zero
   * because either POC is zero, or its effectiveness in
   * that area is zero), no allocation is made.
   */
  bool areaToSearch = false;
  for (j=0; j<myNumAreas; j++)
  {
    if (calcInitialPSR(0, j) > 0)
    {
      areaToSearch = true;
      break;
    }
  }

  if (!areaToSearch)
  {
    /* Resource 0 is useless, so no allocation is made */
    return;
  }

  /* Create list of area numbers, initially in order */
  int* areaList = new int[myNumAreas];

  for (j=0; j<myNumAreas; j++)
  {
    areaList[j] = j;
  }

  // Sort list of areas into descending order of PSR for resource 0.
  quickSort(areaList, myNumAreas);

  #ifdef _ALLOCATION_TESTMODE
  for (int i=0; i< myNumAreas; i++)
  {
	cout << "[" << i << "]" << areaList[i] << " " << calcInitialPSR(0, areaList[i]) << " ";
  }
  #endif


  double PSRmax;                        //Maximum PSR of areas
  double PSR2;                          //2nd highest PSR of areas
  int lastArea = 0;                     //Index of last area in areaList w/highest PSR
  double totalInvEffectiveness = 0.0 ;      //Sum of inverse effectiveness values for all areas in areaList[0,...,lastArea]

  /* Initialise above variables */
  PSRmax = calcInitialPSR(0, areaList[lastArea]);
  totalInvEffectiveness += 1 / myEffectiveness[areaList[lastArea]][0];

  while (lastArea < myNumAreas-1 && calcInitialPSR(0, areaList[lastArea+1]) >= PSRmax)
  {
    lastArea++;
    totalInvEffectiveness += 1 / myEffectiveness[areaList[lastArea]][0];
  }

  if (lastArea < myNumAreas-1)
  {
    /* All areas do not have equal PSR.  2nd highest PSR is next in list */
    PSR2 = calcInitialPSR(0, areaList[lastArea+1]);
  }

  /*
   * Continue to make assignments until myAvailable[0] is reduced to zero.
   * (When the assignments which reduce myAvailable[0] to 0 are made, a
   * break will be used to exit the loop.)
   */
  double *timeNeeded = 0;

  while (1)
  {
    if (lastArea == myNumAreas-1)
    {
      /*
       * Resource 0 now has equal PSR in all areas.  Remaining search endurance
       * (myAvailable[0]) is split between them in such a way that the PSRs for all
       * areas are driven down to the same level.  That is, the search time assigned
       * to each area is proportional to the inverse of resource 0's effectiveness
       * in that area.
       */

      double proportion;
      double time;
      for (j=0; j<myNumAreas; j++)
      {
        /* Proportion of remaining search endurance to assign to this area */
        proportion = (1 / myEffectiveness[j][0] ) / totalInvEffectiveness;

        /* Time to assign to this area */
        time = proportion * myAvailable;

        /* Make assignment */
        myAssignments[j][0] += time;
      }

      /* All hours have now been assigned for searching. */
      break;
    }

    /*
     * Resource 0 does not have equal PSR in all areas.  
	  * The areas with PSR = PSRmax have their PSR driven down to PSR2, or are
	  * driven down as far as possible if there is insufficient search endurance
	  * remaining (myAvailable) to drive them down to PSR2.
     */

    /*
     * Determine what searching is necessary to drive the PSR of all areas 
	  * currently at PSRmax down to PSR2.  No calculation is performed if PSR2 
	  * is zero, as an infinite amount of searching is then required.
     */
    timeNeeded = new double[lastArea + 1];   //Search time to drive PSR down to PSR2 for each area at PSRmax
    double totalTimeNeeded = 0.0;            //Total search time needed for all areas

    if (PSR2 > 0.0)
    {
      /* Determine POD necessary to drive PSRmax down to PSR2 */
      double POD = 1 - PSR2 / PSRmax;

      /* Calculate necessary coverage to achieve this POD */
      double coverageNeeded = -1 * log(1.0 - POD);

      /*
       * Calculate search time needed to achieve this coverage in each area in
       * areaList[0,...,lastArea].
       */
      for (j=0; j<=lastArea; j++)
      {
        timeNeeded[j] = coverageNeeded / (myEffectiveness[areaList[j]][0]);
        totalTimeNeeded += timeNeeded[j];
      }
    }

    /*
     * Check if remaining search endurance (myAvailable) is insufficient to drive
     * the PSR of all areas currently at PSRmax down to PSR2.  myAvailable is
     * always insufficient if PSR2 is zero, as an infinite amount of
     * searching is then required.
     */
    if (!(PSR2 > 0.0) || myAvailable < totalTimeNeeded)
    {
      /*
       * With insufficient search endurance remaining, myAvailable
       * is split between areas in such a way that all areas that currently 
		 * have PSR = PSRmax have the same final PSR.  That is, the search time 
		 * assigned to each area is proportional to the inverse of  the 
		 * resource's effectiveness in that area.
       */

      double proportion;
      double time;
      for (j=0; j<=lastArea; j++)
      {
        /* Proportion of remaining search endurance to assign to this area */
        proportion = (1 / (myEffectiveness[areaList[j]][0]) ) / totalInvEffectiveness;

        /* Time to assign to this area */
        time = proportion * myAvailable;

        /* Make assignment */
        myAssignments[areaList[j]][0] += time;
      }

      /* All hours have now been assigned for searching. */
      break;
    }
    else
    {
      /*
       * Sufficient search endurance (myAvailable) remains to drive PSR of all 
		 * areas at PSRmax down to PSR2.  Assign the required time to each area 
		 * (as calculated above).
       */
      for (j=0; j<=lastArea; j++)
      {
        myAssignments[areaList[j]][0] += timeNeeded[j];
      }

      myAvailable -= totalTimeNeeded;

      /* Update lastArea, PSRmax, PSR2 and totalInvEffectiveness for next iteration */
      PSRmax = PSR2;
      lastArea++;
      totalInvEffectiveness += 1 / myEffectiveness[areaList[lastArea]][0];

      while (lastArea < myNumAreas-1 && calcInitialPSR(0, areaList[lastArea+1]) >= PSRmax)
      {
        lastArea++;
        totalInvEffectiveness += 1 / myEffectiveness[areaList[lastArea]][0];
      }

      if (lastArea < myNumAreas-1)
      {
        /* All areas do not have equal PSR.  2nd highest PSR is next in list */
        PSR2 = calcInitialPSR(0, areaList[lastArea+1]);
      }

      /* Free dynamically allocated memory */
      delete timeNeeded;
      timeNeeded = 0;
    }
  }

  /* Free dynamically allocated memory */
  delete[] areaList;
  areaList = 0;
  delete timeNeeded;
  timeNeeded = 0;

  #ifdef _ALLOCATION_TESTMODE
    cout << "Leaving CharnesCooper::calcAllocation()" << endl;
  #endif
}
