/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file Alloc-W.h
 *  \brief Alloc-W.h Create an allocation using the Washburn algorithm.
 *
 *
 * The Washburn allocator is a fast optimized allocation which can 
 * handle multiple resources, where each resource may have differing
 * effectiveness in each area. The original algorithm is due to Prof.
 * Alan Washburn at the Naval Postgraduate School. It is published
 * in [TODO]xxxxxx. 
 *
 * Author: David Albrecht (DWA), with thanks to Alan Washburn for
 * providing us with his original Fortran code.
 * 
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+---------+-----+-----------------------------------------------------
 * Who |   When  | Ver | What
 *-----+---------+-----+-----------------------------------------------------
 * crt | 04mar03 |  1  | Created file from Washburn stuff in 
 *     |         |     | old Allocatn.h
 *-----+---------+-----+-----------------------------------------------------
 * aso | 23mar03 |  2  | Updated to make many things const 
 *-----+---------+-----+-----------------------------------------------------
 * crt |  7apr03 | 2.5 | Updated to make more things const 
 *-----+---------+-----+-----------------------------------------------------
 * \endverbatim
 */

//============================================================================//
// Written by David Albrecht                              http://sarbayes.org //
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

#ifndef _allocw_h_
#define _allocw_h_

#include "Allocatn.h"
#include <vector>
#include <math.h>
#include "containr.h"
#include "Array2D.h"

using namespace std;

// Forward declarations.
//class Washburn;

// Class Definitions.


/*********************************************************************************/
/// The Washburn allocation class
/**
 * Washburn:
 *
 * Implements the Washburn allocation algorithm.
 *
 * Author : David Albrecht
 *
 */

class Washburn : public Allocation
{
	// Constructors.

	public:
		Washburn(const int p_no_resources, const int p_no_areas, const Array2D& p_effectiveness,
		const valarray<double> p_available, const valarray<double> p_POC);
		~Washburn();
	private:
		Washburn(const Washburn &p_allocation);
		Washburn &operator=(const Washburn &p_allocation);

	// Allocation Functions.

	protected:
		void calcAllocation();
		ActiveArea* firstArea(void) const;
		ActiveArea* nextArea(const int currentArea) const;
		AreaAssignment* firstArea(const int resource) const;
		AreaAssignment* nextArea(const int resource, const int currentArea) const;
		ResourceAssignment* firstRes(const int area) const;
		ResourceAssignment* nextRes(const int area, const int currentResource) const;

	// Properties
	protected:
	enum {ROOT = 0, NULL_NODE = -1};

	private:
		const int FALSE_AREA;
		const double TOL;

		/// Node structure for containing information about area and resource
		//struct Node
		class Node
		{
		public:
		  double  time;  // amount of resource used.
		  bool    isArea; // true if area, false otherwise.
		  int     number; // resource or area number.
		  int     parent; // index of parent node.
		  int     firstChild; // index of first child.
		  int     nextSibling; // index of next sibling.

		  Node()
		  {
		    set(0, false, -1, ROOT, NULL_NODE, NULL_NODE);
		  }

		  void set(double p_time, bool p_flag, int p_num, int p_parent,
			   int p_child, int p_sibling)
		  {
		    time = p_time;
		    isArea = p_flag;
		    number = p_num;
		    parent = p_parent;
		    firstChild = p_child;
		    nextSibling = p_sibling;
		  }
                };

		// This typedef is need for the lastest version of C++
		//typedef vector<Node> AssignmentTree;

		/// Effectiveness matrix required for Washburn to deal
		/// with the false area.
		Array2D        myExtendedEffectiveness;
		/// The set of assignments, stored as a tree.

		//AssignmentTree myAssignments;
		vector<Node> myAssignments;

		/// Node indices for areas.
                vector<int>    myAreaIndex;
		/// Node indices for resources.
                vector<int>    myResourceIndex;
		/// The Lagrangian multipiers corresponding to the resource
		/// constraints.
                vector<double> myLambda;
		/// The Lagrangian multipiers corresponding to the sum of the
		/// resources for an area.
		vector<double> myMu;
		/// Coefficients for equations to determine how much resource
		/// to allocate to the next area.
		vector<double> myCoefficients;
		/// Next area for resource to be added to.
		int myNextArea;
		/// Next resource to add to next area.
		int myNextResource;

                // private member functions

		/// check whether the optimum has been reached
		bool optimum();

		/// update the assignment tree
		void updateAssignment();

		/// find the child of ROOT in subtree containing the node with index p_index
		int findRootChild(int p_index);

		/// sum the Mu values in the subtree containing the node with index p_index
		double sumMu(int p_index);

		/// create the equations for calculating how much of the resource myNextRes
                /// we can assign to the area myNextArea
		void createEqn(int p_index, double p_coeff);

		/// solve the equations for calculating how much of the resource myNextRes
                /// we can assign to the area myNextArea
		double solveEqn(int p_index, double p_maxTime, int& p_pivot);

		/// update the values in the assignment subtree containing the node with index
		/// p_index, and the corresponding Lambda and Mu values for the nodes in this
                /// subtree.
		void updateValues(int p_index, double factor, double time);

		/// rotate the subtree containing the node with index p_index to make this node
		/// a child of ROOT.
		void rotateSubtree(int p_index);

		/// join the subtree containing the node with index p_index to the node
                /// with index p_parentIndex.
		void joinSubtree(int p_index, int p_parentIndex);

		/// disconnect the subtree which has the node with index p_index as its root from
                /// its old subtree.

		void disconnectSubtree(int p_index);

		/// connect the subtree which has the node with index p_index as its root to
		/// the node with index p_parentIndex.

		void connectSubtree(int p_index, int p_parentIndex);

		/// get the amount of resource p_res allocated to area p_area
		double getAssignment(int p_res, int p_area);

	public:
		friend class AreaIterator;
		friend class ResourceIterator;
		friend class ActiveAreasIterator;
		friend class Node;
};

#endif
