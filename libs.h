#include <stdio.h>      //io
#include <errno.h>      //error handeling
#include <string.h>     //string operations (strcat)
#include <stdarg.h>     //used for messaging
#include <stdbool.h>    //bool type
#include <ctype.h>      //isalpha and isdigit

//ANSI colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define CYN "\033[36m"
#define YELLOW "\033[33m"

/* Functions for printing messages with colors */
void show(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    puts(NULL);
    va_end(args);
}

void sucs(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf(CYN "[+] ");
    vprintf(format, args);
    puts(RESET);
    va_end(args);
}

void info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf(YELLOW "[*] ");
    vprintf(format, args);
    puts(RESET);
    va_end(args);
}

void warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf(RED "[-] ");
    vprintf(format, args);
    puts(RESET);
    va_end(args);
}

#define BUFF_SIZE 256
#define LEXEME_SIZE 256


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *data;
    size_t loaded_size;
    size_t position;
    size_t line_number;
    size_t line_char_pos;
} Buffer;

size_t loadBuffer(Buffer *buffer, FILE *file) {
    size_t read_size = fread(buffer->data, sizeof(char), BUFF_SIZE, file);
    if (ferror(file)) {
        perror(RED"ferror() error"YELLOW);
        exit(EXIT_FAILURE);
    }
    buffer->data[read_size] = '\0';
    return read_size;
}

void allocateBuffer(Buffer *buffer, FILE *file) {
    buffer->data = (char *)calloc(BUFF_SIZE+1, sizeof(char));
    if (buffer->data == NULL) {
        perror(RED"calloc() error"YELLOW);
        exit(EXIT_FAILURE);
    }
    buffer->loaded_size = loadBuffer(buffer, file);
    buffer->position = 0;
    buffer->line_number = 1;
    buffer->line_char_pos = 0;
}

void deallocateBuffer(Buffer *buffer) {
    free(buffer->data);
    buffer->data = NULL; // Set pointer to NULL after freeing
}


/*--[ getNextChar - returns next char in buffer and manage its memory ]--*/
char getNextChar(Buffer *buffer, FILE* file) {

    char current_char = buffer->data[buffer->position];
    if (current_char == '\0') {
        if (buffer->loaded_size < BUFF_SIZE){
            return EOF;
        }
        buffer->position = 0;
        buffer->loaded_size = loadBuffer(buffer, file);
    }

    if (current_char == '\n') {
        buffer->line_number++;
        buffer->line_char_pos = 0;
    }

    buffer->position++;
    buffer->line_char_pos++;

    return current_char;
}

int intcat(int* infix, char posfix) { 

    int num_digits = snprintf(NULL, 0, "%d", *infix);
    char* holder = (char*)malloc((num_digits + 2) * sizeof(char));
    if (holder == NULL) {
        perror(RED"malloc() error"YELLOW);
        exit(EXIT_FAILURE);
    }
    
    sprintf(holder, "%d", *infix); 
    strcat(holder, &posfix);

    *infix = atoi(holder); 
    free(holder);
} 