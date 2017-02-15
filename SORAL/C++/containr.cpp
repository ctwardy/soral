/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file containr.cpp
 *  \brief containr.cpp contains the parent container object - currently disabled
 * 
 *
 * Implements the base contaier class. It provides default implementations for 
 * the getAreaNum and getResourceNum which will not be implemented by all 
 * objects of this type.
 *
 * <b><u>Version History</u></b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 05/12/01 |  1  | Created.                                            
 *-----+----------------+-----------------------------------------------------
 * ASO | 05/12/01 |  1  | This file should now be safe to delete. Container no
 *     |          |     | longer exists as a base class. Make sure to update  
 *     |          |     | makefile when this file is removed.                 
 *----------------------------------------------------------------------------
 * \endverbatim
 */



#include "containr.h"



/*****************************************************************************************
 * Container
 *
 * Constructor for the base object which stores an object index an a time for which it is 
 * used. The is an interface object and requires a more specific implementation. It stores 
 * the amount of time an object is used.
 *
 * Author : Michael Eldridge
 * 
 */

/*

Container::Container(double p_time)
:	time(p_time)
{
}

*/

/*****************************************************************************************
 * Container
 *
 * Destructor for the container object. There is no memory allocated to this object so 
 * this is empty.
 *
 * Author : Michael Eldridge
 * 
 */


/*
Container::~Container()

{

}
*/


/*****************************************************************************************
 * Container
 *
 * Base implementation for getting the resource number. This returns a invalid number as 
 * the more specific implementation will implement the appropriate accessor functions.
 *
 * Author : Michael Eldridge
 * 
 */

/*

int Container::getResourceNum(void)
{
	return -1;
}

*/
/*****************************************************************************************
 * Container
 *
 * Base implementation for getting the area number. This returns a invalid number as 
 * the more specific implementation will implement the appropriate accessor functions.
 *
 * Author : Michael Eldridge
 * 
 */
/*
int Container::getAreaNum(void)
{
	return -1;
}
*/
/*****************************************************************************************
 * Container
 *
 * Returns the time used by this object, whether it be the amount of time a resource is 
 * assinged to an area or the amount of time a area has been assigned.
 *
 * Author : Michael Eldridge
 * 
 */

/*

double Container::getTime(void)
{
	return time;
}
*/
