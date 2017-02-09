/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file Itr-test.cpp
 *  \brief Itr-test.cpp contains test cases - currently disabled
 * 
 *
 * Test cases for the functions getAssignmentsForResource(),
 * getAssignmentsForArea() and getAssignedAreas() - along
 * with the iterators returned by these functions - for the
 * CharnesCooper class.
 *
 * <b><u>Version History</u></b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 17/02/02 |  1  | Created.                                            
 *----------------------------------------------------------------------------
 * GT  | 25/02/02 |  2  | Bugs fixed and additional tests added.
 *----------------------------------------------------------------------------
 * ASO | 26/12/02 |  3  | Rewritten to reflect code restructure and to make 
 *     |          |     | more general.
 *----------------------------------------------------------------------------
 * \endverbatim
 */

/********************
 * WORK IN PROGRESS *
 ********************
 * [TODO] ASO 30/12/02 - Still working otu how best to implement testing 
 * without adding extra baggage. Some lines below have been uncommented...
 * this isn't going anywhere yet.
 */

#include <iostream> // ASO changed to iostream from iostream.h to meet the C++ standard
#include "Allocatn.h"
#include <cstdio> // ASO changed to cstdio from stdio.h to meet the C++ standard
#include "testing.h"



/*****************************************************************************
 * main()
 * 
 * This function displays the following after each test:
 * 1. Expected results
 * 2. Actual results
 *
 * (3. Whether the test was PASSED or FAILED)   (Not for all tests - please check through the output)
 *
 * Author: Gareth Thompson
 * Rewritten: Andre Oboler
 */

int main()
{
  printf("Testing ActiveAreaIterator, AreaIterator and ResourceIterator.\n");
  printf("These tests should be compatable for all children of the allocation class, to \n");
  printf("test a new allocation class, simply change the type of the `alloc' object ");
  printf("in the source code of file Itr-test.cpp the spot in commented `[CHANGE HERE]'.\n");
  
  printf("TESTING getAssignmentsForResource(), getAssignmentsForArea() and getAssignedAreas()\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

//ASO Test Disabled 18/12/02   const int numResources = 1;
//ASO Test Disabled 18/12/02   const int numAreas = 8;
//ASO Test Disabled 18/12/02   double effectiveness[numResources][numAreas] = { {1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0} };
//ASO Test Disabled 18/12/02   double POC[numAreas] = {1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0};
//ASO Test Disabled 18/12/02   double assignments[numResources][numAreas] =   { {1.0,  4.9,  0.0,  0.0,  11.1,  4.0,  7.0,  0.0} };

  /*******************************************************************************/
  //                               [CHANGE HERE] 
  // change the type of alloc to any child class of allocation to test that class

//ASO Test Disabled 18/12/02   CharnesCooper alloc(numResources, numAreas, &effectiveness[0][0], POC);

  /*******************************************************************************/
  
//ASO Test Disabled 18/12/02   alloc.setAllocation(&assignments[0][0]);

//ASO Test Disabled 18/12/02   bool passed;
//ASO Test Disabled 18/12/02 Container* conPtr;

  /* Calculate indices of first assignment in list and last assignment before end of list */
//ASO Test Disabled 18/12/02
/*
  int start = 0;
  while (assignments[0][start] == 0.0) { start ++; }

  int end = numAreas - 1;
  while (assignments[0][end] == 0.0) { end--; }


*/
//ASO Test Disabled 18/12/02 if (true)    /* Do you want to test getAssignmentsForResource()? */
//ASO Test Disabled 18/12/02 {
//ASO Test Disabled 18/12/02   printf("Testing getAssignmentsForResource()\n");
//ASO Test Disabled 18/12/02   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

//ASO Test Disabled 18/12/02   ResourceIterator* resItr = alloc.getAssignmentsForResource(0); // ASO 28/11/02 - did not match signature
  // was: Iterator* resItr = alloc.getAssignmentsForResource();



  /* Testing goToStart() and atStart() */
//ASO Test Disabled 18/12/02   printf("Testing goToStart() and atStart():\n\n");

//ASO Test Disabled 18/12/02   printf("\tMoving forward a couple of positions [prefix and postfix ++]...\n");
//ASO Test Disabled 18/12/02   (*resItr)++;
//ASO Test Disabled 18/12/02   ++(*resItr);

//ASO Test Disabled 18/12/02   printf("\tAt start? ");
//ASO Test Disabled 18/12/02   if (resItr->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tGoing to start...\n");
//ASO Test Disabled 18/12/02   resItr->goToStart();

//ASO Test Disabled 18/12/02   printf("\tAt start? ");
//ASO Test Disabled 18/12/02   if (resItr->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\n");

//ASO Test Disabled 18/12/02   printf("\tMoving backward a couple of positions [prefix and postfix --]...\n");
//ASO Test Disabled 18/12/02   (*resItr)--;
//ASO Test Disabled 18/12/02   --(*resItr);

//ASO Test Disabled 18/12/02   printf("\tAt start? ");
//ASO Test Disabled 18/12/02   if (resItr->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tExpected data at start:\n");

//ASO Test Disabled 18/12/02   printf("\t\tAREA: %2d\tTIME: %9.6f\n\n", start, assignments[0][start]);

//ASO Test Disabled 18/12/02   printf("\tActual data at start:\n");

//ASO Test Disabled 18/12/02   conPtr = (*resItr)();

//ASO Test Disabled 18/12/02   printf("\t\tAREA: %2d\tTIME: %9.6f\n\n", conPtr->getAreaNum(), conPtr->getTime());

//ASO Test Disabled 18/12/02   printf("\tCorrect data at start? ");

//ASO Test Disabled 18/12/02   if ( (start == conPtr->getAreaNum()) && (doubleEqual(assignments[0][start], conPtr->getTime())) )
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   delete conPtr;




  /* Testing goToEnd() and atEnd() */
//ASO Test Disabled 18/12/02   printf("Testing goToEnd() and atEnd():\n\n");

//ASO Test Disabled 18/12/02   printf("\tGoing to start...\n");
//ASO Test Disabled 18/12/02   resItr->goToStart();

//ASO Test Disabled 18/12/02   printf("\tAt end? ");
//ASO Test Disabled 18/12/02   if (resItr->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tGoing to end...\n");
//ASO Test Disabled 18/12/02   resItr->goToEnd();

//ASO Test Disabled 18/12/02   printf("\tAt end? ");
//ASO Test Disabled 18/12/02   if (resItr->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tMoving forward a couple of positions...\n");
//ASO Test Disabled 18/12/02   ++(*resItr);
//ASO Test Disabled 18/12/02   ++(*resItr);

//ASO Test Disabled 18/12/02   printf("\tAt end? ");
//ASO Test Disabled 18/12/02   if (resItr->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tDecrementing...\n\n");
//ASO Test Disabled 18/12/02   --(*resItr);

//ASO Test Disabled 18/12/02   printf("\tExpected data just before end:\n");

//ASO Test Disabled 18/12/02   printf("\t\tAREA: %2d\tTIME: %9.6f\n\n", end, assignments[0][end]);

//ASO Test Disabled 18/12/02   printf("\tActual data at just before end:\n");

//ASO Test Disabled 18/12/02   conPtr = (*resItr)();

//ASO Test Disabled 18/12/02   printf("\t\tAREA: %2d\tTIME: %9.6f\n\n", conPtr->getAreaNum(), conPtr->getTime());

//ASO Test Disabled 18/12/02   printf("\tCorrect data just before end? ");

//ASO Test Disabled 18/12/02   if ( (end == conPtr->getAreaNum()) && (doubleEqual(assignments[0][end], conPtr->getTime())) )
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   delete conPtr;



  /* Testing operator++, atStart() and atEnd() */
//ASO Test Disabled 18/12/02   printf("Testing operator++, atStart() and atEnd() by progressing through assignments list forwards...\n\n");

  /* Display expected assignments */
//ASO Test Disabled 18/12/02   printf("\tExpected assignments list:\n");

//ASO Test Disabled 18/12/02   for (int i=0; i<numAreas; i++)
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     if (assignments[0][i] != 0.0)
//ASO Test Disabled 18/12/02     {
//ASO Test Disabled 18/12/02       printf("\t\tAREA: %2d\tTIME: %9.6f\tAT START: %d\tAT END: %d\n", i, assignments[0][i], start == i, 0);
//ASO Test Disabled 18/12/02     }
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   printf("\t\tNow at end!\n\n");

  /* Display actual assignments */
//ASO Test Disabled 18/12/02   printf("\tActual assignments list:\n");

//ASO Test Disabled 18/12/02   resItr->goToStart();

//ASO Test Disabled 18/12/02   while (!resItr->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     conPtr = (*resItr)();
//ASO Test Disabled 18/12/02     printf("\t\tAREA: %2d\tTIME: %9.6f\tAT START: %d\tAT END: %d\n", conPtr->getAreaNum(), conPtr->getTime(), resItr->atStart(), resItr->atEnd());
//ASO Test Disabled 18/12/02    delete conPtr;

//ASO Test Disabled 18/12/02     ++(*resItr);
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   printf("\t\tNow at end!\n\n");

//ASO Test Disabled 18/12/02   printf("PLEASE CHECK IF THE ABOVE IS CORRECT!!!\n\n");




  /* Testing operator-- */
//ASO Test Disabled 18/12/02   printf("Testing operator-- by progressing through assignments list backwards...\n\n");

  /* Display expected assignments */
//ASO Test Disabled 18/12/02   printf("\tExpected assignments list:\n");

//ASO Test Disabled 18/12/02   for (int i=numAreas-1; i>=0; i--)
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     if (assignments[0][i] != 0.0)
//ASO Test Disabled 18/12/02     {
//ASO Test Disabled 18/12/02       printf("\t\tAREA: %2d\tTIME: %9.6f\n", i, assignments[0][i]);
//ASO Test Disabled 18/12/02     }
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\n");

  /* Display actual assignments */
//ASO Test Disabled 18/12/02   printf("\tActual assignments list:\n");

//ASO Test Disabled 18/12/02   resItr->goToEnd();

//ASO Test Disabled 18/12/02   while (!resItr->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     --(*resItr);

//ASO Test Disabled 18/12/02     conPtr = (*resItr)();
//ASO Test Disabled 18/12/02     printf("\t\tAREA: %2d\tTIME: %9.6f\n", conPtr->getAreaNum(), conPtr->getTime());
//ASO Test Disabled 18/12/02     delete conPtr;
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\n");

//ASO Test Disabled 18/12/02   printf("PLEASE CHECK IF THE ABOVE IS CORRECT!!!\n\n");

//ASO Test Disabled 18/12/02 }




//ASO Test Disabled 18/12/02 if (true)    /* Do you want to test getAssignmentsForArea()? */
//ASO Test Disabled 18/12/02 {
//ASO Test Disabled 18/12/02   printf("Testing getAssignmentsForArea()\n");
//ASO Test Disabled 18/12/02   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

//ASO Test Disabled 18/12/02   int areaNum = 0;

//ASO Test Disabled 18/12/02   AreaIterator* areaItr1 = alloc.getAssignmentsForArea(areaNum);



  /* Testing goToStart() and atStart() */
//ASO Test Disabled 18/12/02   printf("Testing goToStart() and atStart():\n\n");

//ASO Test Disabled 18/12/02   printf("\tMoving forward a couple of positions [prefix and postfix ++]...\n");
//ASO Test Disabled 18/12/02   (*areaItr1)++;
//ASO Test Disabled 18/12/02   ++(*areaItr1);

//ASO Test Disabled 18/12/02   printf("\tAt start? ");
//ASO Test Disabled 18/12/02   if (areaItr1->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tGoing to start...\n");
//ASO Test Disabled 18/12/02   areaItr1->goToStart();
//ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02   printf("\tAt start? ");
//ASO Test Disabled 18/12/02   if (areaItr1->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02   printf("\n");
//ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02   printf("\tMoving backward a couple of positions [prefix and postifx --]...\n");
//ASO Test Disabled 18/12/02   (*areaItr1)--;
//ASO Test Disabled 18/12/02   --(*areaItr1);

//ASO Test Disabled 18/12/02   printf("\tAt start? ");
//ASO Test Disabled 18/12/02   if (areaItr1->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tExpected data at start:\n");

//ASO Test Disabled 18/12/02   printf("\t\tRESOURCE: %2d\tTIME: %9.6f\n\n", 0, assignments[0][areaNum]);

//ASO Test Disabled 18/12/02   printf("\tActual data at start:\n");

//ASO Test Disabled 18/12/02   conPtr = (*areaItr1)();
//ASO Test Disabled 18/12/02   printf("\t\tRESOURCE: %2d\tTIME: %9.6f\n\n", conPtr->getResourceNum(), conPtr->getTime());

//ASO Test Disabled 18/12/02   printf("\tCorrect data at start? ");

//ASO Test Disabled 18/12/02   if ( (conPtr->getResourceNum() == 0) && (doubleEqual(assignments[0][areaNum], conPtr->getTime())) )
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   delete conPtr;





  /* Testing goToEnd() and atEnd() */
//ASO Test Disabled 18/12/02   printf("Testing goToEnd() and atEnd():\n\n");

//ASO Test Disabled 18/12/02   printf("\tGoing to start...\n");
//ASO Test Disabled 18/12/02   areaItr1->goToStart();

//ASO Test Disabled 18/12/02   printf("\tAt end? ");
//ASO Test Disabled 18/12/02   if (areaItr1->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02 //ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02 printf("No.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tGoing to end...\n");
//ASO Test Disabled 18/12/02   areaItr1->goToEnd();

//ASO Test Disabled 18/12/02   printf("\tAt end? ");
//ASO Test Disabled 18/12/02   if (areaItr1->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tMoving forward a couple of positions...\n");
//ASO Test Disabled 18/12/02   ++(*areaItr1);
//ASO Test Disabled 18/12/02   ++(*areaItr1);

//ASO Test Disabled 18/12/02   printf("\tAt end? ");
//ASO Test Disabled 18/12/02   if (areaItr1->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tDecrementing...\n\n");
//ASO Test Disabled 18/12/02   --(*areaItr1);
//ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02   printf("\tExpected data just before end:\n");
//ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02   printf("\t\tRESOURCE: %2d\tTIME: %9.6f\n\n", 0, assignments[0][areaNum]);
//ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02   printf("\tActual data at just before end:\n");
//ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02   conPtr = (*areaItr1)();
//ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02   printf("\t\tRESOURCE: %2d\tTIME: %9.6f\n\n", conPtr->getResourceNum(), conPtr->getTime());

//ASO Test Disabled 18/12/02   printf("\tCorrect data just before end? ");

//ASO Test Disabled 18/12/02   if ( (conPtr->getResourceNum() == 0) && (doubleEqual(assignments[0][areaNum], conPtr->getTime())) )
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   delete conPtr;



  /* Testing operator++, atStart() and atEnd() */
//ASO Test Disabled 18/12/02   printf("Testing operator++, atStart() and atEnd() by progressing through assignments list forwards...\n\n");

  /* Display expected assignments */
//ASO Test Disabled 18/12/02   printf("\tExpected assignments list:\n");

//ASO Test Disabled 18/12/02   printf("\t\tRESOURCE:  0\tTIME: %9.6f\tAT START: 1\tAT END: 0\n", assignments[0][areaNum]);
//ASO Test Disabled 18/12/02   printf("\t\tNow at end!\n\n");

  /* Display actual assignments */
//ASO Test Disabled 18/12/02   printf("\tActual assignments list:\n");

//ASO Test Disabled 18/12/02   areaItr1->goToStart();

//ASO Test Disabled 18/12/02   while (!areaItr1->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     conPtr = (*areaItr1)();
//ASO Test Disabled 18/12/02     printf("\t\tRESOURCE: %2d\tTIME: %9.6f\tAT START: %d\tAT END: %d\n", conPtr->getResourceNum(), conPtr->getTime(), areaItr1->atStart(), areaItr1->atEnd());
//ASO Test Disabled 18/12/02     delete conPtr;

//ASO Test Disabled 18/12/02     ++(*areaItr1);
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   printf("\t\tNow at end!\n\n");

//ASO Test Disabled 18/12/02   printf("PLEASE CHECK IF THE ABOVE IS CORRECT!!!\n\n");



  /* Testing operator-- */
//ASO Test Disabled 18/12/02   printf("Testing operator-- by progressing through assignments list backwards...\n\n");

  /* Display expected assignments */
//ASO Test Disabled 18/12/02   printf("\tExpected assignments list:\n");

//ASO Test Disabled 18/12/02   printf("\t\tRESOURCE:  0\tTIME: %9.6f\n", assignments[0][areaNum]);

//ASO Test Disabled 18/12/02   printf("\n");

  /* Display actual assignments */
//ASO Test Disabled 18/12/02   printf("\tActual assignments list:\n");

//ASO Test Disabled 18/12/02   areaItr1->goToEnd();

//ASO Test Disabled 18/12/02   while (!areaItr1->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     --(*areaItr1);

//ASO Test Disabled 18/12/02     conPtr = (*areaItr1)();
//ASO Test Disabled 18/12/02     printf("\t\tRESOURCE: %2d\tTIME: %9.6f\n", conPtr->getResourceNum(), conPtr->getTime());
//ASO Test Disabled 18/12/02     delete conPtr;
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\n");

//ASO Test Disabled 18/12/02   printf("PLEASE CHECK IF THE ABOVE IS CORRECT!!!\n\n");



  /* Brief test that we can extract the correct set of assignments */
//ASO Test Disabled 18/12/02   printf("Brief test that we can extract the correct set of assignments\n\n");

//ASO Test Disabled 18/12/02   for (int areaNum=0; areaNum<numAreas; areaNum++)
//ASO Test Disabled 18/12/02   {
    /* Expected assignments for this area */
//ASO Test Disabled 18/12/02     printf("\tExpected assignments for area %d:\n", areaNum);

//ASO Test Disabled 18/12/02     printf("\t\tRESOURCE:  0\tTIME: %9.6f\n\n", assignments[0][areaNum]);

    /* Actual assignment for this area */
//ASO Test Disabled 18/12/02     printf("\tActual assignments for area %d [only assignments with non-zero times shown]:\n", areaNum);

//ASO Test Disabled 18/12/02     AreaIterator* areaItr2 = alloc.getAssignmentsForArea(areaNum);
//ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02     for (areaItr2->goToStart(); !areaItr2->atEnd(); ++(*areaItr2))
//ASO Test Disabled 18/12/02     {
//ASO Test Disabled 18/12/02       printf("\t\tRESOURCE: %2d\tTIME: %9.6f\n\n", (*areaItr2)()->getResourceNum(), (*areaItr2)()->getTime());
//ASO Test Disabled 18/12/02     }

//ASO Test Disabled 18/12/02     printf("\n\n");

//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("PLEASE CHECK IF THE ABOVE IS CORRECT!!!\n\n");

//ASO Test Disabled 18/12/02 }



//ASO Test Disabled 18/12/02 if (true)    /* Do you want to test getAssignedAreas()? */
//ASO Test Disabled 18/12/02 {
//ASO Test Disabled 18/12/02   printf("Testing getAssignedAreas()\n");
//ASO Test Disabled 18/12/02   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

//ASO Test Disabled 18/12/02   AssignedAreasIterator* assnItr = alloc.getAssignedAreas();



  /* Testing goToStart() and atStart() */
//ASO Test Disabled 18/12/02   printf("Testing goToStart() and atStart():\n\n");

//ASO Test Disabled 18/12/02   printf("\tMoving forward a couple of positions [prefix and postfix ++]...\n");
//ASO Test Disabled 18/12/02   (*assnItr)++;
//ASO Test Disabled 18/12/02   ++(*assnItr);

//ASO Test Disabled 18/12/02   printf("\tAt start? ");
//ASO Test Disabled 18/12/02   if (assnItr->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tGoing to start...\n");
//ASO Test Disabled 18/12/02   assnItr->goToStart();

//ASO Test Disabled 18/12/02   printf("\tAt start? ");
//ASO Test Disabled 18/12/02   if (assnItr->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tMoving backward a couple of positions [prefix and postfix --]...\n");
//ASO Test Disabled 18/12/02   (*assnItr)--;
//ASO Test Disabled 18/12/02   --(*assnItr);
//ASO Test Disabled 18/12/02
//ASO Test Disabled 18/12/02   printf("\tAt start? ");
//ASO Test Disabled 18/12/02   if (assnItr->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tExpected data at start:\n");

//ASO Test Disabled 18/12/02   printf("\t\tAREA: %2d\n\n", start);

//ASO Test Disabled 18/12/02   printf("\tActual data at start:\n");

//ASO Test Disabled 18/12/02   conPtr = (*assnItr)();

//ASO Test Disabled 18/12/02   printf("\t\tAREA: %2d\n\n", conPtr->getAreaNum());

//ASO Test Disabled 18/12/02   printf("\tCorrect data at start? ");

//ASO Test Disabled 18/12/02   if ( (start == conPtr->getAreaNum()))
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   delete conPtr;




  /* Testing goToEnd() and atEnd() */
//ASO Test Disabled 18/12/02   printf("Testing goToEnd() and atEnd():\n\n");

//ASO Test Disabled 18/12/02   printf("\tGoing to start...\n");
//ASO Test Disabled 18/12/02   assnItr->goToStart();

//ASO Test Disabled 18/12/02   printf("\tAt end? ");
//ASO Test Disabled 18/12/02   if (assnItr->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tGoing to end...\n");
//ASO Test Disabled 18/12/02   assnItr->goToEnd();

//ASO Test Disabled 18/12/02   printf("\tAt end? ");
//ASO Test Disabled 18/12/02   if (assnItr->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tMoving forward a couple of positions...\n");
//ASO Test Disabled 18/12/02   ++(*assnItr);
//ASO Test Disabled 18/12/02   ++(*assnItr);

//ASO Test Disabled 18/12/02   printf("\tAt end? ");
//ASO Test Disabled 18/12/02   if (assnItr->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\tDecrementing...\n\n");
//ASO Test Disabled 18/12/02   --(*assnItr);

//ASO Test Disabled 18/12/02   printf("\tExpected data just before end:\n");

//ASO Test Disabled 18/12/02   printf("\t\tAREA: %2d\n\n", end);

//ASO Test Disabled 18/12/02   printf("\tActual data at just before end:\n");

//ASO Test Disabled 18/12/02   conPtr = (*assnItr)();

//ASO Test Disabled 18/12/02   printf("\t\tAREA: %2d\n\n", conPtr->getAreaNum());

//ASO Test Disabled 18/12/02   printf("\tCorrect data just before end? ");

//ASO Test Disabled 18/12/02   if ( (end == conPtr->getAreaNum()) )
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("Yes.  PASSED\n\n");
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   else
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     printf("No.  FAILED\n\n");
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   delete conPtr;



  /* Testing operator++, atStart() and atEnd() */
//ASO Test Disabled 18/12/02   printf("Testing operator++, atStart() and atEnd() by progressing through assigned area list forwards...\n\n");

  /* Display expected assigned areas */
//ASO Test Disabled 18/12/02   printf("\tExpected assigned areas:\n");

//ASO Test Disabled 18/12/02   for (int i=0; i<numAreas; i++)
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     if (assignments[0][i] != 0.0)
//ASO Test Disabled 18/12/02     {
//ASO Test Disabled 18/12/02       printf("\t\tAREA: %2d\tAT START: %d\tAT END: %d\n", i, start == i, 0);
//ASO Test Disabled 18/12/02     }
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   printf("\t\tNow at end!\n\n");

  /* Display actual assigned areas */
//ASO Test Disabled 18/12/02   printf("\tActual assigned areas:\n");

//ASO Test Disabled 18/12/02   assnItr->goToStart();

//ASO Test Disabled 18/12/02   while (!assnItr->atEnd())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     conPtr = (*assnItr)();
//ASO Test Disabled 18/12/02     printf("\t\tAREA: %2d\tAT START: %d\tAT END: %d\n", conPtr->getAreaNum(), assnItr->atStart(), assnItr->atEnd());
//ASO Test Disabled 18/12/02     delete conPtr;

//ASO Test Disabled 18/12/02     ++(*assnItr);
//ASO Test Disabled 18/12/02   }
//ASO Test Disabled 18/12/02   printf("\t\tNow at end!\n\n");

//ASO Test Disabled 18/12/02   printf("PLEASE CHECK IF THE ABOVE IS CORRECT!!!\n\n");




  /* Testing operator-- */
//ASO Test Disabled 18/12/02   printf("Testing operator-- by progressing through assigned area list backwards...\n\n");

  /* Display expected assigned areas */
//ASO Test Disabled 18/12/02   printf("\tExpected assigned areas:\n");

//ASO Test Disabled 18/12/02   for (int i=numAreas-1; i>=0; i--)
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     if (assignments[0][i] != 0.0)
//ASO Test Disabled 18/12/02     {
//ASO Test Disabled 18/12/02       printf("\t\tAREA: %2d\n", i);
//ASO Test Disabled 18/12/02     }
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\n");

  /* Display actual assigned areas */
//ASO Test Disabled 18/12/02   printf("\tActual assigned areas:\n");

//ASO Test Disabled 18/12/02   assnItr->goToEnd();

//ASO Test Disabled 18/12/02   while (!assnItr->atStart())
//ASO Test Disabled 18/12/02   {
//ASO Test Disabled 18/12/02     --(*assnItr);

//ASO Test Disabled 18/12/02     conPtr = (*assnItr)();
//ASO Test Disabled 18/12/02     printf("\t\tAREA: %2d\n", conPtr->getAreaNum());
//ASO Test Disabled 18/12/02     delete conPtr;
//ASO Test Disabled 18/12/02   }

//ASO Test Disabled 18/12/02   printf("\n");

//ASO Test Disabled 18/12/02   printf("PLEASE CHECK IF THE ABOVE IS CORRECT!!!\n\n");

//ASO Test Disabled 18/12/02 }



  return 0;
}
