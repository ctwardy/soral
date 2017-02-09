/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file Array2D.h
 *  \brief Array2D.h A dynamic matrix of doubles
 * 
 *
 * This object is a container for a dynamically created 2D array of doubles
 * It's destructor cleans up the dynamically created memory.
 *
 * <b><u>Version History</u></b>
 *
 * \verbatim
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What                                                
 *-----+----------+-----+-----------------------------------------------------
 * ASO | 17/12/02 |  1  | Created                                             
 *----------------------------------------------------------------------------
 * \endverbatim
 */

/***********************************************************************************/
/// A dynamically allocated Matrix of doubles
/**
 * Array2D:
 *
 * This class encapsulates a dynamically allocated 2D array.
 * Generic code created by Michael and adapted for SAR by Andre
 * both on 19/12/02 after phone and e-mail communication.
 * * Thank you Michael :) *
 *
 *
 * Author : Michael Eldridge and Andre Oboler 
 * 
 */

#ifndef _Array2D_h_
#define _Array2D_h_

class Array2D  
{
public:	
	Array2D(const int rows, const int columns);		
	Array2D(const int rows, const int columns, const double* array1D);
	//set(const int rows, const int columns, const double* array1D);
	virtual ~Array2D();	
	void print(void);

public:
	/// The number of rows in the matrix
	const int numRows;
	/// The number of columns in the matrix
	const int numColumns;
	/// The values of the matrix. Access as myArray2d.value[row][column]
	double **value;
};
#endif
