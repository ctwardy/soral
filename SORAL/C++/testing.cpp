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

//============================================================================//
// Written by Gareth Thompson                            http://sarbayes.org  //
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
