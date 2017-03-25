/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file Allocatn.cpp
 *  \brief Allocatn.cpp contains the generic allocation code
 *
 * Implements the base Allocation class. This class is used as the default
 * interface to an allocation object. All other objects that need to be used
 * as an allocation object inherit from this.
 *
 * For more details, see the header file (Allocatn.h).
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 05/12/01 |  1  | Created.
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 02/02/02 |  2  | Slight modifications.
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 25/02/02 |  3  | Modifications (bug fixing).
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 19/01/03 |  4  | Changed to work with vectors
 *-----+----------+-----+-----------------------------------------------------
 * crt | 10mar03  | 4.5 | Began post-code-review changes.
 *-----+----------+-----+-----------------------------------------------------
 * crt | 11mar03  | 4.6 | Disabled copy ctor, assignment for itors.
 *     |          |     | Redid calcCoverage w/o itors. Similar. (cvs 1.10)
 *-----+----------+-----+-----------------------------------------------------
 * aso | 12mar03  | 4.7 | Cleaning up comments, remove get functions that 
 *     |          |     | return iterators. Allocation should not return itrs.
 *-----+----------+-----+-----------------------------------------------------
 * crt | 28mar03  | 4.8 | Privatization, reprotection, modification.
 *-----+----------+-----+-----------------------------------------------------
 * crt | 18apr03  |  5  | Fixed getTotalPOS to recalculate getNewPOC when
 *     |          |     | forceRecalc is set. Bug found by GT.
 *-----+----------+-----+-----------------------------------------------------
 * \endverbatim
 */


//===========================================================================//
// Written by Michael Eldridge, Gareth Thompson, Andre Oboler, and C. Twardy //
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


#include "memory.h"
#include <iostream> // ASO 29/11/02 The new C++ standard. No longer iostream.h
#include "Allocatn.h"
#include "containr.h"
#include <cstdlib>

using namespace std; //ASO 29/11/02 iostream declares things in the std 
                     //namespace rather than global as iostream.h did.
                     
                     
extern "C"  
valarray<double> toValArray(unsigned int size, const double inArray[]) {
    valarray<double> outArray(size);
    for (int i = 0; i < size; i++) {
        outArray[i] = inArray[i];
    }
    return outArray;
}
                     

/**** Allocation *************************************************************/
/// Base constructor for the allocation class. 
/**
 * Base constructor for the allocation class. Creates all the memory
 * objects for storing all of the search information that is not dependant 
 * on the search algorithm. The Assignments parameters are NOT stored in 
 * allocation as they are specific to the algorithm. For example, 
 * Washburn uses a tree structure while Charnes Cooper uses an Array2D. 
 * The most efficient storage type should be used for allocations as
 * the potential number of allocations is areas * resources, which can be 
 * larger.
 *
 */
                            

Allocation::Allocation(const int p_no_resources, 
							  const int p_no_areas, 
							  const Array2D& p_effectiveness,
							  const valarray<double> p_endurance, 
							  const valarray<double> p_POC)
  : myNumResources(p_no_resources),
	 myNumAreas(p_no_areas),             
	 myEffectiveness(p_effectiveness),   // Assumes copy ctor for Array2D
	 myEndurance(p_endurance),           
	 myPOC(p_POC),                       
	 myNewPOC(myPOC),                    // NewPOC initially equals old
	 myCoverage(myNumAreas),             // valarray filled with zeros
	 myPOD(myNumAreas),                  //            "
	 myPOS(myNumAreas),                  //            "
	 myTotalPOS(0),                      // No searching done yet.
	 forceRecalc(false)                  // Only UserDef changes this.
{
#ifdef _ALLOCATION_TESTMODE
  cout << "Creating base allocation object (Allocation::Allocation)" << endl;
#endif

#ifdef _ALLOCATION_TESTMODE
  cout << "Done making base allocation (Allocation::Allocation)" << endl;
#endif
}

Allocation::Allocation(const Allocation &p_allocation)
: myNumResources(p_allocation.myNumResources),
	 myNumAreas(p_allocation.myNumAreas),
	 myEffectiveness(p_allocation.myEffectiveness),
	 myEndurance(p_allocation.myEndurance),
	 myPOC(p_allocation.myPOC),
	 myNewPOC(p_allocation.myNewPOC),
	 myCoverage(p_allocation.myCoverage),
	 myPOD(p_allocation.myPOD),
	 myPOS(p_allocation.myPOS),
	 myTotalPOS(p_allocation.myTotalPOS),
	 forceRecalc(p_allocation.forceRecalc)
{

}
/// 
/**** ~Allocation ************************************************************/
/**
 * Reclaims all the memory used by the base allocation object.
 *
 * \todo ASO 12mar03 Should this exist? We removed most fo the other 
 * "unuseful" destructors.
 *  Now we are using the vector class, the clean up is taken care of by the
 *  vectors destructor. So we don't have to "delete [] myCoverage;" etc.
 *
 */

Allocation::~Allocation()
{
#ifdef _ALLOCATION_TESTMODE
   cout << "Deleting base allocation object (Allocation::~Allocation)" << endl;
#endif

// 		delete myPOC.clear();
// 		delete [] myCoverage;
// 		delete [] myPOD;
// 		delete [] myPOS;
// 		delete [] myNewPOC;
	

#ifdef _ALLOCATION_TESTMODE
	 cout << "Done deleting base allocation (Allocation::~Allocation)" << endl;
#endif
}

/**** getEndurance() *********************************************************/
/// Returns the original amount (endurance) for this resource and area.

double Allocation::getEndurance(int resourceNum)
{
	return myEndurance[resourceNum];
}





/**** getEffectiveness() *****************************************************/
/// Return the effectiveness of a resource in an area.
/**
 * Return the effectiveness of a resource in an area (pass the area first,
 * keeping in line with the order they are stored in the Array2D). If:
 *    W = sweep width   (this resource, this area)
 *    v = velocity      (this resource, this area)
 *    A = size of area  (m^2, or km^2 or whatever units v is measured in, sq.)
 * Effectiveness = W*v/A
 *
 * This function just returns a value the user gave us. We keep this table 
 * in case we need to recalculate (as in UserDef) and in case we wish to
 * copy construct. 
 *
 * In addition, it tracks history, because the estimated effectiveness of 
 * resource R in area A may change as the search progresses (and you learn
 * more about area A, for example). Also remember, as the search progresses,
 * the user's resource and area lists may not match the ones in this
 * allocation anymore! Therefore a get function is useful.
 * 
 * But why have to return it a piece at a time? Because it is sufficient,
 * and far more efficient than passing back the whole darn structure even
 * if the user only wanted one value! And to discourage the user
 * from creating another copy from ours. Just use ours as needed. Since
 * we <em>need</em> to keep it, the user doesn't have to.
 *
 * Author: crt
 */
double Allocation::getEffectiveness(int areaNum, 
								int resourceNum)
{
  return myEffectiveness[areaNum][resourceNum];
}



/////////////////////////////////////////////////////////////
// Below lie get functions for <em>calculated</em> values.
/////////////////////////////////////////////////////////////



/**** getCoverage() *********************************************************/
/// Returns the coverage for a specified area.
/**
 * Returns the coverage for the specified area. If the coverage for that
 * area has not been calculated, it calculates and stores it. This prevents
 * the coverage from being calculated multiple times. Admittedly, the 
 * calculation itself is simple enough not to merit storing. However, the 
 * calculation involves a traversal of myAssignments, which may be
 * expensive. And coverage is needed to calculate POD, POS, and newPOC.
 * Furthermore, the storage is quite small.
 *
 * In fact, the current implementation will recalculate whenever the 
 * current value is zero. If the user is smart and only requests coverage
 * for active areas, this works like a charm. If the user is stupid and
 * keeps asking for coverage of areas not being searched, it will keep
 * recalculating the value of zero. I only wish it also taunted them for
 * their foolish ways.
 * 
 * "But wait," you say. Surely we could initialize myCoverage to all "-1"
 * rather than "0" and so recalculate if and only if the coverage really
 * hasn't been calculated. Well, yes, but at the expense of initializing
 * every area to the WRONG value. The coverage of a non-searched area is
 * zero, and all areas start as not-searched. The present way is semantically 
 * correct, and has no penalty for proper use.
 *
 * \todo OK, I've been persuaded that initializing to "-1" has several
 * advantages. Change the implementation and the polemic.
 *
 * <b>forceRecalc</b>
 * Our clever plans break down for UserDef, which can change its allocation
 * after having already calculated with a previous one. So Allocation
 * provides a protected variable, <em>forceRecalc</em> which is false by
 * default, but which UserDef can set to true. In all the following functions,
 * we check for the forceRecalc flag. We reset the flag only after
 * recalculating getTotalPOS (which in this case also recalculates getNewPOC), 
 * since only then do we know that every value
 * in the active areas has been recalculated.
 * <b>Warning:</b> with UserDef, it is <em>especially</em> important to use 
 * the iterators for access, because only active areas are updated. If there 
 * is an area which was previously active in this UserDef, but is now 
 * inactive, any stored values will be what they used to be.
 * 
 *   -crt (27mar03)
 */

double Allocation::getCoverage(int areaNum)
{
#ifdef _ALLOCATION_TESTMODE
  cout << "Getting coverage for this area (Allocation::getCoverage)" << endl;
#endif
  
  if (forceRecalc || myCoverage[areaNum] == 0) // Probably not calculated yet
	{
	  myCoverage[areaNum] = calcCoverage(areaNum);
	}

#ifdef _ALLOCATION_TESTMODE
  cout << "getCoverage: Returning coverage[" << areaNum << "] ";
  cout << "= " << myCoverage[areaNum];
#endif

	return myCoverage[areaNum];
}

/**** getPOD() *************************************************************/
/// Returns the POD for a specified area
/**
 * Returns the POD for the specified area. If the POD for this area has 
 * not been calculated, it calculates and stores it. For a full discussion
 * of the reasons for this approach, see getCoverage.
 *
 */

double Allocation::getPOD(int areaNum)
{
#ifdef _ALLOCATION_TESTMODE
   cout << "Getting the POD for this allocation (Allocation::getPOD)" << endl;
#endif
	
   if (forceRecalc || myPOD[areaNum] == 0)    // Probably not calculated yet.
	  {
		 myPOD[areaNum]=calcPOD(areaNum);
	  }

#ifdef _ALLOCATION_TESTMODE
   cout << "getPOD: Returning the POD[" << areaNum << "] ";
	cout << "= " << myPOD[areaNum] << endl;
#endif
  
   return myPOD[areaNum];
}

/**** getPOS() **************************************************************/
/// Returns the POS for a specified area
/**
 * Returns the POS for the specified area. If the POS for this area
 * has not been calculated, it calculates and stores it. For a full discussion
 * of the reasons for this approach, see getCoverage.
 *
 */

double Allocation::getPOS(int areaNum)
{
#ifdef _ALLOCATION_TESTMODE
   cout << "Getting the POS for this allocation (Allocation::getPOS)" << endl;
#endif

	if (forceRecalc || myPOS[areaNum] == 0)    // Probably not calculated yet
	{
	  myPOS[areaNum]=calcPOS(areaNum);
	}


#ifdef _ALLOCATION_TESTMODE
	cout << "getPOS: Returning the POS[" << areaNum << "] ";
   cout << "= " << myPOS[areaNum] << endl;
#endif

	return myPOS[areaNum];
}

/**** getNewPOC() *********************************************************/
/// Returns the new POC for a specified area, calculating it only if needed.
/**
 * Returns the newPOC for the specified area. If the newPOC has not been 
 * calculated, it calculates and stores it. This is similar to the approach
 * detailed in getCoverage, but with a twist.
 * 
 * The proper way to initialize myNewPOC is with the previous POC values.
 * So to check whether it has been calculated already, we compare it 
 * with the original POC values. 
 * 
 * We now have the desired behavior. See getCoverage for a full discussion.
 * 
 */

double Allocation::getNewPOC(int areaNum)
{
#ifdef _ALLOCATION_TESTMODE
   cout << "Getting the NewPOC for this area (Allocation::getNewPOC)" << endl;
#endif

	if (forceRecalc || myNewPOC[areaNum] == myPOC[areaNum]) // Probably not calculated yet
	{ 
	  myNewPOC[areaNum] = calcNewPOC(areaNum);
	}


#ifdef _ALLOCATION_TESTMODE
	cout << "getNewPOC: Returning NewPOC[" << areaNum << "] ";
   cout << "= " << myNewPOC[areaNum] << "." << endl;
#endif

	return myNewPOC[areaNum];
}



// Only here to help debug whether the number we passed in was received.
double Allocation::getPOC_debug_only(int areaNum) {
    return myPOC[areaNum];
}


/**** getTotalPOS() **********************************************************/
/// Returns the totalPOS over all areas, calculating it if needed
/**
 * Returns the totalPOS over all areas. If the totalPOS has not been 
 * calculated, it calculates and stores it. This is so that when each 
 * request is made to get a totalPOS value, it is not calculated 
 * multiple times. The savings can be substantial.
 *
 * To speed up calculation, we only consider active areas. If forceRecalc
 * is true, we also recalculate newPOC in the active areas, and then
 * reset forceRecalc. 
 *
 * (New 27mar03, crt)
 */

double Allocation::getTotalPOS(void)
{
#ifdef _ALLOCATION_TESTMODE
   cout << "Getting total POS for this allocation (Allocation::getTotalPOS)" << endl;
#endif

	if (forceRecalc || myTotalPOS == 0)
	{
#ifdef _ALLOCATION_TESTMODE
	  cout << "getTotalPOS: Total POS not calculated. Doing so now." << endl;
#endif

		int area_num;
		ActiveArea *curr_area = firstArea();      // Get first active area
		while (curr_area != NULL)
	   {
		  area_num    = curr_area->getActiveAreaNum();
		  myTotalPOS += getPOS(area_num);

		  if (forceRecalc)          // Special case: we recalculate NewPOC
		  {                         // here so that we may reset forceRecalc.
			 getNewPOC(area_num);
		  }

		  delete curr_area;                       // New object. Must delete!
		  curr_area   = nextArea(area_num);
		}
	}

	// We've now recalculated everything of interest. Reset forceRecalc.
	forceRecalc = false;

#ifdef _ALLOCATION_TESTMODE
	cout << "getTotalPOS: Returning the Total POS = " << myTotalPOS << endl;
#endif

	return myTotalPOS;
}



/**** calcCoverage() ********************************************************/
/// Calculates the coverage for a given area number.
/**
 * Calculates the coverage for a given area number, for this allocation.
 * For each resource, coverage = effectiveness * time. Total coverage is 
 * just the sum.
 *
 * 11mar03 crt: Redone using accessor functions rather than iterators;
 *              Less indirection. Thanks to ASO for the suggestion.
 */

double Allocation::calcCoverage(const int areaNum)
{
	#ifdef _ALLOCATION_TESTMODE
     cout << "Calculating the coverage (Allocation::calcCoverage)" << endl;
	#endif

	 double time, coverage = 0.0;
	 int res_num;

	ResourceAssignment *res_assign = firstRes(areaNum); // Get first resource
	while (res_assign != NULL)
	{
	  res_num   = res_assign->getResourceNum();
	  time      = res_assign->getTime();
	  coverage += myEffectiveness[areaNum][res_num] * time;
	  delete res_assign; // firstRes() returns a new object. Delete else leak.
	  res_assign = nextRes(areaNum, res_num);
	}


	#ifdef _ALLOCATION_TESTMODE
		cout << "New coverage = " << coverage << endl;
		cout << "Returning the coverage (Allocation::calcCoverage)" << endl;
	#endif

	return coverage;
}
