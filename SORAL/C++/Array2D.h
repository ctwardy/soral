/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-03         *
 *                                                                   *
 *********************************************************************/
/** \file Array2D.h
 *  \brief Array2D.h A dynamically-allocated matrix of doubles
 *
 * This file just containst the Array2D class. See the class for
 * more details.
 *
 * <b>Version History</b>
 *
 * \verbatim
 *-----+---------+-----+-----------------------------------------------------
 * Who |   When  | Ver | What
 *-----+---------+-----+-----------------------------------------------------
 * ASO | 17dec02 |  1  | Created
 *-----+---------+-----+-----------------------------------------------------
 * crt |  1apr03 | 1.5 | Comments and prep for privatization.
 *-----+---------+-----+-----------------------------------------------------
 * crt |  4apr03 |  2  | ASO privatized, moved [] to the class level
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

#ifndef _Array2D_h_
#define _Array2D_h_

#include <valarray>

using namespace std;
enum joinType {ROW, COLUMN};

/**** Array2D ***************************************************************/
/// Array2D is a dynamically allocated Matrix of doubles
/**
 * C and C++ 2-dimensional arrays must be dimensioned at compile-time.
 * We need a 2-D array that is allocated dynamically. We could just
 * use double**, but then there are a lot of potential memory leaks,
 * so we've wrapped up the functionality in a small class that gives
 * us nice initialization, constructor/destructor memory management,
 * and the ability to change implementation later.
 *
 * It is designed to be a simple, lightweight implementation that 
 * gives us just the functionality we need, which is basically 
 * construction and destruction for memory-management and 
 * initialization, plus square-bracket[][] indexing.
 * 
 * Generic code created by Michael and adapted by Andre
 * both on 19/12/02 after phone and e-mail communication.
 * * Thank you Michael :) *
 *
 *
 * Author : Michael Eldridge and Andre Oboler
 */

class Array2D
{
public:
	Array2D(const int p_rows, const int p_columns);
	Array2D(const int p_rows, const int p_columns, const valarray<double> p_array1D);
	Array2D(const Array2D &p_array2D);
	Array2D(const Array2D& p_base, const Array2D& p_extension, const joinType p_joinTo);
	virtual ~Array2D();
	void print(void) const;
	double* const &operator[](int index);
	double* const &operator[](int index) const;
	double operator=(int index); // disable the built-in assignment operator.

	const int getNumColumns() const
	{
		return numColumns;
	}
	
	const int getNumRows() const
	{
		return numRows;
	}

// Data members
public:
private:
	/// The values of the matrix. Access as array2D[row][column]
	double **value;

	/// The number of rows in the matrix
	const int numRows;
	/// The number of columns in the matrix
	const int numColumns;


};
#endif
