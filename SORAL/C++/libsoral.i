/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-17         *
 *                                                                   *
 *********************************************************************/
/** \file libsoral.i
 *  \brief libsoral.i defines how SWIG should create libsoral interfaces
 *  for interpreted languages.
 */


/* Surpressed warnings:
 *
 * 383 = operator++ ignored. Python doesn't have this operator and the C++
 *       lib uses it in its incrementor classes. I've simply wrapped the ++
 *       calls with another function named increment()
 */

%module soral
%rename(printSelf) print;
#pragma SWIG nowarn=383
%{
#include "Allocatn.h"
#include "containr.h"
#include "Alloc-CC.h"
#include "Array2D.h"
%}


%include "carrays.i"
%array_class(double, doubleArray);

/* Special typemap for initializing valarray<double> parameters */
/*%include "typemaps.i"
%typemap(in) const valarray<double> (valarray<double> temp($1_dim0)) { 
    int i;
    if (!PySequence_Check($input)) { 
        PyErr_SetString(PyExc_ValueError, "Expected a sequence"); 
        SWIG_fail;
    }
    if (PySequence_Length($input) != $1_dim0) {
        PyErr_SetString(PyExc_ValueError, "Size mismatch. Expected $1_dim0 elements");
        SWIG_fail; 
    }
    for (i = 0; i < $1_dim0; i++) {
        PyObject *o = PySequence_GetItem($input, i); 
        if (PyNumber_Check(o)) {
            temp[i] = (double) PyFloat_AsDouble(o); 
        } else {
            PyErr_SetString(PyExc_ValueError, "Sequence elements must be numbers");
            SWIG_fail; 
        }
    }
    $1 = temp; 
}*/


%include "Allocatn.h"
%include "containr.h"
%include "Alloc-CC.h"
%include "Array2D.h"

