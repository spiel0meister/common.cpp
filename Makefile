CPP=g++ -std=c++17
CFLAGS=-ggdb

all: main

main: main.cpp
	$(CPP) $(CFLAGS) -o $@ main.cpp 
