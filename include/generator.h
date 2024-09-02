#ifndef __GENERATOR_H_
#define __GENERATOR_H_

#include "parser.h"

typedef enum {LOCATION,STR,REGISTER,IMMEDIATE,EMPTY} address_type; 
typedef enum {
    LOAD_VAR = 256,                /*[0]=reg_addr|[1]=scope|[2]name*/ 
    LOAD_VECT = 257,               /*[0]=reg_addr|[1]=add_result_sizeaddr|[2]NULL*/      
    BRANCH_IF = 258,     /*[0]=NULL|[1]=condition|[2]inst_addr*/
    BRANCH = 259,                  /*[0]=NULL|[1]=NULL|[2]inst_addr*/
    LABEL = 260,                   /*[0]id|[1]NULL|[2]NULL*/
    MOVE = 261,                    /*[0]dest[1]NULL[2]data to ret*/
    PUSH = 262,                    /*[0]reg or data to push to stack*/
    POP = 263,                     /*[0]dest to pop to*/
    BRANCH_AND_LINK = 264,         /*[2]inst_addr*/
    STORE = 265,                   /*[0] reg to sore in mem; [1] scope [2] offset mem*/ // translate to STRREG|WORD|DATA
    ADD = 266,               /* PLUS_ALOP  [0]receivesresult*/
    SUB = 267,              /* MINUS_ALOP  */
    MULT = 268,           /* MULT_PRE_ALOP  */
    DIV = 269,            /* DIV_PRE_ALOP  */
    EQ_REL = 270,                /* EQ_RELOP  */
    NOTEQ_REL = 271,             /* NOTEQ_RELOP  */
    LESSEQ_REL= 272,            /* LESSEQ_RELOP  */
    GREATEQ_REL = 273,           /* GREATEQ_RELOP  */
    GREAT_REL = 274,             /* GREAT_RELOP  */
    LESS_REL = 275,              /* LESS_RELOP  */ 
    RET = 276, /*RETURN*/ //ret
    LOAD_IMMEDIATE = 277, //li
} code; 

typedef struct{
    address_type type;
	uint value;
	char * data;
}address;

typedef struct q{
    code operation;
    address address[3];
    uint location;
    struct q* next;
}quadruple;


quadruple* generate(syntax_t_node* syntax_root);
extern quadruple start;
void init_generation(syntax_t_node* root);
void print_quadruple_linked_list(quadruple head);

#endif