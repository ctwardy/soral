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
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 05/12/01 |  1  | Created.                                            
 *----------------------------------------------------------------------------
 * GT  | 25/02/02 |  2  | Modifications: AreaAssignment now encapsulates a    
 *     |          |     | resource number, rather than an area number.        
 *----------------------------------------------------------------------------
 * ASO | 10/12/02 |  3  | Undid change 2                                      
 *----------------------------------------------------------------------------
 * crt | 13jan02  |  3  | Documentation. cvs 1.3
 *----------------------------------------------------------------------------
 * \endverbatim
 */

#include "containr.h"

//Gareth Thompson 24-2-2002
//Altered so that AreaAssignment encapsulates a resource number, rather than an area number
///*****************************************************************************************
// * Container
// *
// * Constructor for the AreaAssignment container. The time is stored in the base class while the area 
// * number which is specific to this storage object is stored here.
// *
// * Author : Michael Eldridge
// * 
// */
//
//AreaAssignment::AreaAssignment(int p_areaNum, double p_time)
//:	Container(p_time),
//	areaNum(p_areaNum)
//{
//}

/// Creates an AreaAssignment (area number and time). 
/************************************************************************************/
/** AreaAssignment
 *
 * Constructor for the AreaAssignment container. 
 *
 * Author : Michael Eldridge
 * 
 */
AreaAssignment::AreaAssignment(int p_areaNum, double p_time)
:	time(p_time), areaNum(p_areaNum)
{
	// should set in body and check time > 0. ASO 10/12/02
}


/// use default destructor
/************************************************************************************/
/** ~AreaAssignment
 *
 * Destructor for the AreaAssignment object. There is no memory allocated to this object so 
 * this is empty.
 *
 * Author : Michael Eldridge
 * 
 */
AreaAssignment::~AreaAssignment()
{
}

//Gareth Thompson 24-2-2002
//getResourceNum() replaced with getAreaNum(), so that AreaAssignment
//encapculates a resource number, rather than an area number
///*****************************************************************************************
// * Container
// *
// * Returns the area number this container corresponds to.  
// *
// * Author : Michael Eldridge
// * 
// */
//
//int AreaAssignment::getAreaNum(void)
//{
//	return areaNum;
//}

/// Returns the area number this AreaAssignment corresponds to.
/*************************************************************************************/
/** getAreaNum()
 *
 * Returns the area number this AreaAssignment corresponds to. 
 *
 * The reason a get function is used is without a set function, the calling
 * function can not change the data.
 *
 * Author : Michael Eldridge
 * 
 */

int AreaAssignment::getAreaNum(void)
{
	return areaNum;
}

/// Returns the time this AreaAssignment corresponds to.
/*************************************************************************************/
/** getTime()
 *
 * Returns the time this AreaAssignment corresponds to.
 *
 * The reason a get function is used is without a set function, the calling
 * function can not change the data.
 *
 * Author : Michael Eldridge
 *
 * ASO 10/12/02 - Moved here after getting rid of base class
 * 
 */

double AreaAssignment::getTime(void)
{
	return time;
}

