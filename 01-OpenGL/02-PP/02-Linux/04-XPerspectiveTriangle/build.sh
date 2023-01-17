#!/bin/bash

#-lm is for math.h

g++ -o OGL OGL.cpp -lX11 -lGL -lGLU -lGLEW -lm

./OGL