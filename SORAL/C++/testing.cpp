/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file testing.cpp
 *  \brief testing.cpp Miscellaneous functions
 * 
 *
 * Miscellaneous functions that are useful during testing.
 *
 * <b><u>Version History</u></b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 11/02/02 |  1  | Created.                                            
 *----------------------------------------------------------------------------
 * \endverbatim
 */

#include "testing.h"

 /*****************************************************************************
 * doubleEqual
 *
 * Compares two floating-point numbers (of type double),
 * returning true if they are considered to be equal,
 * and false if they are not.
 *
 * Two floating point numbers are considered to be equal
 * if either of the following conditions are met:
 * a) Both are zero
 * b) Neither is zero, and the ratio of the larger to the
 *    smaller is between 1.0 and 1.01.
 *
 * Author: Gareth Thompson
 */

bool doubleEqual(double d1, double d2)
{
  if (d1 == 0.0 && d2 == 0.0) return true;
  if (d1 != 0.0 && d2 != 0.0)
  {
	double ratio = d1 / d2;
	if (ratio < 1.0) ratio = 1/ratio;
	if (ratio <= 1.01) return true;
  }
  return false;
}
