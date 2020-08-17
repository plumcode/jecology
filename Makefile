jecology : jecology.o universe.o highercreature.o lowestcreature.o basecreature.o getopt.o jecoopt.o jecolib.o jecoconsole.o
	g++ -o jecology universe.o jecology.o jecolib.o highercreature.o lowestcreature.o  basecreature.o jecoopt.o getopt.o \
		jecoconsole.o -lncurses

jecology.o : jecology.cpp universe.hpp highercreature.hpp lowestcreature.hpp basecreature.hpp jecoopt.h
	g++ -c jecology.cpp
jecoconsole.o: jecoconsole.cpp jecoconsole.h highercreature.hpp lowestcreature.hpp basecreature.hpp jecoopt.h
	g++ -c jecoconsole.cpp
universe.o: universe.cpp universe.hpp highercreature.hpp lowestcreature.hpp basecreature.hpp jecolib.h jecoopt.h
	g++ -c universe.cpp
highercreature.o : highercreature.cpp highercreature.hpp basecreature.hpp jecoopt.h
	g++ -c highercreature.cpp
lowestcreature.o : lowestcreature.cpp lowestcreature.hpp basecreature.hpp jecoopt.h
	g++ -c lowestcreature.cpp
basecreature.o : basecreature.cpp basecreature.hpp jecoopt.h
	g++ -c basecreature.cpp
jecolib.o : jecolib.cpp jecolib.h jecoconsole.h highercreature.hpp lowestcreature.hpp basecreature.hpp jecoopt.h
	g++ -c jecolib.cpp
jecoopt.o : jecoopt.cpp jecoopt.h getopt.h jecodefs.h
	g++ -c jecoopt.cpp
getopt.o : getopt.cpp getopt.h
	g++ -c getopt.cpp

clean : 
	rm jecology jecology.o universe.o highercreature.o lowestcreature.o basecreature.o jecoconsole.o jecoopt.o jecolib.o getopt.o 
