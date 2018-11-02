#!/bin/bash
g++ -o bin/macos/animatron-macos main.cpp objeto.cpp -L/System/Library/Frameworks -framework GLUT -framework OpenGL
bin/macos/animatron-macos