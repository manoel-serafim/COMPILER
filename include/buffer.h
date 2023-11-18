#ifndef __BUFFER__
#define __BUFFER__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*--[BUFFER DEFINITIONS]--*/
#define BUFF_SIZE 256

/*--[BUFFER STRUCTS]--*/
typedef struct {
    char *data;
    size_t loaded_size;
    size_t position;
    size_t line_number;
    size_t line_char_pos;
} Buffer;

size_t load_buffer(Buffer *buffer, FILE *file);
void allocate_buffer(Buffer *buffer, FILE *file);
void deallocate_buffer(Buffer *buffer);

#endif