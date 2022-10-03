#!/bin/bash

gcc -c main.c -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
g++ -o app.exe main.o -lm