#include <buffer.h>
#include <macros.h>

/*--[BUFFER FUNCTIONS]--*/

size_t load_buffer(Buffer *buffer, FILE *file) {
    size_t read_size = fread(buffer->data, sizeof(char), BUFF_SIZE, file);
    if (ferror(file)) {
        perror(RED"ferror() error"YELLOW);
        exit(EXIT_FAILURE);
    }
    buffer->data[read_size] = '\0';
    buffer->position = 0;
    return read_size;
}

void allocate_buffer(Buffer *buffer, FILE *file) {
    buffer->data = (char *)calloc(BUFF_SIZE+1, sizeof(char));
    if (buffer->data == NULL) {
        perror(RED"calloc() error"YELLOW);
        exit(EXIT_FAILURE);
    }
    buffer->loaded_size = load_buffer(buffer, file);
    buffer->position = 0;
    buffer->line_number = 1;
    buffer->line_char_pos = 0;
}

void deallocate_buffer(Buffer *buffer) {
    free(buffer->data);
    buffer->data = NULL; // Set pointer to NULL after freeing
}