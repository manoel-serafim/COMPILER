#include "assembler.h"

uint offset_calc(char* scope, char* variable)
{
    return 1;
}

void assemble(quadruple const * head)
{
    quadruple* instruction_pointer = (quadruple *) head;
    while(instruction_pointer != NULL)
    {
        switch(instruction_pointer.operation)
        {
            case LOAD_VAR:
                //lw $reg, offset(s0)
                fprintf("%s a%d, %d(s0)", "lw", instruction_pointer->address[0].value, offset_calc(instruction_pointer->address[1], instruction_pointer->address[2]));
                
                break;
            case LOAD_VECT:
                //lw $reg, offset+off(s0)
                break;
            case BRANCH_IF:
                //get location
                instruction_pointer = instruction_pointer->next;
                //gen branch instruction
                //bne $reg1, $reg2, immediate_location
                break;
            case BRANCH:
                break;
            case LABEL:
                break;
            case MOVE:
                break;
            case PUSH:
                break;
            case POP:
                break;
            case BRANCH_AND_LINK:
                break;
            case STORE:
                break;
            case ADD:
                break;
            case SUB:
                break;
            case MULT:
                break;
            case DIV:
                break;
            case EQ_REL:
                break;
            case NOTEQ_REL:
                break;
            case LESSEQ_REL:
                break;
            case GREATEQ_REL:
                break;
            case GREAT_REL:
                break;
            case LESS_REL:
                break;
            case RET:
                break;
            case LOAD_IMMEDIATE:
                break;
            
            
        }
    }
}

