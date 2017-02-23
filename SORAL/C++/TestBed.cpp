/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file TestBed.cpp
 *  \brief This is a testbed to check SORAL on several known cases.
 *
 * We have defined several test cases to check some boundary
 * conditions and proper numerical results. This file runs SORAL
 * over those cases (9 at the time of writing this header).
 *
 * Right now the tests are hardcoded into main(). Eventually it should
 * probably read them from a file, but that's a low priority change.
 * The main goal is to have quick automated testing so we can see if
 * our modifications have broken anything numerically.
 * 
 * Variables:
 *    p = Initial Probability Map
 *    w = Effectiveness vector
 *    T = Endurance vector
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 18jan03  |  1  | Created
 *-----+----------+-----+-----------------------------------------------------
 * crt |  7apr03  |  2  | Put in full test suite.
 *-----+----------+-----+-----------------------------------------------------
 * crt |  1may03  |  3  | Changed for itors returning objects not pointers
 *-----+----------+-----+-----------------------------------------------------
 * \endverbatim
 */

//===========================================================================//
// Written by Andre Oboler and Charles Twardy            http://sarbayes.org //
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

#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
#include "containr.h"
#include "Allocatn.h"
#include "Array2D.h"
#include "Alloc-W.h"
#include "Alloc-CC.h"
#include "UserDef.h"

using namespace std;

/// Standard allocation types for easy reference.
enum allocationType {CHARNES, WASHBURN};

/// Standard strings for the allocation names, to use with enum.
static const char *allocationNames[] = {"Charnes Cooper", "Washburn"};

// Function definitions
void printAssignments(const Allocation& theAllocation);
bool testCase(const allocationType whichAllocation,
				  const int caseNum,
				  const int num_areas, 
				  const int num_resources, 
				  const valarray<double> poc, 
				  const valarray<double> endurance,
				  const Array2D& eff,
				  const Array2D& answer);
bool matches(const Allocation& theAlloc, 
				 const Array2D& answer,
				 const int numAreas,
				 const int numResources);


int main(int argc, char **argv)
{
  int num_areas, num_resources, caseNum;
  bool error = false;

  valarray<double> * p; /// POC
  valarray<double> * T; /// Endurance (time, hence T)
  Array2D * w;          /// Effectiveness (a function of sweep width, hence w)
  Array2D * a;          /// Answer
  
  //----- Case 0: 1 area,  1 resource -----
  caseNum = 0; num_areas = 1;   num_resources   = 1;
  cout << "--------[ Case " << caseNum << " ]---------" << endl;
  
  p = new valarray<double>(num_areas);
  T = new valarray<double>(num_resources);
  w = new Array2D(num_areas, num_resources);
  a = new Array2D(num_areas, num_resources);

  (*p)[0]    =  4;
  (*T)[0]    =  0.05;
  (*w)[0][0] =  4;
  (*a)[0][0] =  0.05;

  error = testCase(CHARNES, caseNum, num_areas, num_resources, *p, *T, *w, *a);
  error = testCase(WASHBURN, caseNum, num_areas, num_resources, *p, *T, *w, *a);

  delete p; delete T; delete w; delete a;

  //----- Case 1: 4 areas, 1 resource -----
  caseNum = 1; num_areas = 4;   num_resources = 1;
  cout << "--------[ Case " << caseNum << " ]---------" << endl;

  p = new valarray<double>(num_areas);
  T = new valarray<double>(num_resources);
  w = new Array2D(num_areas, num_resources);
  a = new Array2D(num_areas, num_resources);

  (*p)[0]    =  8; 
  (*p)[1]    =  4; 
  (*p)[2]    =  1; 
  (*p)[3]    =  2;
  (*T)[0]    =  0.05;
  (*w)[0][0] =  1; 
  (*w)[1][0] =  4; 
  (*w)[2][0] = 12; 
  (*w)[3][0] =  8;
  (*a)[0][0] =  0; 
  (*a)[1][0] =  0.033333; 
  (*a)[2][0] =  0; 
  (*a)[3][0] =  0.0166667;

  error = testCase(CHARNES, caseNum, num_areas, num_resources, *p, *T, *w, *a);
  error = testCase(WASHBURN, caseNum, num_areas, num_resources, *p, *T, *w, *a);

  delete p; delete T; delete w; delete a;

  //----- Case 2: 4 areas, 1 resource -----
  caseNum = 2; num_areas = 4;   num_resources = 1;
  cout << "--------[ Case " << caseNum << " ]---------" << endl;
  
  p = new valarray<double>(num_areas);
  T = new valarray<double>(num_resources);
  w = new Array2D(num_areas, num_resources);
  a = new Array2D(num_areas, num_resources);

  (*p)[0]    =  4; 
  (*p)[1]    =  2; 
  (*p)[2]    =  8; 
  (*p)[3]    =  1;
  (*T)[0]    =  0.10;
  (*w)[0][0] =  4; 
  (*w)[1][0] =  1; 
  (*w)[2][0] =  1; 
  (*w)[3][0] = 12;
  (*a)[0][0] =  0.092980; 
  (*a)[1][0] =  0; 
  (*a)[2][0] =  0; 
  (*a)[3][0] =  0.007020;

  error = testCase(CHARNES, caseNum, num_areas, num_resources, *p, *T, *w, *a);
  error = testCase(WASHBURN, caseNum, num_areas, num_resources, *p, *T, *w, *a);

  delete p; delete T; delete w; delete a;


  //----- Case 3: 3 areas, 1 resource -----
  caseNum = 3; num_areas = 3;   num_resources = 1;
  cout << "--------[ Case " << caseNum << " ]---------" << endl;
  
  p = new valarray<double>(num_areas);
  T = new valarray<double>(num_resources);
  w = new Array2D(num_areas, num_resources);
  a = new Array2D(num_areas, num_resources);

  (*p)[0]    =  2; 
  (*p)[1]    =  4; 
  (*p)[2]    =  2; 

  (*T)[0]    =  0.20;

  (*w)[0][0] =  9; 
  (*w)[1][0] =  3; 
  (*w)[2][0] =  6; 

  (*a)[0][0] =  0.07322410073711; 
  (*a)[1][0] =  0.08451726617526; 
  (*a)[2][0] =  0.04225863308763; 


  error = testCase(CHARNES, caseNum, num_areas, num_resources, *p, *T, *w, *a);
  error = testCase(WASHBURN, caseNum, num_areas, num_resources, *p, *T, *w, *a);

  delete p; delete T; delete w; delete a;

  //----- Case 4: 4 areas, 1 resource -----
  // 2 unviable search areas
  caseNum = 4; num_areas = 4;   num_resources   = 1;
  cout << "--------[ Case " << caseNum << " ]---------" << endl;
  
  p = new valarray<double>(num_areas);
  T = new valarray<double>(num_resources);
  w = new Array2D(num_areas, num_resources);
  a = new Array2D(num_areas, num_resources);

  (*p)[0]    =  1; 
  (*p)[1]    =  4; 
  (*p)[2]    = 20; 
  (*p)[3]    =  0;
  (*T)[0]    =  0.50;
  (*w)[0][0] =  8; 
  (*w)[1][0] =  4; 
  (*w)[2][0] =  0; 
  (*w)[3][0] = 10;
  (*a)[0][0] =  0.10890; 
  (*a)[1][0] =  0.39110; 
  (*a)[2][0] =  0; 
  (*a)[3][0] =  0;

  error = testCase(CHARNES, caseNum, num_areas, num_resources, *p, *T, *w, *a);
  error = testCase(WASHBURN, caseNum, num_areas, num_resources, *p, *T, *w, *a);

  delete p; delete T; delete w; delete a;


  //----- Case 5: 3 areas, 1 resource -----
  caseNum = 5; num_areas = 3;   num_resources   = 1;
  cout << "--------[ Case " << caseNum << " ]---------" << endl;
  
  p = new valarray<double>(num_areas);
  T = new valarray<double>(num_resources);
  w = new Array2D(num_areas, num_resources);
  a = new Array2D(num_areas, num_resources);

  (*p)[0]    =  2; 
  (*p)[1]    =  6; 
  (*p)[2]    =  4; 

  (*T)[0]    =  0.50;
  (*w)[0][0] =  6; 
  (*w)[1][0] =  2; 
  (*w)[2][0] =  3; 

  (*a)[0][0] =  0.083333; 
  (*a)[1][0] =  0.25; 
  (*a)[2][0] =  0.166667; 

  error = testCase(CHARNES, caseNum, num_areas, num_resources, *p, *T, *w, *a);
  error = testCase(WASHBURN, caseNum, num_areas, num_resources, *p, *T, *w, *a);

  delete p; delete T; delete w; delete a;

  //----- Case 6:  -----
  // No viable searches
  caseNum = 6; num_areas = 4;   num_resources   = 1;
  cout << "--------[ Case " << caseNum << " ]---------" << endl;
  
  p = new valarray<double>(num_areas);
  T = new valarray<double>(num_resources);
  w = new Array2D(num_areas, num_resources);
  a = new Array2D(num_areas, num_resources);

  (*p)[0]    =  0; 
  (*p)[1]    =  7; 
  (*p)[2]    =  0; 
  (*p)[3]    =  5;
  (*T)[0]    =  0.50;
  (*w)[0][0] =  8; 
  (*w)[1][0] =  0; 
  (*w)[2][0] =  0; 
  (*w)[3][0] =  0;
  (*a)[0][0] =  0;
  (*a)[1][0] =  0;
  (*a)[2][0] =  0; 
  (*a)[3][0] =  0;

  error = testCase(CHARNES, caseNum, num_areas, num_resources, *p, *T, *w, *a);
  error = testCase(WASHBURN, caseNum, num_areas, num_resources, *p, *T, *w, *a);

  delete p; delete T; delete w; delete a;

  //----- Case 7: 2 resources, 2 areas -----
  // Requires Washburn for full answer
  // A case we could solve by hand
  caseNum = 7; num_areas = 2;   num_resources = 2;
  cout << "--------[ Case " << caseNum << " ]---------" << endl;
  
  p = new valarray<double>(num_areas);
  T = new valarray<double>(num_resources);
  w = new Array2D(num_areas, num_resources);
  a = new Array2D(num_areas, num_resources);

  (*p)[0]    =  0.5; 
  (*p)[1]    =  0.5; 

  (*T)[0]    =  16.1;
  (*T)[1]    =  13.9;

  (*w)[0][0] =  0.1; 
  (*w)[0][1] =  0.05; 
  (*w)[1][0] =  0.02; 
  (*w)[1][1] =  0.005; 

  (*a)[0][0] =  10.30365;
  (*a)[0][1] =  13.9;
  (*a)[1][0] =  5.79635;
  (*a)[1][1] =  0; 

  error = testCase(WASHBURN, caseNum, num_areas, num_resources, *p, *T, *w, *a);

  delete p; delete T; delete w; delete a;

  //----- Case 8: 4 areas, 3 resources -----
  // Requires Washburn for full answer
  // From Washburn's JOTA paper
  caseNum = 8; num_areas = 4;   num_resources = 3;
  cout << "--------[ Case " << caseNum << " ]---------" << endl;
  
  p = new valarray<double>(num_areas);
  T = new valarray<double>(num_resources);
  w = new Array2D(num_areas, num_resources);
  a = new Array2D(num_areas, num_resources);

  (*p)[0]    =  1000; 
  (*p)[1]    =  1000; 
  (*p)[2]    =  2000; 
  (*p)[3]    =  2000; 

  (*T)[0]    =  3;
  (*T)[1]    =  2;
  (*T)[2]    =  1;

  (*w)[0][0] =  1; 
  (*w)[0][1] =  3; 
  (*w)[0][2] =  0; 
  (*w)[1][0] =  2; 
  (*w)[1][1] =  2; 
  (*w)[1][2] =  1; 
  (*w)[2][0] =  3; 
  (*w)[2][1] =  2; 
  (*w)[2][2] =  0; 
  (*w)[3][0] =  4; 
  (*w)[3][1] =  1; 
  (*w)[3][2] =  1; 

  (*a)[0][0] =  0;
  (*a)[0][1] =  1.22976;
  (*a)[0][2] =  0;
  (*a)[1][0] =  0.37167;
  (*a)[1][1] =  0.77024; 
  (*a)[1][2] =  1; 
  (*a)[2][0] =  1.46081;
  (*a)[2][1] =  0; 
  (*a)[2][2] =  0; 
  (*a)[3][0] =  1.16753;
  (*a)[3][1] =  0; 
  (*a)[3][2] =  0; 

  // Uncomment next line to see an error: Charnes-Cooper can't handle 2 resources properly
  //error = testCase(CHARNES, caseNum, num_areas, num_resources, *p, *T, *w, *a);
  error = testCase(WASHBURN, caseNum, num_areas, num_resources, *p, *T, *w, *a);

  delete p; delete T; delete w; delete a;

  //----- Case 9: 1 area, 1 resource ------
  // Things exactly balance for Washburn: 
  //   Lambda(1) = W(1,1) * Mu(1), so T = 5*exp(-5)*sqrt(TOL)/2.
  // So no resource is allocated even though Mu(1) > TOL.
  // Seems to work for Charnes-Cooper too!
  caseNum = 9; num_areas = 1; num_resources = 1;
  cout << "--------[ Case " << caseNum << " ]---------" << endl;
  
  p = new valarray<double>(num_areas);
  T = new valarray<double>(num_resources);
  w = new Array2D(num_areas, num_resources);
  a = new Array2D(num_areas, num_resources);

  double TOL = sqrt(numeric_limits<double>::epsilon()); // Machine tolerance.
  (*p)[0]    =  2*TOL; 

  (*T)[0]    =  5*exp(-5.0)*sqrt(TOL)/2;

  (*w)[0][0] =  1/TOL; 

  (*a)[0][0] =  0;

  error = testCase(CHARNES, caseNum, num_areas, num_resources, *p, *T, *w, *a);
  error = testCase(WASHBURN, caseNum, num_areas, num_resources, *p, *T, *w, *a);

  delete p; delete T; delete w; delete a;


  //------[ Done with Cases ]------


  /// Return standard values in accord with.
  /// http://www.itworld.com/nl/lnx_tip/08092002/
  if (error) 
	 { 
		return 1; 
	 };

  return 0; // Success!
}

/******************************************************************/
/// Takes a case, creates an allocation, and compares the answer
/**
 * Takes a case, defined by its essential variables, creates an 
 * allocation of the requested type, and then checks that the
 * results of that allocation match the answer supplied by the
 * case.
 * 
 * Relies on the enum <em>allocationType</em> for choosing
 * which allocation to run.
 *
 * Calls <em>matches</em> to check for approximate match, to
 * a tolerance defined in <em>matches</em>.
 *
 * crt 7apr03
 */
bool testCase(const allocationType whichAllocation,
				  const int caseNum,
				  const int num_areas, 
				  const int num_resources, 
				  const valarray<double> poc, 
				  const valarray<double> endurance,
				  const Array2D& effectiveness,
				  const Array2D& answer)
  {
	bool error = false;
	const char * name = allocationNames[whichAllocation];
	Allocation * theAllocation;

	switch (whichAllocation)
	  {
	  case CHARNES:
		 theAllocation = new CharnesCooper(num_resources, num_areas, effectiveness, endurance, poc);
		 break;
	  case WASHBURN:
		 theAllocation = new Washburn(num_resources, num_areas, effectiveness, endurance, poc);
		 break;
	  default:
		 cerr << "ERROR: BAD ALLOCATION TYPE passed to testCase." << endl;
	  }

	if (!matches( (*theAllocation), answer, num_areas, num_resources))
	  {
		 cout << "*** Error in " << name << " for Case " << caseNum << ".  ";
		 error = true;
	  }
	else
	  { 
		 cout << name << " passed case " << caseNum << ".  ";
	  }

   //------[ Test conversion to UserDef ]-----------

	// Convert to a UserDef allocation named newAllocation.
	UserDef newAllocation(*theAllocation);

	// Remove 5 time units from resource 0 in area 0.
	newAllocation.remove(0,0,5);

	// Add those units back
	newAllocation.add(0,0,5);

	// Test that we still have the proper answer. (Same as above.)
	if (!matches(newAllocation, answer, num_areas, num_resources))
	  {
		 cout << "*** Error in UserDef conversion for Case " << caseNum << endl;
		 error = true;
	  }
	else
	  { 
		 cout << "UserDef conversion passed case " << caseNum << endl;
	  }

	
	delete theAllocation;
	return error;
}

/**** matches() ************************************************************/
/// Determines if an allocation approximately matches an answer
/**
 * Takes a calculated allocation and compares it to a known correct
 * answer to see if they match within some tolerance. 
 * Because Allocation does not provide getNumAreas and 
 * getNumResources, it must also be passed those values. 
 *
 * We could avoid those values by using the ActiveAreasIterator,
 * but that could miss some areas. We need to check that all
 * inactive areas should have been so. That means we can't 
 * use ActiveAreasIterator, which, of course, skips inactive areas.
 * 
 * Defines its own numerical tolerance <em>tol</em> at some
 * intuitively appealing level, rather than using a more
 * rigorous level of comparison. 
 * \todo Use a more rigorous <em>tol</em>.
 *
 * crt 7apr03
 */

bool matches(const Allocation& theAllocation, 
				 const Array2D& answer,
				 const int numAreas,
				 const int numResources)
{
    double tol = 0.0001;

	for (int areaIndex = 0; areaIndex < numAreas; areaIndex++)
	  {
		ResourceIterator activeRes(theAllocation, areaIndex);

		if (activeRes.atEnd()) 
		  // Area has no assignments. Make sure that's correct.
		  // Guards against errors by omission (forgot an assignment).
		  // Must test this first, before the while!
		  {
			 for (int resIndex = 0; resIndex < numResources; resIndex++)
				{
				  if (answer[areaIndex][resIndex] != 0)
					 {
						cerr << "*** Error: Area " << areaIndex 
							 << " incorrectly assigned zero resources." 
							 << endl;
						return 0;
					 }
				}
		  }
	   // Check the normal case: assigned values are the right amount
		while (!(activeRes.atEnd()))
		  {
			ResourceAssignment resAssign (*activeRes); 
			int resIndex = resAssign.getResourceNum();
			double time  = resAssign.getTime();
	
			double trueTime = answer[areaIndex][resIndex];
			if ( (time < trueTime - tol) || (time > trueTime + tol) )
			  {
				 cerr << "*** Error: Area " << areaIndex 
						<< " Resource " << resIndex
						<< " assigned the wrong time." << endl;
				 cerr << "     Time was        : " << time << endl;
				 cerr << "     Should have been: " << trueTime << endl;
				return 0;
			  }
		  
			++activeRes; //increment resource in this area
		  }
		
	  }
	
	return 1; // We made it to here, all assigments matched.
}


/**** printAssignments() *************************************************/
/// Prints the assignments in an Allocation.
/**
 * Prints all and only the assignments in an Allocation, by using
 * the standard iterator paradigm: start with ActiveAreasIterator
 * and proceed from there.
 *
 * Since this program now compares answers numerically, and only
 * prints the offending allocations, maybe we can remove this
 * function, which now lives usefully in sample.cpp?
 * \todo Remove printAssignments from here?
 *
 * Author: Andre Oboler
 */

void printAssignments(const Allocation& theAllocation)
{

	ActiveAreasIterator activeItr(theAllocation);

	//While there are still areas with assignments
	while(!(activeItr.atEnd()))
	{
	    ActiveArea area(*activeItr); 
	    int        areaIndex(area.getActiveAreaNum());

		ResourceIterator resItr(theAllocation, areaIndex);
		
		while (!(resItr.atEnd()))
		{
		  ResourceAssignment resAssign(*resItr);
		  int resIndex (resAssign.getResourceNum());
		  double time  (resAssign.getTime());

		  cout << "  Area: " << areaIndex 
			   << "  Resource: " << resIndex 
			   << "  Time: " << time << endl;		  

		  ++resItr;
		}

		++activeItr;
	}

}

