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
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 05/12/01 |  1  | Created.                                            
 *----------------------------------------------------------------------------
 * GT  | 25/02/02 |  2  | Modifications.  ResourceAssignment now encapsulates 
 *     |          |     | an area number rather than a resource number.       
 *----------------------------------------------------------------------------
 * crt | 13jan02  |  3  | Documentation. And noticed that ASO has already
 *     |          |     | undone the v2 change. Good. Param. name typos.
 *----------------------------------------------------------------------------
 * \endverbatim
 */

#include "containr.h"

//Gareth Thompson 24-2-2002
//Altered so that ResourceAssignment encapculates an area number, rather than a resource number
///*****************************************************************************************
// * Container
// *
// * Constructor for the resource container. The time is stored in the base class while 
// * the resource number which is specific to this storage object is stored here.
// *
// * Author : Michael Eldridge
// * 
// */
//
//ResourceAssignment::ResourceAssignment(int p_resourceNum, double p_time)
//:	Container(p_time),
//	resourceNum(p_resourceNum)
//{
//}

/// Constructor for the ResourceAssignment
/*************************************************************************************/
/** ResourceAssignment
 *
 * Constructor for the ResourceAssignment container. 
 * Stores the resource number and the time. Does no error checking. (Hmmm...)
 *
 * Author : Michael Eldridge
 * 
 */

ResourceAssignment::ResourceAssignment(int p_resourceNum, double p_time)
:	resourceNum(p_resourceNum), time(p_time)
{
}


/// use default destructor
/************************************************************************************/
/** ~ResourceAssignment
 *
 * Destructor for the ResourceAssignment. 
 * There is no memory allocated to this object so this is empty.
 *
 * Author : Michael Eldridge
 * 
 */

ResourceAssignment::~ResourceAssignment()
{
}


//Gareth Thompson 24-2-2002
//getResourceNum() replaced with getAreaNum(), so that ResourceAssignment
//encapculates an area number, rather than a resource number
///*****************************************************************************************
// * Container
// *
// * Returns the resource number this container corresponds to.  
// *
// * Author : Michael Eldridge
// * 
// */
//
//int ResourceAssignment::getResourceNum(void)
//{
//	return resourceNum;
//}

/// Returns the resource number this ResourceAssignment container corresponds to.
/************************************************************************************/
/** getResourceNum()
 *
 * Author : Michael Eldridge
 * 
 */

int ResourceAssignment::getResourceNum(void)
{
	return resourceNum;
}


/// Returns the time used by this ResourceAssignment object
/************************************************************************************/
/** getTime()
 *
 * Returns the time used by this object
 *
 * Author : Michael Eldridge
 *
 * ASO 10/12/02 - Moved here after getting rid of base class
 * 
 */

double ResourceAssignment::getTime(void)
{
	return time;
}
