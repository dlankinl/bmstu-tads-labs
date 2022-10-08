#!/bin/bash

gcc -c str_handler.c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion

gcc -c number_t.c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion

gcc -c main.c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion

gcc -o app.exe str_handler.o number_t.o main.o  -lm