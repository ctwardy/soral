#Various test programs for Allocation class

Itr-test: Allocatn.o Array2D.o Alloc-CC.o Alloc-W.o cc-alloc.o itr_area.o itr_assn.o itr_res.o con_area.o con_assn.o con_res.o testing.o
	g++ -o SORAL Allocatn.o Array2D.o Alloc-CC.o Alloc-W.o cc-alloc.o itr_area.o itr_assn.o itr_res.o containr.o con_area.o con_assn.o con_res.o testing.o

Itr-testTESTMODE: Itr-testTESTMODE.o AllocatnTESTMODE.o Array2DTESTMODE.o Alloc-CCTESTMODE.o cc-allocTESTMODE.o itrTESTMODE.o itr_areaTESTMODE.o itr_assnTESTMODE.o itr_resTESTMODE.o containrTESTMODE.o con_areaTESTMODE.o con_assnTESTMODE.o con_resTESTMODE.o testingTESTMODE.o
	g++ -o Itr-testTESTMODE Itr-testTESTMODE.o AllocatnTESTMODE.o Array2DTESTMODE.o Alloc-CCTESTMODE.o cc-allocTESTMODE.o itrTESTMODE.o itr_areaTESTMODE.o itr_assnTESTMODE.o itr_resTESTMODE.o containrTESTMODE.o con_areaTESTMODE.o con_assnTESTMODE.o con_resTESTMODE.o testingTESTMODE.o


Clc-test: Clc-test.o Allocatn.o Alloc-CC.o cc-alloc.o itr_area.o itr_assn.o itr_res.o containr.o con_area.o con_assn.o con_res.o testing.o
	g++ -o Clc-test Clc-test.o Allocatn.o Alloc-CC.o cc-alloc.o itr_area.o itr_assn.o itr_res.o containr.o con_area.o con_assn.o con_res.o testing.o

Clc-testTESTMODE: Clc-testTESTMODE.o AllocatnTESTMODE.o Alloc-CCTESTMODE.o cc-allocTESTMODE.o itrTESTMODE.o itr_areaTESTMODE.o itr_assnTESTMODE.o itr_resTESTMODE.o containrTESTMODE.o con_areaTESTMODE.o con_assnTESTMODE.o con_resTESTMODE.o testingTESTMODE.o
	g++ -o Clc-testTESTMODE Clc-testTESTMODE.o AllocatnTESTMODE.o Alloc-CCTESTMODE.o cc-allocTESTMODE.o itrTESTMODE.o itr_areaTESTMODE.o itr_assnTESTMODE.o itr_resTESTMODE.o containrTESTMODE.o con_areaTESTMODE.o con_assnTESTMODE.o con_resTESTMODE.o testingTESTMODE.o



Clc-test.o: Clc-test.cpp Allocatn.h testing.h
	g++ -c Clc-test.cpp

Clc-testTESTMODE.o: Clc-test.cpp Allocatn.h testing.h
	g++ -o Clc-testTESTMODE.o -c Clc-test.cpp -D _ALLOCATION_TESTMODE



CC-test: CC-test.o Allocatn.o Alloc-CC.o cc-alloc.o itr_area.o itr_assn.o itr_res.o containr.o con_area.o con_assn.o con_res.o testing.o
	g++ -o CC-test CC-test.o Allocatn.o Alloc-CC.o cc-alloc.o itr_area.o itr_assn.o itr_res.o containr.o con_area.o con_assn.o con_res.o testing.o

CC-testTESTMODE: CC-testTESTMODE.o AllocatnTESTMODE.o Alloc-CCTESTMODE.o cc-allocTESTMODE.o itrTESTMODE.o itr_areaTESTMODE.o itr_assnTESTMODE.o itr_resTESTMODE.o containrTESTMODE.o con_areaTESTMODE.o con_assnTESTMODE.o con_resTESTMODE.o testingTESTMODE.o
	g++ -o CC-testTESTMODE CC-testTESTMODE.o AllocatnTESTMODE.o Alloc-CCTESTMODE.o cc-allocTESTMODE.o itrTESTMODE.o itr_areaTESTMODE.o itr_assnTESTMODE.o itr_resTESTMODE.o containrTESTMODE.o con_areaTESTMODE.o con_assnTESTMODE.o con_resTESTMODE.o testingTESTMODE.o



CC-test.o: CC-test.cpp Allocatn.h testing.h
	g++ -c CC-test.cpp

CC-testTESTMODE.o: CC-test.cpp Allocatn.h testing.h
	g++ -o CC-testTESTMODE.o -c CC-test.cpp -D _ALLOCATION_TESTMODE



Allocatn.o: Allocatn.cpp Allocatn.h containr.h
	g++ -c Allocatn.cpp

AllocatnTESTMODE.o: Allocatn.cpp Allocatn.h containr.h
	g++ -o AllocatnTESTMODE.o -c Allocatn.cpp -D _ALLOCATION_TESTMODE


array2D.o: Array2D.cpp Array2D.h
	g++ -c Array2D.cpp

array2DTESTMODE.o: Array2D.cpp Array2D.h
	g++ -o Array2D.cpp


Alloc-CC.o: Alloc-CC.cpp Allocatn.h
	g++ -c Alloc-CC.cpp

Alloc-CCTESTMODE.o: Alloc-CC.cpp Allocatn.h
	g++ -o Alloc-CCTESTMODE.o -c Alloc-CC.cpp -D _ALLOCATION_TESTMODE



itr.o: itr.cpp Allocatn.h
	g++ -c itr.cpp

itrTESTMODE.o: itr.cpp Allocatn.h
	g++ -o itrTESTMODE.o -c itr.cpp -D _ALLOCATION_TESTMODE



itr_area.o: itr_area.cpp Allocatn.h containr.h
	g++ -c itr_area.cpp

itr_areaTESTMODE.o: itr_area.cpp Allocatn.h containr.h
	g++ -o itr_areaTESTMODE.o -c itr_area.cpp -D _ALLOCATION_TESTMODE



itr_assn.o: itr_assn.cpp Allocatn.h containr.h
	g++ -c itr_assn.cpp

itr_assnTESTMODE.o: itr_assn.cpp Allocatn.h containr.h
	g++ -o itr_assnTESTMODE.o -c itr_assn.cpp -D _ALLOCATION_TESTMODE



itr_res.o: itr_res.cpp Allocatn.h containr.h
	g++ -c itr_res.cpp

itr_resTESTMODE.o: itr_res.cpp Allocatn.h containr.h
	g++ -o itr_resTESTMODE.o -c itr_res.cpp -D _ALLOCATION_TESTMODE



con_area.o: con_area.cpp containr.h
	g++ -c con_area.cpp

con_areaTESTMODE.o: con_area.cpp containr.h
	g++ -o con_areaTESTMODE.o -c con_area.cpp -D _ALLOCATION_TESTMODE



con_assn.o: con_assn.cpp containr.h
	g++ -c con_assn.cpp

con_assnTESTMODE.o: con_assn.cpp containr.h
	g++ -o con_assnTESTMODE.o -c con_assn.cpp -D _ALLOCATION_TESTMODE



con_res.o: con_res.cpp containr.h
	g++ -c con_res.cpp

con_resTESTMODE.o: con_res.cpp containr.h
	g++ -o con_resTESTMODE.o -c con_res.cpp -D _ALLOCATION_TESTMODE



cc-alloc.o: cc-alloc.cpp Allocatn.h
	g++ -c cc-alloc.cpp

cc-allocTESTMODE.o: cc-alloc.cpp Allocatn.h
	g++ -o cc-allocTESTMODE.o -c cc-alloc.cpp -D _ALLOCATION_TESTMODE



testing.o: testing.cpp testing.h
	g++ -c testing.cpp

testingTESTMODE.o: testin
