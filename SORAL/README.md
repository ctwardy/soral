Installation Notes for SORAL library
====================================

The SORAL library is written in C++. It has been tested with
gcc on LInux and gcc/clang Mac.  [Windows?]

SORAL includes SWIG profiles for generating Python and Node
wrappers.

It uses Doxygen to generate documentation.

Dependencies:
-------------

C++: `make` and `gcc` or compatible C++ compiler.

In order to run `make all` you will need:
 * doxygen 
 * SWIG
 * Python
 * Node

### Linux (Debian variants)

 * doxygen: apt-get install doxygen
 * swig 3: apt-get install swig
 * python-dev: apt-get install python-dev
   - Or a distribution like Anaconda Python
 * node-gyp: apt-get install node-gyp
 
### MacOS: 

 * Swig: see http://macappstore.org/swig/
 * Anaconda Python: see https://www.continuum.io/why-anaconda
   - Other Python can work, but this is what we used.
 * Node.js: https://nodejs.org/en/
 * node-gyp: sudo npm install -g node-gyp
 
### Generated Files (do not hand edit)

These files are made by swig via Makefile and should not be hand edited:

 * python/soral.py
 * python/soral\_wrap.cpp
 
You will need python_dev or equivalent package for your OS.





