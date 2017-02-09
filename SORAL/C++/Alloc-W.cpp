/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/

/** \file Alloc-W.cpp
 *  \brief Alloc-W.cpp contains the Washburn allocation code
 * 
 *
 * Contains calcAllocation() and the functions used by the iterators 
 * for moving over allocations. 
 *
 * Authors: David Albrecht (DWA)
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * DWA | 08/01/03 |  1  | Created.                                            
 *-----+----------+-----+-----------------------------------------------------
 * DWA | 15/02/03 |  2  | Fixed init and other index bugs              
 *-----+----------+-----+-----------------------------------------------------
 * crt | 28/03/03 |  3  | Naming changes.
 *-----+----------+-----+-----------------------------------------------------
 * \endverbatim
 */

//============================================================================//
// Written by david Albrecht                              http://sarbayes.org //
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

#include "Alloc-W.h"
#include "Array2D.h"
#include <iostream> 
//#include <limits.h>
#include <math.h>
#include <limits>

using namespace std; 

// Define our numerical tolerance TOL. The authors of 
// Numerical Recipes recommend TOL no smaller than
// the square root of machine precision.
Washburn::Washburn(const int p_no_resources, 
						 const int p_no_areas, 
						 const Array2D& p_effectiveness,
						 const valarray<double> p_endurance,
						 const valarray<double> p_POC)
:  Allocation(p_no_resources, p_no_areas, p_effectiveness, p_endurance, p_POC),
  FALSE_AREA(p_no_areas),
  TOL(sqrt(numeric_limits<double>::epsilon())),
  myExtendedEffectiveness(p_no_areas+1, p_no_resources), 
  myAssignments(p_no_areas+p_no_resources+2), 
  myAreaIndex(p_no_areas+1), myResourceIndex(p_no_resources),
  myLambda(p_no_resources), myMu(p_no_areas+1),
  myCoefficients(p_no_areas + p_no_resources + 2)
{


  // Calculate the weight needed for the effectiveness of the FALSE_AREA.

  double weight = 0;
  int i, j;

  for (j = 0; j < myNumResources; j++)
  {
    weight += myEndurance[j];
  }
  
  if (weight > 0)
  {
    weight = 5/weight;
  }
  else
  {
    throw "No Resources available";
  }

  // Initialize all the data structures

  myAssignments[ROOT].set(0, false, ROOT, NULL_NODE, 1, NULL_NODE);

  for (i = 0; i < myNumAreas; ++i)
  {
    myMu[i] = myPOC[i];
    myAreaIndex[i] = i+1;
    myAssignments[i+1].set(0, true, i, ROOT, NULL_NODE, i+2); // i+2 is next sibling

    for (j = 0; j < myNumResources; ++j)
    {
      myExtendedEffectiveness[i][j] = myEffectiveness[i][j];
    }
  }

  myMu[FALSE_AREA] = sqrt(TOL)*exp(-5.0);
  myAssignments[FALSE_AREA+1].set(0, true, FALSE_AREA, ROOT, FALSE_AREA+2, 
				  NULL_NODE);

  for (j = 0; j < myNumResources; j++)
  {
    myLambda[j] = myMu[FALSE_AREA]*weight;
    myResourceIndex[j] = FALSE_AREA + 2 + j;
    myExtendedEffectiveness[FALSE_AREA][j] = weight;
    myAssignments[FALSE_AREA+2+j].set(myEndurance[j], false, j, FALSE_AREA+1, 
				      NULL_NODE, FALSE_AREA+3+j);
  }
  myAssignments[FALSE_AREA+1+myNumResources].set(myEndurance[myNumResources-1], false, myNumResources-1, 
	  FALSE_AREA+1, NULL_NODE, NULL_NODE);

  #ifdef _ALLOCATION_TESTMODE
  cout << endl << "Effectiveness" << endl;

  for (i = 0; i <= myNumAreas; ++i)
  {
    for (j = 0; j < myNumResources; ++j)
    {
      cout << i << " " << j << " " << myExtendedEffectiveness[i][j] << endl;
    }
  }

  cout << endl << "Resources " << endl;

  for (i = 0; i < myNumResources; ++i)
  {
    cout << i << " Index " << myResourceIndex[i] 
	 << " Lambda " << myLambda[i] << endl;
  }

  cout << endl << "Areas " << endl;

  for (i = 0; i < myNumAreas; ++i)
  {
    cout << i << " Index " << myAreaIndex[i] 
	 << " Mu " << myMu[i] << endl;
  }

  cout << "Assignments " << endl;

  for (i = 0; i < p_no_areas+p_no_resources+2; ++i)
  {
    cout << i
	 << " time " << myAssignments[i].time << endl
	 << "isArea " << myAssignments[i].isArea << endl
	 << "number " << myAssignments[i].number << endl
	 << "parent " << myAssignments[i].parent << endl
	 << "child " << myAssignments[i].firstChild << endl
	 << "sibling " << myAssignments[i].nextSibling << endl << endl;
  }
  #endif
  
  calcAllocation();
  #ifdef _ALLOCATION_TESTMODE
  cout << endl << "Optimal Assignments " << endl;

  for (i = 0; i < p_no_areas+p_no_resources+2; ++i)
  {
    cout << i
	 << " time " << myAssignments[i].time << endl
	 << "isArea " << myAssignments[i].isArea << endl
	 << "number " << myAssignments[i].number << endl
	 << "parent " << myAssignments[i].parent << endl
	 << "child " << myAssignments[i].firstChild << endl
	 << "sibling " << myAssignments[i].nextSibling << endl << endl;
  }
  #endif

}

Washburn::~Washburn()
{
}

/// Returns the area number of the first area in this allocation.
/***************************************************************************/
/**
 * firstArea()
 *
 * Returns the area number of the first area in this allocation. 
 *
 * If the allocation is empty, returns -1
 * 
 * Author: David Albrecht (DWA)
 */
 
		
ActiveArea* Washburn::firstArea(void) const
{
  for (int i = 0; i < myNumAreas; ++i)
  {
    int index = myAreaIndex[i];

    if (myAssignments[index].parent != ROOT || 
	myAssignments[index].firstChild != NULL_NODE)
    {
      return new ActiveArea(i);
    }
  }
  
  return NULL;
}

/// Returns the area number of the first area in this allocation.
/***************************************************************************/
/**
 * firstArea()
 *
 * Returns the first AreaAssignment (an area and a time) that a given 
 * resource was assigned to.
 * 
 * If the resource does not exist in this allocation a NULL is returned.
 * 
 * Author: David Albrecht (DWA)
 */

AreaAssignment* Washburn::firstArea(const int resource) const
{
  int resourceIndex = myResourceIndex[resource];
  int parentIndex = myAssignments[resourceIndex].parent;
  int childIndex = myAssignments[resourceIndex].firstChild;
  if (parentIndex == ROOT && childIndex != NULL_NODE)
  {
    return new AreaAssignment(myAssignments[childIndex].number, 
			      myAssignments[childIndex].time);
  }
  else if (parentIndex != ROOT && myAssignments[parentIndex].number != FALSE_AREA)
  {
    return new AreaAssignment(myAssignments[parentIndex].number, 
			      myAssignments[resourceIndex].time);
  }

  return NULL;
}
 
/// Given an area number, returns the next area that has something assigned to it
/****************************************************************************/
/**
 * nextArea()
 *
 * Given an area number, returns the next area that has something assigned to 
 * it in this set of allocations.
 *
 * If there is no other area with an allocation of resources greater than 0, 
 * the function returns -1. 
 *
 * Author: David Albrecht (DWA)
 */

ActiveArea* Washburn::nextArea(const int currentArea) const
{
  for (int i = currentArea+1; i < myNumAreas; ++i)
  {
    int index = myAreaIndex[i];

    if (myAssignments[index].parent != ROOT 
		|| myAssignments[index].firstChild != NULL_NODE)
    {
      return new ActiveArea(i);
    }
  }
  
  return NULL;
}

/// Given an area number, returns the next area that has something assigned to it
/****************************************************************************/
/**
 * nextArea()
 *
 * Given a resource and an area, 
 * returns the next area (and time) that has this resource assigned to.
 *
 * If there are no more areas or the resource is not assigned to any more areas
 * it returns NULL.
 *
 * Author: David Albrecht (DWA)
 */

AreaAssignment* Washburn::nextArea(const int resource, const int currentArea) const
{
  int resourceIndex = myResourceIndex[resource];
  int areaIndex = myAreaIndex[currentArea];

  if (myAssignments[resourceIndex].parent == areaIndex)
  {
    int childIndex = myAssignments[resourceIndex].firstChild;

    if (childIndex != NULL_NODE)
    {
      return new AreaAssignment(myAssignments[childIndex].number,
				myAssignments[childIndex].time);
    }
    
    return NULL;
  }

  if (myAssignments[areaIndex].parent == resourceIndex)
  {
    int siblingIndex = myAssignments[areaIndex].nextSibling;

    if (siblingIndex != NULL_NODE)
    {
      return new AreaAssignment(myAssignments[siblingIndex].number,
				myAssignments[siblingIndex].time);
    }
  }

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
 * If there are no resources, it returns a NULL.
 *
 * Author: David Albrecht (DWA)
 */

ResourceAssignment* Washburn::firstRes(const int area) const
{
  int areaIndex = myAreaIndex[area];
  int parentIndex = myAssignments[areaIndex].parent;

  if (parentIndex != ROOT)
  {
    return new ResourceAssignment(myAssignments[parentIndex].number, 
				  myAssignments[areaIndex].time);
  }

  int childIndex = myAssignments[areaIndex].firstChild;

  if (parentIndex == ROOT && childIndex != NULL_NODE)
  {
    return new ResourceAssignment(myAssignments[childIndex].number, 
				  myAssignments[childIndex].time);
  }

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
 * If there are no next resources, it returns a NULL.
 *
 * Author: David Albrecht (DWA)
 */

ResourceAssignment* Washburn::nextRes(const int area, const int currentResource) const
{
  int resourceIndex = myResourceIndex[currentResource];
  int areaIndex = myAreaIndex[area];

  if (myAssignments[areaIndex].parent == resourceIndex)
  {
    int childIndex = myAssignments[areaIndex].firstChild;

    if (childIndex != NULL_NODE)
    {
      return new ResourceAssignment(myAssignments[childIndex].number,
				    myAssignments[childIndex].time);
    }
    
    return NULL;
  }

  if (myAssignments[resourceIndex].parent == areaIndex)
  {
    int siblingIndex = myAssignments[resourceIndex].nextSibling;

    if (siblingIndex != NULL_NODE)
    {
      return new ResourceAssignment(myAssignments[siblingIndex].number,
				    myAssignments[siblingIndex].time);
    }
  }

  return NULL;
}
	
		
/// Calculate the allocation using the Washburn algorithm		
/***************************************************************************/
/**
 * calcAllocationWashburn()
 * 
 * Uses the Washburn algorithm to calculate the optimal assignment of
 * resources to the set of areas. 
 *
 * This set of assignments is stored in myAssignments.
 *
 * Author: David Albrecht (DWA)
 */

void Washburn::calcAllocation()
{
  #ifdef _ALLOCATION_TESTMODE
    cout << "Entering Washburn::calcAllocation()" << endl;
  #endif
    
    while (!optimum())
    {

      #ifdef _ALLOCATION_TESTMODE
        cout << endl << " NEXT PIVOT " << myNextArea << " " << myNextResource << endl;
//		  << "Enter Pivot" << endl;
//	  cin >> myNextArea >> myNextResource;
//	  cout << endl << " NEXT PIVOT " << myNextArea << " " << myNextResource << endl;
      #endif
	  
	  updateAssignment();
	  
	  #ifdef _ALLOCATION_TESTMODE
	    cout << endl << "Updated Assignments " << endl;

	    for (int i = 0; i < myNumAreas+myNumResources+2; ++i)
		{
		   cout << i << endl 
		    	 << "time " << myAssignments[i].time << endl
			     << "isArea " << myAssignments[i].isArea << endl
			     << "number " << myAssignments[i].number << endl
			     << "parent " << myAssignments[i].parent << endl
			     << "child " << myAssignments[i].firstChild << endl
			     << "sibling " << myAssignments[i].nextSibling << endl << endl;
		}
        
	    cout << endl << "Lambda " << endl;

        for (i = 0; i < myNumResources; ++i)
		{
           cout << i << " " << myLambda[i] << endl;
		}

        cout << endl << "Mu " << endl;

        for (i = 0; i < myNumAreas; ++i)
		{
          cout << i << " " << myMu[i] << endl;
		}
        #endif
	}
  #ifdef _ALLOCATION_TESTMODE
    cout << "Leaving Washburn::calcAllocation()" << endl;
  #endif
}

/// check whether the optimum has been reached
/***************************************************************************/
/**
 * optimum()
 * 
 * This function checkes whether the Lagrangian multipliers satisfy the
 * Karush-Kuhn-Tucker conditions. These conditions are:
 *
 *      myLambda[j] >= myExtendedEffectiveness[i][j]*myMu[i]
 *
 * If all the conditions hold, then the functions returns true. Otherwise
 * the function returns false.
 *
 * The function also finds the i and j corresponding to the largest value of
 * 
 *    myExtendedEffectiveness[i][j]*myMu[i]/myLambda[j]
 *
 * The values of i and j, are myNextArea and myNextResource, respectively.
 *
 * Author: David Albrecht (DWA)
 */
bool Washburn::optimum()
{
  double kkt = 1.0;

  for (int i = 0; i <= myNumAreas; ++i)
  {
    for (int j = 0; j < myNumResources; ++j)
    {
      if (kkt*myLambda[j] < myExtendedEffectiveness[i][j]*myMu[i])
      {
	myNextArea = i;
	myNextResource = j;
	
	///\todo Check: Do we we need to check divide by zero here?

	kkt = myExtendedEffectiveness[i][j]*myMu[i]/myLambda[j];
      }
    }
  }

  #ifdef _ALLOCATION_TESTMODE
  cout << endl << "KKT " << kkt << endl;
  #endif

  if (kkt < 1 + TOL)
  {
    return true;
  }
  
  return false;
}

/// update the assignment tree
/***************************************************************************/
/**
 * updateAssignment()
 * 
 * Update the assignment so that time of resource myNextResource 
 * is added to the area myNextArea.
 *
 * Author: David Albrecht (DWA)
 */

void Washburn::updateAssignment()
{
  double time = 0;
  double timeStep = 0;

  bool finished = false;

  // These are defined for readability of statements below.
  int areaIndex = myAreaIndex[myNextArea];
  int resourceIndex = myResourceIndex[myNextResource];

  while (!finished)
  {
    for (int i = 0; i < myNumAreas + myNumResources + 2; ++i)
    {
      myCoefficients[i] = 0;
    }

    int areaRootChild = findRootChild(areaIndex);
    int resourceRootChild = findRootChild(resourceIndex);
    int pivotIndex;

    if (areaRootChild == resourceRootChild)
    {
      // area myNextArea and resource myNextResource belong to same subtree

      double coeff = (myLambda[myNextResource] - myMu[myNextArea]*myExtendedEffectiveness[myNextArea][myNextResource])/sumMu(areaRootChild);

	  // Setup and solve the equation which determines how much of myNextResource
	  // we can add to myNextArea, without the amount of a resource that is currently
	  // being used in an area being decreased to zero. The amount of myNextResource 
	  // we can add to myNextArea is denoted by timeStep, and the resource and
	  // area combination, which is decreased to zero is index by pivotIndex. 
      createEqn(areaRootChild, coeff);
	  myCoefficients[resourceIndex] = 1;
	  myCoefficients[areaIndex] += myExtendedEffectiveness[myNextArea][myNextResource];
      pivotIndex = resourceIndex;
      timeStep = solveEqn(areaRootChild, myEndurance[myNextResource], pivotIndex);
      
	  // Update the myMu, myLambda, and the resource values.

	  updateValues(areaRootChild, exp(coeff*timeStep), timeStep);
      
	  // time is the total amount of myNextResource we add to myNextArea
	  
	  time += timeStep;

	  if (pivotIndex == resourceIndex 
          && myAssignments[resourceIndex].firstChild == NULL_NODE)
      {
		  // All myNextResource can be added to myNextArea
	
		  myLambda[myNextResource] = myExtendedEffectiveness[myNextArea][myNextResource]*myMu[myNextArea];
	      joinSubtree(resourceIndex, areaIndex);
	      // myAssignments[resourceIndex].time = time;
		  myAssignments[resourceIndex].time = myEndurance[myNextResource];
	      finished = true;
      }
      else
      {
	      joinSubtree(pivotIndex, ROOT);
      }
    }
    else
    {
      // area myNextArea and resource myNextResource belong to 
      // different subtrees
    
 	  // Setup and solve the equation which determines how much of myNextResource
	  // we can add to myNextArea, without the amount of a resource that is currently
	  // being used in an area being decreased to zero. The amount of myNextResource 
	  // we can add to myNextArea is denoted by timeStep, and the resource and
	  // area combination, which is decreased to zero is index by pivotIndex. 
  
      double resourceCoeff = myLambda[myNextResource]/sumMu(resourceRootChild);
      
	  // First determine timeStep subject to the constraints with respect 
	  // to myNextResource
      createEqn(resourceRootChild, resourceCoeff);
      myCoefficients[resourceIndex] = 1;
      pivotIndex = resourceIndex;
      timeStep = solveEqn(resourceRootChild, myEndurance[myNextResource], pivotIndex);

      // If areaRootChild has any children, then determine timeStep subject to the 
	  // constraints corresponding to myNextArea
 
      double areaCoeff = -myExtendedEffectiveness[myNextArea][myNextResource]*myMu[myNextArea]/sumMu(areaRootChild);

      if (myAssignments[areaRootChild].firstChild == NULL_NODE)
      {
		  myCoefficients[areaRootChild] = 0;
	  }
	  else 
	  {
	      createEqn(areaRootChild, areaCoeff);
	      myCoefficients[areaIndex] += myExtendedEffectiveness[myNextArea][myNextResource];
	      timeStep = solveEqn(areaRootChild, timeStep, pivotIndex);
      }


	  // tmax is maximum amount of myNextResource we can add to myNextArea that we can
	  // guarantee will increase the probability of detection.
      double tmax = log(myExtendedEffectiveness[myNextArea][myNextResource]*myMu[myNextArea]/myLambda[myNextResource])/(resourceCoeff - areaCoeff);
      
      if (tmax < timeStep)
      {
         timeStep = tmax;
      }

      time += timeStep;

 	  // Update the myMu, myLambda, and the resource values.
	  
	  updateValues(resourceRootChild, exp(timeStep*resourceCoeff), timeStep);
      updateValues(areaRootChild, exp(timeStep*areaCoeff), timeStep);
      
	  if (timeStep < tmax && pivotIndex == resourceIndex 
                       && myAssignments[resourceIndex].firstChild == NULL_NODE)
      {
		// All myNextResource can be added to myNextArea
        myLambda[myNextResource] = myExtendedEffectiveness[myNextArea][myNextResource]*myMu[myNextArea];
        joinSubtree(resourceIndex, areaIndex);
	    // myAssignments[resourceIndex].time = time;
        myAssignments[resourceIndex].time = myEndurance[myNextResource];
        finished = true;
      }
      else if (timeStep < tmax)
      {
        joinSubtree(pivotIndex, ROOT);
      }
      else if (areaIndex == areaRootChild)
      {
	    joinSubtree(areaIndex, resourceIndex);
	    myAssignments[areaIndex].time = time;
	    finished = true;
      }
      else if (resourceIndex == resourceRootChild)
      {
        joinSubtree(resourceIndex, areaIndex);
        myAssignments[resourceIndex].time = time;
		finished = true;
      }
      else
      {
        rotateSubtree(resourceIndex);
		joinSubtree(resourceIndex, areaIndex);
        myAssignments[resourceIndex].time = time;
		finished = true;
      }	
    }
  }
}

/// find the child of ROOT in subtree containing the node with index p_index
/***************************************************************************/
/**
 * findRootChild(p_index)
 * 
 * Returns the index of the node which is a child of ROOT and is also
 * in the subtree containing the node with index p_index.
 *
 * Author: David Albrecht (DWA)
 */
int Washburn::findRootChild(int p_index)
{
  int parentIndex = myAssignments[p_index].parent;

  while (parentIndex != ROOT)
  {
    p_index = parentIndex;
    parentIndex = myAssignments[p_index].parent;
  }

  return p_index;
}
    
/// sum the Mu values in the subtree containing the node with index p_index
/***************************************************************************/
/**
 * sumMu(p_index)
 * 
 * Returns the sum of the Mu values corresponding to the areas contained 
 * in the subtree whose root node has index p_index.
 *
 * Author: David Albrecht (DWA)
 */
double Washburn::sumMu(int p_index)
{
  double sum = 0;

  if (p_index != NULL_NODE)
  {
    if (myAssignments[p_index].isArea)
    {
      sum += myMu[myAssignments[p_index].number];
    }

    sum += sumMu(myAssignments[p_index].firstChild);
    
    if (myAssignments[p_index].parent != ROOT)
    {
      sum += sumMu(myAssignments[p_index].nextSibling);
    }
  }

  return sum;
}

/// create the equations 
/***************************************************************************/
/**
 * createEqn(p_index, p_coeff)
 * 
 * Create the equations for calculating how much of the resource myNextRes
 * we can assign to the area myNextArea
 *
 * Author: David Albrecht (DWA)
 */
void Washburn::createEqn(int p_index, double p_coeff)
{
  if (p_index != NULL_NODE)
  {
    if (myAssignments[p_index].isArea)
    {
      myCoefficients[p_index] = p_coeff;
    }

    createEqn(myAssignments[p_index].firstChild, p_coeff);

    if (myAssignments[p_index].parent != ROOT)
    {
      createEqn(myAssignments[p_index].nextSibling, p_coeff);
    }
  }
}
		
/// solve the equations.
/***************************************************************************/
/**
 * solveEqn(p_index, p_maxTime, p_pivot)
 * 
 * Solve the equations for calculating how much of the resource myNextResource
 * we can assign to the area myNextArea
 *
 * Author: David Albrecht (DWA)
 */
double Washburn::solveEqn(int p_index, double p_maxTime, int& p_pivot)
{
  double time = p_maxTime;

  if (p_index != NULL_NODE)
  {
    time = solveEqn(myAssignments[p_index].firstChild, p_maxTime, p_pivot);

    int parentIndex = myAssignments[p_index].parent;

    if (parentIndex != ROOT)
    {
      time = solveEqn(myAssignments[p_index].nextSibling, time, p_pivot);
      
      int nodeNum = myAssignments[p_index].number;
      int parentNum = myAssignments[parentIndex].number;

      if (myAssignments[p_index].isArea)
      {
	///\todo Check: Do we need to check whether effectiveness is nozero?

	myCoefficients[p_index] /= myExtendedEffectiveness[nodeNum][parentNum];
	myCoefficients[parentIndex] -= myCoefficients[p_index];
      }
      else
      {
	myCoefficients[parentIndex] -= myCoefficients[p_index]*myExtendedEffectiveness[parentNum][nodeNum];
      }

      if (time*myCoefficients[p_index] > myAssignments[p_index].time)
      {
	time = myAssignments[p_index].time/myCoefficients[p_index];
	p_pivot = p_index;
      }
    }
    else
    {
      myCoefficients[p_index] = 0;
    }
  }

  return time;
}

/// update the values in the data structures
/***************************************************************************/
/**
 * updateValues(p_index, factor, time)
 * 
 * Update the values in the assignment subtree containing the node with index
 * p_index, and the Lambda and Mu values for the nodes in this subtree.
 *
 * Author: David Albrecht (DWA)
 */
void Washburn::updateValues(int p_index, double factor, double time)
{
  if (p_index != NULL_NODE)
  {
    myAssignments[p_index].time -= time*myCoefficients[p_index];

    int number = myAssignments[p_index].number;
    if (myAssignments[p_index].isArea)
    {
      myMu[number] *= factor;
    }
    else
    {
      myLambda[number] *= factor;
    }

    updateValues(myAssignments[p_index].firstChild, factor, time);

    if (myAssignments[p_index].parent != ROOT)
    {
      updateValues(myAssignments[p_index].nextSibling, factor, time);
    }
  }
}

/// rotate the subtree
/***************************************************************************/
/**
 * rotateSubtree(p_index)
 * 
 * Rotate the subtree containing the node with index p_index to make this node
 * a child of ROOT.
 *
 * Author: David Albrecht (DWA)
 */
void Washburn::rotateSubtree(int p_index)
{
  int parentIndex = myAssignments[p_index].parent;

  if (parentIndex != ROOT)
  {
    rotateSubtree(parentIndex);
    disconnectSubtree(parentIndex);
	disconnectSubtree(p_index);
    connectSubtree(parentIndex, p_index);
    connectSubtree(p_index, ROOT);
    
    // swap time values of nodes with indicies parentIndex and p_index
    
    double tmp = myAssignments[p_index].time;
    myAssignments[p_index].time = myAssignments[parentIndex].time;
    myAssignments[parentIndex].time = tmp;
  }
}

/// make the node with p_index a child of the node with index p_newParentIndex
/***************************************************************************/
/**
 * joinSubtree(p_index, p_parentIndex)
 *
 * Join the subtree containing the node with index p_index to the node
 * with index p_parentIndex.
 *
 * Author: David Albrecht (DWA)
 */
void Washburn::joinSubtree(int p_index, int p_parentIndex)
{
  disconnectSubtree(p_index);
  connectSubtree(p_index, p_parentIndex);
}

/// Disconnect the subtree 
/***************************************************************************/
/**
 * disconnectSubtree(int p_index)
 *
 * Disconnect the subtree which has the node with index p_index as its root 
 * from its old subtree.
 *
 * Author: David Albrecht (DWA)
 */
void Washburn::disconnectSubtree(int p_index)
{
  int parentIndex = myAssignments[p_index].parent;
  int siblingIndex = myAssignments[parentIndex].firstChild;

  if (siblingIndex == p_index)
  {
    myAssignments[parentIndex].firstChild = myAssignments[siblingIndex].nextSibling;
  }
  else
  {
    int nextSiblingIndex = myAssignments[siblingIndex].nextSibling;

    while (nextSiblingIndex != p_index)
    {
      siblingIndex = nextSiblingIndex;
      nextSiblingIndex = myAssignments[siblingIndex].nextSibling;
    }
    myAssignments[siblingIndex].nextSibling = myAssignments[nextSiblingIndex].nextSibling;
  }
}

/// connect the subtree 
/***************************************************************************/
/**
 * connectSubtree(p_index, p_parentIndex)
 * 
 * Connect the subtree which has the node with index p_index as its root to
 * the node with index p_parentIndex.
 *
 * Author: David Albrecht (DWA)
 */

void Washburn::connectSubtree(int p_index, int p_parentIndex)
{
  myAssignments[p_index].nextSibling = myAssignments[p_parentIndex].firstChild;
  myAssignments[p_parentIndex].firstChild = p_index;
  myAssignments[p_index].parent = p_parentIndex;
}

/// get the amount of resource p_res allocated to area p_area
/***************************************************************************/
/**
 * getAssignment(p_resource, p_area)
 * 
 * Returns the amount of resource p_resource which has been allocated to the
 * area p_area.
 *
 * Author: David Albrecht (DWA)
 */

double Washburn::getAssignment(int p_resource, int p_area)
{
  int resourceIndex = myResourceIndex[p_resource];
  int areaIndex = myAreaIndex[p_area];

  if (myAssignments[resourceIndex].parent == areaIndex)
  {
    return myAssignments[resourceIndex].time;
  }

  if (myAssignments[areaIndex].parent == resourceIndex)
  {
    return myAssignments[areaIndex].time;
  }

  return 0;
}
