/*********************************************************************
 *      SARBayes OPTIMAL RESOURCE ALLOCATION LIBRARY 2001-17         *
 *                                                                   *
 *********************************************************************/
/** \file libsoral.i
 *  \brief libsoral.i defines how SWIG should create libsoral interfaces
 *  for interpreted languages.
 */


%module soral
%{
#include "Allocatn.h"
#include "containr.h"
#include "Alloc-CC.h"
%}
