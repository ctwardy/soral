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
%rename(incr) operator++();
#pragma SWIG nowarn=383
%{
#include "Allocatn.h"
#include "containr.h"
#include "Alloc-CC.h"
#include "Alloc-W.h"
#include "Array2D.h"
%}


%include "carrays.i"
%array_class(double, doubleArray);



%include "Allocatn.h"
%include "containr.h"
%include "Alloc-CC.h"
%include "Alloc-W.h"
%include "Array2D.h"

