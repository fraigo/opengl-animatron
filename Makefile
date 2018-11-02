OSNAME := $(shell uname)

# Linux (default)
EXE = animatron-win.exe
LDFLAGS = -lopengl32 -lglu32 -lglut32

# Windows (cygwin)
ifeq "$(OSNAME)" "Linux"
    EXE = animatron-linux
	LDFLAGS = -lGL -lGLU -lglut
endif

# OS X
ifeq "$(OSNAME)" "Darwin"
	EXE = animatron-mac
    LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
endif


$(EXE) : main.cpp objeto.cpp
		gcc -o $@ $< $(CFLAGS) $(LDFLAGS)

