#!/bin/bash

#-lm is for math.h
#-lSOIL for processing images during texturing

gcc -o OGL OGL.c -lX11 -lGL -lGLU -lm

./OGL
