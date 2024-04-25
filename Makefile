# This is a Makefile to build DungeonQuest on UNIX systems
# It builds an executable called dq3

SRC=DungeonQuest/Dungeon\ Quest\ III.cpp
CXX=g++

CXXFLAGS=-std=c++11 -Dstrcpy_s=strcpy

.PHONY: all
all: dq3

dq3: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@
