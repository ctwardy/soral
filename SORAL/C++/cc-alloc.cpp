/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file cc-alloc.cpp
 *  \brief cc-alloc.cpp Implements a Charnes Cooper allocation
 *
 * Implements a specific allocation object which uses the Charnes Cooper 
 * allocation method. This class inherits most of its behaviour from the base 
 * allocation class.
 *
 * <b><u>Version History</u></b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * ME  | 05/12/01 |  1  | Created.                                            
 *----------------------------------------------------------------------------
 * GT  | 25/02/02 |  2  | Modifications (bug fixing).                         
 *----------------------------------------------------------------------------
 * \endverbatim
 */


#include "Allocatn.h"
#include <iostream>
#include "memory.h"

using namespace std;

/*****************************************************************************************
 * CharnesCooper
 *
 * Constructor for the Charnes Cooper allocation object. Most of theh information is 
 * stored in the base allocation class.
 *
 * Author : Michael Eldridge
 * 
 */

// Altered by Gareth Thompson 24-2-2002 to initialise myAssignments
// (which is now a member of CharnesCooper rather than the base Allocation class)
// rewritten to use Array2D 17/12/02 - ASO

CharnesCooper::CharnesCooper(int p_no_resources, int p_no_areas, const Array2D& p_effectiveness,
		const vector<double>& p_available, const vector<double>& p_POC)
:	Allocation(p_no_resources, p_no_areas, p_effectiveness, p_available, p_POC),
	myAssignments(p_no_areas, p_no_resources)
	
{
	//memset(myAssignments, 0, (sizeof(double) * p_no_areas * p_no_resources)); 			

	#ifdef _ALLOCATION_TESTMODE
		cout << "Creating a Charnes Cooper search object (CharnesCooper::CharnesCooper)" << endl;
	#endif
	calcAllocation();
}

/*****************************************************************************************
 * CharnesCooper
 *
 * Reclaims all the memory used by this object.
 *
 * Author : Michael Eldridge
 * 
 */

//Altered by Gareth Thompson 24-2-2002 to delete myAssignments
//(which is now a member of CharnesCooper rather than the base Allocation class)

/// use default destructor
CharnesCooper::~CharnesCooper()
{

	#ifdef _ALLOCATION_TESTMODE
		cout << "Destorying a Charnes Cooper search object (CharnesCooper::~CharnesCooper)" << endl;
	#endif
}



/*****************************************************************************************
 * setAllocation
 *
 * This is used to specifically set all the allocation information. This could be used in 
 * the case where are previously run search may need to be rerun with slight alterations.
 *
 * Author : Michael Eldridge
 *
 * ASO 5/12/02 - All alterations will occur through the manualAllocation class.
 * [TODO] This function shoudl be removed (after being weeded out of testing)
 * 
 */
/*
 void CharnesCooper::setAllocation(const double *assignment)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Setting the allocation table (CharnesCooper::setAllocation)" << endl;
	#endif
	
	memcpy(myAssignments, assignment, (myNumAreas * myNumResources) * sizeof(double));

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished setting the allocation table (CharnesCooper::setAllocation)" << endl;
	#endif
}
*/

//Gareth Thompson 24-2-2002
//Removed test functions (which directly access myAssignments) from Allocation class
//and placed them in CharnesCooper class


// Test functions.

/*****************************************************************************************
 * SetTableValue
 *
 * This is a test function which is used to set a particular values within the assignemts 
 * table. 
 *
 */

/*void CharnesCooper::SetTableValue(int p_x, int p_y, int p_value)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Setting a particular value in the allocation table (CharnesCooper::SetTableValue)" << endl;
	#endif
	
	int y = p_y * myNumAreas;
	int offset = (y + p_x);

	*(myAssignments + offset) = p_value;

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished setting a particular value in the allocation table (CharnesCooper::SetTableValue)" << endl;
	#endif
}
*/
/*****************************************************************************************
 * PrintTable
 *
 * This is a test function which will display all the values in the assignments array in a 
 * tablular form.
 *
 */
/*
void CharnesCooper::PrintTable(void)
{
	#ifdef _ALLOCATION_TESTMODE
		cout << "Displaying the allocation table (CharnesCooper::PrintTable)" << endl;
	#endif
	
	//Added by Gareth Thompson 2-2-2002, for testing purposes
	cout << "Number of resources: " << myNumResources << endl;
	cout << "Number of areas: " << myNumAreas << endl;

	//Altered by Gareth Thompson 2-2-2002 to fix syntax error
	//for (unsigned int i = 0 ; i < unsigned int(myNumAreas * myNumResources) ; i++)
	for (unsigned i = 0 ; i < unsigned(myNumAreas * myNumResources) ; i++)
		cout << i << " = " << myAssignments[i] << endl; 

	#ifdef _ALLOCATION_TESTMODE
		cout << "Finished displaying the allocation table (CharnesCooper::PrintTable)" << endl;
	#endif
}
*/
