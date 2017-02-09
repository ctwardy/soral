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
 *---------------------------------------------------------------------
 * GT  | 25/02/02 |  2  | Modifications.  AreaAssignment now
 *     |          |     | encapsulates a resource number rather than an
 *     |          |     | area number, whilst ResourceAssignment now
 *     |          |     | encapsulates an area number rather than a
 *     |          |     | resource number.
 *---------------------------------------------------------------------
 * ASO | 10/12/02 |  3  | Modified. Removed base class "container" and
 *     |          |     | updated "child" classes as needed.
 *---------------------------------------------------------------------
 * crt | 13jan02  | 3.5 | Fixed param names to match encapsulation:
 *     |          |     | ASO had already undone change 2. 
 *     |          |     | AreaAssignment encapsulates an area.
 *     |          |     | ResourceAssignment encapsulates a resource.
 *     |          |     | So they now take p_areaNum and p_resourceNum,
 *     |          |     | respectively. Now matches implementations.
 *---------------------------------------------------------------------
 * \endverbatim
*/


#ifndef _containr_h_
#define _containr_h_

/*****************************************************************************************
 * Container
 *
 * The main container class. This is a pure virtual which provides the common interface
 * required for each of the different container types.
 *
 * Author : Michael Eldridge
 *
 * ASO 10/12/02 - Class removed. The encapsulation of one double that was only needed for
 * two of the three child classes made this abstraction not worth while. A cleaner
 * simpler design was chosen although this does duplicate a few lines of code.
 *
 */

/*
class Container
{
	// Constructors.

	public:
		Container(double p_time);
		virtual ~Container();
	private:
		Container(const Container &p_container);
		Container &operator=(const Container &p_container);

	// Virtual Functions.

	public:
		virtual int getResourceNum(void);
		virtual int getAreaNum(void);

	// Member Functions.

	public:
		double getTime(void);

	// Member variables.

	protected:
		double time;
};
*/

/*********************************************************************************/
/// An assignment giving an area and a time. It must belong to a resource to have meaning.
/**
 * AreaAssignment:
 *
 * An AreaAssignment is a pair of numbers belonging to a resource, giving
 * an area to which that resource has been assigned, and the time
 * for which it has been assigned to that area. A resource can have many 
 * AreaAssignments. Each behaves as a tuple (area, time). 
 *
 * Note : At the moment the iterator will not go off the end of the list.
 *
 * Author : Michael Eldridge
 *
 *
 */

//Gareth Thompson 24-2-2002
//Altered so that an AreaAssignment now encapsulates a RESOURCE NUMBER,
//rather than an AREA NUMBER.
// ASO 10/12/02 - reverted to an area number.
class AreaAssignment // ASO 10/12/02 : public Container
{
	// Constructors.

	public:
		AreaAssignment(int p_areaNum, double p_time);
		~AreaAssignment();
	private:
		AreaAssignment(const AreaAssignment &area_ass);
		AreaAssignment &operator=(const AreaAssignment &p_container);

	// Inherited functions.

	public:		
		int getAreaNum(void);
		//int getResourceNum(void);
		double getTime(void);


	// Member variables.

	private:
		/// The area number part of this tuple
		int areaNum; /**< As this is a copy and not the value in the allocation 
		               *  this value should be immutable. */
		//int resourceNum; // Which resource's assignments are we going through?
		/// The time part of this tuple
		double time; /**< As this is a copy and not the value in the allocation 
					     *  this value should be immutable. */
};

/*****************************************************************************************/
/// An assignment giving a resource and a time. It must belong to some area to have meaning.

/** ResourceAssignment
 *
 * Logically a tuple (resource, time) naming a resource number and a duration
 * for which that resource has been assigned (to some area). An Area can have 
 * many ResourceAssignment, each telling which resource is assigned to it
 * and for how long.
 *
 * Note : At the moment the iterator will not go off the end of the list.
 *
 * Author : Michael Eldridge
 *
 */

//Gareth Thompson 24-2-2002
//Altered so that a ResourceAssignment now encapsulates an AREA NUMBER,
//rather than a RESOURCE NUMBER.

class ResourceAssignment // ASO 10/12/02 : public Container
{

	// Constructors.
	public:
		ResourceAssignment(int p_resourceNum, double p_time);
		~ResourceAssignment();
	private:
		ResourceAssignment(const ResourceAssignment &res_ass);
		ResourceAssignment &operator=(const ResourceAssignment &res_ass);

	// Inherited functions.

	public:
		//int getResourceNum(void);
		int getResourceNum(void);
		double getTime(void);

	// Member variables.

	private:
		/// The resource number part of this touple
		int resourceNum;/**< As this is a copy and not the value in the allocation 
		                  *  this value should be immutable. */

		/// The time part of this touple
		double time;  /**< As this is a copy and not the value in the allocation 
					       *  this value should be immutable. */
};

/*****************************************************************************************
 * ActiveArea()
 *
 * Description: (added ASO 9/12/02) - a list of assigned areas.
 *
 * Note : At the moment the iterator will not go off the end of the list.
 *
 * Author : Michael Eldridge
 * Renamed: ASO 10/12/02
 * Removed: ASO 17/12/02 Silly to have a container for ints.
 *          NOTE: This class may be needed in the future... do NOT delete it.
 *
 */

/*class ActiveArea // ASO 10/12/02 : public Container
{
	// Constructors.

	public:
		ActiveArea(int p_areaNum);
		~ActiveArea();
	private:
		ActiveArea(const ActiveArea &area_ass);
		ActiveArea &operator=(const ActiveArea &area_ass); //ASO 9/12/02 changed from  &container to &area_ass

	// Inherited functions.

	public:
		int getAreaNum(void);


	// Member variables.

	private:
		int areaNum;
};
*/
#endif
