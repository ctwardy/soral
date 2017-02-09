/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file Alloc-CC.cpp
 *  \brief Alloc-CC.cpp contains the CharnesCooper specific allocation code
 *
 *
 * Contains calcAllocation() and the functions used by the iterators
 * for moving over allocations. The code here is all for CharnesCooper which
 * stored its allocation in an Array2D object.
 *
 * <b><u>Version History</u></b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 05/12/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 12/01/01 |  2  | Modified.
 *----------------------------------------------------------------------------
 * GT  | 02/02/02 |  3  | Modified.
 *----------------------------------------------------------------------------
 * GT  | 25/02/02 |  4  | Minor modifications.
 *----------------------------------------------------------------------------
 * ASO | 5/12/02  |  5  | New functions added
 *----------------------------------------------------------------------------
 * ASO | 9/12/02  |  6  | New functions from 5 altered and completed
 *----------------------------------------------------------------------------
 * \endverbatim
 */

#include "Allocatn.h"
#include <iostream> // ASO 29/11/02 changed to iostream from iostream.h to meet the C++ standard

using namespace std; // ASO 29/11/02 needed as iostream declares function in std.


// ASO 9/12/02 - Should CharnesCooper contain myAssignments?
// If the structure of myAssignments differs with each implementation
// (CC, washburn etc) then it should nto be stored in the base class.
// If not it should be in the base class. The start of a constructor is below...
// it may not be correct.

/*
void CharnesCooper::CharnesCooper(int p_no_resources, int p_no_areas, const double *p_effectiveness,
		const double *p_POC)
		:Allocation(p_no_resources, p_no_areas, *p_effectiveness, *p_POC)
{
	memset(myAssignments, 0, (sizeof(double) * p_no_areas * p_no_resources));
}
*/

/// Returns the area number of the first area in this allocation.
/***************************************************************************/
/**
 * firstArea()
 *
 * Returns the area number of the first area in this allocation.
 *
 * If the allocation is empty, returns -1
 *
 * Future change: It would be better if it through an exception
 *
 * Author: Andre Oboler (ASO)
 */

int CharnesCooper::firstArea(void)
{
  int i;
  int j;

  // Find index of first non zero cell in myAssignments
  for(i=0; i < myNumAreas; i++)
  {
    for (j=0; j < myNumResources; j++)
    {
	  /*if(testmode==true)
	  {
			cout << "Checking value[AreaIndex=" << i << "][ResourceIndex=" << j <<"] = " << myAssignments.value[i][j] << "\n";
	  }*/
      if (myAssignments.value[i][j]!=0)
      {
		return i;
      }
    }
  }

  // If no resource was found
  return -1;
}

 /// Returns the area number of the first area in this allocation.
/***************************************************************************/
/**
 * firstArea()
 *
 * Returns the first AreaAssignment (an area and a time) that a given
 * resource was assignmened to.
 *
 * If the resource does not exist in this allocation an area assignment of
 * area -1 for time 0 is returned.
 *
 * Future change: It would be better if it through an exception
 *
 * Author: Andre Oboler (ASO)
 */

AreaAssignment* CharnesCooper::firstArea(int resource)
{

  int i;

  // Find index of first non zero area for this resource
  for(i=0; i<myNumAreas; i++)
  {
    if (myAssignments.value[i][resource]!=0)
    {
      return new AreaAssignment(i, myAssignments.value[i][resource]);
    }
  }

  //Check in case this resource not assigned to any areas
  return NULL;
}

 /// Given an area number, returns the next area that has something assignned to it
 /****************************************************************************/
 /**
 * nextArea()
 *
 * Given an area number, returns the next area that has something assignned to
 * it in this set of allocations.
 *
 * If there is no other area with an allocation of resources greater than 0,
 * the function returns -1.
 * NOTE: This function searches by AREA, that is, it searches through all area N
 * and all resources before searchting through area N+1 and all resources... etc.
 *
 * Given a resource and an area,
 * returns the next area (and time) that has _this resource_ was assigned to.
 *
 * If there are no more areas or the resource is nto assigned to any more areas
 * returns an area of -1 for time 0
 *
 * Future change: It would be better if it through exceptions
 *
 * Author: Andre Oboler (ASO)
 */

int CharnesCooper::nextArea(int area)
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

AreaAssignment* CharnesCooper::nextArea(int resource, int area) // params: What we are talking about, where we are now (in that order)
{
  int tempArea;

  // Across 1 step
  for (tempArea=area+1; tempArea<myNumAreas ; tempArea++)
  {
    if (myAssignments.value[tempArea][resource] > 0)
    {
      // Return the area with a non zero resource allocation
      // We do not care about which resourse is here.
      return new AreaAssignment(tempArea,
				myAssignments.value[tempArea][resource]);
    }
  }

  // No more areas with assignments of this resource
  return NULL;
}


/// Given an area, it returns the first resource assigned to that area
 /*****************************************************************************/
 /**
 * firstRes()
 *
 * Given an area, it returns the first resource assigned to that
 * area (returned as a ResourceAssignment with the resource and time).
 *
 * If there are no resources, it returns an assingnment of resource -1 for time 0.
 *
 * Future change: It would be better if it through exceptions
 *
 * Author: Andre Oboler (ASO)
 */

ResourceAssignment* CharnesCooper::firstRes(int area)
{
  int tempResource;

  // step down to bottom looking for a non zero cell
  for(tempResource=0; tempResource<myNumResources; tempResource++)
  {
    if (myAssignments.value[area][tempResource] > 0)
    {
       // Return the resource with a non zero allocation
       // We know the area (passed in) and only return the resource and time

      return new ResourceAssignment(tempResource,
				    myAssignments.value[area][tempResource]);
    }
  }

  // No more resources assigned to this area
  return NULL;
}

/// Given a resource and an area, it returns the next ResourceAssignment for that area
/****************************************************************************/
/**
 * nextRes()
 *
 * Given a resource and an area, it returns
 * the next resource assigned to that area (as a ResourceAssignment).
 *
 * If there are no next resources, it returns an assingnment of resource -1 for time 0.
 * This is a sentinal value.
 *
 * Future change: This one should perhaps NOT throw an exception.
 * Or return a "warning" exception "No more resources"
 *
 * Author: Andre Oboler (ASO)
 */

ResourceAssignment* CharnesCooper::nextRes(int Area, int Resource) // params: What we are talking about, where we are now (in that order)
{

  int tempResource;
  // step down to bottom looking for a non zero cell
  for(tempResource=Resource+1; tempResource<myNumResources; tempResource++)
  {
    if (myAssignments.value[Area][tempResource] > 0)
    {
      // Return the resource (and time) with a non zero allocation
      // We already know the area as it was passed in (so no need
      // to return this to the user)
      return new ResourceAssignment(tempResource,
				    myAssignments.value[Area][tempResource]);
    }
  }

  // No more areas with assignments
  return NULL;
}

/// Top level of quickSort algorithm. The recursive part is in qSort.
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

  /*for (int i=0; i< arraySize; i++)
  {
	cout << "[" << i << "]" << items[i] << " " << calcInitialPSR(0, items[i]) << " ";
  }	*/
}


void CharnesCooper::qSort(int items[], int left, int right)
{
  int initialLeft, initialRight, temp;
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
 * resource 0 to the set of areas. The search endurance (time the resource is
 * available for) is stored in myAvailable[0].
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
    myAssignments.value[j][0] = 0.0;
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

  /*
   * Sort list of areas into descending order of PSR for resource
   * 0.  Uses selection sort.
   */

  quickSort(areaList, myNumAreas);

  #ifdef _ALLOCATION_TESTMODE
  for (int i=0; i< myNumAreas; i++)
  {
	cout << "[" << i << "]" << areaList[i] << " " << calcInitialPSR(0, areaList[i]) << " ";
  }
  #endif
/*
  double minPSR;
  int minIndex;
  int m, n;

  for (m=myNumAreas-1; m>0; m--)
  {
    /* Find minimum PSR in areaList[0,...,m] */
/*    minIndex = 0;
    minPSR = calcInitialPSR(0, areaList[0]);

    for (n=1; n<=m; n++)
    {
      if (calcInitialPSR(0, areaList[n]) < minPSR)
      {
        minIndex = n;
        minPSR = calcInitialPSR(0, areaList[n]);
      }
    }

    int temp = areaList[minIndex];
    areaList[minIndex] = areaList[m];
    areaList[m] = temp;
  }

  */

  // double searchEndRem = myAvailable[0];  //Remaining search endurance (after any assignments that have been made)
											// No need for this extra layer. Just reduce the stored level of available resource
  double PSRmax;                            //Maximum PSR of areas
  double PSR2;                              //2nd highest PSR of areas
  int lastArea = 0;                         //Index of last area in areaList that has equal highest PSR
  double totalInvEffectiveness = 0.0 ;      //Sum of inverse effectiveness values for all areas in areaList[0,...,lastArea]

  /* Initialise above variables */
  PSRmax = calcInitialPSR(0, areaList[lastArea]);
  totalInvEffectiveness += 1 / myEffectiveness.value[areaList[lastArea]][0];

  while (lastArea < myNumAreas-1 && calcInitialPSR(0, areaList[lastArea+1]) >= PSRmax)
  {
    lastArea++;
    totalInvEffectiveness += 1 / myEffectiveness.value[areaList[lastArea]][0];
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
        proportion = (1 / myEffectiveness.value[j][0] ) / totalInvEffectiveness;

        /* Time to assign to this area */
        time = proportion * myAvailable[0];

        /* Make assignment */
        myAssignments.value[j][0] += time;
      }

      /* All hours have now been assigned for searching. */
      break;
    }

    /*
     * Resource 0 does not have equal PSR in all areas.  The areas with PSR = PSRmax
     * have their PSR driven down to PSR2, or are driven down as far as possible if
     * there is insufficient search endurance remaining (myAvailable[0]) to drive them
     * down to PSR2.
     */

    /*
     * Determine what searching is necessary to drive the PSR of all areas currently
     * at PSRmax down to PSR2.  No calculation is performed if PSR2 is zero,
     * as an infinite amount of searching is then required.
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
        timeNeeded[j] = coverageNeeded / (myEffectiveness.value[areaList[j]][0]);
        totalTimeNeeded += timeNeeded[j];
      }
    }

    /*
     * Check if remaining search endurance (myAvailable[0]) is insufficient to drive
     * the PSR of all areas currently at PSRmax down to PSR2.  myAvailable[0] is
     * always insufficient if PSR2 is zero, as an infinite amount of
     * searching is then required.
     */
    if (!(PSR2 > 0.0) || myAvailable[0] < totalTimeNeeded)
    {
      /*
       * With insufficient search endurance remaining, myAvailable[0]
       * is split between areas in such a way that all areas that currently have
       * PSR = PSRmax have the same final PSR.  That is, the search time assigned
       * to each area is proportional to the inverse of resource 0's effectiveness
       * in that area.
       */

      double proportion;
      double time;
      for (j=0; j<=lastArea; j++)
      {
        /* Proportion of remaining search endurance to assign to this area */
        proportion = (1 / (myEffectiveness.value[areaList[j]][0]) ) / totalInvEffectiveness;

        /* Time to assign to this area */
        time = proportion * myAvailable[0];

        /* Make assignment */
        myAssignments.value[areaList[j]][0] += time;
      }

      /* All hours have now been assigned for searching. */
      break;
    }
    else
    {
      /*
       * Sufficient search endurance (myAvailable[0]) remains to drive PSR of all areas at
       * PSRmax down to PSR2.  Assign the required time to each area (as calculated above).
       */
      for (j=0; j<=lastArea; j++)
      {
        myAssignments.value[areaList[j]][0] += timeNeeded[j];
      }

      myAvailable[0] -= totalTimeNeeded;

      /* Update lastArea, PSRmax, PSR2 and totalInvEffectiveness for next iteration */
      PSRmax = PSR2;
      lastArea++;
      totalInvEffectiveness += 1 / myEffectiveness.value[areaList[lastArea]][0];

      while (lastArea < myNumAreas-1 && calcInitialPSR(0, areaList[lastArea+1]) >= PSRmax)
      {
        lastArea++;
        totalInvEffectiveness += 1 / myEffectiveness.value[areaList[lastArea]][0];
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
  delete areaList;
  areaList = 0;
  delete timeNeeded;
  timeNeeded = 0;

  #ifdef _ALLOCATION_TESTMODE
    cout << "Leaving CharnesCooper::calcAllocation()" << endl;
  #endif
}
