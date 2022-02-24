
LIBS=-lm   `pkg-config --libs   sdl2` -lstdc++
CFLAGS=-O3 `pkg-config --cflags sdl2` -std=c++11 -fopenmp

.PHONY : all clean cl rebuild re run

all : main

run : main
	./$^


SRC:=$(shell find -type f -name "*.c" -or -name "*.cpp" -or -name "*.asm")

main : Makefile $(SRC)
#	@echo $^
	c++ $(CFLAGS) -o $@ main.cpp M34.cpp $(LIBS)

clean cl :
	file * | awk '/ELF/ { gsub(/:.*/,"") ; print }' | xargs -r rm
	rm -f *.deps

rebuild re : clean all

