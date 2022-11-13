__start__: obj __lines_for_space__ interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp ../opis_dzialan/opis_dzialan.cmd ../Program/config/config.xml

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall



interp: obj/main.o obj/LibInterface.o obj/Set4LibInterface.o obj/ProgramInterpreter.o obj/Configuration.o obj/xmlinterp.o obj/Scene.o obj/Sender.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/LibInterface.o obj/Set4LibInterface.o obj/ProgramInterpreter.o  obj/Configuration.o obj/xmlinterp.o obj/Scene.o obj/Sender.o -ldl -lxerces-c

obj/main.o: src/main.cpp inc/Interp4Command.hh 
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh inc/Interp4Command.hh
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/Set4LibInterface.o: src/Set4LibInterface.cpp inc/Set4LibInterface.hh inc/LibInterface.hh 
	g++ -c ${CPPFLAGS} -o obj/Set4LibInterface.o src/Set4LibInterface.cpp

obj/ProgramInterpreter.o: src/ProgramInterpreter.cpp inc/ProgramInterpreter.hh inc/Set4LibInterface.hh 
	g++ -c ${CPPFLAGS} -o obj/ProgramInterpreter.o src/ProgramInterpreter.cpp 

obj/Configuration.o: src/Configuration.cpp inc/Configuration.hh 
	g++ -c ${CPPFLAGS} -o obj/Configuration.o src/Configuration.cpp 

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh 
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp 

obj/Scene.o: src/Scene.cpp inc/Scene.hh 
	g++ -c ${CPPFLAGS} -o obj/Scene.o src/Scene.cpp 

obj/Sender.o: src/Sender.cpp inc/Sender.hh 
	g++ -c ${CPPFLAGS} -o obj/Sender.o src/Sender.cpp 

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
