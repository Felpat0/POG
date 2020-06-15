game: main.o MapElements.o
	g++ main.o MapElements.o -o game

main.o: main.cpp
	g++ -c main.cpp

MapElements.o: MapElements.cpp MapElements.h
	g++ -c MapElements.cpp

clean: 
	rm *.o