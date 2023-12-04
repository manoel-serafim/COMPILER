#ifndef __PARSER_H_
#define __PARSER_H_



/*--[Sintax Tree Definitions]--*/

typedef enum {STMT_T, EXP_T} node_type;
typedef enum {IF_T, WHILE_T, RETURN_T, ASSIGN_T} stmt_type;
typedef enum {OP_I, ID_I} exp_identifier;
typedef enum {INT_T, VOID_T} exp_type;
struct exp {exp_identifier id; exp_type type;};

#define MAXCHILDREN 3 // max of three expressions under each stmt

/*--[Sintax Tree Structure - used also in semantic analysis]--*/
typedef struct node
{
    struct node * child[MAXCHILDREN];
    struct node * sibling;
    int position[2]; //char & line position
    node_type type;
    union {stmt_type stmt; struct exp exp; } has; // node has a stmt or an exp
    union { int op; int val; char* content;} attr;
    
} syntax_t_node;

syntax_t_node* new_stmt_node(stmt_type);
syntax_t_node* new_exp_node(exp_identifier);

#endif