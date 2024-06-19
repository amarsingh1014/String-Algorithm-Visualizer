CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: main.o StringAlgorithms.o
	$(CXX) $(CXXFLAGS) -o main main.o StringAlgorithms.o $(LDFLAGS)

StringAlgorithms.o: StringAlgorithms.cpp StringAlgorithms.h
	$(CXX) $(CXXFLAGS) -c StringAlgorithms.cpp

main.o: main.cpp StringAlgorithms.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o main