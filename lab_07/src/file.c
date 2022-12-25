#include "file.h"

int file_find_words(FILE *f, char letter, size_t to_print)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    size_t flag = 0;
    // printf("%c - letter\n", letter);

    while ((read = getline(&line, &len, f)) != -1)
    {
        flag = 0;
        line[strlen(line) - 1] = 0;
        if (line[0] == letter && to_print)
            printf("%s\n", line);
        else
            flag = 1;
    }
    (void) flag;
    free(line);
    return EXIT_SUCCESS;
}