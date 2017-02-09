/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file Allocatn.h
 *  \brief Allocatn.h Calculate and store an allocation of resources to areas (abstract)
 *
 *
 * An Allocation object is used to create an assignment of resources to
 * areas for a single sortie, and to calculate various measures about that
 * allocation. It may be used in two distinct ways:
 *
 * 1. Calculating an optimal allocation.
 *    The following steps are performed:
 *    .) The user selects a particular allocation type (e.g. CharnesCooper
 *       class to use the Charnes-Cooper allocation algorithm.)
 *    a) The numbers of resources and areas, POC values and
 *       (estimated) effectiveness values are specified upon
 *       construction of the object.
 *    b) calcAllocation() is called with the search endurance (time
 *       available) for each resource.  This causes the optimal
 *       allocation to be calculated and stored.
 *    c) Information about the allocation is obtained.
 *       getAssignmentsForResource(), getAssignmentsForArea() and
 *       getAssignedAreas() may be used to obtain the assignments,
 *       whilst getCoverage(), getPOD(), getPOS(), getNewPOC() and
 *       getTotalPOS() may be used to evaluate the success of the
 *       allocation.
 *
 * 2. Evaluating the success of a user-specified allocation.
 *    The following steps are performed:
 *    a) The numbers of resources and areas, POC values and
 *       (measured) effectiveness values are specified upon
 *       construction of the object.
 *    b) setAllocation() is called to specify the actual amount
 *       of time for which each resource searches each area.
 *    c) Information about the allocation is obtained.
 *       getCoverage(), getPOD(), getPOS(), getNewPOC() and
 *       getTotalPOS() are used to evaluate the success of the
 *       allocation.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 05/12/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 02/02/02 |  2  | Slight modifications.
 *----------------------------------------------------------------------------
 * GT  | 25/02/02 |  3  | Modifications (bug fixing).
 *----------------------------------------------------------------------------
 * ASO | 10/12/02 |  5  | Re-written for new iterator design
 *----------------------------------------------------------------------------
 * crt | 13jan03  |  5  | Minor documentation edits. (CVS 1.4)
 *----------------------------------------------------------------------------
 * \endverbatim
 */

#ifndef _allocation_h_
#define _allocation_h_

#include <vector>
#include <math.h>
#include "containr.h"
#include "Array2D.h"

using namespace std;

// Forward declarations.

class Allocation;
class CharnesCooper;

// Class Definitions.

/*************************************************************************************/
/// Iterate through all resource assignments in a given area
/**
 * AreaIterator:
 *
 * An iterator which is designed to iterate through the resources that have been allocated
 * to the specified area.
 *
 * Author : Michael Eldridge
 *
 */

class AreaIterator // ASO removed inheritance prior to removing base class
{
	// Constructors.

	public:
		//Altered by Gareth Thompson 24-2-2002
		//myAssignments has been moved to the CharnesCooper class, so these iterators
		//are now specific to that class
		AreaIterator(Allocation& p_allocation, int p_area_no);
		//ASO 29/11/02 line above and this switched back. AreaIterator(CharnesCooper *p_allocation, int p_area_no);

		~AreaIterator();
	private:
		//AreaIterator(const AreaIterator &p_area_itr);
		//AreaIterator &operator=(const AreaIterator &p_area_itr);


		public:
		void operator++(void);
		AreaAssignment* operator*(void);
		AreaAssignment* get(void);
		int getResource(void)
		{
			return resource;
		}



		bool atEnd(void);

	// Member Variables.

		protected:
		//Altered by Gareth Thompson 24-2-2002
		//myAssignments has been moved to the CharnesCooper class, so these iterators
		//are now specific to that class
		//ASO 29/11/02 lines below switched

		/// The allocation being iterated over
		Allocation& myAllocation;

		/// The current area + time pair for this resource
		AreaAssignment *current;

		//public:
		/// The resource who's areas the iterator is moving over
		int resource; /**< This value may not change */



};

/************************************************************************************/
/// Iterate through all areas a given resource is assigned to
/**
 * ResourceIterator:
 *
 * An iterator which is designed to iterate through the areas that the specified resource
 * has been assigned to.
 *
 * Author : Michael Eldridge
 *
 */

class ResourceIterator // ASO 28/11/02 no longer inherits from a base iterator class
{
	// Constructors.

	public:
		//Altered by Gareth Thompson 24-2-2002
		//myAssignments has been moved to the CharnesCooper class, so these iterators
		//are now specific to that class
		// 29/11/02 - ASO switched lines below.
		/// From an allocation and area create an object to iterate over resources assigned there
		/**
		 * Constructor that takes an allocation (could be any sub type)
		 * and an area number and then allows the user to iterates over
		 * all resources allocated to that area (and how long they are there for)
		 */
		ResourceIterator(Allocation& p_allocation, int tempArea);
		//ResourceIterator(CharnesCooper *p_allocation, int p_resource_no);

		~ResourceIterator();
	private:
		//Do I still need these?
		//ResourceIterator(const ResourceIterator &p_resource_itr);
		//ResourceIterator &operator=(const ResourceIterator &p_resource_itr);

	public:

		void operator++(void);

		//Altered by Gareth Thompson 24-2-2002, to avoid returning a reference to a local variable
		ResourceAssignment* get(void);
		ResourceAssignment* operator*(void);

		bool atEnd(void);
		int getArea(void)
		{
			return area;
		}

	// Member Variables.

		protected:
		//Altered by Gareth Thompson 24-2-2002
		//myAssignments has been moved to the CharnesCooper class, so these iterators
		//are now specific to that class
		// ASO 29/11/02 - Lines below switched
		Allocation& myAllocation;
		//CharnesCooper *myAllocation;

		/* End block of moved code */
		/***************************/

		ResourceAssignment* current; // The current assignment ResourceIterator is "pointing to"

		//public:
		int area; // The area we are looking for assignments in.

};

/***********************************************************************/
/// Iterate through those areas that have something assigned to them
/**
 * ActiveAreasIterator:
 *
 * An iterator that has been designed to iterate through all the areas that have resources
 * assigned to them.
 *
 * Author : Michael Eldridge
 *
 */

class ActiveAreasIterator // ASO removed inheritence prior to removign base class
{
	// Constructors.

	public:
		//Altered by Gareth Thompson 24-2-2002
		//myAssignments has been moved to the CharnesCooper class, so these iterators
		//are now specific to that class
		// ASO 29/11/02 - Switched lines below
		ActiveAreasIterator(Allocation& p_allocation);
		//ActiveAreasIterator(CharnesCooper *p_allocation);

		~ActiveAreasIterator();

	private:
		//ActiveAreasIterator(const ResourceIterator &p_resource_itr);
		//ActiveAreasIterator &operator=(const ActiveAreasIterator &p_resource_itr);



		public:

		void operator++(void);

		// Perhaps it shoudl be: ActiveArea* get(void);
		int get(void);

	public:
		bool atEnd(void);
		int operator*(void);

	// Member Variables.


	protected:
		//Altered by Gareth Thompson 24-2-2002
		//myAssignments has been moved to the CharnesCooper class, so these iterators
		//are now specific to that class
		//ASO 29/11/02 - Lines below switched
		/// The allocation object being iterated over
		Allocation& myAllocation; /**< This will be some child class of the virtual Allocation class */
		//CharnesCooper *myAllocation;
		int current; /**< The current area being pointed to */

	// Functions.

		// Now handled in allocation classes:
		//	private:
		//		bool CheckForResources(int areaNum);
};
/*************************************************************************************/
/// This is the virtual allocation class from which all others are derived
/**
 * Allocation:
 *
 * The main allocation control class. Provides an interface to the search algorithms that
 * can be executed from this library.
 *
 * Author : Michael Eldridge
 *
 */

class Allocation
{
	// Constructors.

	public:
		Allocation(int p_no_resources, int p_no_areas, const Array2D& p_effectiveness,
			const vector<double>& p_available, const vector<double>& p_POC);


		virtual ~Allocation();
	private:
		Allocation(const Allocation &p_allocation);
		// Removed ASO 17/12/02 Allocation &operator=(const Allocation &p_allocation);

	// Functions.
	public:

		//Altered by Gareth Thompson 24-2-2002: searchEndurance now const
		virtual void calcAllocation() = 0;

		//ASO 28/11/02 Return types changed from iterator to specific flavors of iterator
		AreaIterator *getAssignmentsForArea(int areaNum);
		ResourceIterator *getAssignmentsForResource(int resourceNum);	// Altered by Andre Oboler 28/11/02. As this a signature nothing should be set.
		// WAS: Iterator *getAssignmentsForResource(int resourceNum = 0);
		ActiveAreasIterator *getAssignedAreas(void);


		virtual double getCoverage(int areaNum);
		virtual double getPOD(int areaNum);
		virtual double getPOS(int areaNum);
		virtual double getNewPOC(int areaNum);
		virtual double getTotalPOS(void);
		double getAvailable(int resourceNum);
		bool haveAvailable(void);

	//ASO 5/12/02 attempted to change this to private to meet spec..
	// C++ does not allow derived classes to access private features of the base class
	// protected must be used instead.
	protected:
		virtual double calcCoverage(int areaNum);

		virtual double calcPOD(int areaNum)
		{
			//Altered by Gareth Thompson 24-2-2002 to simply RETURN POD value
			//*(myPOD + areaNum) = 1 - exp(-1 * getCoverage(areaNum));
			//return *(myPOD + areaNum);
			return 1 - exp(-1 * getCoverage(areaNum));
		}

		virtual double calcPOS(int areaNum)
		{
			//Altered by Gareth Thompson 24-2-2002 to simply RETURN POS value
			//*(myPOS + areaNum) = getPOD(areaNum) * getNewPOC(areaNum);
			//return *(myPOS + areaNum);

			// ASO 19/1/03 change part of conversion to vectors
			//return getPOD(areaNum) * (*(myPOC + areaNum));
			return getPOD(areaNum) * (myPOC[areaNum]);
		}

		virtual double calcNewPOC(int areaNum)
		{
			//Altered by Gareth Thompson 24-2-2002 to simply RETURN New POC value
			//*(myNewPOC + areaNum) = (1 - getPOD(areaNum) * (*(myPOC + areaNum)));
			//return *(myNewPOC + areaNum);

			// ASO 19/1/03 change part of conversion to vectors
			//return (1 - getPOD(areaNum)) * (*(myPOC + areaNum));
			return (1 - getPOD(areaNum)) * (myPOC[areaNum]);
		}


		virtual double calcInitialPSR(int resourceNum, int areaNum)
		{
			// ASO 19/1/03 change part of conversion to vectors
			//return (myEffectiveness.value[areaNum][resourceNum]) * (*(myPOC + areaNum));
			return (myEffectiveness.value[areaNum][resourceNum]) * (myPOC[areaNum]);
		}

		//What is this? It is not in the documentation. - ASO 5/12/02
		// Removed ASO 17/12/02
		/*virtual int Index(int resourceNum, int areaNum)
		{
			return (resourceNum * myNumAreas) + areaNum;
		}*/

		// ASO 05/12/02 - Functions created
		// NB: If you change the signature of these make sure to change all implementations as well.

		// ASO C++ reminder: The "= 0" at the end denotes these functions as pure virtual.
		virtual int firstArea(void) =0;

		virtual int nextArea(int area) =0;

		virtual AreaAssignment* firstArea(int Resource)=0;

		virtual AreaAssignment* nextArea(int Resource, int Area)=0; // params: What we are talking about, where we are now (in that order)

		virtual ResourceAssignment* firstRes(int Area) =0;

		virtual ResourceAssignment* nextRes(int Area, int Resource) =0; // params: What we are talking about, where we are now (in that order)





	//Gareth Thompson 24-2-2002:
	//Removed testing functions which directly access myAssignments and placed them in CharnesCooper class
	//(As myAssignments is now a member of the derived CharnesCooper class)
	//protected:
	//	virtual void SetTableValue(int p_x, int p_y, int p_value);
	//	virtual void PrintTable(void);

	// Member Variables.
	public:

		// ASO 29/11/02: Moved back here from CC
		// ASO 17/12/02 Back to CC and made protected (so only iterators use it)
		// This should be put in each algorithm because it will be a different structure for each
		//double *myAssignments;

	protected:
		//Gareth Thompson 24-2-2002: removed myAssignments and placed in derived class

		/// The total number of areas
		const int myNumAreas;
		/// The total number of resource groups
		const int myNumResources;
		/// The probability of containment
		vector<double> myPOC;
		/// The effectiveness of each resource in each area
		const Array2D& myEffectiveness;
		/// The following is a duplication of myEffectivness
		/**
		 *  It is needed for the conversion to UserDef i.e. so it can
		 *  be used in the constructor of another layer of
		 *  the allocation object underlying UserDef.
		 *
		 *  See the constructor UserDef(Allocation oldAllocation) for further details.
		 *  Disabled 19/1/02 (should no longer be needed as allocation takes an Array2D)
		 */
		//const double *myEffectivenessUserDef;

		/// The number of resource hours available for each resource
		vector<double> myAvailable;
		/// coverage
		vector<double> myCoverage;
		/// probability of discovery
		vector<double> myPOD;
		/// probability of search
		vector<double> myPOS;
		/// new probability of containment (after trying a resource allocation)
		vector<double> myNewPOC;
		/// Total probability of search
		double myTotalPOS;

		// ASO 5/12/02 moved here
		// ASO 17/12/02 Removed
		/*virtual int TableSize(void)
		{
			return (myNumAreas * myNumResources);
		}*/


	//Gareth Thompson 24-2-2002:
	//Removed friend classes which directly access myAssignments and placed them in CharnesCooper class
	//(As myAssignments is now a member of the derived CharnesCooper class)
	// Friend Classes.
	//
	// ASO 29/11/02: Iterator removed, others now re-enabled
	public:
		/// So that the AreaIterator can access the first and next functions
		friend class AreaIterator;
		/// So that the ResourceIterator can access the first and next functions
		friend class ResourceIterator;
		/// So that the ActiveAreasIterator can access the first and next functions
		friend class ActiveAreasIterator;
		/// So allocations can be converted to UserDef
		friend class UserDef;

};

/*********************************************************************************/
/// The Charnes-Cooper allocation class
/**
 * CharnesCooper:
 *
 * Implements the Charnes-Cooper allocation algorithm. The allocation is stored in a
 * matrix.
 *
 * Author : Michael Eldridge
 *
 */

class CharnesCooper : public Allocation
{
	// Constructors.

	public:
		CharnesCooper(int p_no_resources, int p_no_areas, const Array2D& p_effectiveness,
			const vector<double>& p_available, const vector<double>& p_POC);
		~CharnesCooper();
	private:
		CharnesCooper(const CharnesCooper &p_allocation);
		CharnesCooper &operator=(const CharnesCooper &p_allocation);

		void quickSort(int items[], int arraySize);
		void qSort(int items[], int left, int right);


	// Allocation Functions.

	protected:
		//Altered by Gareth Thompson 24-2-2002: searchEndurance now const
		// ASO Made protected 17/12/02
		void calcAllocation();

		// Added by ASO 5/12/02
		int firstArea(void);
		int nextArea(int area);
		AreaAssignment* firstArea(int Resource);
		AreaAssignment* nextArea(int Resource, int Area); // params: What we are talking about, where we are now (in that order)
		ResourceAssignment* firstRes(int Area);
		ResourceAssignment* nextRes(int Area, int Resource); // params: What we are talking about, where we are now (in that order)

		// Moved from base allocation class 3/2/03 - ASO
		virtual inline double calcInitialPSR(int resourceNum, int areaNum)
		{
			// ASO 19/1/03 change part of conversion to vectors
			//return (myEffectiveness.value[areaNum][resourceNum]) * (*(myPOC + areaNum));
			return (myEffectiveness.value[areaNum][resourceNum]) * (myPOC[areaNum]);
		}


	//Gareth Thompson 24-2-2002:
	//Removed testing functions (which directly access myAssignments)
	//from Allocation class and placed them here
	//(As myAssignments is now a member of the derived CharnesCooper class)

	// Test functions

	public:
		//Removed - ASO 17/12/02 void SetTableValue(int p_x, int p_y, int p_value);
		//Removed - ASO 17/12/02 void PrintTable(void);

	// Member variables

	// ASO 29/11/02: Moved back to base class so other classes can use it
	// ASO 17/12/02 moved back here and changed to a pointer to a 2D array.
	private:
		//Gareth Thompson 24-2-2002: Removed from base class and placed here
		/// The set of assignments, stored as a dynamically allocated matrix
		Array2D myAssignments;


	//Gareth Thompson 24-2-2002:
	//Removed friend classes (which directly access myAssignments) from base Allocation class
	// and placed them here
	//(As myAssignments is now a member of the derived CharnesCooper class)

	// Friend Classes.
	// ASO 9/12/02
	// note could make friend functions rather than class to achieve better coupling
	// i.e. iterators get access only to the 2 functions they need (a first and a next)

	public:
		//friend class Iterator;
		friend class AreaIterator;
		friend class ResourceIterator;
		friend class ActiveAreasIterator;
};

/***********************************************************************************/
/// The user-defined Allocation class. The user may create their own allocation here.
/**
 * UserDef:
 *
 * Allocation class for user-specified allocations. This class allows the user
 * to create an allocation from scratch, or to import an existing allocation and
 * tweak it. This class is needed because search managers will almost always
 * be aware of more constraints than the current program can handle.
 *
 * Author : Andre Oboler
 */

class UserDef : public Allocation
{
	// Constructors.

	public:
		UserDef(int p_no_resources, int p_no_areas, const Array2D& p_effectiveness,
			const vector<double>& p_available, const vector<double>& p_POC);

		UserDef(Allocation& oldAllocation);

		~UserDef();
	private:
		UserDef(const UserDef &p_allocation);
		UserDef &operator=(const UserDef &p_allocation);

	// Allocation Functions.

	protected:
		//void calcAllocation(const double *searchEndurance);

	public:
		void clearAll();
		void clearArea(int area);
		void clearResource(int resource);
		void remove(int from, int resource, double amount);
		void remove(int from, int resource);
		void add(int to, int resource, double amount);
		void add(int to, int resource);
		void move(int from, int to, int resource);
		void move(int from, int to, int resource, double amount);

	// Functions.


		// ASO 5/12/02 No longer needed in this class, altering allocation will occur in the manualAllocation class.
		// Put back in to allow testing to compile ok ASO 9/12/02. [TODO] Weed out of testing and remove.
		//public:
		//Removed - ASO 17/12/02 void setAllocation(const double *assignment);

	// Added by ASO 5/12/02
	protected:
		int firstArea(void);
		int nextArea(int area);
		AreaAssignment* firstArea(int Resource);
		AreaAssignment* nextArea(int Resource, int Area); // params: What we are talking about, where we are now (in that order)
		ResourceAssignment* firstRes(int Area);
		ResourceAssignment* nextRes(int Area, int Resource); // params: What we are talking about, where we are now (in that order)

	//Gareth Thompson 24-2-2002:
	//Removed testing functions (which directly access myAssignments)
	//from Allocation class and placed them here
	//(As myAssignments is now a member of the derived CharnesCooper class)

	// Test functions

	public:
		//Removed - ASO 17/12/02 void SetTableValue(int p_x, int p_y, int p_value);
		//Removed - ASO 17/12/02 void PrintTable(void);

	// Member variables

	// ASO 29/11/02: Moved back to base class so other classes can use it
	// ASO 17/12/02 moved back here and changed to a pointer to a 2D array.
	private:
		//Gareth Thompson 24-2-2002: Removed from base class and placed here
		/// The set of assignments is stored as a dynamically allocated matrix
		Array2D myAssignments;


	//Gareth Thompson 24-2-2002:
	//Removed friend classes (which directly access myAssignments) from base Allocation class
	// and placed them here
	//(As myAssignments is now a member of the derived CharnesCooper class)

	// Friend Classes.
	// ASO 9/12/02
	// note could make friend functions rather than class to achieve better coupling
	// i.e. iterators get access only to the 2 functions they need (a first and a next)

	public:
		//friend class Iterator;
		/// So that the AreaIterator can access the first an dnext functions
		friend class AreaIterator;
		/// So that the ResourceIterator can access the first an dnext functions
		friend class ResourceIterator;
		/// So that the ActiveAreasIterator can access the first an dnext functions
		friend class ActiveAreasIterator;
};

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
		Washburn::Washburn(int p_no_resources, int p_no_areas, const Array2D& p_effectiveness,
		const vector<double>& p_available, const vector<double>& p_POC);
		~Washburn();
	private:
		Washburn(const Washburn &p_allocation);
		Washburn &operator=(const Washburn &p_allocation);

	// Allocation Functions.

	protected:
		void calcAllocation();
		int firstArea(void);
		int nextArea(int area);
		AreaAssignment* firstArea(int Resource);
		AreaAssignment* nextArea(int Resource, int Area);
		ResourceAssignment* firstRes(int Area);
		ResourceAssignment* nextRes(int Area, int Resource);

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

