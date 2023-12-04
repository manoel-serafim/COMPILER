#include <parser.h>
#include "lexer.h"

syntax_t_node * new_stmt_node(stmt_type stmt_type){
    syntax_t_node * p_node = malloc(sizeof(syntax_t_node));
    if(p_node == NULL){
        perror("malloc() error:");
    }else{
        for(int i=0; i<MAXCHILDREN; i++){
            p_node->child[i] = NULL;
        }
        p_node->sibling = NULL;
        p_node->has.stmt = stmt_type; 
        p_node->position[0] = (glob_context.p_buffer)->line_number;
        p_node->position[1] = (glob_context.p_buffer)->line_char_pos;
    }
    return p_node;
}

syntax_t_node * new_exp_node(exp_identifier exp_id, exp_type exp_tp){
    syntax_t_node * p_node = malloc(sizeof(syntax_t_node));
    if(p_node == NULL){
        perror("malloc() error:");
    } else {
        for(int i=0; i<MAXCHILDREN; i++){
            p_node->child[i] = NULL;
        }
        p_node->sibling = NULL;
        p_node->has.exp.id = exp_id;
        p_node->has.exp.type = exp_tp;
        switch (exp_tp)
        {
        case INT_T:
            p_node->attr.content = "INTERGER";
            break;
        case VOID_T:
            p_node->attr.content = "VOID";
            break;
        default:
            break;
        }
        p_node->has.exp.type = VOID_T;
        p_node->position[0] = (glob_context.p_buffer)->line_number;
        p_node->position[1] = (glob_context.p_buffer)->line_char_pos;
        p_node->type = EXP_T;
    }
    return p_node;
}

