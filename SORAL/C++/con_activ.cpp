/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file con_activ.cpp
 *  \brief con_activ.cpp contains code for the ActiveArea container.
 *
 * Implementation of the ActiveArea container object. This container
 * stores an area number. Although a little silly to wrap an int,
 * it prevents memory leaks, makes other code nicer, and gives us
 * flexibility.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 05/12/02 |  1  | Created.
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 17/12/02 |  2  | Removed. This class really just encapsulated an int.
 *     |          |     | At the moment this is a waste, but in the future if
 *     |          |     | active area can contain more new data... it may be
 *     |          |     | worth reviving.
 *-----+----------+-----+-----------------------------------------------------
 * crt | 06mar03  |  3  | Removed base container stuff. (cvs 1.4)
 *-----+----------+-----+-----------------------------------------------------
 * crt | 13mar03  | 3.5 | Enabled. (cvs 1.5)
 *-----+----------+-----+-----------------------------------------------------
 * crt | 01may03  |  4  | Defined copy ctor; const'd
 *-----+----------+-----+-----------------------------------------------------
 * \endverbatim
 */

//===========================================================================//
// Written by Michael Eldridge and Andre Oboler          http://sarbayes.org //
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
// Permission is hereby granted to use or copy this program for any purpose, /
// provided the above notices are retained on all copies.  Permission to     //
// modify the code and to distribute modified code is granted, provided the  //
// above notices are retained, in accordance with the GNU GPL.               //
//===========================================================================//

#include "containr.h"

/**** ActiveArea()***********************************************************/
/// Constructor for the ActiveArea container.
/**
 * WARNING: Performs ZERO error-checking.
 *
 * Author : Michael Eldridge
 *
 * Updated: 10/12/02 ASO
 */

ActiveArea::ActiveArea(const int p_areaNum)
:	activeAreaNum(p_areaNum)
{
}

/**** ActiveArea Copy Constructor **************************************************/
/// Copy Constructor for the ActiveArea container.
/**
 * Author: Charles Twardy
 */
ActiveArea::ActiveArea(const ActiveArea &p_activeArea)
  : activeAreaNum(p_activeArea.getActiveAreaNum())
{

}



/**** getAreaNum() **********************************************************/
/// Returns the area number this container corresponds to.
/**
 * Author : Michael Eldridge
 */
int ActiveArea::getActiveAreaNum(void) const
{
	return activeAreaNum;
}

