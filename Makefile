OSNAME := $(shell uname)
RM = rm

# Windows (default)
EXE = bin/linuxanimatron-win.exe
LDFLAGS = -lopengl32 -lglu32 -lglut32
CFLAGS = 

# Linux (cygwin)
ifeq "$(OSNAME)" "Linux"
    EXE = bin/linux/animatron-linux
	LDFLAGS = -lGL -lGLU -lglut
endif

# OS X
ifeq "$(OSNAME)" "Darwin"
	EXE = bin/macos/animatron-macos
    LDFLAGS = -L/System/Library/Frameworks -framework GLUT -framework OpenGL
endif



CC=g++
SOURCES= main.cpp object3d.cpp
DEPS= object3d.h
OBJECTS=$(SOURCES:.cpp=.o)


all: $(EXE) clean
		@echo Make has finished.

$(EXE): $(OBJECTS)
		$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
		$(CC) $(LDFLAGS) -c $*.cpp

clean: 
		$(RM) $(OBJECTS)
