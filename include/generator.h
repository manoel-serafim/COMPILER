#ifndef __GENERATOR_H_
#define __GENERATOR_H_

#include "parser.h"

typedef enum {LOCATION,STR,REGISTER,IMMEDIATE} address_type; 
typedef enum {
    LOAD_VAR = 256,                /*[0]=reg_addr|[1]=scope|[2]name*/ 
    LOAD_VECT = 257,               /*[0]=reg_addr|[1]=add_result_sizeaddr|[2]NULL*/      
    BRANCH_IF_NOT_EQUAL = 258,     /*[0]=NULL|[1]=condition|[2]inst_addr*/
    BRANCH = 259;                  /*[0]=NULL|[1]=NULL|[2]inst_addr*/
    LABEL = 260;                   /*[0]id|[1]NULL|[2]NULL*/
    MOVE = 261;                    /*[0]dest[1]NULL[2]data to ret*/
    PUSH = 262;                    /*[0]reg or data to push to stack*/
    POP = 263;                     /*[0]dest to pop to*/
    BRANCH_AND_LINK = 264;         /*[2]inst_addr*/
    STORE = 265,                   /*[0] dest reg with addr; [2] addr with content*/ // translate to STRREG|WORD|DATA
    PLUS_ALOP = 266,               /* PLUS_ALOP  [0]receivesresult*/
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
	int value;
	char * data;
}address;

typedef struct q{
    code operation;
    address address[3];
    uint location;
    struct q* next;
}quadruple;



extern quadruple* start;

#endif