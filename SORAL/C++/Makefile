# crt 18Feb03 This is the cleaned-up simplified Makefile for SORAL
# It doesn't build the test programs like the old one did, so the old one
# is still around in Makefile.old. It has a lot of good ideas.
#
# I've added a line to build a library libsoral.a under *nix.
#
# I've removed lines for testing programs but left lines for TESTMODE
# versions of these files. But I haven't checked that TESTMODE calls
# work. Mostly I just "make". 
#
#
# ASO 18feb03 - Added TestBed to what Charles had.
# ASO 19feb03 - Added userDef to the makefile
# crt 06mar03 - Alphabetized .o listing. 
#               Added Alloc-W.o entry. (?!) How was it compiling before? (?!)
#               Removed extraneous mentions of .h files. 
#               They're included by the .cpp!
# crt 19apr03 - Added "make test" to compile exec in testmode.
# crt 01may03 - Added "make sample" to make the sample prog. Modified so
#               you can make both exec and sample.

OBJS = Allocatn.o Array2D.o Alloc-CC.o Alloc-W.o userDef.o itr_area.o itr_activ.o itr_res.o con_area.o con_activ.o con_res.o 
TB1  = TestBed.o
S1   = sample.o
CPPFLAGS=-fPIC


TESTOBJS = AllocatnTESTMODE.o Array2DTESTMODE.o Alloc-CCTESTMODE.o Alloc-WTESTMODE.o userDefTESTMODE.o itr_areaTESTMODE.o itr_activTESTMODE.o itr_resTESTMODE.o con_areaTESTMODE.o con_activTESTMODE.o con_resTESTMODE.o
TB2      = TestBedTESTMODE.o
S2       = sampleTESTMODE.o

OS       := $(shell uname -s)

libsoral.a: $(OBJS)
ifeq ($(OS),"Windows*")
	echo "Don't know how to make a library on Windows yet."
else
	echo "Assuming this is *nix. Building libsoral.a"
	ar -r libSoral.a $(OBJS)
endif

python: ../python ../python/soral_wrap.cpp ../python/_soral.so

../python/soral_wrap.cpp: *.h libsoral.i
	swig -c++ -python -outdir ../python -o ../python/soral_wrap.cpp libsoral.i

../python/_soral.so: ../python/setup.py libSoral.a ../python/soral_wrap.cpp 
	(cd ../python && python setup.py build_ext --inplace)

# To use the library:  g++ mycode.cc -o mycode -lSoral
# If the library isn't in the current dir (or path), you'll need to 
# use -L and -I to specify libpath and includepath for Soral.
#
# Of course, you'll need to mention the relevant header files
# in your code. Hopefully only Allocatn.h and the .h file of
# any algorithm you use.

libinstall:
	echo "libinstall should put libsoral.a and *.h in the right places"
	echo "But right now it does nothing."

clean:
	rm -f $(OBJS) $(TB1) $(S1) libsoral.a
	rm -f $(TESTOBJS) $(TB2) $(S2)

exec: $(OBJS) $(TB1)
	ar -r libSoral.a $(OBJS)
	g++ $(CPPFLAGS) -o SORALtestBed $(OBJS) $(TB1)

test: $(TESTOBJS) $(TB2)
	ar -r libSoral.a $(TESTOBJS)
	g++ $(CPPFLAGS) -o SORALtestBed $(TESTOBJS) $(TB2)

sample: $(OBJS) $(S1)
	ar -r libSoral.a $(OBJS)
	g++ $(CPPFLAGS) -o sample $(OBJS) $(S1)

#-----------------------


Alloc-CC.o: Alloc-CC.cpp 
	g++ $(CPPFLAGS) -c Alloc-CC.cpp

Alloc-CCTESTMODE.o: Alloc-CC.cpp 
	g++ $(CPPFLAGS) -o Alloc-CCTESTMODE.o -c Alloc-CC.cpp -D _ALLOCATION_TESTMODE

Alloc-W.o: Alloc-W.cpp 
	g++ $(CPPFLAGS) -c Alloc-W.cpp

Alloc-WTESTMODE.o: Alloc-W.cpp 
	g++ $(CPPFLAGS) -o Alloc-WTESTMODE.o -c Alloc-W.cpp -D _ALLOCATION_TESTMODE


Allocatn.o: Allocatn.cpp 
	g++ $(CPPFLAGS) -c Allocatn.cpp

AllocatnTESTMODE.o: Allocatn.cpp 
	g++ $(CPPFLAGS) -o AllocatnTESTMODE.o -c Allocatn.cpp -D _ALLOCATION_TESTMODE


Array2D.o: Array2D.cpp 
	g++ $(CPPFLAGS) -c Array2D.cpp

Array2DTESTMODE.o: Array2D.cpp 
	g++ $(CPPFLAGS) -o Array2DTESTMODE.o -c Array2D.cpp -D _ALLOCATION_TESTMODE



CC-test.o: CC-test.cpp 
	g++ $(CPPFLAGS) -c CC-test.cpp -D _ALLOCATION_TESTMODE

CC-testTESTMODE.o: CC-test.cpp 
	g++ $(CPPFLAGS) -o CC-testTESTMODE.o -c CC-test.cpp -D _ALLOCATION_TESTMODE


con_area.o: con_area.cpp 
	g++ $(CPPFLAGS) -c con_area.cpp

con_areaTESTMODE.o: con_area.cpp
	g++ $(CPPFLAGS) -o con_areaTESTMODE.o -c con_area.cpp -D _ALLOCATION_TESTMODE


con_activ.o: con_activ.cpp 
	g++ $(CPPFLAGS) -c con_activ.cpp

con_activTESTMODE.o: con_activ.cpp 
	g++ $(CPPFLAGS) -o con_activTESTMODE.o -c con_activ.cpp -D _ALLOCATION_TESTMODE


con_res.o: con_res.cpp 
	g++ $(CPPFLAGS) -c con_res.cpp

con_resTESTMODE.o: con_res.cpp 
	g++ $(CPPFLAGS) -o con_resTESTMODE.o -c con_res.cpp -D _ALLOCATION_TESTMODE



itr_area.o: itr_area.cpp 
	g++ $(CPPFLAGS) -c itr_area.cpp

itr_areaTESTMODE.o: itr_area.cpp 
	g++ $(CPPFLAGS) -o itr_areaTESTMODE.o -c itr_area.cpp -D _ALLOCATION_TESTMODE



itr_activ.o: itr_activ.cpp 
	g++ $(CPPFLAGS) -c itr_activ.cpp

itr_activTESTMODE.o: itr_activ.cpp 
	g++ $(CPPFLAGS) -o itr_activTESTMODE.o -c itr_activ.cpp -D _ALLOCATION_TESTMODE



itr_res.o: itr_res.cpp 
	g++ $(CPPFLAGS) -c itr_res.cpp

itr_resTESTMODE.o: itr_res.cpp 
	g++ $(CPPFLAGS) -o itr_resTESTMODE.o -c itr_res.cpp -D _ALLOCATION_TESTMODE

sample.o: sample.cpp
	g++ $(CPPFLAGS) -c sample.cpp

userDef.o: userDef.cpp 
	g++ $(CPPFLAGS) -c userDef.cpp

userDefTESTMODE.o: userDef.cpp
	g++ $(CPPFLAGS) -o userDefTESTMODE.o -c userDef.cpp -D _ALLOCATION_TESTMODE


TestBed.o: TestBed.cpp
	g++ $(CPPFLAGS) -c TestBed.cpp
TestBedTESTMODE.o: 
	g++ $(CPPFLAGS) -o TestBedTESTMODE.o -c TestBed.cpp -D _ALLOCATION_TESTMODE





