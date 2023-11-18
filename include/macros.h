#include "libs.h"

#ifndef MACROS          //if already inserted it should not be redefined by itself
#define MACROS
/*--[ MACROS ]--*/
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
#endif