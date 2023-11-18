#ifndef __LEXER__
#define __LEXER__


#include "macros.h"     //messaging
#include "libs.h"       //libraries
#include "buffer.h"



/*--[TOKEN DEFINITIONS]--*/
#define LEXEME_SIZE 256
/*--[TOKEN ENUMS]--*/
typedef enum {
    // Identifiers
    ID=256, // for not scrambling with ASCII
    NUM,             
    
    // Keywords (e.g., if, while, etc.)
    IF,
    ELSE,
    WHILE,
    RETURN,
    // Types
    INT,
    VOID,

    // Algebraic Operators (e.g., +, -, etc.)
    PLUS_ALOP,
    MINUS_ALOP,
    MULT_PRE_ALOP,
    DIV_PRE_ALOP,
    
    // Relational Operators (e.g., >, <, etc.)
    EQ_RELOP,
    NOTEQ_RELOP,
    LESSEQ_RELOP,
    GREATEQ_RELOP,
    GREAT_RELOP,
    LESS_RELOP,
    
    // Definition Operators (e.g., =)
    EQUAL,
    
    // Separators (e.g., (, ), {, }, etc.)
    CURLYOP_BRACKET,
    CURLYCL_BRACKET,
    CIRCLEOP_BRACKET,
    CIRCLECL_BRACKET,
    SQUAREOP_BRACKET,
    SQUARECL_BRACKET,
    
    // Punctuation (e.g., ;, ,, etc.)
    SEMICOL_PUNCT,
    COMMA_PUNCT,
    
    // Special
    INVALID,
    WHITESPACE,          
    COMMENT,
    STRING
} token_type;

/*--[TOKEN STRUCTS]--*/
typedef struct {
    token_type type;
    char lexeme[LEXEME_SIZE];
} TokenRecord;


/*--[LEXER TABLE ENUMS]--*/
typedef enum {
    START,
    IN_ID,
    IN_NUM,
    IN_DIV_OR_COMM,
    IN_COMMENT,
    IN_BLOCK_COMMENT,
    IN_LESS_OR_LEQ,
    IN_LEQ,
    IN_GREAT_OR_GEQ,
    IN_GEQ,
    IN_EQ_OR_EQRELOP,
    IN_EQRELOP,
    IN_NOTRELOP,
    OUT_NOTRELOP,
    IN_STRING,
    DONE,
    ERROR
} LexerState;

/*--[LEXER TABLE STRUCTS]--*/
typedef struct {
    LexerState next_state;
    token_type token_type;
    bool consumed; // Should advance input?
} LexerTableEntry;

/*--[ get_next_token - reuses previous buffer for optimization - returns into the token ]--*/
void get_next_token( Buffer* buffer, FILE * stream, TokenRecord * token );

#endif
