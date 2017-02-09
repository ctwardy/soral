/********************************************************************* 
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *         
 *                                                                   *
 *********************************************************************/
/** \file Array2D.cpp
 *  \brief Array2D.cpp is a container for dynamically created matrix of doubles
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

#include <iostream>
#include "Array2D.h"
#include "memory.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/// Construct an empty array of size row x column
Array2D::Array2D(const int rows, const int columns) 
:			numRows(rows),
			numColumns(columns),
			value(new double *[rows])
	{
		for (int i = 0; i < rows; i++)
		{
			value[i] = new double[columns];
			for (int j = 0; j < columns; j++)
				value[i][j] = 0;
		}			
	}

/// Construct an empty array of size row x column and fill with the value in the array passed in
Array2D::Array2D(const int rows, const int columns, const double* array1D) 
:			numRows(rows),
			numColumns(columns),
			value(new double *[rows])
	{
		for (int i = 0; i < rows; i++)
		{
			value[i] = new double[columns];
			for (int j = 0; j < columns; j++)
				value[i][j] = array1D[i*columns+j];
		}			
	}

/// Reclaims all memory in the 2D array
Array2D::~Array2D() 
{
	for (int i = 0; i < numRows; i++)
	{
		delete [] value[i];
	}

	delete [] value;
}

/*
ASO 17/12/02 - Might be useful later on.
void Array2D::set(const int rows, const int columns, const double* array1D) 
{
	value=new int *[rows];
	numRows=rows;
	numColumns=columns;

	for (int i = 0; i < rows; i++)
	{
		value[i] = new int[columns];
		for (int j = 0; j < columns; j++)
			value[i][j] = array1D[i*columns+j];
	}			
}
*/

void Array2D::print(void)
{
	int i,j;

	cout << "\n";
	for(i=0; i<(4*numColumns); i++)
	{
		cout << "---";
	}
	cout << "-";

	for(i=0; i<numRows; i++)
	{
		for(j=0; j<numColumns; j++)
		{
			cout << "|";
			printf("%3f",value[i][j]);
		}
		cout << "|\n";
		for(j=0; j<(4*numColumns); j++)
		{
			cout << "---";
		}
		cout << "-\n";
	}
}
