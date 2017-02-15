/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file Alloc-CC.h
 *  \brief Alloc-CC.h Create an allocation using the Charnes-Cooper algorithm.
 *
 *
 * The Charnes-Cooper allocator is a fast optimized allocation which can 
 * handle a single resource type (such as trained ground searchers). 
 * That resource may have differing effectiveness in each area. 
 * The algorithm is presented accessibly in (Frost [TODO] 200x) in the
 * manual to his implementation in Pascal. A more general description 
 * is in the last (fourth) article of (Frost [TODO] 199x) available at
 * [TODO] http://xxxxxxxxx
 * 
 * The mathematics are presented in detail in (Stone [TODO]19xx). 
 * The original paper is [TODO] xxxxx. 
 *
 * Author: Gareth Thompson, Andre Oboler and Michael Eldridge
 * 
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+---------+-----+-----------------------------------------------------
 * Who |   When  | Ver | What
 *-----+---------+-----+-----------------------------------------------------
 * crt | 04mar03 |  1  | Created file from CC stuff in 
 *     |         |     | old Allocatn.h
 *-----+---------+-----+-----------------------------------------------------
 * crt | 05mar03 |  2  | Cleaned comments, removed destructor. (cvs 1.2)
 *-----+---------+-----+-----------------------------------------------------
 * \endverbatim
 */

//============================================================================//
// Written by Gareth Thompson & Andre Oboler              http://sarbayes.org //
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


#ifndef _alloc_CC_h_
#define _alloc_CC_h_

#include "Allocatn.h"
#include <vector>
#include <math.h>
#include "containr.h"
#include "Array2D.h"

using namespace std;

/****************************************************************************/
/// The Charnes-Cooper allocation class
/**
 * CharnesCooper:
 *
 * Implements the Charnes-Cooper allocation algorithm. The allocation is 
 * stored in a matrix (Array2D). More details in the file header.
 *
 * Author : Michael Eldridge
 *
 */

class CharnesCooper : public Allocation
{
	// Constructors.

	public:
		CharnesCooper(const int p_no_resources, 
						  const int p_no_areas, 
						  const Array2D& p_effectiveness,
						  const valarray<double> p_available, 
						  const valarray<double> p_POC);
		// Use the default destructor, so don't declare: ~CharnesCooper();

	private:
		CharnesCooper(const CharnesCooper &p_allocation);
		CharnesCooper &operator=(const CharnesCooper &p_allocation);
		void quickSort(int items[], int arraySize);
		void qSort(int items[], int left, int right);


	// Allocation Functions. 
   // Made protected 17/12/02 by ASO. So descendants of CC can use.
	protected:
		void calcAllocation();
		ActiveArea* firstArea(void) const;        
		ActiveArea* nextArea(const int currentArea) const;
		AreaAssignment* firstArea(const int Resource) const;
		AreaAssignment* nextArea(const int Resource, const int currentArea) const; 
		ResourceAssignment* firstRes(const int Area) const;
		ResourceAssignment* nextRes(const int Area, const int currentResource) const; 


		/// Calculates the initial Probable Success Rate used in CC.
		/*****************************************************************/
		/**
		 * Calculates the initial PSR (Probable Success Rate) upon which
		 * the Charnes-Cooper algorithm is based. If 
		 *     W = sweep width (this resource, in this area)
		 *     v = velocity    (this resource, in this area)
		 *     A = area size   (m^2 or km^2 or whatever units v is in)
		 *     p = POC or POA  (this area)
		 * Effectiveness = Wv/A, so:
		 *     PSR = Wvp/A = Wv * (p/A) = Wv * Pden
		 * where Pden is the probability density of the area.
		 * So PSR is the rate at which probability is swept up. 
		 * For one resource, if you search highest-PSR areas first,
		 * you win. Maximal change in probability per time.
		 *
		 */
		double calcInitialPSR(const int resourceNum, const int areaNum)
		{
		  return (myEffectiveness[areaNum][resourceNum]) * (myPOC[areaNum]); 
		}
		

	// Member variables

	private:
		/// The set of assignments, stored as a dynamically allocated matrix
		Array2D myAssignments;

		/// The amount of our resource still available.
		double myAvailable;


	// Friend Classes.
	// ASO 9/12/02
	// For better coupling, could make friend functions rather than class
	// i.e. iterators get access only to the 2 functions they need 
	// (a first and a next)

	public:
		friend class AreaIterator;
		friend class ResourceIterator;
		friend class ActiveAreasIterator;
};

#endif
