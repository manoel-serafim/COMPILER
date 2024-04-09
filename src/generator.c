#include "parser.h"

static void generate_expression( syntax_t_node* branch )
{
    switch(branch->has.exp.kind)
    {
        case OP_EK:
        case ID_EK:
        case NUM_EK:
        case TYPE_EK:
        case VECT_ID_EK:
    }

}

static void generate_statement( syntax_t_node* branch )
{
    switch(branch->has.exp.kind)
    {
        case OP_EK:
        case ID_EK:
        case NUM_EK:
        case TYPE_EK:
        case VECT_ID_EK:
    }

}



void generate(syntax_t_node* syntax_root){
    if(syntax_root != NULL)
    {
        /*switch case here*/
        switch(syntax_root->type)
        {
            case EXP_T:
                generate_expression(syntax_root)
                break;
            case STMT_T:
                break;
        }

        generate(syntax_root->sibling)
    }
}