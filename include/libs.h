#ifndef LIBS_H          //if already inserted it should not be redefined by itself
#define LIBS_H


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


#endif