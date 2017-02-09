/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file Allocatn.h
 *  \brief Allocatn.h Defines base classes for resource allocation.
 *
 *
 * An Allocation object is used to create an assignment of resources to
 * areas for a single sortie, and to calculate various measures about that
 * allocation. This file defines the base level (abstract) allocation 
 * class. All other allocations inherit from this one. It <em>also</em>
 * defines the iterators used to extract allocations from <em>any</em>
 * concrete allocation object.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+---------+-----+-----------------------------------------------------
 * Who |   When  | Ver | What
 *-----+---------+-----+-----------------------------------------------------
 * ME  | 05dec01 |  1  | Created.
 *-----+---------+-----+-----------------------------------------------------
 * GT  | 02feb02 |  2  | Slight modifications.
 *-----+---------+-----+-----------------------------------------------------
 * GT  | 25feb02 |  3  | Modifications (bug fixing).
 *-----+---------+-----+-----------------------------------------------------
 * ASO | 10dec02 |  4  | Re-written for new iterator design
 *-----+---------+-----+-----------------------------------------------------
 * crt | 13jan03 |  5  | Minor documentation edits. (CVS 1.4)
 *-----+---------+-----+-----------------------------------------------------
 * crt | 04mar03 |  6  | (Received as CVS-1.11) After code review.
 *     |         |     | Removed subclasses to new files, cleaned 
 *     |         |     | comments, fixed vars, and more.
 *-----+---------+-----+-----------------------------------------------------
 * crt | 10mar03 |  7  | Reduced forward decls, add enums, clean. (cvs 1.15)
 *-----+---------+-----+-----------------------------------------------------
 * ASO | 25mar03 |  8  | Vector to valarray.
 *-----+---------+-----+-----------------------------------------------------
 * crt | 26mar03 |  9  | Made protected private. Other minor. (cvs 1.21)
 *-----+---------+-----+-----------------------------------------------------
 * crt | 18apr03 | 10  | Declared iterator destructors. GT spotted bug.
 *-----+---------+-----+-----------------------------------------------------
 * crt | 01may03 | 11  | Iterators return objects, not pointers
 *-----+---------+-----+-----------------------------------------------------
 * \endverbatim
 */

//===========================================================================//
// Written by Michael Eldridge, Gareth Thompson, Andre Oboler, and C. Twardy //
//                                                       http://sarbayes.org //
//---------------------------------------------------------------------------//
// The SORAL implementation is free software, but it is Copyright (C)        //
// 2001-2003 the authors and Monash University (the SARBayes project).       //
// It is distributed under the terms of the GNU General Public License.      //
// See the file COPYING for copying permission.                              //
//                                                                           //
// If those licencing arrangements are not satisfactory, please contact us!  //
// We are willing to offer alternative arrangements if the need should arise.//
//                                                                           //
// THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED OR //
// IMPLIED.  ANY USE IS AT YOUR OWN RISK.                                    //
//                                                                           //
// Permission is hereby granted to use or copy this program for any purpose, //
// provided the above notices are retained on all copies.  Permission to     //
// modify the code and to distribute modified code is granted, provided the  //
// above notices are retained, in accordance with the GNU GPL.               //
//===========================================================================//

#ifndef _allocation_h_
#define _allocation_h_

#include <vector>
#include <math.h>
#include <valarray>
#include "containr.h"
#include "Array2D.h"

using namespace std;


// Forward declarations.
class Allocation;


// Class Definitions.

/**** AreaIterator **********************************************************/
/// Iterate through all area assignments for a given resource
/**
 * An iterator which iterates through the area assignments
 * for a specified resource.  Conceptually, returns a pair (A,T) 
 * of (area, duration assigned there), thus "area iterator".
 *
 * Like the other iterators, it uses accessor functions defined 
 * in Allocatn.h and implemented in each allocation class.
 *
 * Author : Michael Eldridge
 *
 */

class AreaIterator 
{
	// Constructors and Destructors
	public:
		AreaIterator(const Allocation& p_allocation, const int p_resource_num);
		~AreaIterator();

   private:
		/// Disable copy constructor by declaring private, and not defining.
		AreaIterator(const AreaIterator &p_area_itr);

		/// Disable assignment operator by declaring private, and not defining.
		AreaIterator &operator=(const AreaIterator &p_area_itr);


	// Methods

   public:
		void operator++(void);

		AreaAssignment operator*(void) const;

		bool atEnd(void) const;

		int getResource(void) const
		{
			return myResource;
		}


	// Member Variables.

	protected:
		/// The allocation being iterated over
		const Allocation& myAllocation;

		/// The current area + time pair for this resource
		AreaAssignment *current;

		//public:
		/// The resource for which we're reading assignments.
		const int myResource; /**< This value may not change */



};

/**** ResourceIterator ******************************************************/
/// Iterate through all resources assigned to a given area
/**
 * An iterator which iterates through the resources assigned to
 * a given area. Conceptually, returns a pair (R,T) of 
 * (resource, time allocated here). Thus "resource iterator".
 *
 * Like the other iterators, it uses accessor functions defined 
 * in Allocatn.h and implemented in each allocation class.
 *
 * Author : Michael Eldridge
 *
 */

class ResourceIterator
{
	// Constructors and Destructors

	public:
		ResourceIterator(const Allocation& p_allocation, const int p_area_num);
		~ResourceIterator();

	private:
		/// Disable copy constructor by declaring private, and not defining.
		ResourceIterator(const ResourceIterator &p_resource_itr);

		/// Disable assignment operator by declaring private, and not defining.
		ResourceIterator &operator=(const ResourceIterator &p_resource_itr);


	// Methods
	public:

		void operator++(void);

		//Altered by Gareth Thompson 24-2-2002, to avoid returning a reference to a local variable
		ResourceAssignment operator*(void) const;

		bool atEnd(void) const;

		int getArea(void) const
		{
			return myArea;
		}

	// Member Variables.
	protected:
		const Allocation& myAllocation;

		/// The current resource + time pair for this area
		ResourceAssignment* current; 

		//public:
		// The area we are looking for assignments in.
		const int myArea; /**< This value may not change */

};

/**** ActiveAreasIterator ****************************************************/
/// Iterate through those areas that have something assigned to them
/**
 * An iterator that iterates through all and only those areas
 * which have resources assigned to them. Like the other iterators, 
 * it uses accessor functions defined in Allocatn.h and implemented 
 * in each allocation class.
 *
 *
 * Author : Michael Eldridge
 */

class ActiveAreasIterator // ASO removed inheritence prior to removing base class
{
	// Constructors and Destructors
	public:
		ActiveAreasIterator(const Allocation& p_allocation);
		~ActiveAreasIterator();

	private:
		/// Disable copy constructor by declaring private, and not defining.
		ActiveAreasIterator(ActiveAreasIterator &p_activeArea_itr);

		/// Disable assignment operator by declaring private, and not defining.
		ActiveAreasIterator &operator=(ActiveAreasIterator &p_activeArea_itr);

	// Methods

	public:

		ActiveArea operator*(void) const; 
		void operator++(void);
		bool atEnd(void) const;


	// Member Variables.

	protected:

		const Allocation& myAllocation; /**< This will be an instance of some child class of the virtual Allocation class */

		ActiveArea* current; /**< The current area being pointed to */

};




/**** Allocation ************************************************************/
/// This is the virtual allocation class from which all others are derived
/**
 * The abstract allocation class. Provides a standard interface for the 
 * concrete allocation algorithms that can be run from this library. This 
 * abstract class also handles the calculations common to all allocations 
 * (Coverage, POD, POS, New POC, etc.) so that individual algorithms do not 
 * have to reimplement them.
 * 
 * Crucially, it also provides the iterators which are common for <em>all</em>
 * allocations, so that users have a common interface even if all algorithms 
 * have different internal data structures. To make this possible, each 
 * specific allocation algorithm must implement the six simple virtual 
 * accessor functions defined here. Not a bad tradeoff. (In addition, 
 * algorithm writers please kindly implement calcAllocation() and call it 
 * from your constructor. The code doesn't care, but it will help other 
 * readers figure out what's going on.)
 *
 * The public interface is designed with a few things in mind:
 *  - All allocations should have a common interface
 *  - The object just does allocations, and reports some vital numbers
 *    relevant to those allocations.
 *  - The interface should provide just enough to extract everything
 *    you need. The user should keep track of other things, like 
 *    resource or area names, etc.
 *  - Allocation objects should be self-sufficient. They must be able
 *    to hang around for a whole search (as a history, for example)
 *    without risk of their data expiring. Therefore they copy their
 *    input to (hidden) local variables.
 *  - Since they may be used as histories, they must provide get 
 *    functions even to variables the user would obviously know when
 *    they created the allocation object.
 *  - But we deliberately do <em>not</em> provide some get functions,
 *    because if the user has forgotten those, they are probably also
 *    misusing the allocation object.
 *
 * <b>Note on protected versus private</b>: 
 * Prevailing wisdom says that member variables are always private. But
 * we have made some protected instead, because child classes are themselves
 * allocations, and need to refer to variables like myEffectiveness quite
 * often. Forcing them to use the indirection of a get function, which is
 * just an alias for returning the variable makes their code uglier. Such 
 * variables are already const, so only deliberate misuse presents a 
 * problem. Yes an end-user could inherit from the class just to get at 
 * the variables directly. But you know what? This is open source. A user
 * that wants to modify the variables that badly can probably manage 
 * anyway. Call it low-clutter programming. Eschew superfluous indirection.
 *
 * Some members remain private: the calculated variables are not always 
 * calculated in advance, so access <em>must</em> go through the get
 * functions. This is not a concern with variables passed in as const.
 * Those are always defined and don't change, so if you're an allocation
 * object yourself, why not just use them?
 * 
 * <b>Note on functions not provided:</b>
 * We do not provide getNumAreas() and getNumResources(). As pure
 * allocation objects, all we care about are the resources and areas
 * we get passed, and to us they are just sequential numbers from 0. 
 * We don't care if the user only sent us a subset of resources (or
 * areas), or if the user later gets more resources or splits areas.
 * So the user had darn well better keep around
 * an index to take him from our sequential numbers back to actual
 * areas in effect at the time the allocation was made. And if they
 * have to ask us how many areas and resources we had, they've already
 * messed up. (Besides, if they <em>really</em> need this, they can
 * use the iterators and count.)
 * 
 * We do not provide a getPOC() function. If the user doesn't know what
 * our original POC map looked like (oops?), they can get it in at least
 * two ways:
 *  - Use the getNewPOC() from the previous allocation.  
 *    (You do remember what order you ran the allocations, don't you?)
 *  - POS = oldPOC - newPOC. You do the math.
 * But may I remind the user that if they don't keep track of this 
 * themselves, and they have added, deleted, merged, or split areas,
 * they're already toast.
 *
 * We do not provide an assignment operator. That would be nuts. 
 *
 * <b>Note on valarray</b>: We make extensive use of valarray. Why?
 * We had at one stage replaced our "double *" with
 * vectors, to gain all the notation, encapsulation, and memory cleanup 
 * advantages of classes. In our first code review Michael noted that
 * vectors have a lot of overhead and that we never need dynamic resizing.
 * David pointed out that valarrays provided all the advantages of vectors
 * without the overhead: they don't resize (easily), and they're designed 
 * from the ground up for speed. Thanks Bjarne!
 * 
 * Code Author : Michael Eldridge
 * Polemics    : Charles Twardy
 * Sponsored by: The letter É. (Is your editor unicode?)
 *
 */

class Allocation
{
	// Constructors and Destructors

	public:
		Allocation(const int p_no_resources, 
					  const int p_no_areas, 
					  const Array2D& p_effectiveness,
					  const valarray<double> p_endurance, 
					  const valarray<double> p_POC);
		 /// The default copy constructor for the base case
		Allocation(const Allocation &p_allocation); // added ASO 30mar03
		virtual ~Allocation();
	private:

	// Functions.
	public:

		double getEndurance(int resourceNum);///\todo Define here? Inline?
		double getEffectiveness(int areaNum, int resourceNum);///\todo Define here? Inline?
		virtual void calcAllocation() = 0;       // pure virtual

		///\todo Once upon a time these were virtual. Any reason to change back?
		double getCoverage(int areaNum);
		double getPOD(int areaNum);
		double getPOS(int areaNum);
		double getNewPOC(int areaNum);
		double getTotalPOS(void);

   private:   // No one should see these directly. Even the kids.

		virtual double calcCoverage(const int areaNum);

		virtual double calcPOD(const int areaNum)
		{
			return 1 - exp(-1 * getCoverage(areaNum));
		}

		virtual double calcPOS(int areaNum)
		{
			return getPOD(areaNum) * (myPOC[areaNum]);
		}

		virtual double calcNewPOC(const int areaNum)
		{
		   return (1 - getPOD(areaNum)) * (myPOC[areaNum]);
			// crt: could also do myPOC[areaNum] - getPOS(areaNum)
		}


		// ASO 05/12/02 - Functions created
		// NB: If you change the signatures of these make sure to change
		//     ALL implementations as well. (ie if you use int* or ActiveArea* 
		//     to avoid memory leaks and/or for consistency.
		// ASO C++ reminder: The "= 0" denotes these functions as pure virtual.
		// Also: we return pointers rather than objects so users can keep
		// a single pointer in their loop, and so we can return NULL when req.
		virtual ActiveArea* firstArea(void) const =0;

		virtual ActiveArea* nextArea(const int currentArea) const =0;

		virtual AreaAssignment* firstArea(const int resource) const =0;

		// ASO 30mar03 - currentArea: emphasizes that we're getting next area
		// Resource does not change, hence not called "current".
		virtual AreaAssignment* nextArea(const int resource, const int currentArea) const =0;

		virtual ResourceAssignment* firstRes(const int area) const =0;

		// ASO 30mar03 - currentResource: emphasizes that we're getting next res.
		// Area does not change, hence not called "current".
		virtual ResourceAssignment* nextRes(const int area, const int currentResource) const =0;


	// Member Variables.
	public:
		// Each allocator stores its own assignments as it chooses. 
		// No public vars. To convert subtypes, define copy constructors.

   protected: // Variables the kids need to see. Const only please.

		/// The total number of areas
		const int myNumAreas;

		/// The total number of resource groups
		const int myNumResources;

		/// The original probability of containment (ie probability of area, POA)
		valarray<double> myPOC;

		/// The effectiveness of each resource in each area. (W*v/A)
		const Array2D& myEffectiveness;

		/// The amount of time originally made available for each resource
		/**
		 * myEndurance is used to store the number of hours 
		 * <em>originally</em> passed in. This means it will not change. 
		 * UserDef and other functions will need their own storage for
		 * unassigned hours (suggest myAvailable or myUnassignedResources). 
		 * This move is to clean up semantics.
		 */
		const valarray<double> myEndurance;

		/// A flag to force recalculation. For UserDef.
		/**
		 * The only non-const protected data member. Normally, an allocation
		 * is set in stone as soon as the object exists, so we can calculate
		 * coverage, POD, newPOC, and POS once and store them. But UserDef
		 * could change again at any time, and defeat our cleverness.
		 * Either we need to make the get functions virtual (just for 
		 * UserDef), or make them always calculate on the fly (expensive
		 * for repeated getTotalPOS operations), or provide a flag to
		 * force recalculation. Here's the flag. Since we have protected
		 * data members, we put it here because quite obviously it exists
		 * precisely so that the kids can set it. (Well, one of them anyway.)
		 * 
		 * If you remove it, please change the logic in the appropriate
		 * get functions. And beware: since we provide it, some non-UserDef
		 * algorithm may just use it. Though I can't just now see <em>why</em>.
		 *
		 * Author: crt
		 */
		bool forceRecalc; // Wish we could set it to false here.

   private: // Calculated variables. NO direct access!

		/// coverage
		valarray<double> myCoverage;

		/// probability of detection
		valarray<double> myPOD;

		/// probability of success
		valarray<double> myPOS;

		/// new probability of containment (after trying a resource allocation)
		valarray<double> myNewPOC;

		/// Total probability of success
		double myTotalPOS;

	// External methods
	public:
		/// So that the AreaIterator can access the first & next functions
		friend class AreaIterator;
		/// So that the ResourceIterator can access the first & next functions
		friend class ResourceIterator;
		/// So that the ActiveAreasIterator can access the first & next functions
		friend class ActiveAreasIterator;

};


#endif

