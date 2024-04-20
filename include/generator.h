#ifndef __GENERATOR_H_
#define __GENERATOR_H_

#include "parser.h"

typedef enum {REGISTER, IMMEDIATE} address_type; 

typedef struct{
    address_type type;
    int value;
}address;

typedef struct q{
    uint16_t operation;
    address address[3];
    struct q* next;
}quadruple;

extern quadruple* head;

#endif