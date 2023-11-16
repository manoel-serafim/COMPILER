/*
    TABLE-DRIVEN LEXER
*/

#include "libs.h"

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
    IN_GREAT_OR_GEQ,
    IN_GEQ,
    IN_EQ_OR_EQRELOP,
    IN_EQRELOP,
    IN_NOTRELOP,
    OUT_NOTRELOP,
    IN_STRING,
    DONE
} LexerState;

// Define the lexer table
typedef struct {
    LexerState nextState;
    TokenType tokenType;
    bool shouldConsume; // Should advance input?
} LexerTableEntry;

// 128 because of the 128 ASCII chars
/*--[ LexTable - using meaningfull vars not only ints ]--*/
LexerTableEntry lexerTable[16][128] = { 
    /*--[TODO]--*/
    /*recheck each delimiter for all of the chars possible*/
    /*recheck null input chars*/
    // START state
    [START] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['a'...'z'] = { IN_ID, ID, true },
        ['A'...'Z'] = { IN_ID, ID, true },
        ['_'] = { IN_ID, ID, true },
        ['$'] = { IN_ID, ID, true },
        ['0'...'9'] = { IN_NUM, NUM, true },
        ['/'] = { IN_DIV_OR_COMM, DIV_PRE_ALOP, true }, 
        ['+'] = { DONE, PLUS_ALOP, true }, 
        ['-'] = { DONE, MINUS_ALOP, true }, 
        ['*'] = { DONE, MULT_PRE_ALOP, true }, 
        ['<'] = { IN_LESS_OR_LEQ, LESS_RELOP, true }, 
        ['>'] = { IN_GREAT_OR_GEQ, GREAT_RELOP, true }, 
        ['='] = { IN_EQ_OR_EQRELOP, EQUAL, true }, 
        ['!'] = { IN_NOTRELOP, NOTEQ_RELOP, true }, //NO LOOKAHEAD STATE
        [';'] = { DONE, SEMICOL_PUNCT, true }, //NO LOOKAHEAD 
        [','] = { DONE, COMMA_PUNCT, true }, //NO LOOKAHEAD
        ['"'] = { IN_STRING, STRING, true }, // NO LOOKAHEAD STATE
        ['('] = { DONE, CIRCLEOP_BRACKET, true }, 
        [')'] = { DONE, CIRCLECL_BRACKET, true },
        ['{'] = { DONE, CURLYOP_BRACKET, true },
        ['}'] = { DONE, CURLYCL_BRACKET, true },
        ['['] = { DONE, SQUAREOP_BRACKET, true },
        [']'] = { DONE, SQUARECL_BRACKET, true },
        [' '] = { START, WHITESPACE, true },
        ['\t'] = { START, WHITESPACE, true },
        ['\n'] = { START, WHITESPACE, true },
    },
    // IN_ID state
    [IN_ID] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['a'...'z'] = { IN_ID, ID, true },
        ['A'...'Z'] = { IN_ID, ID, true },
        ['0'...'9'] = { IN_ID, ID, true },
        ['_'] = { IN_ID, ID, true },
        ['$'] = { IN_ID, ID, true },
        [' '|'\t'|'\n'| '='| '['| ';'| '('| '<'| '>'| '+'| '-'| '*'| '/'| '|'| ')'| ']'| '!'] = { DONE, ID, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['\0'] = { DONE, ID, false } // IF FILE ONLY HAS AN ID
    },
    // IN_NUM state
    [IN_NUM] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['0'...'9'] = { IN_NUM, NUM, true },
        [' '| '\t'| '\n'| '\0'| '='| ';'| '+'| '-'| '*'| '/'| '|'| ']'] = { DONE, NUM, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['\0'] = { DONE, ERROR, false } // CATCH-ALL OTHERS
    },
    // IN_DIV_OR_COMM
    [IN_DIV_OR_COMM] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['*'] = { IN_COMMENT, COMMENT, true },
        ['0'...'9'] = { DONE, DIV_PRE_ALOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['a'...'z'] = { DONE, DIV_PRE_ALOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['A'...'Z'] = { DONE, DIV_PRE_ALOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '/'| '|'| ')'| ']'| '!'] = { DONE, DIV_PRE_ALOP, false } // IN CASE OF DELIMITERS (RETURN TOKENTYPE)

    },
    // IN_COMMENT state
    [IN_COMMENT] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['*'] = { IN_BLOCK_COMMENT, COMMENT, true },
        ['0'...'9'] = { IN_COMMENT, COMMENT, true }, // STAY FOR ALLCHAR
        ['a'...'z'] = { IN_COMMENT, COMMENT, true }, // STAY FOR ALLCHAR
        ['A'...'Z'] = { IN_COMMENT, COMMENT, true }, // STAY FOR ALLCHAR
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '/'| '|'| ')'| ']'| '!'] = { IN_COMMENT, COMMENT, true } // STAY FOR ALLCHAR
    },
    // IN_BLOCK_COMMENT state
    [IN_BLOCK_COMMENT] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['/'] = { START, COMMENT, true }, // Go back to initial state to get the next token
        ['*'] = { IN_BLOCK_COMMENT, COMMENT, true },
        ['0'...'9'] = { IN_COMMENT, COMMENT, true }, // GOBACK FOR ALLCHAR
        ['a'...'z'] = { IN_COMMENT, COMMENT, true }, // GOBACK FOR ALLCHAR
        ['A'...'Z'] = { IN_COMMENT, COMMENT, true }, // GOBACK FOR ALLCHAR
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '|'| ')'| ']'| '!'] = { IN_COMMENT, COMMENT, true } // GOBACK FOR ALLCHAR
    },
    // IN_LESS_OR_LEQ state
    [IN_LESS_OR_LEQ] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['='] = { DONE, LESSEQ_RELOP, true },
        ['0'...'9'] = { DONE, LESS_RELOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['a'...'z'] = { DONE, LESS_RELOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['A'...'Z'] = { DONE, LESS_RELOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '|'| ')'| ']'| '!'|'/'|'*'] = { DONE, LESS_RELOP, false } // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
    },
    // IN_LESS_OR_LEQ state
    [IN_GREAT_OR_GEQ] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['='] = { DONE, GREATEQ_RELOP, true },
        ['0'...'9'] = { DONE, GREAT_RELOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['a'...'z'] = { DONE, GREAT_RELOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['A'...'Z'] = { DONE, GREAT_RELOP, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '|'| ')'| ']'| '!'|'/'|'*'] = { DONE, GREAT_RELOP, false } // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
    },
    // IN_EQRELOP
    [IN_EQ_OR_EQRELOP] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['='] = { DONE, EQ_RELOP, true },
        ['0'...'9'] = { DONE, EQUAL, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['a'...'z'] = { DONE, EQUAL, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['A'...'Z'] = { DONE, EQUAL, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '|'| ')'| ']'| '!'|'/'|'*'] = { DONE, EQUAL, false } // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
    },
    [IN_NOTRELOP] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['='] = { DONE, NOTEQ_RELOP, false },
        ['0'...'9'] = { DONE, ERROR, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['a'...'z'] = { DONE, ERROR, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        ['A'...'Z'] = { DONE, ERROR, false }, // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '|'| ')'| ']'| '!'|'/'|'*'] = { DONE, ERROR, false } // IN CASE OF DELIMITERS (RETURN TOKENTYPE)
    },
    [IN_STRING] = {
        ['\0'...'~'] = { DONE, ERROR, true }, // DEFAULT TO ERROR
        ['"'] = { DONE, STRING, true },
        ['0'...'9'] = { IN_STRING, STRING, true }, // STAY IN STR
        ['a'...'z'] = { IN_STRING, STRING, true }, // STAY IN STR
        ['A'...'Z'] = { IN_STRING, STRING, true }, // STAY IN STR
        [' '| '\t'| '\n'| '['| ';'| '('| '<'| '>'| '+'| '-'| '|'| ')'| ']'| '!'|'/'|'*'] = { IN_STRING, STRING, true } // STAY IN STR
    },
    // DONE state
    [DONE] = {}
};


/*--[ getNextChar - returns next char in buffer ]--*/

/*--[ getNextToken - reuses prev buffer for optimization - returns TokenType ]--*/
TokenType getNextToken( Buffer buffer, FILE * stream ){

    char ch;
    TokenType token_type;
    LexerTableEntry table_entry = { START, -1, false };

    while( table_entry.nextState != DONE && table_entry.tokenType != ERROR){ 
        
        ch = getNextChar(&buffer, stream);
        table_entry = lexerTable[table_entry.nextState][ch];

        //if should not consume, go back one pos in buffer->position
        if( !table_entry.shouldConsume ) buffer.position-- ;

    }
    if(table_entry.tokenType == ERROR ) warn("AN ERROR OCCURED AT LINE: %d IN THE %dth CHAR:\n", buffer.line_number, buffer.line_char_pos);
    
    return table_entry.tokenType;

    

}

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
    
    Buffer buffer;
    allocateBuffer(&buffer, stream);

    int token_type = getNextToken(buffer, stream);
    printf("%d", token_type);
    
    deallocateBuffer(&buffer);
    


    
    
    //closing stream
    fclose(stream);



    return 0;
}