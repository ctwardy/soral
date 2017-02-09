/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file con_res.cpp
 *  \brief con_res.cpp Implementation of a resource container object
 *
 *
 * Implementation of the ResourceAssignment object.
 * A ResourceAssignment stores a resource number and the amount of time
 * that resource is going to search an area. It must belong to an area
 * to have meaning.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+---------+-----+-----------------------------------------------------
 * Who |   When  | Ver | What
 *-----+---------+-----+-----------------------------------------------------
 * ME  | 05dec01 |  1  | Created.
 *-----+---------+-----+-----------------------------------------------------
 * GT  | 25dec02 |  2  | Modifications.  ResourceAssignment now encapsulates
 *     |         |     | an area number rather than a resource number.
 *-----+---------+-----+-----------------------------------------------------
 * crt | 13jan03 |  3  | Documentation. And noticed that ASO has already
 *     |         |     | undone the v2 change. Good. Param. name typos.
 *-----+---------+-----+-----------------------------------------------------
 * crt | 06mar03 |  4  | Removed container base stuff. Minor clean. (cvs 1.5)
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

/**** ResourceAssignment ctor ***********************************************/
/// Constructor for the ResourceAssignment given (resourceNum, time)
/**
 * Stores the resource number and the time. Does no error checking. (Hmmm...)
 *
 * Author : Michael Eldridge
 *
 */

ResourceAssignment::ResourceAssignment(const int p_resourceNum, const double p_time)
  :	resourceNum(p_resourceNum), time(p_time)
{
}

/**** ResourceAssignment copy ctor ******************************************/
/// Copy constructor for ResourceAssignment
/**
 * Author : Charles Twardy
 */
ResourceAssignment::ResourceAssignment(const ResourceAssignment &p_resAssignment)
  :  resourceNum(p_resAssignment.getResourceNum()),
	 time(p_resAssignment.getTime())
{
   
}


/**** getResourceNum() *******************************************************/
/// Returns the resource number stored in this ResourceAssignment.
/**
 * Author : Michael Eldridge
 */

int ResourceAssignment::getResourceNum(void) const
{
	return resourceNum;
}


/**** getTime() **************************************************************/
/// Returns the time stored in this ResourceAssignment object
/**
 * Author : Michael Eldridge
 */

double ResourceAssignment::getTime(void) const
{
	return time;
}
