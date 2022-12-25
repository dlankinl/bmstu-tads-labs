#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int file_find_words(FILE *f, char letter);
int file_find_words(FILE *f, char letter, size_t to_print);

#endif // __FILE_H__