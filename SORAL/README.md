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
 * node: apt-get install node
 * node-gyp: apt-get install node-gyp
 
### MacOS: 

 * Swig: see http://macappstore.org/swig/
 * Anaconda Python: see https://www.continuum.io/why-anaconda
   - Other Python can work, but this is what we used.
 * Node.js: https://nodejs.org/en/
 * node: sudo npm install -g node
 * node-gyp: sudo npm install -g node-gyp
 

### Makefile Tweaks

You may need to know which Node V8 version you're using. This is not simply the Node version but the V8 system under Node.
Easiest way to check is:
    $ sudo npm install -g node-v8-version
    $ v8v -s 
or check the table at
    https://nodejs.org/en/download/releases/
    
    
 
 
### Generated Files (do not hand edit)

These files are made by swig via Makefile and should not be hand edited:

 * python/soral.py
 * python/soral\_wrap.cpp
 
You will need python_dev or equivalent package for your OS.





