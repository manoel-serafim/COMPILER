%{
#include "../../include/lexer.h"
#include <stdio.h>
ParsingContext glob_context;
#define yylex() get_next_token(glob_context.p_buffer, glob_context.stream, glob_context.p_token_rec)
%}

%token ID NUM IF ELSE WHILE RETURN INT VOID PLUS_ALOP MINUS_ALOP MULT_PRE_ALOP DIV_PRE_ALOP EQ_RELOP NOTEQ_RELOP LESSEQ_RELOP GREATEQ_RELOP GREAT_RELOP LESS_RELOP EQUAL CURLYOP_BRACKET CURLYCL_BRACKET CIRCLEOP_BRACKET CIRCLECL_BRACKET SQUAREOP_BRACKET SQUARECL_BRACKET SEMICOL_PUNCT COMMA_PUNCT WHITESPACE COMMENT STRING


%%
/*
program:
    NUM YYEOF { printf("Result = %d\n"); }
    | YYEOF/* empty */{ printf("empty = %d\n"); }
    ;
*/

program:
    declaration_list
    ;

declaration_list:
    declaration_list declaration
    | declaration
    ;

declaration:
    var_declaration
    | fun_declaration
    ;

var-declaration:
    type-specifier ID SEMICOL_PUNCT
    | type-specifier ID SQUAREOP_BRACK NUM SQUARECL_BRACKET SEMICOL_PUNCT
    ;

type_specifier:
    INT
    | VOID
    ;

fun_declaration:
    type_specifier ID CIRCLEOP_BRACKET parameters CIRCLECL_BRACKET compound_declaration
    ;

parameters:
    parameter-list
    | VOID
    ;

parameter_list:
    parameter_list COMMA_PUNCT parameter
    | parameter
    ;

parameter:
    type_specifier ID
    | type_specifier ID SQUAREOP_BRACKET SQUARECL_BRACKET
    ;

compound-declaration:
    CURLYOP_BRACKET local_declarations statement_list CURLYCL_BRACKET
    ;

local_declarations:
    local_declarations var_declaration
    |
    ;

statement_list:
    statement_list statement
    |
    ;

statement:
    expression_declaration
    | compound_declaration
    | selection_declaration
    | iteration_declaration
    | return_declaration
    ;

expression_declaration:
    expression SEMICOL_PUNCT | SEMICOL_PUNCT
    ;

selection_declaration:
    IF CIRCLEOP_BRACKET expression CIRCLECL_BRACKET statement
    | IF CIRCLEOP_BRACKET expression CIRCLECL_BRACKET statement ELSE statement
    ;

iteration_declaration:
    WHILE CIRCLEOP_BRACKET expression CIRCLECL_BRACKET statement
    ;

return_declaration:
    RETURN SEMICOL_PUNCT
    | RETURN expression SEMICOL_PUNCT
    ;

expression:
    var EQUAL expression
    | simple_expression
    ;

var:
    ID
    | ID SQUAREOP_BRACKET expression SQUARECL_BRACKET
    ;

simple_expression:
    sum_expression relational sum_expression
    | sum_expression
    ;

relational:
    EQ_RELOP
    | NOTEQ_RELOP
    | LESSEQ_RELOP
    | GREATEQ_RELOP
    | GREAT_RELOP
    | LESS_RELOP
    ;

sum_expression:
    sum_expression sum term
    | term
    ;

sum:
    PLUS_ALOP
    | MINUS_ALOP
    ;

term:
    term mult factor
    | factor
    ;

mult:
    MULT_PRE_ALOP
    | DIV_PRE_ALOP
    ;

factor:
    CIRCLEOP_BRACKET expression CIRCLECL_BRACKET
    | var
    | activation
    | NUM
    ;

activation:
    ID CIRCLEOP_BRACKET arguments CIRCLECL_BRACKET
    ;

arguments:
    argument_list
    |
    ;

argument_list:
    argument_list COMMA_PUNCT expression
    | expression
    ;
%%


int main(int argc, char *argv[]) {
    # if YYDEBUG == 1
    extern int yydebug;
    yydebug = 1;
    #endif

    if (argc != 2) {
        //NOT ENOUGH ARGS
        printf(RED"Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    glob_context.stream = fopen( argv[1] , "r" );
    if (glob_context.stream == NULL) {
        //FOPEN ERROR
        perror(RED"fopen() error"YELLOW);
        return 1;
    }
    glob_context.p_buffer = malloc(sizeof(Buffer));
    allocate_buffer(glob_context.p_buffer, glob_context.stream);


    glob_context.p_token_rec = malloc(sizeof(TokenRecord)); 

    yyparse();

    deallocate_buffer(glob_context.p_buffer);
    free(glob_context.p_buffer);
    free(glob_context.p_token_rec);
    fclose(glob_context.stream);


    return EXIT_SUCCESS;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}