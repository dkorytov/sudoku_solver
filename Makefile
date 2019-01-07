CC=g++
CFLAGS=-c -g -O3 -Wall
LDFLAGS=
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:src/%.cpp=obj/%.o)
EXECUTABLE=solver

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

${OBJECTS}: obj/%.o : src/%.cpp
	$(CC) $(CFLAGS) $< -o $@
