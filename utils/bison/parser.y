%{
#include "lexer.h"
#include "tree.h"
#include "macros.h"
#include <stdio.h>
#define yylex() get_next_token(glob_context.p_buffer, glob_context.stream, glob_context.p_token_rec)
void yyerror(const char *s);
%}

%token ID NUM IF ELSE WHILE RETURN INT VOID PLUS_ALOP MINUS_ALOP MULT_PRE_ALOP DIV_PRE_ALOP EQ_RELOP NOTEQ_RELOP LESSEQ_RELOP GREATEQ_RELOP GREAT_RELOP LESS_RELOP EQUAL CURLYOP_BRACKET CURLYCL_BRACKET CIRCLEOP_BRACKET CIRCLECL_BRACKET SQUAREOP_BRACKET SQUARECL_BRACKET SEMICOL_PUNCT COMMA_PUNCT WHITESPACE COMMENT STRING


%%
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

var_declaration:
    type_specifier ID SEMICOL_PUNCT
    | type_specifier ID SQUAREOP_BRACKET NUM SQUARECL_BRACKET SEMICOL_PUNCT
    ;

type_specifier:
    INT
    | VOID
    ;

fun_declaration:
    type_specifier ID CIRCLEOP_BRACKET parameters CIRCLECL_BRACKET compound_declaration
    ;

parameters:
    parameter_list
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

compound_declaration:
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

const char* yytokentypeToString(enum yytokentype token) {
    switch (token) {
        case YYEMPTY: return "YYEMPTY";
        case YYEOF: return "YYEOF";
        case YYerror: return "YYerror";
        case YYUNDEF: return "YYUNDEF";
        case ID: return "ID";
        case NUM: return "NUM";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case WHILE: return "WHILE";
        case RETURN: return "RETURN";
        case INT: return "INT";
        case VOID: return "VOID";
        case PLUS_ALOP: return "PLUS_ALOP";
        case MINUS_ALOP: return "MINUS_ALOP";
        case MULT_PRE_ALOP: return "MULT_PRE_ALOP";
        case DIV_PRE_ALOP: return "DIV_PRE_ALOP";
        case EQ_RELOP: return "EQ_RELOP";
        case NOTEQ_RELOP: return "NOTEQ_RELOP";
        case LESSEQ_RELOP: return "LESSEQ_RELOP";
        case GREATEQ_RELOP: return "GREATEQ_RELOP";
        case GREAT_RELOP: return "GREAT_RELOP";
        case LESS_RELOP: return "LESS_RELOP";
        case EQUAL: return "EQUAL";
        case CURLYOP_BRACKET: return "CURLYOP_BRACKET";
        case CURLYCL_BRACKET: return "CURLYCL_BRACKET";
        case CIRCLEOP_BRACKET: return "CIRCLEOP_BRACKET";
        case CIRCLECL_BRACKET: return "CIRCLECL_BRACKET";
        case SQUAREOP_BRACKET: return "SQUAREOP_BRACKET";
        case SQUARECL_BRACKET: return "SQUARECL_BRACKET";
        case SEMICOL_PUNCT: return "SEMICOL_PUNCT";
        case COMMA_PUNCT: return "COMMA_PUNCT";
        case WHITESPACE: return "WHITESPACE";
        case COMMENT: return "COMMENT";
        case STRING: return "STRING";
        default: return "Unknown token";
    }
}


void yyerror(const char *s) {
    puts(RED"__________________________________________[ SYNTATIC ERROR ]________________________________________");
    int in_line_placement = (glob_context.p_buffer)->line_char_pos;
    fpos_t line_placement = (glob_context.p_buffer)->line_pos;
    printf(CYN"\t[!] THE ERROR OCCURRED AT THE %zu-th LINE IN THE %zu-th CHAR [!]\n"RESET, (glob_context.p_buffer)->line_number, (glob_context.p_buffer)->line_char_pos);
    printf(YELLOW"\t[!] TOKEN LEXEME: "RED"%s "YELLOW"TOKEN TYPE: "RED"%s "YELLOW"[!]\n", (glob_context.p_token_rec)->lexeme, yytokentypeToString((glob_context.p_token_rec)->type));
    puts(RED"____________________________________________________________________________________________________"RESET);
}