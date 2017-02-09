/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file con_area.cpp
 *  \brief con_area.cpp Implementation of the AreaAssignment container object.
 *
 *
 * Implementation of the AreaAssignment container object.
 * This one holds the (area, time) details for a particular resource.
 * That is, it stores the area number and the amount of time the given
 * resource is going to search there.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+---------+-----+-----------------------------------------------------
 * Who |   When  | Ver | What
 *-----+---------+-----+-----------------------------------------------------
 * ME  | 05dec01 |  1  | Created.
 *-----+---------+-----+-----------------------------------------------------
 * GT  | 25feb02 |  2  | Modifications: AreaAssignment now encapsulates a
 *     |         |     | resource number, rather than an area number.
 *-----+---------+-----+-----------------------------------------------------
 * ASO | 10dec02 |  3  | Undid change 2
 *-----+---------+-----+-----------------------------------------------------
 * crt | 13jan03 | 3.5 | Documentation. cvs 1.3
 *-----+---------+-----+-----------------------------------------------------
 * crt | 06mar03 |  4  | Cleaned up. Removed container base. (cvs 1.5)
 *-----+---------+-----+-----------------------------------------------------
 * crt | 01may03 |  5  | Defined copy ctor; const'd
 *-----+---------+-----+-----------------------------------------------------
 * \endverbatim
 */

//===========================================================================//
// Written by Michael Eldridge and Gareth Thompson       http://sarbayes.org //
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

#include "containr.h"

/**** AreaAssignment() ******************************************************/
/// Constructor for AreaAssignment, given (area number, time).
/**
 * Author : Michael Eldridge
 */
AreaAssignment::AreaAssignment(const int p_areaNum, const double p_time)
  :	time(p_time), areaNum(p_areaNum)
{
	//\todo should set in body and check time > 0. ASO 10/12/02
}


/**** AreaAssignment copy ctor *********************************************/
/// Copy constructor for AreaAssignment
/**
 * Author : Charles Twardy
 */
AreaAssignment::AreaAssignment(const AreaAssignment &p_areaAssignment)
  :  areaNum(p_areaAssignment.getAreaNum()),
	 time(p_areaAssignment.getTime())
{
   
}

/**** getAreaNum() **********************************************************/
/// Returns the area number stored in this AreaAssignment 
/**
 * We use a "get" function with no "set" function (rather than
 * just declaring the variable public) so that the calling
 * function cannot change the data.
 *
 * Author : Michael Eldridge
 *
 */

int AreaAssignment::getAreaNum(void) const
{
	return areaNum;
}

/**** getTime() *************************************************************/
/// Returns the time stored in this AreaAssignment
/**
 * We use a "get" function with no "set" function (rather than
 * just declaring the variable public) so that the calling
 * function cannot change the data.
 *
 * Author : Michael Eldridge
 *
 */

double AreaAssignment::getTime(void) const
{
	return time;
}

