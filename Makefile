


PRE:=$(shell ./mk-headers.sh)
PRE:=$(shell ./mk-shell.sh)
SRC:=$(shell find -type f -name "*.c" -or -name "*.cpp" -or -name "*.asm")
HDR:=$(shell find -type f -name "*.h" -or -name "*.hpp")
RES:=$(shell find -type f -name "*.png")
DIR:=$(shell find -L -mindepth 1 -type d -not -wholename "*/.*" -printf "-I %P ")




CC=g++
LIBS  = `pkg-config --libs   sdl2,SDL2_image` -lm     $(OPENMP)  
CFLAGS= `pkg-config --cflags sdl2,SDL2_image` -Werror $(OPENMP) $(DIR)
CPPFLAGS=$(CFLAGS)

# optim
CFLAGS+=-O3

# parallel for
#OPENMP=-fopenmp
OPENMP=

.PHONY : all
all : main


.PHONY : run
run : main
	./$^


OBS+=camera.o
OBS+=db_init.o
OBS+=db_update.o
OBS+=fast_gauss_rand.o
OBS+=frame.o
OBS+=img_init.o
OBS+=loop.o
OBS+=M34.o
OBS+=main.o
OBS+=normal_ray.o
OBS+=ray.o
OBS+=rnd.o
OBS+=sfere.o
OBS+=shadow_ray.o
OBS+=skybox.o

#main.o : $(SRC) $(HDR)

$(OBS) : Makefile $(SRC) $(HDR)


main : Makefile $(OBS)
	$(CC) $(CFLAGS) -o $@ $(OBS) $(LIBS)

#DYN+=draw_scene_gl.h
#draw_scene_gl.h : scenes/scene.obj obj2c.sh
#	./obj2c.sh scenes/scene.obj > $@

.PHONY : clean cl
clean cl :
	file * | awk '/ELF/ { gsub(/:.*/,"") ; print }' | xargs -r rm
	rm -fR dyn

.PHONY : rebuild re
rebuild re : clean all

