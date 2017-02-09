/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file Allocatn.cpp
 *  \brief Allocatn.cpp contains the generic allocation code
 *
 * Implements the base Allocation class. This class is used as the default
 * interface to an allocation object. All other objects that need to be used
 * as an allocation object inherit from this.
 *
 * An Allocation object may be used in two distinct ways:
 *
 * 1. Calculating an optimal allocation.
 *    [eg. CharnesCooper class to use the Charnes-Cooper allocation algorithm.]
 *    The following steps are performed:
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
 *    [No concrete class is currently available to enable this.]
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
 * <b><u>Version History</u></b>
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
 * ASO | 19/01/03 |  4  | Changed to work with vectors
 *----------------------------------------------------------------------------
 * \endverbatim
 */



#include "memory.h"
#include <iostream> // ASO 29/11/02 changed to iostream from iostream.h to meet the C++ standard
#include "Allocatn.h"
#include "containr.h"
#include <stdlib.h>

/*
// AGM SAR removed.
int main()
{
	return 0;
}
*/

using namespace std; //ASO 29/11/02 iostream declares things int he std namespace rather
                     //than global as iostream.h did, as a result we must now use name space std.
/*****************************************************************************************
 * Allocation
 *
 * Base constructor for the allocation class. Creates all the memory objects for storing
 * all of the search information. It is stored in a 2D array which is specified by the
 * number of areas (columns) and the number of resources (rows).
 *
 */

//Altered by Gareth Thompson 24-2-2002 to remove references to myAssignments
//(Assignments are now stored in derived classes)

Allocation::Allocation(int p_no_resources, int p_no_areas, const Array2D& p_effectiveness,
		const vector<double>& p_available, const vector<double>& p_POC)
:	//myAssignments(new double[p_no_areas * p_no_resources]),
	myNumResources(p_no_resources),
	myNumAreas(p_no_areas),
	//myEffectiveness(p_no_areas, p_no_resources, p_effectiveness),
	//myEffectivenessUserDef(p_effectiveness),
	myEffectiveness(p_effectiveness),
	//myAvailable(new double [p_no_resources]),
	//myAvailable(),
	//myPOC(new double[p_no_areas]),
	//myPOC(),
	myCoverage(0),
	myPOD(0),
	myPOS(0),
	myNewPOC(0),
	myTotalPOS(0)
{
	int i=0;

	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating base allocation object (Allocation::Allocation)" << endl;
	#endif

	// ASO 29/11/02 line below reincluded as my assignments have been merged
	// back into the base class

	//memset(myAssignments, 0, (sizeof(double) * p_no_areas * p_no_resources));

	// ASO 5/1/03 the memcpy and the for loop below it are two ways
	// of doing the same thing

	//memcpy(myPOC, p_POC, (sizeof(double) * p_no_areas));

	for (i=0; i<p_no_areas; i++)
	{
		myPOC.push_back(p_POC[i]);
	}

	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating myAvailable\n";
	#endif

	for (i=0; i<p_no_resources; i++)
	{
		#ifdef _ALLOCATION_TESTMODE
			cout << "Available[" << i << "] = " << p_available[i] <<"\n";
		#endif

		myAvailable.push_back(p_available[i]);
	}


	//ASO 17/12/02 - no done by constructor
	//memcpy(myEffectiveness, p_effectiveness, (sizeof(double) * p_no_areas * p_no_resources));

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished creating base allocation object (Allocation::Allocation)" << endl;
	#endif
}


/*****************************************************************************************
 * ~Allocation
 *
 * Reclaims all the memory used by the base allocation object.
 *
 */

//Altered by Gareth Thompson 24-2-2002 to remove references to myAssignments
//(Assignments are now stored in derived classes)

/// Reclaims all the memory used by the base allocation object.
Allocation::~Allocation()
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Deleting base allocation object (Allocation::~Allocation)" << endl;
	#endif

   /**
    *  Note: Now we are using the vector class, the clean up is taken care fo by the
	*  default destructor.
	*
	*	delete myPOC.clear();
	*	delete [] myCoverage;
	*	delete [] myPOD;
	*	delete [] myPOS;
	*	delete [] myNewPOC;
	*/

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished deleting base allocation object (Allocation::~Allocation)" << endl;
	#endif
}

/*****************************************************************************************
 * getCoverage
 *
 * Returns the coverage for the specified area. If the coverage has not been calculated it
 * calculates it for each area and stores it. This is so that when each request is made to
 * get a coverage value, it is not calculated multiple times.
 *
 */

double Allocation::getCoverage(int areaNum)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Getting the coverage for this allocation (Allocation::getCoverage)" << endl;
	#endif

	double cov;

	if (myCoverage.empty())
	{

		#ifdef _ALLOCATION_TESTMODE
			cout << "Coverage not yet calculated, doing it now (Allocation::getCoverage)" << endl;
		#endif

		for (int i = 0; i < myNumAreas; i++)
		{
			#ifdef _ALLOCATION_TESTMODE
				cout << "Allocation::calcCoverage() : About to calculate coverage for area " << i << endl;
			#endif
			cov=calcCoverage(i);
			myCoverage.push_back(cov);

			#ifdef _ALLOCATION_TESTMODE
				cout << "Coverage for area " << i << " = " << myCoverage[i];
				cout << " (Allocation::getCoverage)" << endl;
			#endif

		}
	}

	#ifdef _ALLOCATION_TESTMODE
		cout << "Returning the coverage (Allocation::getCoverage)" << endl;
	#endif

	return myCoverage[areaNum];
}

/*****************************************************************************************
 * getPOD
 *
 * Returns the POD for the specified area. If the POD has not been calculated it
 * calculates it for each area and stores it. This is so that when each request is made to
 * get a POD value, it is not calculated multiple times.
 *
 */

double Allocation::getPOD(int areaNum)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Getting the POD for this allocation (Allocation::getPOD)" << endl;
	#endif

		if (myPOD.empty())
	{

		#ifdef _ALLOCATION_TESTMODE
			cout << "POD not yet calculated, doing it now (Allocation::getPOD)" << endl;
		#endif


		for (int i = 0; i < myNumAreas; i++)
		{
			//Altered by Gareth Thompson 24-2-2002:
			//Now uses calcPOD() instead of calcCoverage()
			myPOD.push_back(calcPOD(i));

			#ifdef _ALLOCATION_TESTMODE
				cout << "POD for area " << i << " = " << myPOD[i];
				cout << " (Allocation::getPOD)" << endl;
			#endif

		}
	}

	#ifdef _ALLOCATION_TESTMODE
		cout << "New POD = " << myPOD[areaNum] << endl;
		cout << "Returning the POD (Allocation::getPOD)" << endl;
	#endif

	return myPOD[areaNum];
}

/*****************************************************************************************
 * getPOS
 *
 * Returns the POS for the specified area. If the POS has not been calculated it
 * calculates it for each area and stores it. This is so that when each request is made to
 * get a POS value, it is not calculated multiple times.
 *
 */

double Allocation::getPOS(int areaNum)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Getting the POS for this allocation (Allocation::getPOS)" << endl;
	#endif

	if (myPOS.empty())
	{

		#ifdef _ALLOCATION_TESTMODE
			cout << "POS not yet calculated, doing it now (Allocation::getPOS)" << endl;
		#endif

		for (int i = 0; i < myNumAreas; i++)
		{
			//Altered by Gareth Thompson 24-2-2002:
			//Now uses calcPOS() instead of calcCoverage()
			myPOS.push_back(calcPOS(i));

			#ifdef _ALLOCATION_TESTMODE
				cout << "POS for area " << i << " = " << myPOS[i];
				cout << " (Allocation::getPOD)" << endl;
			#endif

		}
	}

	#ifdef _ALLOCATION_TESTMODE
		cout << "New POS = " << myPOS[areaNum] << endl;
		cout << "Returning the POS (Allocation::getPOS)" << endl;
	#endif

	return myPOS[areaNum];
}

/*****************************************************************************************
 * getNewPOC
 *
 * Returns the newPOC for the specified area. If the newPOC has not been calculated it
 * calculates it for each area and stores it. This is so that when each request is made to
 * get a newPOC value, it is not calculated multiple times.
 *
 */

double Allocation::getNewPOC(int areaNum)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Getting the NewPOC for this allocation (Allocation::getNewPOC)" << endl;
	#endif

	if (myNewPOC.empty())
	{

	#ifdef _ALLOCATION_TESTMODE
		cout << "NewPOC not yet calculated, doing it now (Allocation::getNewPOC)" << endl;
	#endif


		for (int i = 0; i < myNumAreas; i++)
		{
			//Altered by Gareth Thompson 24-2-2002:
			//Now uses calcNewPOC() instead of calcCoverage()
			myNewPOC.push_back(calcNewPOC(i));

			#ifdef _ALLOCATION_TESTMODE
				cout << "NewPOC for area " << i << " = " << myNewPOC[i];
				cout << " (Allocation::getPOD)" << endl;
			#endif
		}
	}

	#ifdef _ALLOCATION_TESTMODE
		cout << "Returning the NewPOC (Allocation::getNewPOC)" << endl;
	#endif

	return myNewPOC[areaNum];
}

/*****************************************************************************************
 * getTotalPOS
 *
 * Returns the totalPOS for the specified area. If the totalPOS has not been calculated it
 * calculates it for each area and stores it. This is so that when each request is made to
 * get a totalPOS value, it is not calculated multiple times.
 *
 */

double Allocation::getTotalPOS(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Getting the total POS for this allocation (Allocation::getTotalPOS)" << endl;
	#endif

	if (myTotalPOS == 0)
	{

		#ifdef _ALLOCATION_TESTMODE
			cout << "Total POS not yet calculated, doing it now (Allocation::getTotalPOS)" << endl;
		#endif

		for (int i = 1 ; i < myNumAreas ; i++)
		{
			myTotalPOS += getPOS(i);
		}
	}

	#ifdef _ALLOCATION_TESTMODE
		cout << "Total POS = myTotalPOS" << endl;
		cout << "Returning the Total POS (Allocation::getTotalPOS)" << endl;
	#endif

	return myTotalPOS;
}

/// Returns how many of that resource are so far unallocated
/*************************************************************************************/
/**
 *
 *  Returns how many of that resource are so far unallocated (hence available to be
 *  allocated).
 */
double Allocation::getAvailable(int resourceNum)
{
	return myAvailable[resourceNum];
}

/// Returns true if there are any resources with time available, otherwise returns false
/*************************************************************************************/
/**
 *
 *  Predicate function "Do I have resources available / unallocated?"
 *
 *  True: Yes, there are unallocated resouces. If you are using UserDef
 *  you should ensure you use them before finalising the allocation
 *
 *  False: All resources have been allocated somewhere, it is safe to run the allocation.
 */
bool Allocation::haveAvailable(void)
{
	int i;

	for (i=0; i<myNumResources; i++)
	{
		if (myAvailable[i]>0)
		{
			return true;
		}
	}
	return false;
}

/*****************************************************************************************
 * calcCoverage
 *
 * Calclates the coverage for a given area number.
 *
 * [TODO] ASO - Warning!!! This function RELIES on a CC structure being used. ( I think)
 *
 */

//Gareth Thompson 24-2-2002:
//Altered function to obtain iterator using getAssignmentsForArea, rather than constructor
//This change is needed because myAssignments is no longer a member of Allocation

double Allocation::calcCoverage(int areaNum)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Calculating the coverage for this allocation (Allocation::calcCoverage)" << endl;
	#endif

	double coverage = 0.0;



	AreaIterator* itr = getAssignmentsForArea(areaNum);
	//AreaIterator itr(this, areaNum);

	while (!itr->atEnd())
	{
		AreaAssignment *tempAreaAssignment;
		tempAreaAssignment = itr->get();


		//Altered by Gareth Thompson 24-2-2002, as iterators now return POINTERS to containers
		//coverage += myEffectiveness[index] * itr().getTime();

		#ifdef _ALLOCATION_TESTMODE
			cout << "Allocation::calcCoverage() : About to obtain the container that the iterator is pointing to" << endl;
		#endif
		AreaAssignment* con = itr->get();

		#ifdef _ALLOCATION_TESTMODE
			cout << "Allocation::calcCoverage() : About to calculate coverage" << endl;
		#endif
		coverage += myEffectiveness.value[tempAreaAssignment->getAreaNum()][itr->getResource()] * con->getTime();

		#ifdef _ALLOCATION_TESTMODE
			cout << "Allocation::calcCoverage() : About to delete container" << endl;
		#endif
		delete con;

		#ifdef _ALLOCATION_TESTMODE
			cout << "Allocation::calcCoverage() : About to increment iterator" << endl;
		#endif
		++(*itr);
	}

	#ifdef _ALLOCATION_TESTMODE
		cout << "New coverage = " << coverage << endl;
		cout << "Returning the calculated coveraged (Allocation::calcCoverage)" << endl;
	#endif

	delete itr;

	return coverage;
}
/// Returns an iterator which goes through a list of resourses assigned to an area
/**************************************************************************************/
/**
 * getAssignmentsForArea
 *
 * Returns an iterator which is capable of going through a list of resourses that are
 * assigned to the given area. This protects the allcation object from any external
 * alteration.
 *
 * Author : Michael Eldridge (ASO moved from CC)
 *
 */

AreaIterator *Allocation::getAssignmentsForArea(int areaNum)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Getting a new iterator to go over the areas (CharnesCooper::getAssignmentsForArea)";
		cout << endl;
	#endif

	return new AreaIterator(*this, areaNum);
	// REASON FOR *this
	// -----------------
	// note this is type pointer,
	// * this is type allocation,
	// and when "*this" is caught with "allocation& alloc"
	// it becomes a reference.
}

/// Returns an iterator which goes through a list of areas a resource is assigned to
/**************************************************************************************/
/**
 * getAssignmentsForResource
 *
 * Returns an iterator which is capable of going through a list of areas that the given
 * resource has been assigned to. This protects the allcation object from any external
 * alteration.
 *
 * Author : Michael Eldridge (ASO moved from CC)
 *
 */

ResourceIterator *Allocation::getAssignmentsForResource(int resourceNum = 0)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Getting a new iterator to go over the resources (CharnesCooper::getAssignmentsForResource)";
		cout << endl;
	#endif

	return new ResourceIterator(*this, resourceNum);
	// REASON FOR *this
	// -----------------
	// note this is type pointer,
	// * this is type allocation,
	// and when "*this" is caught with "allocation& alloc"
	// it becomes a reference.
}

/// Returns an iterator which goes through all areas and all resources assigned there
/**************************************************************************************/
/**
 * getAssignmentsForResource
 *
 * Returns an iterator which is capable of going through all the areas that have resources
 * assigned to them. This protects the allcation object from any external
 * alteration.
 *
 * Author : Michael Eldridge (ASO moved from CC)
 *
 */

ActiveAreasIterator *Allocation::getAssignedAreas(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Getting a new iterator to go over the assigned areas (CharnesCooper::getAssignedAreas)";
		cout << endl;
	#endif

	return new ActiveAreasIterator(*this);
	// REASON FOR *this
	// -----------------
	// note this is type pointer,
	// * this is type allocation,
	// and when "*this" is caught with "allocation& alloc"
	// it becomes a reference.
}
