/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file containr.h
 *  \brief containr.h contains AreaAssignment and ResourceAssignment
 *
 * These objects are used to return area and resource information to
 * the user. The information is wrappered in this class so that the
 * user can not do  harmful operations on the allocation list.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+----------+-----+----------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+----------------------------------------------
 * ME  | 05/12/01 |  1  | Created.
 *-----+----------+-----+----------------------------------------------
 * GT  | 25/02/02 |  2  | Modifications.  AreaAssignment now
 *     |          |     | encapsulates a resource number rather than an
 *     |          |     | area number, whilst ResourceAssignment now
 *     |          |     | encapsulates an area number rather than a
 *     |          |     | resource number.
 *-----+----------+-----+----------------------------------------------
 * ASO | 10/12/02 |  3  | Modified. Removed base class "container" and
 *     |          |     | updated "child" classes as needed. Undid
 *     |          |     | change 2.
 *-----+----------+-----+----------------------------------------------
 * crt | 13jan03  | 3.5 | Fixed param names to match encapsulation:
 *     |          |     | AreaAssignment encapsulates an area.
 *     |          |     | ResourceAssignment encapsulates a resource.
 *     |          |     | So they now take p_areaNum and p_resourceNum,
 *     |          |     | respectively. Now matches implementations.
 *-----+----------+-----+----------------------------------------------
 * crt | 06mar03  |  4  | Removed unused base container class.
 *     |          |     | Cleaned up. (cvs 1.5)
 *-----+----------+-----+----------------------------------------------
 * crt | 13mar03  | 4.5 | Re-enabled ActiveArea after design discussion
 *-----+----------+-----+----------------------------------------------
 * crt | 01may03  |  5  | Defined copy ctors
 *-----+----------+-----+----------------------------------------------
 * \endverbatim
*/

//===========================================================================//
// Written by Michael Eldridge & Gareth Thompson.        http://sarbayes.org //
//---------------------------------------------------------------------------//
// The SORAL implementation is free software, but it is Copyright (C)        //
// 2001-2003 the authors and Monash University (the SARBayes project).       //
// It is distributed under the terms of the GNU General Public License.      //
// See the file COPYING for copying permission.                              //
//                                                                           //
// If those licencing arrangements are not satisfactory, please contact us!  //
// We are willing to offer alternative arrangements, if the need should arise//
//                                                                           //
// THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED OR /
// IMPLIED.  ANY USE IS AT YOUR OWN RISK.                                    //
//                                                                           //
// Permission is hereby granted to use or copy this program for any purpose, //
// provided the above notices are retained on all copies.  Permission to     //
// modify the code and to distribute modified code is granted, provided the  //
// above notices are retained, in accordance with the GNU GPL.               //
//===========================================================================//


#ifndef _containr_h_
#define _containr_h_

/**** AreaAssignment *******************************************************************/
/// An assignment of an area and a time. It must belong to a resource to have meaning.
/**
 * Logically a tuple (area, time), an AreaAssignment is a pair of numbers
 * belonging to a resource, giving an area to which that resource has been
 * assigned, and the time for which it has been assigned to that area.
 * A resource can have many AreaAssignments.
 *
 * Author : Michael Eldridge
 *
 */

class AreaAssignment
{
	// Constructors.

	public:
		AreaAssignment(const int p_areaNum, const double p_time);
		~AreaAssignment() {};
		AreaAssignment(const AreaAssignment &p_areaAssignment);
    private:
		// disable assignment
		AreaAssignment &operator=(const AreaAssignment &p_areaAssignment);

	// Functions.

	public:
		int getAreaNum(void) const;
		double getTime(void) const;


	// Member variables.
		/**
		 * The (area number, time) tuple stored in this object contains
		 * <em>copies</em> of the values stored in the relevant Allocation
		 * object. This object does not allow these values to be modified 
		 * because this could potentially cause confusion: people would
		 * think they were modifying the assignments stored in the Allocation
		 * object itself, but they would not actually be doing so.
		 */
	private:
		/// The area number part of this tuple. Immutable copy from Allocation.
		const int areaNum; 

		/// The time part of this tuple. Immutable copy from Allocation.
		const double time;
};

/**** ResourceAssignment ******************************************************/
/// An assignment giving a resource and a time. It must belong to an area.
/**
 * Logically a tuple (resource, time), ResourceAssignment is a pair of numbers
 * belonging to an area, naming a resource number and the duration
 * for which that resource has been assigned (to the area).
 * An area can have many ResourceAssignments.
 *
 * Author : Michael Eldridge
 *
 */

class ResourceAssignment
{

	// Constructors.
	public:
		ResourceAssignment(const int p_resourceNum, const double p_time);
		~ResourceAssignment() {};
		ResourceAssignment(const ResourceAssignment &p_resAssignment);
    private:
		// disable assignment
		ResourceAssignment &operator=(const ResourceAssignment &p_resAssignment);

	// Functions
	public:

		int getResourceNum(void) const;
		double getTime(void) const;

	// Member variables.
		/**
		 * The (resource number, time) tuple stored in this object contains
		 * <em>copies</em> of the values stored in the relevant Allocation
		 * object. This object does not allow these values to be modified 
		 * because this could potentially cause confusion: people would
		 * think they were modifying the assignments stored in the Allocation
		 * object itself, but they would not actually be doing so.
		 */

	private:
		/// The resource number part of this tuple. Immutable copy frm Allocation
		const int resourceNum;

		/// The time part of this tuple. Immutable copy from Allocation.
		const double time; 
};

/// An area which has some assignments.
/**** ActiveArea *************************************************************/
/**
 * Description: an area which has some assignments. In practice, just a 
 * wrapper for an int. Why wrap an int?
 *    a) solves potential memory leaks
 *    b) keeps parallel structure with other container objects
 *
 * Author : Michael Eldridge
 *
 * Class reactivated 13mar03. ASO and crt reviewed global design and
 * decided overhead was small and there were real benefits to maintenance.
 * So we wrapped the int.
 *
 */

class ActiveArea
{
	// Constructors.

	public:
		ActiveArea(const int p_areaNum);
		~ActiveArea() {};
		ActiveArea(const ActiveArea &p_activeArea);
    private:
		ActiveArea &operator=(const ActiveArea &p_activeArea); // disable

	// Inherited functions.

	public:
		int getActiveAreaNum(void) const;


	// Member variables.

	private:
		/// The number of this "active" area.
		/**
		 * This object stores a <em>copy</em> of the active area number.
		 * This object does not allow that value to be modified 
		 * because such modification could potentially cause confusion: 
		 * people might think they were modifying the Allocation itself, but
		 * they would not actually be doing so.
		 */
		const int activeAreaNum; 
};

#endif
