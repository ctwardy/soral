# SORAL Makefile
#
# ChangeLog (Oldest First)
# -------------------------
# 
# 2003-02-18 crt - "cleaned-up simplified Makefile for SORAL"
#   * Removed lines for testing programs, but kept for TESTMODE versions.
#   * Old version kept around as Makefile.old. "It has a lot of good ideas."
#   * Added target libsoral.a under *nix. (The actual *library*.)
# 2003-02-18 ASO - Added TestBed to what Charles had.
# 2003-02-19 ASO - Added userDef to the makefile
# 2003-03-06 crt - Alphabetized .o listing. Added Alloc-W.o. (How was it working b4?)
# 2003-04-19 crt - Added "make test" to compile exec in testmode.
# 2003-05-01 crt - Added "make sample" to make the sample prog.
#   * Modified so you can make both exec and sample.
# ...
# 2017-01 - Heartfelt apps hired to refresh SORAL from 2003-era snapshots
# 2017-04: ...
# 


OBJS = Allocatn.o Array2D.o Alloc-CC.o Alloc-W.o userDef.o itr_area.o itr_activ.o itr_res.o con_area.o con_activ.o con_res.o 
TB1  = TestBed.o
S1   = sample.o
CPP = g++
# CPPFLAGS=-fPIC
export MACOSX_DEPLOYMENT_TARGET=10.12

OS := $(shell uname)
ifeq ($(OS),Darwin)
	# MacOS commands 
	USE_OSX_SDK = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
	export CFLAGS=-fPIC --sysroot=$(USE_OSX_SDK)
	export CPPFLAGS=-fPIC --sysroot=$(USE_OSX_SDK) 
	export LDFLAGS=-L$(USE_OSX_SDK)/usr/lib
else
	# Linux
	export CFLAGS=-fPIC  
	export CPPFLAGS=-fPIC 
endif


# You may need to add your V8 version here; see https://nodejs.org/en/download/releases/ for a table of values
NODE_VERSION_RAW := $(strip $(shell node --version) )
NODE_VERSION := $(subst v,,$(NODE_VERSION_RAW))

NODE_VER_COMP_7 = $(strip $(shell ./vercomp.sh $(NODE_VERSION) 7.0))

NODE_V8_VERSION=
ifeq ($(strip $(NODE_VERSION)),7.4.0) 
NODE_V8_VERSION=-DV8_VERSION=0x050450 
endif
ifeq ($(strip $(NODE_VERSION)),5.12.0) 
NODE_V8_VERSION=-DV8_VERSION=0x040685 
endif

# Check NODE version
# $(info NODE_VER_COMP_7 is $(NODE_VER_COMP_7) )


TESTOBJS = AllocatnTESTMODE.o Array2DTESTMODE.o Alloc-CCTESTMODE.o Alloc-WTESTMODE.o userDefTESTMODE.o itr_areaTESTMODE.o itr_activTESTMODE.o itr_resTESTMODE.o con_areaTESTMODE.o con_activTESTMODE.o con_resTESTMODE.o
TB2	  = TestBedTESTMODE.o
S2	   = sampleTESTMODE.o

# Wants swig 3 or higher
SWIG = swig

OS	   := $(shell uname -s)

all: CPP python node

CPP: libsoral.a

libsoral.a: $(OBJS)
ifeq ($(OS),"Windows*")
	echo "Don't know how to make a library on Windows yet."
else
	echo "Assuming this is *nix. Building libsoral.a"
	ar -r libSoral.a $(OBJS)
endif

python: libsoral.a ../python ../python/soral_wrap.cpp ../python/_soral.so

../python/soral_wrap.cpp: *.h libsoral.i
	$(SWIG) -c++ -python -outdir ../python -o ../python/soral_wrap.cpp libsoral.i

../python/_soral.so: ../python/setup.py libSoral.a ../python/soral_wrap.cpp 
	( cd ../python && python setup.py build_ext --inplace )

node: nodeVersionCheck libsoral.a ../node/soral_wrap.cpp

../node/soral_wrap.cpp: *.h libsoral.i
	@echo ""
	@echo "** Detected Node version: $(NODE_VERSION)"
	@echo "** NODE_V8_VERSION flag: $(NODE_V8_VERSION)"
	@echo "** Check the NODE_V8_VERSION setting in the Makefile if you have trouble compiling"
	@echo "** If you don't need Node, just do make CPP python"
	@echo ""
	$(SWIG) -c++ -javascript -v8 $(NODE_V8_VERSION) -outdir ../node -o ../node/soral_wrap_raw.cpp libsoral.i
	cat ../node/soral_wrap_headers.cpp ../node/soral_wrap_raw.cpp > ../node/soral_wrap.cpp
	( cd ../node && node-gyp clean && node-gyp configure   && node-gyp build   )


runtests: runtests.cpp
	$(CPP) $(CPPFLAGS) runtests.cpp -L. -lSoral -o runtests


# To use the library:  $(CPP) mycode.cc -o mycode -lSoral
# If the library isn't in the current dir (or path), you'll need to 
# use -L and -I to specify libpath and includepath for Soral.
#
# Of course, you'll need to mention the relevant header files
# in your code. Hopefully only Allocatn.h and the .h file of
# any algorithm you use.

libinstall:
	echo "libinstall should put libsoral.a and *.h in the right places"
	echo "But right now it does nothing."

clean: clean-CPP clean-python clean-node

clean-CPP:
	rm -f $(OBJS) $(TB1) $(S1) libsoral.a
	rm -f $(TESTOBJS) $(TB2) $(S2)

clean-python:
	rm -rf ../python/build/temp*
	rm -f ../python/soral.pyc
	rm -f ../python/soral.py
	rm -f ../python/__pycache__/*
	rm -f ../python/_soral.so
	rm -f ../python/soral_wrap.cpp

clean-node:
	rm -f ../node/build/Release/soral.node
	rm -f ../node/build/Release/obj.target/soral.node
	rm -f ../node/build/Release/obj.target/soral/soral_wrap.o
	rm -f ../node/soral_wrap_raw.cpp
	rm -f ../node/soral_wrap.cpp

exec: libsoral.a $(TB1)
	$(CPP) $(CPPFLAGS) -o SORALtestBed $(OBJS) $(TB1)

test: $(TESTOBJS) $(TB2)
	ar -r libSoral.a $(TESTOBJS)
	$(CPP) $(CPPFLAGS) -o SORALtestBed $(TESTOBJS) $(TB2)

sample: libsoral.a $(S1)
	$(CPP) $(CPPFLAGS) -o sample $(OBJS) $(S1)

#-----------------------


Alloc-CC.o: Alloc-CC.cpp 
	$(CPP) $(CPPFLAGS) -c Alloc-CC.cpp

Alloc-CCTESTMODE.o: Alloc-CC.cpp 
	$(CPP) $(CPPFLAGS) -o Alloc-CCTESTMODE.o -c Alloc-CC.cpp -D _ALLOCATION_TESTMODE

Alloc-W.o: Alloc-W.cpp 
	$(CPP) $(CPPFLAGS) -c Alloc-W.cpp

Alloc-WTESTMODE.o: Alloc-W.cpp 
	$(CPP) $(CPPFLAGS) -o Alloc-WTESTMODE.o -c Alloc-W.cpp -D _ALLOCATION_TESTMODE


Allocatn.o: Allocatn.cpp 
	$(CPP) $(CPPFLAGS) -c Allocatn.cpp

AllocatnTESTMODE.o: Allocatn.cpp 
	$(CPP) $(CPPFLAGS) -o AllocatnTESTMODE.o -c Allocatn.cpp -D _ALLOCATION_TESTMODE


Array2D.o: Array2D.cpp 
	$(CPP) $(CPPFLAGS) -c Array2D.cpp

Array2DTESTMODE.o: Array2D.cpp 
	$(CPP) $(CPPFLAGS) -o Array2DTESTMODE.o -c Array2D.cpp -D _ALLOCATION_TESTMODE



CC-test.o: CC-test.cpp 
	$(CPP) $(CPPFLAGS) -c CC-test.cpp -D _ALLOCATION_TESTMODE

CC-testTESTMODE.o: CC-test.cpp 
	$(CPP) $(CPPFLAGS) -o CC-testTESTMODE.o -c CC-test.cpp -D _ALLOCATION_TESTMODE


con_area.o: con_area.cpp 
	$(CPP) $(CPPFLAGS) -c con_area.cpp

con_areaTESTMODE.o: con_area.cpp
	$(CPP) $(CPPFLAGS) -o con_areaTESTMODE.o -c con_area.cpp -D _ALLOCATION_TESTMODE


con_activ.o: con_activ.cpp 
	$(CPP) $(CPPFLAGS) -c con_activ.cpp

con_activTESTMODE.o: con_activ.cpp 
	$(CPP) $(CPPFLAGS) -o con_activTESTMODE.o -c con_activ.cpp -D _ALLOCATION_TESTMODE


con_res.o: con_res.cpp 
	$(CPP) $(CPPFLAGS) -c con_res.cpp

con_resTESTMODE.o: con_res.cpp 
	$(CPP) $(CPPFLAGS) -o con_resTESTMODE.o -c con_res.cpp -D _ALLOCATION_TESTMODE



itr_area.o: itr_area.cpp 
	$(CPP) $(CPPFLAGS) -c itr_area.cpp

itr_areaTESTMODE.o: itr_area.cpp 
	$(CPP) $(CPPFLAGS) -o itr_areaTESTMODE.o -c itr_area.cpp -D _ALLOCATION_TESTMODE



itr_activ.o: itr_activ.cpp 
	$(CPP) $(CPPFLAGS) -c itr_activ.cpp

itr_activTESTMODE.o: itr_activ.cpp 
	$(CPP) $(CPPFLAGS) -o itr_activTESTMODE.o -c itr_activ.cpp -D _ALLOCATION_TESTMODE



itr_res.o: itr_res.cpp 
	$(CPP) $(CPPFLAGS) -c itr_res.cpp

itr_resTESTMODE.o: itr_res.cpp 
	$(CPP) $(CPPFLAGS) -o itr_resTESTMODE.o -c itr_res.cpp -D _ALLOCATION_TESTMODE

sample.o: sample.cpp
	$(CPP) $(CPPFLAGS) -c sample.cpp

userDef.o: userDef.cpp 
	$(CPP) $(CPPFLAGS) -c userDef.cpp

userDefTESTMODE.o: userDef.cpp
	$(CPP) $(CPPFLAGS) -o userDefTESTMODE.o -c userDef.cpp -D _ALLOCATION_TESTMODE


TestBed.o: TestBed.cpp
	$(CPP) $(CPPFLAGS) -c TestBed.cpp
TestBedTESTMODE.o: 
	$(CPP) $(CPPFLAGS) -o TestBedTESTMODE.o -c TestBed.cpp -D _ALLOCATION_TESTMODE






nodeVersionCheck: 
ifeq ($(NODE_VER_COMP_7),>)
	@echo "YOUR NODE VERSION IS $(NODE_VERSION_RAW) / $(NODE_VERSION)"
	@echo "Fun fact: At the time of writing swig doesn't support Node v7 and up."
	@echo "Watch https://github.com/swig/swig/issues/804 for progress in supporting Node v7,"
	@echo "or use an older version of Node"
	@echo "Unsupported NODE version"
	@false
else
	@true	
endif



