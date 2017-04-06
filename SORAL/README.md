Installation Notes for SORAL library
====================================


The SORAL library is written in C++ and the ports for Python and Node are generated from that using SWIG.

Dependencies: 
-------------

### Linux

 * python-dev: apt-get install python-dev
 * swig 3: apt-get install swig
 * node-gyp: apt-get install node-gyp
 
### MacOS: 

 * Anaconda Python: see https://www.continuum.io/why-anaconda
 * Swig: see http://macappstore.org/swig/
 * node-gyp: sudo npm install -g node-gyp
 
### Generated Files (do not hand edit)

These files are made by swig via Makefile and should not be hand edited:

 * python/soral.py
 * python/soral_wrap.cpp
 
You will need python_dev or equivalent package for your OS.





