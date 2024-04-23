#ifndef __GENERATOR_H_
#define __GENERATOR_H_

#include "parser.h"

typedef enum {IMMEDIATE,STR,REGISTER,EMPTY} address_type; 
typedef enum {
    LOAD_VAR = 256,
    LOAD_VECT = 257,

    PLUS_ALOP = 266,               /* PLUS_ALOP  */
    MINUS_ALOP = 267,              /* MINUS_ALOP  */
    MULT_PRE_ALOP = 268,           /* MULT_PRE_ALOP  */
    DIV_PRE_ALOP = 269,            /* DIV_PRE_ALOP  */
    EQ_RELOP = 270,                /* EQ_RELOP  */
    NOTEQ_RELOP = 271,             /* NOTEQ_RELOP  */
    LESSEQ_RELOP = 272,            /* LESSEQ_RELOP  */
    GREATEQ_RELOP = 273,           /* GREATEQ_RELOP  */
    GREAT_RELOP = 274,             /* GREAT_RELOP  */
    LESS_RELOP = 275              /* LESS_RELOP  */  
} code; 

typedef struct{
    address_type type;
    union{
		int value;
		char * data;
	}content;
}address;

typedef struct q{
    code operation;
    address address[3];
    struct q* next;
}quadruple;



extern quadruple* start;

#endif