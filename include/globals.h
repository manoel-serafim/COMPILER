
#ifndef __GLOBALS__
#define __GLOBALS__

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
    STRING,
    FIN,
} token_type;



#endif