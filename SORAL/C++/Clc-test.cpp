/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file Clc-test.cpp
 *  \brief Clc-test.cpp contains test cases - currently disabled
 *
 * Test cases for the functions setAllocation(), getCoverage(),
 * getPOD(), getPOS(), getNewPOC() and getTotalPOS() in the
 * CharnesCooper class.
 *
 * <b><u>Version History</u></b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 16/02/02 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 25/02/02 |  2  | Bugs fixed.
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
#include "Allocatn.h"
#include "testing.h"



/*****************************************************************************
 * main()
 *
 * Performs a series of tests on the setAllocation(),
 * getCoverage(), getPOD, getPOS, getNewPOC and getTotalPOS()
 * functions in the CharnesCooper class.
 *
 * This function displays the following after each test:
 * 1. Expected results
 * 2. Actual results
 * 3. Whether the test was PASSED or FAILED
 *
 * Author: Gareth Thompson
 */
/*
int main()
{
  printf("TESTING setAllocation(), getCoverage(), getPOD(), getPOS(), getNewPOC() and getTotalPOS()\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

  const int numResources = 1;
  const int numAreas = 4;
  double effectiveness[numResources][numAreas] = { {1.0,  4.0,  12.0,  8.0} };
  double POC[numAreas] = {8.0, 4.0, 1.0, 2.0};
  double assignments[numResources][numAreas] =   { {0.0, 0.033333333, 0.0, 0.016666667} };

  double expectedCoverage[numAreas] = {0.0, 0.133333333, 0.0, 0.133333333};
  double expectedPOD[numAreas] = {0.0, 0.1248, 0.0, 0.1248};
  double expectedPOS[numAreas] = {0.0, 0.4992, 0.0, 0.2496};
  double expectedNewPOC[numAreas] = {8.0, 3.5008, 1.0, 1.7504};
  double expectedTotalPOS = 0.7488;

  CharnesCooper alloc1(numResources, numAreas, &effectiveness[0][0], POC);
  alloc1.setAllocation(&assignments[0][0]);

  bool passed;




if (true) 
*/
/* Do you want to test setAllocation() ? */
/*
{
  printf("TESTING setAllocation()\n");
  printf("-----------------------\n\n");
*/
  /* Display expected assignments */
/*
  printf("Expected allocation:\n\n");

  for (int i=0; i<numAreas; i++)
  {
    printf("\tAREA: %d\tTIME: %f\n", i, assignments[0][i]);
  }

  printf("\n\n");
*/
  /* Display actual assignments */
/*  printf("Actual allocation [only nonzero assignments are shown]:\n\n");

  ResourceIterator actualAssignments(&alloc1, 0);

  actualAssignments.goToStart();

  while (!actualAssignments.atEnd())
  {
    printf("\tAREA: %d\tTIME: %f\n", actualAssignments.Index(), actualAssignments()->getTime());
    ++actualAssignments;
  };

  printf("\n\n");

  printf("--> Test setAllocation(): ");

  actualAssignments.goToStart();
*/
  /* Is each assignment correct? */
/*  bool* assignmentsCorrect = new bool[numAreas];

  for (int i=0; i<numAreas; i++)
  {
    assignmentsCorrect[i] = false;
  }

  while (!actualAssignments.atEnd())
  {
    if (doubleEqual(assignments[0][actualAssignments.Index()], actualAssignments()->getTime()))
    {
      assignmentsCorrect[actualAssignments.Index()] = true;
    }

    ++actualAssignments;
  }

  passed = true;
  for (int i=0; i<numAreas; i++)
  {
    if (assignmentsCorrect == false && assignments[0][i] != 0.0)
    {
      passed = false;
      break;
    }
  }

  delete [] assignmentsCorrect;

  if (passed)
  {
    printf("PASSED\n\n\n");
  }
  else
  {
    printf("FAILED\n\n\n");
  }
}




if (true) 
*/   /* Do you want to test getCoverage() ? */
/*
{
  printf("TESTING getCoverage()\n");
  printf("---------------------\n\n");
*/
  /* Display expected coverage values */
/*  printf("Expected coverages:\n\n");

  for (int i=0; i<numAreas; i++)
  {
    printf("\tAREA: %d\tCOVERAGE: %f\n", i, expectedCoverage[i]);  
  }

  printf("\n\n");
*/
  /* Display actual coverage values */
/*  printf("Actual coverages:\n\n");

  for (int i=0; i<numAreas; i++)
  {
    printf("\tAREA: %d\tCOVERAGE: %f\n", i, alloc1.getCoverage(i));
  }

  printf("\n\n");

  printf("--> Test getCoverage(): ");

  passed = true;
  for (int i=0; i<numAreas; i++)
  {
    if (!doubleEqual(expectedCoverage[i], alloc1.getCoverage(i)))
    {
      passed = false;
      break;
    }
  }

  if (passed)
  {
    printf("PASSED\n\n\n");
  }
  else
  {
    printf("FAILED\n\n\n");
  }
}
  



if (true)    
*//* Do you want to test getPOD() ? */
/*{
*/
  /* 
   * Create a new allocation object.
   * This ensures that getPOD() can be used (implicitly calculating coverages)
   * without getCoverage() first being explictly called.
   */
/*  CharnesCooper alloc2(numResources, numAreas, &effectiveness[0][0], POC);
  alloc2.setAllocation(&assignments[0][0]);


  printf("TESTING getPOD()\n");
  printf("----------------\n\n");
*/
  /* Display expected POD values */
/*  printf("Expected PODs:\n\n");

  for (int i=0; i<numAreas; i++)
  {
    printf("\tAREA: %d\tPOD: %f\n", i, expectedPOD[i]);  
  }

  printf("\n\n");
*/
  /* Display actual POD values */
/*  printf("Actual PODs:\n\n");

  for (int i=0; i<numAreas; i++)
  {
    printf("\tAREA: %d\tPOD: %f\n", i, alloc2.getPOD(i));
  }

  printf("\n\n");

  printf("--> Test getPOD(): ");

  passed = true;
  for (int i=0; i<numAreas; i++)
  {
    if (!doubleEqual(expectedPOD[i], alloc2.getPOD(i)))
    {
      passed = false;
      break;
    }
  }

  if (passed)
  {
    printf("PASSED\n\n\n");
  }
  else
  {
    printf("FAILED\n\n\n");
  }
}




if (true)    
*//* Do you want to test getPOS() ? */
/*{
*/
  /* 
   * Create a new allocation object.
   * This ensures that getPOS() can be used (implicitly calculating coverages and PODs)
   * without getCoverage() or getPOD() first being explictly called.
   */
/*  CharnesCooper alloc3(numResources, numAreas, &effectiveness[0][0], POC);
  alloc3.setAllocation(&assignments[0][0]);

  printf("TESTING getPOS()\n");
  printf("----------------\n\n");
*/
  /* Display expected POS values */
/*  printf("Expected POSs:\n\n");

  for (int i=0; i<numAreas; i++)
  {
    printf("\tAREA: %d\tPOS: %f\n", i, expectedPOS[i]);  
  }

  printf("\n\n");
*/
  /* Display actual POS values */
/*  printf("Actual POSs:\n\n");

  for (int i=0; i<numAreas; i++)
  {
    printf("\tAREA: %d\tPOS: %f\n", i, alloc3.getPOS(i));
  }

  printf("\n\n");

  printf("--> Test getPOS(): ");

  passed = true;
  for (int i=0; i<numAreas; i++)
  {
    if (!doubleEqual(expectedPOS[i], alloc3.getPOS(i)))
    {
      passed = false;
      break;
    }
  }

  if (passed)
  {
    printf("PASSED\n\n\n");
  }
  else
  {
    printf("FAILED\n\n\n");
  }
}




if (true)    
*//* Do you want to test getNewPOC() ? */
/*{
*/
  /* 
   * Create a new allocation object.
   * This ensures that getNewPOC() can be used (implicitly calculating coverages and PODs)
   * without getCoverage() or getPOD() first being explictly called.
   */
/*  CharnesCooper alloc4(numResources, numAreas, &effectiveness[0][0], POC);
  alloc4.setAllocation(&assignments[0][0]);

  printf("TESTING getNewPOC()\n");
  printf("-------------------\n\n");
*/
  /* Display expected New POC values */
/*  printf("Expected New POCs:\n\n");

  for (int i=0; i<numAreas; i++)
  {
    printf("\tAREA: %d\tNew POC: %f\n", i, expectedNewPOC[i]);  
  }

  printf("\n\n");
*/
  /* Display actual New POC values */
/*  printf("Actual New POCs:\n\n");

  for (int i=0; i<numAreas; i++)
  {
    printf("\tAREA: %d\tNew POC: %f\n", i, alloc4.getNewPOC(i));
  }

  printf("\n\n");

  printf("--> Test getNewPOC(): ");

  passed = true;
  for (int i=0; i<numAreas; i++)
  {
    if (!doubleEqual(expectedNewPOC[i], alloc4.getNewPOC(i)))
    {
      passed = false;
      break;
    }
  }

  if (passed)
  {
    printf("PASSED\n\n\n");
  }
  else
  {
    printf("FAILED\n\n\n");
  }
}




if (true)    
*//* Do you want to test getTotalPOS() ? */
/*{
*/
  /* 
   * Create a new allocation object.
   * This ensures that getTotalPOS() can be used (implicitly calculating coverages, PODs and POSs)
   * without getCoverage(), getPOD() or getPOS() first being explictly called.
   */
/*  CharnesCooper alloc5(numResources, numAreas, &effectiveness[0][0], POC);
  alloc5.setAllocation(&assignments[0][0]);

  printf("TESTING getTotalPOS()\n");
  printf("---------------------\n\n");
*/
  /* Display expected Total POS */
/*  printf("Expected Total POS: %f\n\n", expectedTotalPOS);
*/

  /* Display actual Total POS */
/*  printf("Actual Total POS: %f\n\n", alloc5.getTotalPOS());

  printf("--> Test getTotalPOS(): ");

  if (doubleEqual(expectedTotalPOS, alloc5.getTotalPOS()))
  {
    printf("PASSED\n\n\n");
  }
  else
  {
    printf("FAILED\n\n\n");
  }
}



  return 0;
}
*/
