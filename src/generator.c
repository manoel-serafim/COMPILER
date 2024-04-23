#include "parser.h"
#include "generator.h"
#ifndef YYPARSE
#include "../utils/bison/parser.tab.h"
#endif


quadruple* head = malloc(sizeof quadruple);
quadruple* start = head;
address holder;
char * scope = "global";





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
            instruction->address[0].content.value = reserve_register();
            instruction->address[0].type = REGISTER;
            //(branch.attr.op, dest, r2, r3)
            instruction->operation = branch->attr.op;

            //if one of the registers of operand where used, now we can free them
            if(instruction->address[1].type = REGISTER){
                free_register(instruction->address[1].content.value);
            }
            if(instruction->address[2].type = REGISTER){
                free_register(instruction->address[2].content.value);
            }

            head->next = instruction;
            head = head->next;    
            
            //The holder is the register in which the op will be stored;
            holder = instruction->address[0];
            break;

        case ID_EK:
            instruction->address[1].content.data = scope;
            instruction->address[1].type = STR;

            instruction->address[2].content.data = branch->attr.content;
            instruction->address[2].type = STR;

            instruction->operation = LOAD_VAR;
            instruction->address[0].type = REGISTER;
            instruction->address[0].content.value = reserve_register();
            
            head->next = instruction;
            head = head->next;  

            holder = instruction->address[0];

            break;
        case NUM_EK:
            holder.type = IMMEDIATE;
            holder.content.value = branch->attr.val;

            break;

        case TYPE_EK:
            generate(branch->child[0]);
            break;

        case VECT_ID_EK:
            instruction->address[1].content.data = scope;
            instruction->address[1].type = STR;

            instruction->address[2].content.data = branch->attr.content;
            instruction->address[2].type = STR;

            instruction->operation = LOAD_VAR;
            instruction->address[0].type = REGISTER;
            instruction->address[0].content.value = reserve_register();

            head->next = instruction;
            head = head->next;  
            
            //this will have to generate the op to calc the size
            adder = malloc(sizeof(quadruple));

            adder->address[1]= instruction->address[0];

            //calc the base addr
            generate(branch->child[0]);

            adder->address[2] = holder;
            adder->operation = PLUS_ALOP;
            adder->address[0].type = REGISTER;
            adder->address[0].content.value = reserve_register();
            
            head->next = adder;
            head = head->next;  

            vect_loader = malloc(sizeof(quadruple));
            vect_loader->address[1]= adder->address[0];

            vect_loader->address[0].type = REGISTER;
            vect_loader->address[0].content.value = reserve_register();
            
            vect_loader->address[2] = NULL;
            vect_loader->operation = LOAD_VECT;

            head->next = vect_loader;
            head = head->next; 

            holder = vect_loader->address[0];

            break;


            break;
        default:
			break;
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