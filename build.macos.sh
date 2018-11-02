#!/bin/bash
gcc -o bin/macos/animatron-macos src/main.cpp src/object3d.cpp -L/System/Library/Frameworks -framework GLUT -framework OpenGL
