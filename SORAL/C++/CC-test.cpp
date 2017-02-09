/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file CC-test.cpp
 *  \brief CC-test.cpp contains test cases - currently disabled
 *
 * Test cases for the calcAllocationCharnesCooper() function
 * in the Allocation class, to ensure that it correctly
 * performs allocations according to the Charnes-Cooper
 * algorithm.
 *
 * <b><u>Version History</u></b>
 *
 * \verbatim
 *-----+----------+-----+----------------------------------------------------- 
 * Who |   When   | Ver | What                                                 
 *-----+----------+-----+----------------------------------------------------- 
 * GT  | 12/01/01 |  1  | Created.                                             
 *---------------------------------------------------------------------------- 
 * GT  | 02/02/02 |  2  | Test cases now in loop.  Updated to take into account
 *     |          |     | changes to iterators in Allocation class.            
 *---------------------------------------------------------------------------- 
 * \endverbatim
 */


//============================================================================//
// Written by Gareth Thompson.                           http://sarbayes.org  //
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


#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include "Allocatn.h"
#include "testing.h"



/*****************************************************************************
 * AllocationTest
 *
 * Structure which contains all necessary data to perform a
 * single test on the calcAllocationCharnesCooper function from
 * the Allocation class.
 *
 * All array members are large enough to hold data for UP TO
 * 50 areas.  If there are fewer areas, the additional locations
 * in the arrays are simply not used.
 *
 * Author: Gareth Thompson
 */

//ASO Test Disabled 18/12/02 struct AllocationTest
//ASO Test Disabled 18/12/02 {
//ASO Test Disabled 18/12/02   int numResources;
//ASO Test Disabled 18/12/02   int numAreas;
//ASO Test Disabled 18/12/02   double effectiveness[1][50];
//ASO Test Disabled 18/12/02   double POC[50];
//ASO Test Disabled 18/12/02   double searchEndurance;
//ASO Test Disabled 18/12/02   double expectedAssignments[50];
//ASO Test Disabled 18/12/02 };

/*****************************************************************************
 * main()
 *
 * Performs a series of tests on the
 * calcAllocationCharnesCooper() function in the Allocation
 * class, to ensure that it correctly performs allocations
 * according to the Charnes-Cooper algorithm.
 *
 * This function displays the following after each test:
 * 1. Expected results
 * 2. Actual results
 * 3. Whether the test was PASSED or FAILED
 *
 * Author: Gareth Thompson
 */

int main()
{

//ASO Test Disabled 18/12/02  printf("TESTING calcAllocationCharnesCooper()\n");
//ASO Test Disabled 18/12/02 printf("[Charnes-Cooper allocation function]\n");
//ASO Test Disabled 18/12/02  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

//ASO Test Disabled 18/12/02  int i;

  /**** CREATE DATA STRUCTURE CONTAINING TEST DATA ****/
//ASO Test Disabled 18/12/02  const int numTests = 6;
//ASO Test Disabled 18/12/02  AllocationTest* testData[numTests+1];

  /*
   * An AllocationTest object is declared using the folliwing syntax:
   * AllocationTest testX = {numResources, numAreas, {{comma separated list of effectiveness values}},
   *                         {comma separated list of POC values}, searchEndurance,
   *                         {comma separated list of expected assignment times}};
   *
   * NOTE: At present, the maximum number of areas is 50.
   *       This may be increased by altering the definition of the AllocationTest struct (see above)
   */
//ASO Test Disabled 18/12/02  AllocationTest test1 = {1, 4, {{1.0, 4.0, 12.0, 8.0}}, {8.0, 4.0, 1.0, 2.0}, 0.05, {0.0, 0.03333333, 0.0, 0.01666667}};
//ASO Test Disabled 18/12/02  AllocationTest test2 = {1, 4, {{4.0, 1.0, 1.0, 12.0}}, {4.0, 2.0, 8.0, 1.0}, 0.10, {0.09298, 0.0, 0.0, 0.00702}};
//ASO Test Disabled 18/12/02  AllocationTest test3 = {1, 3, {{9.0, 3.0, 6.0}}, {2.0, 4.0, 2.0}, 0.20, {0.073224, 0.0845173, 0.0422587}};
//ASO Test Disabled 18/12/02  AllocationTest test4 = {1, 4, {{8.0, 4.0, 0.0, 10.0}}, {1.0, 4.0, 20.0, 0.0}, 0.50, {0.108904, 0.391096, 0.0, 0.0}};
//ASO Test Disabled 18/12/02  AllocationTest test5 = {1, 3, {{6.0, 2.0, 3.0}}, {2.0, 6.0, 4.0}, 0.50, {0.083333, 0.25, 0.166667}};
//ASO Test Disabled 18/12/02  AllocationTest test6 = {1, 4, {{8.0, 0.0, 0.0, 0.0}}, {0.0, 7.0, 0.0, 5.0}, 0.50, {0.0, 0.0, 0.0, 0.0}};

//ASO Test Disabled 18/12/02  testData[1] = &test1;
//ASO Test Disabled 18/12/02  testData[2] = &test2;
//ASO Test Disabled 18/12/02  testData[3] = &test3;
//ASO Test Disabled 18/12/02  testData[4] = &test4;
//ASO Test Disabled 18/12/02  testData[5] = &test5;
//ASO Test Disabled 18/12/02  testData[6] = &test6;

  /**** RUN TEST CASES ****/

//ASO Test Disabled 18/12/02  for (int testNum = 1; testNum<=numTests; testNum++)
//ASO Test Disabled 18/12/02  {
//ASO Test Disabled 18/12/02	printf("TEST CASE %d\n", testNum);
//ASO Test Disabled 18/12/02	printf("~~~~~~~~~~~\n\n");

//ASO Test Disabled 18/12/02	CharnesCooper alloc(testData[testNum]->numResources, testData[testNum]->numAreas, &testData[testNum]->effectiveness[0][0], testData[testNum]->POC);

	/*
	 * Use Charnes-Cooper algorithm to calculate allocation.
	 * (Default resource allocation algorithm is Charnes Cooper if there is one resource)
	 */
	//[TODO - fix] alloc.calcAllocation(&(testData[testNum]->searchEndurance));

	/* Display expected assignments */
//ASO Test Disabled 18/12/02	printf("Expected allocation:\n");

//ASO Test Disabled 18/12/02	for (i=0; i<testData[testNum]->numAreas; i++)
//ASO Test Disabled 18/12/02	{
//ASO Test Disabled 18/12/02	  printf("\tAREA: %d\tTIME: %f\n", i, testData[testNum]->expectedAssignments[i]);
//ASO Test Disabled 18/12/02	}

//ASO Test Disabled 18/12/02	printf("\n\n");

	/* Display actual assignments */
//ASO Test Disabled 18/12/02	printf("Actual allocation [only nonzero assignments are shown]:\n");

//ASO Test Disabled 18/12/02	ResourceIterator actualAssignments(&alloc, 0);

	//[TODO - fix] actualAssignments.goToStart();

//ASO Test Disabled 18/12/02	while (!actualAssignments.atEnd())
//ASO Test Disabled 18/12/02	{
//[TODO - fix]          printf("\tAREA: %d", actualAssignments.Index());

//[TODO - fix]         ResourceAssignment* con = actualAssignments(); // ASO 10/12/02 Changed to ResourceAssignment from Container
//[TODO - fix]         printf("\tTIME: %f\n", con->getTime());
//[TODO - fix]         delete con;

//ASO Test Disabled 18/12/02	  ++actualAssignments;
//ASO Test Disabled 18/12/02	}

//ASO Test Disabled 18/12/02	printf("\n\n");

//ASO Test Disabled 18/12/02	printf("--> Test %d: ", testNum);

//[TODO - fix]	actualAssignments.goToStart();

//ASO Test Disabled 18/12/02	bool passed = true;

//ASO Test Disabled 18/12/02	while (!actualAssignments.atEnd())
//ASO Test Disabled 18/12/02	{
//[TODO - fix]	  ResourceAssignment* con = actualAssignments(); // ASO 10/12/02 Changed to ResourceAssignment from Container
//[TODO - fix]	  if (doubleEqual(testData[testNum]->expectedAssignments[actualAssignments.Index()], con->getTime()))
//ASO Test Disabled 18/12/02	  {
//[TODO - fix]            testData[testNum]->expectedAssignments[actualAssignments.Index()] = 0.0;
//ASO Test Disabled 18/12/02	  }
 //[TODO - fix]          else
//ASO Test Disabled 18/12/02          {
//ASO Test Disabled 18/12/02            passed = false;
//ASO Test Disabled 18/12/02          }
 //[TODO - fix]	  delete con;

//ASO Test Disabled 18/12/02	  ++actualAssignments;
//ASO Test Disabled 18/12/02	}

//ASO Test Disabled 18/12/02	for (i = 0; i < testData[testNum]->numAreas; i++)
//ASO Test Disabled 18/12/02	{
//ASO Test Disabled 18/12/02	  if (testData[testNum]->expectedAssignments[i] != 0.0)
//ASO Test Disabled 18/12/02	  {
//ASO Test Disabled 18/12/02		passed = false;
//ASO Test Disabled 18/12/02		break;
//ASO Test Disabled 18/12/02	  }
//ASO Test Disabled 18/12/02	}

//ASO Test Disabled 18/12/02	if (passed)
//ASO Test Disabled 18/12/02	{
//ASO Test Disabled 18/12/02	  printf("PASSED\n\n\n");
//ASO Test Disabled 18/12/02	}
//ASO Test Disabled 18/12/02	else
//ASO Test Disabled 18/12/02	{
//ASO Test Disabled 18/12/02	  printf("FAILED\n\n\n");
//ASO Test Disabled 18/12/02	}
//ASO Test Disabled 18/12/02  }

return 0;
}

