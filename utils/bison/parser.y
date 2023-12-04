%{
#include "parser.h"
#include "macros.h"
#define YYSTYPE syntax_t_node * //return of bison when ref to $
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1 // is defined before any use of it
#include "lexer.h"
#include <stdio.h>
#define yylex() get_next_token(glob_context.p_buffer, glob_context.stream, glob_context.p_token_rec)
void yyerror(char * err);

static syntax_t_node* syntax_tree_root; //root of the tree
syntax_t_node* parse(void);


%}

%token ID NUM IF ELSE WHILE RETURN INT VOID PLUS_ALOP MINUS_ALOP MULT_PRE_ALOP DIV_PRE_ALOP EQ_RELOP NOTEQ_RELOP LESSEQ_RELOP GREATEQ_RELOP GREAT_RELOP LESS_RELOP EQUAL CURLYOP_BRACKET CURLYCL_BRACKET CIRCLEOP_BRACKET CIRCLECL_BRACKET SQUAREOP_BRACKET SQUARECL_BRACKET SEMICOL_PUNCT COMMA_PUNCT WHITESPACE COMMENT STRING

%%
program:
    declaration_list { syntax_tree_root = $1; } //store value
    ;

declaration_list:
    declaration_list declaration 
    {   
        YYSTYPE temp = $1; 
        if(temp == NULL){ //if it was not def, def it
            $$ = $2;
        }else{
            while(temp->sibling != NULL){ //if was def, find the next brother to define sequentially
                temp = temp->sibling;
            }
            temp->sibling = $2; //found the sibling not def in the chained link and now will set value
            $$ = $1; 
        }
    }
    | declaration
    {
        $$ = $1;
    }
    ;

declaration:
    var_declaration
    {
        $$ = $1; //set variable declaration as top
    }
    | fun_declaration
    {
        $$ = $1; //set function declaration as top
    }
    ;

var_declaration:
    type_specifier identificator SEMICOL_PUNCT
    {
        $$ = $1; //type spec go down semantic value
        $$->child[0]= $2; // Set exp type node como filho de VAR_DECL 
        $2->has.stmt = VAR_SK; //simple variable statement
        $2->type= STMT_T; //declaration statement
        
    }
    | type_specifier identificator SQUAREOP_BRACKET number SQUARECL_BRACKET SEMICOL_PUNCT
    {
        $$ = $1; //type spec go down semantic value
        $$->child[0]= $2; // Set identificator como filho de VAR_DECL 
        $2->has.stmt = VECT_SK; //vector declaration statement
        $2->attr.size = $4->attr.val; // vector[size]
        $2->type = STMT_T; //declaration statement   
    }
    ;

type_specifier:
    INT
    {
        //found leaf structure -semantic value of node
        $$=new_exp_node(TYPE_EK); //create new exp node
        $$->has.exp.type=INT_T;
    }
    | VOID
    {
        //found leaf structure -semantic value of node
        $$=new_exp_node(TYPE_EK); //create new void exp node
        $$->has.exp.type=VOID_T;
    }
    ;

fun_declaration:
    type_specifier identificator CIRCLEOP_BRACKET parameters CIRCLECL_BRACKET compound_declaration
    {
        $$ = $1; //set semantic value to type spec, it will have a node for the specific type
        $$->child[0] = $2; //child + left = identificator (name of func)
        $2->child[0] = $4; //pointer to funct args
        $2->child[1] = $6; // at the side of params it will have the declaration of the procedure
        $2->has.stmt = FUNCT_SK; // this statement is a function
        $2->type = STMT_T; //function declaration statement
    }
    ;

parameters:
    parameter_list
    {
      $$ = $1; //set semantic value to get the parameter declarations
    }
    | VOID
    { /*do nothing*/ }
    ;

parameter_list:
    parameter_list COMMA_PUNCT parameter
    {
        YYSTYPE temp = $1; // temp tree node of param list
        if(temp == NULL){
            $$ = $3; // if not def, get parameter definition
        }else{
            while(temp->sibling != NULL){ //get next empty sibling
                temp = temp->sibling;
            }
            temp->sibling = $3;
            $$ = $1; //get node from parameter_list
        }
    }
    | parameter
    {
        $$ = $1; //get node from parameter
    }
    ;

parameter:
    type_specifier identificator
    {
        $$ = $1; // get node from spec
        $$->child[0] = $2; // the identificator is the left child of the type spec
    }
    | type_specifier identificator SQUAREOP_BRACKET SQUARECL_BRACKET
    {
        $$ = $1; //get node from spec
        $$->child[0] = $2; //identificator is in left child
        $2->has.exp.kind = VECT_ID_EK;
    }
    ;

compound_declaration:
    CURLYOP_BRACKET local_declarations statement_list CURLYCL_BRACKET
    {
        YYSTYPE temp = $2;
        if(temp == NULL){
            $$=$3;
        }else{
            while(temp->sibling != NULL){ //get next empty sibling
                temp = temp->sibling;
            }
            temp->sibling = $3;
            $$ = $2; //get node from parameter_list
        }
    }
    | CURLYOP_BRACKET local_declarations CURLYCL_BRACKET
    {//getting rid of yyempty in local declartions
        $$ = $2;
    }
    | CURLYOP_BRACKET statement_list CURLYCL_BRACKET
    {//no empty in statement list
        $$ = $2;
    }
    | CURLYOP_BRACKET CURLYCL_BRACKET
    {   /*No action on empty*/}
    ;

local_declarations:
    local_declarations var_declaration
    {
        YYSTYPE temp = $1;
        if(temp == NULL){
            $$ = $2;
        }else{
            while(temp->sibling != NULL){
                temp = temp->sibling;
            }   
            temp->sibling = $2;
            $$ = $1;
        }
    }
    | var_declaration
    {
        $$ = $1;
    }
    ;

statement_list:
    statement_list statement
    {
        YYSTYPE temp = $1;
        if(temp == NULL){
            $$ = $2;
        }else{
            while(temp->sibling != NULL){
                temp = temp->sibling;
            }   
            temp->sibling = $2;
            $$ = $1;
        }
    }
    | statement
    {
        $$ = $1;
    }
    ;

statement:
    expression_declaration
    { //all get itself
        $$ = $1;
    }
    | compound_declaration
    {
        $$ = $1;
    }
    | selection_declaration
    {
        $$ = $1;
    }
    | iteration_declaration
    {
        $$ = $1;
    }
    | return_declaration
    {
        $$ = $1;
    }
    ;

expression_declaration:
    expression SEMICOL_PUNCT 
    {
        $$ = $1;
    }
    | SEMICOL_PUNCT
    {/*no semantic value to associate*/}
    ;

selection_declaration:
    IF CIRCLEOP_BRACKET expression CIRCLECL_BRACKET statement
    {
        $$ = new_stmt_node(IF_SK);
        $$->child[0] = $3; // get the op expression
        $$->child[1] = $5; // get the then part
    }
    | IF CIRCLEOP_BRACKET expression CIRCLECL_BRACKET statement ELSE statement
    {
        $$ = new_stmt_node(IF_SK);
        $$->child[0] = $3; // get the op expression
        $$->child[1] = $5; // get the then part
        $$->child[2] = $7; // else part statement
    }
    ;

iteration_declaration:
    WHILE CIRCLEOP_BRACKET expression CIRCLECL_BRACKET statement
    {
        $$ = new_stmt_node(WHILE_SK);
        $$->child[0]= $3; //op expression
        $$->child[1]= $5; // do part statement
    }
    ;

return_declaration:
    RETURN SEMICOL_PUNCT
    {
        $$ = new_stmt_node(RETURN_SK);
    }
    | RETURN expression SEMICOL_PUNCT
    {
        $$ = new_stmt_node(RETURN_SK);
        $$->child[0]= $2; // expression returned
    }
    ;

expression:
    var EQUAL expression
    {
        $$ = new_stmt_node(ASSIGN_SK);
        $$->child[0] = $1; // get var of this expression op
        $$->child[1] = $3; // expression assigned
    }
    | simple_expression
    {
        $$= $1; //get itself
    }
    ;

var:
    identificator
    {
        $$ = $1;
    }
    | identificator SQUAREOP_BRACKET expression SQUARECL_BRACKET
    {
        $$ = $1;
        $$->child[0] = $3; //Child is the expression in [] use for indexing
        $$->has.exp.kind = VECT_ID_EK; //Expression of vector identifier
    }
    ;

simple_expression:
    sum_expression relational sum_expression
    {
        $$ = $2; // get the relational op
        $$->child[0] = $1; //sum_express
        $$->child[1] = $3; //sum_express
    }
    | sum_expression
    {
        $$=$1;
    }
    ;

relational:
    EQ_RELOP
    {
        $$= new_exp_node(OP_EK);
        $$->attr.op= EQ_RELOP;
    }
    | NOTEQ_RELOP
    {
        $$= new_exp_node(OP_EK);
        $$->attr.op= NOTEQ_RELOP;
    }
    | LESSEQ_RELOP
    {
        $$= new_exp_node(OP_EK);
        $$->attr.op= LESSEQ_RELOP;
    }
    | GREATEQ_RELOP
    {
        $$= new_exp_node(OP_EK);
        $$->attr.op= GREATEQ_RELOP;
    }
    | GREAT_RELOP
    {
        $$= new_exp_node(OP_EK);
        $$->attr.op= GREAT_RELOP;
    }
    | LESS_RELOP
    {
        $$= new_exp_node(OP_EK);
        $$->attr.op= LESS_RELOP;
    }
    ;

sum_expression:
    sum_expression sum term
    {
        $$ = $2; //sum node
        $$->child[0] = $1; //the expression is left associative
        $$->child[1] = $3; //term tree is stored
    }
    | term
    {
        $$ = $1; //get the three from itself
    }
    ;

sum:
    PLUS_ALOP
    {
        $$= new_exp_node(OP_EK);
        $$->attr.op= PLUS_ALOP;
    }
    | MINUS_ALOP
    {
        $$= new_exp_node(OP_EK);
        $$->attr.op= MINUS_ALOP;
    }
    ;

term:
    term mult factor
    {
        $$ = $2; //get the left associative term
        $$->child[0] = $1; // get the operator
        $$->child[1] = $3; // get the factor
    }
    | factor
    {
        $$=$1; //get itself
    }
    ;

mult:
     DIV_PRE_ALOP
    {
        $$= new_exp_node(OP_EK);
        $$->attr.op= DIV_PRE_ALOP;
    }
    |MULT_PRE_ALOP
    {
        $$= new_exp_node(OP_EK);
        $$->attr.op= MULT_PRE_ALOP;
    }
    ;

factor:
    CIRCLEOP_BRACKET expression CIRCLECL_BRACKET
    {
        $$ = $2; //get the expression value
    }
    | var
    {
        $$ = $1; //get the variable ident or vec
    }
    | activation
    {
        $$ = $1;
    }
    | number
    {
        $$ = $1;
    }
    ;

activation:
    identificator CIRCLEOP_BRACKET argument_list CIRCLECL_BRACKET
    {
        //call a function
        $$ = $1;//addt
        $$->child[0] = $3; //args
        $$->has.stmt = CALL_SK; 
        $$->type = STMT_T;
    }
    | identificator CIRCLEOP_BRACKET CIRCLECL_BRACKET
    {//no empty in arguments
        $$ = $1;
        $$->has.stmt = CALL_SK;
        $$->type = STMT_T;
    }
    ;

argument_list:
    argument_list COMMA_PUNCT expression
    {
        YYSTYPE temp = $1;
        if(temp == NULL){
            $$ = $3;
        }else{
            while(temp->sibling != NULL){
                temp = temp->sibling;
            }   
            temp->sibling = $3;
            $$ = $1;
        }
    }
    | expression
    {
        $$ = $1;
    }
    ;

number:
    NUM
    {
        $$ = new_exp_node(NUM_EK);
        $$->has.exp.type = CONST_T;
        $$->attr.val = atoi((glob_context.p_token_rec)->lexeme);
    }

identificator:
    ID
    {
        $$ = new_exp_node(ID_EK);
        $$->attr.content = cp_str((glob_context.p_token_rec)->lexeme);
    }
%%


void yyerror(char* err) {
    puts(RED"__________________________________________[ SYNTATIC ERROR ]________________________________________");
    int in_line_placement = (glob_context.p_buffer)->line_char_pos;
    fpos_t line_placement = (glob_context.p_buffer)->line_pos;
    printf(RED"\t [!][!]message: %s"RESET, err);
    printf(CYN"\t[!] THE ERROR OCCURRED AT THE %zu-th LINE IN THE %zu-th CHAR [!]\n"RESET, (glob_context.p_buffer)->line_number, (glob_context.p_buffer)->line_char_pos);
    printf(YELLOW"\t[!] TOKEN LEXEME: "RED"%s "YELLOW"TOKEN TYPE: "RED"%s "YELLOW"[!]\n", (glob_context.p_token_rec)->lexeme, yytokentype_to_string((glob_context.p_token_rec)->type));
    puts(RED"____________________________________________________________________________________________________"RESET);
}

syntax_t_node* parse(void){
    yyparse();
    return syntax_tree_root;
}