#!/bin/bash

gcc -c main.c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
g++ -o app.exe main.o -lm