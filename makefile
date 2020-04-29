# compiles the emulator

# BUILD_DIR ?= ./build
# SRC_DIR ?= ./src

# myapp: main.cpp
clean:
	g++ src/main.cpp src/io.cpp src/features/* -o build/emulator -lglut -lGLU -lGL


# DIR_X	=	(usually ok, might try with -I/usr/X11R6/lib)
# DIR_OPENGL	=	(usually ok, see where to locate glut.h)
# FLAGS_X	=	(usually ok, might try with -L/usr/X11R6/lib -lX11 -lXext -lXmu -lXi)
# FLAGS_OPENGL	= -lglut	

# https://imagecomputing.net/damien.rohmer/data/previous_website/documents/teaching/00_opengl_makefile/compilation_glut.html