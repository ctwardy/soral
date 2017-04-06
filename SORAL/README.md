Installation Notes for SORAL library
====================================


The SORAL library is written in C++ and the ports for Python and Node are generated from that using SWIG.

Dependencies: 
-------------

### Ubuntu

 * apt-get install python-dev
 * apt-get install swig
 
On Mac: 

 * Anaconda Python; see https://www.continuum.io/why-anaconda
 * Swig; see http://macappstore.org/swig/
 
 
### Generated Files (do not hand edit)

These files are made by swig via Makefile and should not be hand edited:

 * python/soral.py
 * python/soral_wrap.cpp
 
You will need python_dev or equivalent package for your OS.





