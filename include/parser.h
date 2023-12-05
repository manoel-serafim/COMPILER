#ifndef __PARSER_H_
#define __PARSER_H_



/*--[Sintax Tree Definitions]--*/

typedef enum {STMT_T, EXP_T} node_type;
typedef enum {IF_SK, WHILE_SK, RETURN_SK, ASSIGN_SK/*=2*/, VAR_SK, VECT_SK, FUNCT_SK, CALL_SK} stmt_kind;
typedef enum {OP_EK, ID_EK, NUM_EK, TYPE_EK/*ie. int decl*/, VECT_ID_EK/*type vector[size]*/, FUNCT_EK/*type funct(params)decl*/} exp_kind;
typedef enum {INT_T, VOID_T, CONST_T} exp_type;
struct exp {exp_kind kind; exp_type type;};

#define MAXCHILDREN 3 // max of three expressions under each stmt
typedef struct arr{
    int size;
    char* identifier;
} array;
/*--[Sintax Tree Structure - used also in semantic analysis]--*/
typedef struct node
{
    struct node * child[MAXCHILDREN];
    struct node * sibling;
    int position[2]; //line position e char position resp
    node_type type;
    union {stmt_kind stmt; struct exp exp; } has; // node has a stmt or an exp
    union { int op;/*tok type*/ int val;/*value assign*/ array array_specs; char* content;/*content of*/} attr; // used in semantic analysis
    
} syntax_t_node;

syntax_t_node* new_stmt_node(stmt_kind);
syntax_t_node* new_exp_node(exp_kind);
char* cp_str(char*);
void print_syntax_tree(syntax_t_node*);
extern syntax_t_node* parse(void);

#endif