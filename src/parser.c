#include <parser.h>
#include "lexer.h"

syntax_t_node * new_stmt_node(stmt_kind stmt_kind){
    syntax_t_node * p_node = malloc(sizeof(syntax_t_node));
    if(p_node == NULL){
        perror("malloc() error:");
    }else{
        for(int i=0; i<MAXCHILDREN; i++){
            p_node->child[i] = NULL;
        }
        p_node->sibling = NULL;
        p_node->has.stmt = stmt_kind; 
        p_node->position[0] = (glob_context.p_buffer)->line_number;
        p_node->position[1] = (glob_context.p_buffer)->line_char_pos;
    }
    return p_node;
}

syntax_t_node * new_exp_node(exp_kind exp_k){
    syntax_t_node * p_node = malloc(sizeof(syntax_t_node));
    if(p_node == NULL){
        perror("malloc() error:");
    } else {
        for(int i=0; i<MAXCHILDREN; i++){
            p_node->child[i] = NULL;
        }
        p_node->sibling = NULL;
        p_node->has.exp.kind = exp_k;
        p_node->has.exp.type = NONE_T;
        p_node->position[0] = (glob_context.p_buffer)->line_number;
        p_node->position[1] = (glob_context.p_buffer)->line_char_pos;
        p_node->type = EXP_T;
    }
    return p_node;
}

char* cp_str(char s[]){
    char* s_new;
    s_new = (char*)malloc(20);
 
    strcpy(s_new, s);
    return (char*)s_new;
}

static int indent_no = 0;
#define ADD_INDENT indent_no+=2
#define SUB_INDENT indent_no-=2

static void indent(void){
    for (int i=0; i< indent_no; i++){
        printf("%s", " ");
    }
}
void print_syntax_tree (syntax_t_node* root){
    ADD_INDENT;
    while (root != NULL){
        indent();
        if(root->type == STMT_T){
            switch (root->has.stmt){
                case IF_SK:
                    puts("IF");
                    break;
                case WHILE_SK:
                    puts("WHILE");
                    break;
                case RETURN_SK:
                    puts("RETURN");
                    break;
                case ASSIGN_SK:
                    puts("ASSIGN");
                    break;
                case VAR_SK:
                    puts("VAR");
                    break;
                case VECT_SK:
                    puts("VECTOR");
                    break;
                case FUNCT_SK:
                    puts("FUNCTION");
                    break;
                case CALL_SK:
                    puts("FUNCTION CALL");
                    break;
                default:
                    puts("UNKNOWN STATEMENT");
                    break;
            }
        }else if( root->type == EXP_T){
            switch (root->has.exp.kind){
                case OP_EK:
                    puts("OPERATOR");
                    break;
                case ID_EK:
                    puts("IDENTIFIER");
                    break;
                case TYPE_EK:
                    puts("DECLARATION");
                    break;
                case VAR_ID_EK:
                    puts("VARIABLE EXPRESSION");
                    break;
                case VECT_ID_EK:
                    puts("VECTOR EXPRESSION");
                    break;
                case FUNCT_EK:
                    puts("FUNCTION DECLARATION");
                    break;
                default:
                    puts("UNKNOWN EXPRESSION KIND");
                    break;
                }
        }else {
        puts("UNKNOWN NODE TYPE");
        }
        for (int i=0;i<MAXCHILDREN;i++){
            print_syntax_tree(root->child[i]);
        }
        root = root->sibling;
    }
    SUB_INDENT;
    


    
}

