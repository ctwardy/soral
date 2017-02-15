# simple make file

SORAL_SOURCE_PATH=../SORAL/C++/

OBJS=Allocatn.o Array2D.o Alloc-CC.o Alloc-W.o itr_area.o itr_assn.o itr_res.o con_area.o con_assn.o con_res.o testing.o Sandr.o Srchman.o menu.o delay.o InputFil.o Input.o Tokenise.o StripWht.o RSizeStr.o FloatCmp.o Resource.o BigArea.o Areas.o setmode.o Err_mngr.o Output.o ChkType.o DataLimt.o ConToStr.o sru.o

main: $(OBJS)
	g++ -g -o AGMSAR $(OBJS)
	

Sandr.o: Sandr.cpp Srchman.h
	g++ -c Sandr.cpp

tester: tester.o InputFil.o test_inf.o Input.o Tokenise.o StripWht.o RSizeStr.o FloatCmp.o Resource.o sru.o test_res.o Srchman.o test_smn.o BigArea.o Areas.o delay.o Output.o ChkType.o DataLimt.o ConToStr.o Err_mngr.o menu.o
	g++ -o tester tester.o InputFil.o test_inf.o Input.o Tokenise.o StripWht.o RSizeStr.o FloatCmp.o Resource.o sru.o test_res.o Srchman.o test_smn.o BigArea.o Areas.o delay.o Output.o ChkType.o DataLimt.o ConToStr.o Err_mngr.o menu.o

tester.o: tester.cpp InputFil.h Resource.h Assignmt.h global.h
	g++ -c tester.cpp

Srchman.o: Srchman.cpp Srchman.h Resource.h InputFil.h Areas.h DataLimt.h menu.h
	g++ -c Srchman.cpp

test_smn.o: test_smn.cpp Srchman.h global.h
	g++ -c test_smn.cpp

InputFil.o: InputFil.cpp InputFil.h
	g++ -c InputFil.cpp

test_inf.o: test_inf.cpp InputFil.h
	g++ -c test_inf.cpp

Input.o: Input.cpp global.h
	g++ -c Input.cpp

Tokenise.o: Tokenise.cpp global.h
	g++ -c Tokenise.cpp

StripWht.o: StripWht.cpp global.h
	g++ -c StripWht.cpp

RSizeStr.o: RSizeStr.cpp global.h
	g++ -c RSizeStr.cpp

FloatCmp.o: FloatCmp.cpp global.h
	g++ -c FloatCmp.cpp

Resource.o: Resource.cpp Resource.h global.h InputFil.h DataLimt.h
	g++ -c Resource.cpp

sru.o : sru.cpp Resource.h global.h InputFil.h DataLimt.h
	g++ -c sru.cpp

test_res.o: test_res.cpp Resource.h
	g++ -c test_res.cpp

BigArea.o: BigArea.cpp Areas.h InputFil.h global.h
	g++ -c BigArea.cpp

Areas.o: Areas.cpp Areas.h InputFil.h
	g++ -c Areas.cpp

setmode.o: setmode.cpp setmode.h Srchman.h Err_mngr.h
	g++ -c setmode.cpp

Err_mngr.o: Err_mngr.cpp Err_mngr.h
	g++ -c Err_mngr.cpp

delay.o: delay.cpp global.h
	g++ -c delay.cpp

Output.o: Output.cpp global.h
	g++ -c Output.cpp

ChkType.o: ChkType.cpp global.h
	g++ -c ChkType.cpp

menu.o: menu.cpp menu.h
	g++ -c menu.cpp

DataLimt.o: DataLimt.h
	g++ -c DataLimt.cpp

ConToStr.o : global.h
	g++ -c ConToStr.cpp

Allocatn.o: $(SORAL_SOURCE_PATH)/Allocatn.cpp $(SORAL_SOURCE_PATH)/Allocatn.h $(SORAL_SOURCE_PATH)/containr.h
	g++ -c $(SORAL_SOURCE_PATH)/Allocatn.cpp

array2D.o: $(SORAL_SOURCE_PATH)/Array2D.cpp $(SORAL_SOURCE_PATH)/Array2D.h
	g++ -c $(SORAL_SOURCE_PATH)/Array2D.cpp


Alloc-CC.o: $(SORAL_SOURCE_PATH)/Alloc-CC.cpp $(SORAL_SOURCE_PATH)/Allocatn.h
	g++ -c $(SORAL_SOURCE_PATH)/Alloc-CC.cpp


Alloc-W.o: $(SORAL_SOURCE_PATH)/Alloc-W.cpp $(SORAL_SOURCE_PATH)/Allocatn.h
	g++ -c $(SORAL_SOURCE_PATH)/Alloc-W.cpp


itr.o: $(SORAL_SOURCE_PATH)/itr.cpp $(SORAL_SOURCE_PATH)/Allocatn.h
	g++ -c $(SORAL_SOURCE_PATH)/itr.cpp

itr_area.o: $(SORAL_SOURCE_PATH)/itr_area.cpp $(SORAL_SOURCE_PATH)/Allocatn.h $(SORAL_SOURCE_PATH)/containr.h
	g++ -c $(SORAL_SOURCE_PATH)/itr_area.cpp

itr_assn.o: $(SORAL_SOURCE_PATH)/itr_assn.cpp $(SORAL_SOURCE_PATH)/Allocatn.h $(SORAL_SOURCE_PATH)/containr.h
	g++ -c $(SORAL_SOURCE_PATH)/itr_assn.cpp

itr_res.o: $(SORAL_SOURCE_PATH)/itr_res.cpp $(SORAL_SOURCE_PATH)/Allocatn.h $(SORAL_SOURCE_PATH)/containr.h
	g++ -c $(SORAL_SOURCE_PATH)/itr_res.cpp

con_area.o: $(SORAL_SOURCE_PATH)/con_area.cpp $(SORAL_SOURCE_PATH)/containr.h
	g++ -c $(SORAL_SOURCE_PATH)/con_area.cpp


con_assn.o: $(SORAL_SOURCE_PATH)/con_assn.cpp $(SORAL_SOURCE_PATH)/containr.h
	g++ -c $(SORAL_SOURCE_PATH)/con_assn.cpp


con_res.o: $(SORAL_SOURCE_PATH)/con_res.cpp $(SORAL_SOURCE_PATH)/containr.h
	g++ -c $(SORAL_SOURCE_PATH)/con_res.cpp

cc-alloc.o: $(SORAL_SOURCE_PATH)/cc-alloc.cpp $(SORAL_SOURCE_PATH)/Allocatn.h
	g++ -c $(SORAL_SOURCE_PATH)/cc-alloc.cpp

testing.o: $(SORAL_SOURCE_PATH)/testing.cpp $(SORAL_SOURCE_PATH)/testing.h
	g++ -c $(SORAL_SOURCE_PATH)/testing.cpp

testingTESTMODE.o: testin

clean:
	clear
	rm *.o
	rm allocate tester

