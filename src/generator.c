#include "parser.h"
#include "generator.h"
#ifndef YYPARSE
#include "../utils/bison/parser.tab.h"
#endif


quadruple* head = malloc(sizeof quadruple);
quadruple* start = head->next;
address holder;





uint_32_t register_status = 0x80000000;
#define SET_BIT(num, pos) ((num) |= (1u << (pos)))
#define RESET_BIT(num, pos) ((num) &= ~(1u << (pos)))



static inline free_register(uint_8_t position){
    RESET_BIT(register_status, position);
}

uint_8_t reserve_register(){

    uint_8_t i;
    for (i = 31; i >= 0; i--) {
        if (!(register_status & (1u << i))) {
            SET_BIT(register_status, i);
            return i;
        }
    }

}

static quadruple* generate_expression(syntax_t_node* branch)
{

    quadruple* instruction = malloc(sizeof(quadruple));


    switch(branch->has.exp.kind)
    {
        case OP_EK:

            //generate the code needed for the execution of the left operand
            generate(branch->child[0]);
            // glob var_ addr
            instruction->address[1] = holder;

            //the address for the current 
            //generate the code needed for the execution of the right operand
            generate(branch->child[1]);
            instruction->address[2] = holder;

            //now we can write the quadruple back inside of the quadruple list
            //dest is a temporary register 
            instruction->address[0].value = reserve_register();
            instruction->address[0].type = REGISTER;
            //(branch.attr.op, dest, r2, r3)
            instruction->operation = branch->attr.op;

            //if one of the registers of operand where used, now we can free them
            if(instruction->address[1].type = REGISTER){
                free_register(instruction->address[1].value);
            }
            if(instruction->address[2].type = REGISTER){
                free_register(instruction->address[2].value);
            }

            head->next = instruction;
            head = head->next;    
            
            //The holder is the register in which the op will be stored;
            holder = instruction->address[0];


        case ID_EK:

            instruction->address[0].type = REGISTER;
            instruction->address[0].value = 
        case NUM_EK:
        case TYPE_EK:
        case VECT_ID_EK:
    }

}

static address generate_statement( syntax_t_node* branch )
{
    switch(branch->has.stmt)
    {
        case IF_SK:
        case WHILE_SK:
        case RETURN_SK:
        case ASSIGN_SK:
        case VAR_SK:
        case VECT_SK:
        case FUNCT_SK:
        case CALL_SK:
        case PARAM_SK:
        case VECT_PARAM_SK:
    }

}



quadruple* generate(syntax_t_node* syntax_root){

    if(syntax_root != NULL)
    {        
        /*switch case here*/
        switch(syntax_root->type)
        {
            case EXP_T:
                generate_expression(syntax_root);
                break;
            case STMT_T:
                generate_expression(syntax_root);
                break;
            default:
				break;
        }
        generate(syntax_root->sibling);
    }
}