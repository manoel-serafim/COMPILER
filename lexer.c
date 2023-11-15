/*
    LEXER
*/


#include <stdio.h>      //io
#include <errno.h>      //error handeling
#include <string.h>     //string operations 
#include <stdarg.h>     //used for messaging
#include <stdbool.h>    //bool type

//ANSI colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define CYN "\033[36m"
#define YELLOW "\033[33m"

/* Functions for printing messages with colors */
void show(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    puts(NULL);
    va_end(args);
}

void sucs(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf(CYN "[+] ");
    vprintf(format, args);
    puts(RESET);
    va_end(args);
}

void info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf(YELLOW "[*] ");
    vprintf(format, args);
    puts(RESET);
    va_end(args);
}

void warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf(RED "[-] ");
    vprintf(format, args);
    puts(RESET);
    va_end(args);
}


//LIBEND

typedef enum {
    // Identifiers
    ID,
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
    ERROR,
    WHITESPACE,          
    COMMENT,
    STRING
} TokenType;


typedef struct {
    TokenType type;
    union {
        char* lexeme;
        int numval;
    } attribute;
} TokenRecord;


// Define the states for the lexer
typedef enum {
    START,
    IN_ID,
    IN_NUM,
    IN_DIV_OR_COMM,
    IN_COMMENT,
    IN_BLOCK_COMMENT,
    IN_LESS_OR_LEQ,
    IN_LEQ,
    IN_STRING,
    DONE
} LexerState;

// Define the lexer table
typedef struct {
    LexerState nextState;
    TokenType tokenType;
    bool shouldConsume;
} LexerTableEntry;

// 128 because of the 128 ASCII chars
/*  [LexTable - using meaningfull vars not only ints]  */
LexerTableEntry lexerTable[200][128] = { 
    // START state
    [START] = {
        ['a'...'z'] = { IN_ID, ID, true },
        ['A'...'Z'] = { IN_ID, ID, true },
        ['0'...'9'] = { IN_NUM, NUM, true },
        ['/'] = { IN_DIV_OR_COMM, DIV_PRE_ALOP, false }, //NO LOOKAHEAD STATE
        ['+'] = { DONE, PLUS_ALOP, false }, //NO LOOKAHEAD
        ['-'] = { DONE, MINUS_ALOP, false }, //NO LOOKAHEAD
        ['*'] = { DONE, MULT_PRE_ALOP, false }, //NO LOOKAHEAD
        ['<'] = { IN_LESS_OR_LEQ, LESS_RELOP, false }, //NO LOOKAHEAD STATE
        ['>'] = { DONE, GREATEQ_RELOP, false }, //NO LOOKAHEAD STATE
        ['='] = { DONE, EQ_RELOP, false }, //NO LOOKAHEAD STATE
        ['!'] = { DONE, SQUARECL_BRACKET, true },
        [';'] = { DONE, SEMICOL_PUNCT, true }, //NO LOOKAHEAD
        [','] = { DONE, COMMA_PUNCT, true }, //NO LOOKAHEAD
        ['"'] = { IN_STRING, STRING, false },
        ['('] = { DONE, CIRCLEOP_BRACKET, true }, 
        [')'] = { DONE, CIRCLECL_BRACKET, true },
        ['{'] = { DONE, CURLYOP_BRACKET, true },
        ['}'] = { DONE, CURLYCL_BRACKET, true },
        ['['] = { DONE, SQUAREOP_BRACKET, true },
        [']'] = { DONE, SQUARECL_BRACKET, true },
        [' '|'\t'|'\n'] = { START, WHITESPACE, true }
    },
    // IN_ID state
    [IN_ID] = {
        ['a'...'z'] = { IN_ID, ID, true },
        ['A'...'Z'] = { IN_ID, ID, true },
        ['0'...'9'] = { IN_ID, ID, true },
        ['_'|'$'] = { IN_ID, ID, true },
        [' '|'\t'|'\n'| '='| '['| ';'| '('| '<'| '>'| '+'| '-'| '*'| '/'| '|'| ')'| ']'| '!'] = { DONE, ID, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['\0'] = { DONE, ERROR, false } // CATCH-ALL OTHERS
    },
    // IN_NUM state
    [IN_NUM] = {
        ['0'...'9'] = { IN_NUM, NUM, true },
        [' '| '\t'| '\n'| '\0'| '='| ';'| '+'| '-'| '*'| '/'| '|'| ']'] = { DONE, NUM, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['0'] = { DONE, ERROR, false } // CATCH-ALL OTHERS
    },
    // IN_DIV_OR_COMM
    [IN_DIV_OR_COMM] = {
        ['*'] = { IN_COMMENT, COMMENT, false },
        ['0'...'9'] = { DONE, DIV_PRE_ALOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['a'...'z'] = { DONE, DIV_PRE_ALOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['A'...'Z'] = { DONE, DIV_PRE_ALOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '/'| '|'| ')'| ']'| '!'] = { DONE, DIV_PRE_ALOP, false } // IN CASE OF DELIMITERS (RETURN TOKENTYPE)

    },
    // IN_COMMENT state
    [IN_COMMENT] = {
        ['*'] = { IN_BLOCK_COMMENT, COMMENT, false },
        ['0'...'9'] = { IN_COMMENT, COMMENT, false }, // STAY FOR ALLCHAR
        ['a'...'z'] = { IN_COMMENT, COMMENT, false }, // STAY FOR ALLCHAR
        ['A'...'Z'] = { IN_COMMENT, COMMENT, false }, // STAY FOR ALLCHAR
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '/'| '|'| ')'| ']'| '!'] = { IN_COMMENT, COMMENT, false } // STAY FOR ALLCHAR
    },
    // IN_BLOCK_COMMENT state
    [IN_BLOCK_COMMENT] = {
        ['/'] = { DONE, COMMENT, false }, // DONE NOT CONSIDERING DELIMITERS
        ['*'] = { IN_BLOCK_COMMENT, COMMENT, false },
        ['0'...'9'] = { IN_COMMENT, COMMENT, false }, // GOBACK FOR ALLCHAR
        ['a'...'z'] = { IN_COMMENT, COMMENT, false }, // GOBACK FOR ALLCHAR
        ['A'...'Z'] = { IN_COMMENT, COMMENT, false }, // GOBACK FOR ALLCHAR
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '|'| ')'| ']'| '!'] = { IN_COMMENT, COMMENT, false } // GOBACK FOR ALLCHAR
    },
    // IN_LESS_OR_LEQ state
    [IN_LESS_OR_LEQ] = {
        ['0'...'9'] = { DONE, LESS_RELOP, false }, // GOBACK FOR ALLCHAR
        ['a'...'z'] = { DONE, LESS_RELOP, false }, // GOBACK FOR ALLCHAR
        ['A'...'Z'] = { DONE, LESS_RELOP, false }, // GOBACK FOR ALLCHAR
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '|'| ')'| ']'| '!'|'/'|'*'] = { DONE, LESS_RELOP, false } // GOBACK FOR ALLCHAR
    },
    // DONE state
    [DONE] = {}
};



/*  [getToken - returns TokenType]  */

/*  [main function - returns status]  */
int main(int argc, char *argv[]) {

    if (argc != 2) {
        //NOT ENOUGH ARGS
        warn("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE * stream = fopen( argv[1] , "r" );
    if (stream == NULL) {
        //FOPEN ERROR
        perror(RED"fopen() error"YELLOW);
        return 1;
    }

    while (!feof(stream)) { //while not in end‐of‐file



    }


    
    //closing stream
    fclose(stream);



    return 0;
}