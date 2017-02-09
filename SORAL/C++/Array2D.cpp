// $Id: Array2D.cpp,v 1.10 2003/04/19 04:03:27 ctwardy Exp $
/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file Array2D.cpp
 *  \brief Array2D.cpp is a dynamically-allocated matrix of doubles
 *
 * This object is a container for a dynamically-allocated 2D array of doubles.
 * For more general information, see the header file.
 * 
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+---------+-----+-----------------------------------------------------
 * Who |   When  | Ver | What
 *-----+---------+-----+-----------------------------------------------------
 * ASO | 17dec02 |  1  | Created
 *-----+---------+-----+-----------------------------------------------------
 * ASO | 30mar03 |  2  | added a copy constructor
 *-----+---------+-----+-----------------------------------------------------
 * crt |  1apr03 | 2.5 | Filled in comments.
 *-----+---------+-----+-----------------------------------------------------
 * crt |  3apr03 |  3  | ASO added []. Just tweaked and cleaned.
 *-----+---------+-----+-----------------------------------------------------
 * crt | 18apr03 |  4  | Fixed bugs in copy & extension constructors.
 *-----+---------+-----+-----------------------------------------------------
 * \endverbatim
 */

//===========================================================================//
// Written by Andre Oboler                                http://sarbayes.org//
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

#include <iostream>
#include "Array2D.h"
#include "memory.h"
#include <assert.h>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction  (remove this comment or chg all others)
//////////////////////////////////////////////////////////////////////

/**** Array2D() constructor ************************************************/
/// Construct an empty 2D array of size p_rows x p_columns
/**
 * Constructor takes the dimensions of the matrix and constructs
 * a matrix with all values initialized to 0.
 */
Array2D::Array2D(const int p_rows, const int p_columns)
:			numRows(p_rows),
			numColumns(p_columns),
			value(new double *[p_rows])
	{
		for (int i = 0; i < p_rows; i++)
		{
			value[i] = new double[p_columns];
			for (int j = 0; j < p_columns; j++)
				value[i][j] = 0;
		}
	}

/**** Array2D() constructor *************************************************/
/// Construct an array of size p_rows x p_columns, filled with passed values.
/**
 * Creates a new array of size row x column, filled with the values
 * in the supplied built-in array <em>array1D</em>.
 * 
 * <em>array1D</em> must be of size [rows*columns]. It is converted
 * to the 2D array as: value[i][j] = array1D[i*columns + j]
 *
 * At the moment, it allocates a new double** and then fills it value
 * by value. That may change if we change our underlying implementation 
 * to valarrays rather than double**.
 *
 * \todo Change assertion to proper exception.
 *
 */
Array2D::Array2D(const int p_rows, 
					  const int p_columns, 
					  const valarray<double> p_array1D)
:			numRows(p_rows),
			numColumns(p_columns),
			value(new double *[p_rows])
	{
	    assert (p_array1D.size() == p_rows * p_columns);

		for (int i = 0; i < p_rows; i++)
		{
			value[i] = new double[p_columns];
			for (int j = 0; j < p_columns; j++)
				value[i][j] = p_array1D[i * p_columns + j];
		}
	}

/**** Array2D() extension constructor ****************************************/
/// The constructor for appending one Array2D to another
/**
 * This constructor makes a new Array2D out of 2 old ones.
 * The second Array2D is appended either below or to the
 * right of the first, depending on the value of p_joinTo.
 * p_joinTo can take values ROW or COLUMN. When ROW, the 
 * second array is appended below the first. When COLUMN,
 * the second array is appended to the right of the first.
 * 
 * If the arrays do not share an edge of the same size, an exception
 * should be thrown (not yet implemented).
 *
 * \todo Throw an exception if arrays are the wrong size.
 */
Array2D::Array2D(const Array2D& p_base, const Array2D& p_extension, const joinType p_joinTo)
:			numRows(p_base.numRows),
			numColumns(p_base.numColumns),
			value(new double *[p_base.numRows])
{
	int i, j, k;	

	// check if ok to construct
		if (p_joinTo == ROW)
		{			
		   // if the number of columns match			
			if (p_base.getNumColumns() == p_extension.getNumColumns()) 
			{				
			   // The old number of rows is too few. Delete it, and
			   // create the correct number of rows.
				delete[] value; 
				value=new double *[p_base.getNumRows() + p_extension.getNumRows()];

				// Copy values across
				for(i=0; i< p_base.getNumRows(); i++)
				{
					value[i] = new double[p_base.getNumColumns()];
					for(k=0; k< p_base.getNumColumns(); k++)
					{
						value[i][k]=p_base[i][k];						
					}
				}
					
				for(j=0; j< p_extension.getNumRows(); j++)
				{
					value[i+j] = new double[p_base.getNumColumns()];
					for(k=0; k< p_extension.getNumColumns(); k++)
					{
						value[i+j][k]=p_extension[j][k];
					}					
				}
			}
			else // number of columns didn't match
			{
				throw "Can't append to bottom: array2Ds have diff # of columns";
			}
		}
		else if (p_joinTo == COLUMN)
		{
		   // if the number of rows match			
			if (p_base.getNumRows() == p_extension.getNumRows()) 
			{				
				// copy values across [a][0..i] and then [a][i+1 .. i+j] to [z]...
				for(i=0; i< p_base.getNumRows(); i++)
				{
					value[i] = new double[p_base.getNumColumns() + p_extension.getNumColumns()];
					for(j=0; j< p_base.getNumColumns(); j++)
					{
						value[i][j]=p_base[i][j];
					}
					for(k=0; k< p_extension.getNumColumns(); k++)
					{
					  value[i][k+j] = p_extension[i][k];
					}
				}
			}
			else
			{
				throw "Can't append to right side: array2Ds have diff. # of rows";
			}
		}
		else
		{
			throw "Invalid joinTo direction";
		}
}

/**** Array2D() copy constructor ********************************************/
/// The Array2D copy constructor
/**
 * Author: ASO
 */
Array2D::Array2D(const Array2D &p_array2D)
:			numRows(p_array2D.numRows),
			numColumns(p_array2D.numColumns),
			value(new double *[p_array2D.numRows])
{	
	for (int i = 0; i < numRows;i++)
	{
		value[i] = new double[numColumns];
		for (int j = 0; j < numColumns; j++)
		{
			value[i][j] = p_array2D.value[i][j];
		}
	}
}

/**** ~Array2D() *************************************************************/
/// Reclaims all memory in the 2D array
/**
 * This destructor reclaims memory from any allocated pointers.
 * If we switch to valarrays, this will be unnecessary.
 */
Array2D::~Array2D()
{
	for (int i = 0; i < numRows; i++)
	{
		delete [] value[i];
	}

	delete [] value;
}



/**** operator[] ***********************************************************/
/// The mutable version of the [] operator.
/**
 * Return the 1D array of all column values for the row provided.
 * 
 * This is <b>not</b> meant to be used alone. It is here to provide
 * [][] indexing into the array, by returning a 1D array which
 * provides its own [] operator.
 *
 * This version is invoked on non-const Array2D objects. On such
 * objects, you can assign directly to the indexed value.
 * Thus <tt>myArray[i][j] = 3.5</tt> will replace the value at (i,j). 
 *  
 * If you use this alone to get a 1D slice, be aware that we
 * may change the return type if we change implementations. We 
 * only guarantee that the return type will provide its own
 * operator[]. It might be a valarray, a vector, an int[] array....
 *
 * To avoid copying an entire 1D array every time someone uses [][],
 * the current implementation hands you a reference. Obviously that
 * reference is valid only so long as the Array2D still exists.
 * There's no reason for you to hang on to the references from [] or
 * [][] anyway. Since you've got the Array2D object, just [][] again.
 *
 */
double* const &Array2D::operator[](int index)
{
	return value[index];
}

/**** operator[] *********************************************************/
/// The const version of the [] operator.
/**
 * Return the 1D array of all column values for the row provided.
 *
 * As per the mutable version of this operator, but this version
 * is invoked on const Array2D objects. On such objects
 * you won't be able to do an assignment like 
 * <tt>myArray[i][j] = 3.5</tt>, though it is the const-ness of the
 * array which prevents that, not anything in this operator.
 *
 */
double* const &Array2D::operator[](int index) const
{
	return value[index];
}

/**** print() ***************************************************************/
/// Prints an Array2D
/**
 * Loops through the Array2D giving a reasonably nice printout.
 */
void Array2D::print(void) const
{
	int i,j;

	cout << "\n";
	for(i=0; i<(4*numColumns); i++)
	{
		cout << "---";
	}
	cout << "-\n";

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

