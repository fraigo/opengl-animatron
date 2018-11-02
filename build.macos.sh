#!/bin/bash
g++ -o bin/macos/animatron-macos main.cpp object3d.cpp -L/System/Library/Frameworks -framework GLUT -framework OpenGL
