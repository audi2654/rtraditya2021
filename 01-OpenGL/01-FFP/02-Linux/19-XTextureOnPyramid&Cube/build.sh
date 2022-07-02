#!/bin/bash

#-lm for math.h
#-lSOIL for SOIL library for texture

gcc -o OGL OGL.c -lX11 -lGL -lGLU -lm -lSOIL

./OGL