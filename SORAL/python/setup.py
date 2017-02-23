#!/usr/bin/env python

"""
setup.py file for SWIG soral
"""

from distutils.core import setup, Extension


soral_module = Extension('_soral',
	sources=['soral_wrap.cpp'],
	include_dirs=['../C++/'],
	library_dirs=['../C++/'],
	libraries=['Soral']
	)

setup (name = 'soral',
	version = '0.1',
	author      = "SWIG Docs",
	description = """Simple swig soral from docs""",
	ext_modules = [soral_module],
	py_modules = ["soral"],
	)

