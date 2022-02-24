
OBJ = main.o

LIBS=-lm   `pkg-config --libs   sdl2` -lstdc++
CFLAGS=-O3 `pkg-config --cflags sdl2` -std=c++11 -fopenmp

.PHONY : all clean cl rebuild re loop loop1 run

all : main

run : main
	./$^

main : Makefile $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

clean cl :
	file * | awk '/ELF/ { gsub(/:.*/,"") ; print }' | xargs -r rm
	rm -f *.deps

rebuild re : clean all


# automatic make loop

loop : 
	make -s loop1

loop1 : 
	date "+%F %T make loop avviato" ;\
    while sleep 1 ; do \
        make -q && continue ;\
        date "+%F %T build" ;\
        make ;\
    done


# advanced autodepend
# http://stackoverflow.com/questions/8025766/makefile-auto-dependency-generation
# qualcuno suggeriva anche -MP 
# ma non sembra fare differenza
# anzi i files .P sono grandi il doppio

%.o : %.cpp
	g++ $(CFLAGS) -MD -c -o $@ $<
	mv -f $*.d $*.deps

-include *.deps
