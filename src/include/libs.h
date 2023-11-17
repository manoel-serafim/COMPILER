#include <stdio.h>      //io
#include <errno.h>      //error handeling
#include <string.h>     //string operations (strcat)
#include <stdarg.h>     //used for messaging
#include <stdbool.h>    //bool type
#include <ctype.h>      //isalpha and isdigit
#include <stdlib.h>     //memory allocations


//ANSI colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define CYN "\033[36m"
#define YELLOW "\033[33m"
#define GREEN "\033[0;32m"

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
    printf(GREEN "[+] ");
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
