#!/bin/bash

#-lm is for math.h

gcc -o OGL OGL.c -lX11 -lGL -lGLU -lGLEW -lm

./OGL