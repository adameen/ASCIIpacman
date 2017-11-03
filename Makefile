CXX=g++
CFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb
CLIBS=-lncurses
OBJECTS=src/main.o src/CMovingObject.o src/CPacman.o src/CGhostEasy.o src/CGhostHard.o src/CGame.o src/CData.o src/CExceptions.o
BIN=./asciipacman

#----------- make PARAMETERS -----------#
# example: 
# all: $(BIN) ...this means: "to make all, execute $(BIN)...$(BIN) which is on the left side (not bash command)
#	make doc ...here are normal commands in bash

all: $(BIN)
	make doc

clean:
	rm -f src/*.o 2>/dev/null
	rm -f $(BIN) 2>/dev/null
	rm -rf ./doc 2>/dev/null

compile: $(BIN)

run:
	$(BIN)

doc:
	doxygen ./Doxyfile 1>/dev/null 2>/dev/null

#---------------------------------------#
#----------- BUILD FILES -----------#
# $@ means src/main.o
# $< means src/main.cpp src/CGame.h src/CData.h,...

$(BIN): $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(BIN) $(CLIBS)

src/main.o: src/main.cpp src/CGame.h src/CData.h src/CExceptions.h src/CMovingObject.h src/CPacman.h src/CGhostEasy.h src/CGhostHard.h
	$(CXX) $(CFLAGS) -c $< -o $@ $(CLIBS)

src/CMovingObject.o: src/CMovingObject.cpp src/CMovingObject.h src/CData.h src/CExceptions.h
	$(CXX) $(CFLAGS) -c $< -o $@ $(CLIBS)

src/CPacman.o: src/CPacman.cpp src/CPacman.h src/CMovingObject.h src/CData.h src/CExceptions.h
	$(CXX) $(CFLAGS) -c $< -o $@ $(CLIBS)

src/CGhostEasy.o: src/CGhostEasy.cpp src/CGhostEasy.h src/CMovingObject.h src/CData.h src/CExceptions.h
	$(CXX) $(CFLAGS) -c $< -o $@ $(CLIBS)

src/CGhostHard.o: src/CGhostHard.cpp src/CGhostHard.h src/CMovingObject.h src/CData.h src/CExceptions.h
	$(CXX) $(CFLAGS) -c $< -o $@ $(CLIBS)

src/CGame.o: src/CGame.cpp src/CGame.h src/CData.h src/CExceptions.h src/CMovingObject.h src/CPacman.h src/CGhostEasy.h src/CGhostHard.h
	$(CXX) $(CFLAGS) -c $< -o $@ $(CLIBS)

src/CData.o: src/CData.cpp src/CData.h src/CExceptions.h
	$(CXX) $(CFLAGS) -c $< -o $@ $(CLIBS)

src/CExceptions.o: src/CExceptions.cpp src/CExceptions.h
	$(CXX) $(CFLAGS) -c $< -o $@ $(CLIBS)

#-----------------------------------#
