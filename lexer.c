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
    INVALID,
    WHITESPACE,          
    COMMENT,
    STRING
} TokenType;


typedef struct {
    TokenType type;
    char lexeme[LEXEME_SIZE];
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
    DONE,
    ERROR
} LexerState;

// Define the lexer table
typedef struct {
    LexerState nextState;
    TokenType tokenType;
    bool shouldConsume; // Should advance input?
} LexerTableEntry;

// 128 because of the 128 ASCII chars
/*--[ LexTable - using meaningfull vars not only ints ]--*/
LexerTableEntry lexerTable[17][128] = { 
    /*--[ only accepting delimiters that make sense ]--*/
    [START] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...'~'] = { ERROR, INVALID, false },
        /*--[RULES]--*/
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
        [' '] = { DONE, WHITESPACE, true },
        ['\t'] = { DONE, WHITESPACE, true },
        ['\n'] = { DONE, WHITESPACE, true }

    },

    // IN_ID state
    [IN_ID] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...'~'] = { ERROR, INVALID, false },

        /*--[RULES]--*/
        ['a'...'z'] = { IN_ID, ID, true },
        ['A'...'Z'] = { IN_ID, ID, true },
        ['0'...'9'] = { IN_ID, ID, true },
        ['_'] = { IN_ID, ID, true },
        ['$'] = { IN_ID, ID, true },

        /*--[DELIMITERS-identifier]--*/
        //arithmetic
        ['+'] = { DONE, ID, false }, 
        ['-'] = { DONE, ID, false }, 
        ['*'] = { DONE, ID, false },
        ['/'] = { DONE, ID, false },
        //relational 
        ['<'] = { DONE, ID, false }, 
        ['>'] = { DONE, ID, false }, 
        ['='] = { DONE, ID, false }, 
        ['!'] = { DONE, ID, false },
        //ponctual 
        [';'] = { DONE, ID, false },
        [','] = { DONE, ID, false },
        //macros
        ['"'] = { DONE, ID, false },
        //in/out functions/arrays
        ['('] = { DONE, ID, false },
        [')'] = { DONE, ID, false },
        ['{'] = { DONE, ID, false },
        ['}'] = { DONE, ID, false },
        ['['] = { DONE, ID, false },
        [']'] = { DONE, ID, false },
        //whitespace
        [' '] = { DONE, ID, false },
        ['\t'] ={ DONE, ID, false },
        ['\n'] ={ DONE, ID, false }

    },

    // IN_NUM state
    [IN_NUM] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...'~'] = { ERROR, INVALID, false },

        /*--[RULES]--*/
        ['0'...'9'] = { IN_NUM, NUM, true },

        /*--[DELIMITERS-number]--*/
        //arithmetic
        ['+'] = { DONE, NUM, false }, 
        ['-'] = { DONE, NUM, false }, 
        ['*'] = { DONE, NUM, false },
        ['/'] = { DONE, NUM, false },
        //relational 
        ['<'] = { DONE, NUM, false }, 
        ['>'] = { DONE, NUM, false }, 
        ['='] = { DONE, NUM, false }, 
        ['!'] = { DONE, NUM, false },
        //ponctual 
        [';'] = { DONE, NUM, false },
        [','] = { DONE, NUM, false },
        //in/out functions/arrays
        //['('] = { DONE, ID, false },
        [')'] = { DONE, NUM, false },
        //['{'] = { DONE, ID, false },
        ['}'] = { DONE, NUM, false },
        //['['] = { DONE, ID, false },
        [']'] = { DONE, NUM, false },
        //whitespace
        [' '] = { DONE, NUM, false },
        ['\t'] ={ DONE, NUM, false },
        ['\n'] ={ DONE, NUM, false }

    },

    // IN_DIV_OR_COMM 
    [IN_DIV_OR_COMM] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...'~'] = { ERROR, INVALID, false }, 

        /*--[RULES]--*/
        ['*'] = { IN_COMMENT, COMMENT, true },

        /*--[DELIMITERS-division]--*/
        //alphanumerical
        ['0'...'9'] = { DONE, DIV_PRE_ALOP, false }, 
        ['a'...'z'] = { DONE, DIV_PRE_ALOP, false }, 
        ['A'...'Z'] = { DONE, DIV_PRE_ALOP, false }, 
        ['_'] = { IN_ID, DIV_PRE_ALOP, false },
        ['$'] = { IN_ID, DIV_PRE_ALOP, false },
        //whitespace
        [' '] = { DONE, DIV_PRE_ALOP, false },
        ['\t'] ={ DONE, DIV_PRE_ALOP, false },
        ['\n'] ={ DONE, DIV_PRE_ALOP, false }
        
    },
    // IN_COMMENT state
    [IN_COMMENT] = {
        /*--[DEFAULTING TO STAY FOR ALL CHARS]--*/
        ['\0'...'~'] = { IN_COMMENT, COMMENT, true },

        /*--[RULES]--*/
        ['*'] = { IN_BLOCK_COMMENT, COMMENT, true },
        
    },
    // IN_BLOCK_COMMENT state
    [IN_BLOCK_COMMENT] = {
        /*--[DEFAULTING TO GO BACK FOR ALL CHARS]--*/
        ['\0'...'~'] = { IN_COMMENT, COMMENT, true },

        /*--[RULES]--*/
        ['/'] = { DONE, COMMENT, true }, // Go back to initial state to get the next token
        ['*'] = { IN_BLOCK_COMMENT, COMMENT, true },

    },

    // IN_LESS_OR_LEQ state
    [IN_LESS_OR_LEQ] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...'~'] = { ERROR, INVALID, false },

        /*--[RULES]--*/
        ['='] = { DONE, LESSEQ_RELOP, true },

        /*--[DELIMITERS-less]--*/
        //alfabethical
        ['a'...'z'] = { DONE, LESS_RELOP, false },
        ['A'...'Z'] = { DONE, LESS_RELOP, false },
        ['0'...'9'] = { DONE, LESS_RELOP, false },
        ['_'] = { DONE, LESS_RELOP, false },
        ['$'] = { DONE, LESS_RELOP, false },
        //string relational
        ['"'] = { DONE, LESS_RELOP, false },
        //whitespace
        [' '] = { DONE, LESS_RELOP, false },
        ['\t'] ={ DONE, LESS_RELOP, false },
        ['\n'] ={ DONE, LESS_RELOP, false }
    },
    // IN_LESS_OR_LEQ state
    [IN_GREAT_OR_GEQ] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...'~'] = { ERROR, INVALID, false },

        /*--[RULES]--*/
        ['='] = { DONE, GREATEQ_RELOP, true },

        /*--[DELIMITERS-grater]--*/
        //alfabethical
        ['a'...'z'] = { DONE, GREAT_RELOP, false },
        ['A'...'Z'] = { DONE, GREAT_RELOP, false },
        ['0'...'9'] = { DONE, GREAT_RELOP, false },
        ['_'] = { DONE, GREAT_RELOP, false },
        ['$'] = { DONE, GREAT_RELOP, false },
        //string relational
        ['"'] = { DONE, GREAT_RELOP, false },
        //whitespace
        [' '] = { DONE, GREAT_RELOP, false },
        ['\t'] ={ DONE, GREAT_RELOP, false },
        ['\n'] ={ DONE, GREAT_RELOP, false }
    },
    // IN_EQRELOP
    [IN_EQ_OR_EQRELOP] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...'~'] = { ERROR, INVALID, false },

        /*--[RULES]--*/
        ['='] = { DONE, EQ_RELOP, true },
        
        /*--[DELIMITERS-equal]--*/
        //alfabethical
        ['a'...'z'] = { DONE, EQUAL, false },
        ['A'...'Z'] = { DONE, EQUAL, false },
        ['0'...'9'] = { DONE, EQUAL, false },
        ['_'] = { DONE, EQUAL, false },
        ['$'] = { DONE, EQUAL, false },
        //string relational
        ['"'] = { DONE, EQUAL, false },
        //whitespace
        [' '] = { DONE, EQUAL, false },
        ['\t'] ={ DONE, EQUAL, false },
        ['\n'] ={ DONE, EQUAL, false }

    },

    [IN_NOTRELOP] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...'~'] = { ERROR, INVALID, false },

        /*--[RULES]--*/
        ['='] = { DONE, NOTEQ_RELOP, true },
        
    },
    [IN_STRING] = {
        /*--[DEFAULTING TO IN_STRING]--*/
        ['\0'...'~'] = { IN_STRING, STRING, true },
        ['"'] = { DONE, STRING, true },

    },
    // DONE state
    [DONE] = {},
    [ERROR]= {
        /*--[GET THE REST OF THE LEXEME]--*/
        /*--[DEFAULTING TO STAY IN ERROR]--*/
        ['\0'...'~'] = { ERROR, INVALID, true },

        /*--[DELIMITERS-error]--*/
        ['a'...'z'] = { DONE, INVALID, true },
        ['A'...'Z'] = { DONE, INVALID, true },
        ['0'...'9'] = { DONE, INVALID, true },
        ['_'] = { DONE, INVALID, true },
        ['$'] = { DONE, INVALID, true },
        //arithmetic
        ['+'] = { DONE, INVALID, true }, 
        ['-'] = { DONE, INVALID, true }, 
        ['*'] = { DONE, INVALID, true },
        ['/'] = { DONE, INVALID, true },
        //relational 
        ['<'] = { DONE, INVALID, true }, 
        ['>'] = { DONE, INVALID, true }, 
        ['='] = { DONE, INVALID, true }, 
        ['!'] = { DONE, INVALID, true },
        //ponctual 
        [';'] = { DONE, INVALID, true },
        [','] = { DONE, INVALID, true },
        //macros
        ['"'] = { DONE, INVALID, true },
        //in/out functions/arrays
        ['('] = { DONE, INVALID, true },
        [')'] = { DONE, INVALID, true },
        ['{'] = { DONE, INVALID, true },
        ['}'] = { DONE, INVALID, true },
        ['['] = { DONE, INVALID, true },
        [']'] = { DONE, INVALID, true },
        //whitespace
        [' '] = { DONE, INVALID, true },
        ['\t'] ={ DONE, INVALID, true },
        ['\n'] ={ DONE, INVALID, true }


    }
};



/*--[ getNextToken - reuses prev buffer for optimization - returns into the token ]--*/
void getNextToken( Buffer* buffer, FILE * stream, TokenRecord * token ){

    char ch;
    LexerTableEntry table_entry = { START, -1, true };
    memset(token->lexeme, 0, sizeof token->lexeme); //clean lexeme

    
    while( table_entry.nextState != DONE && table_entry.nextState != ERROR ){ 

        ch = getNextChar(buffer, stream);
        //adhoc for end of file
        if(ch == EOF){
            token->type = EOF;
            break;
        }

        table_entry = lexerTable[table_entry.nextState][ch];

        if (table_entry.nextState == DONE && (table_entry.tokenType == COMMENT || table_entry.tokenType == WHITESPACE )){
            table_entry.nextState = START;
            memset(token->lexeme, 0, sizeof token->lexeme); //clean lexeme
            continue;
        }

        //if this whas a lookahead , do not consume it
        if( table_entry.shouldConsume == false ) {
            buffer->position--;
            buffer->line_char_pos--;
        }else{
            token->lexeme[strlen(token->lexeme)] = ch;
            token->lexeme[strlen(token->lexeme)+1] = '\0';
        }

    }

    //in error get the rest of the lexeme
    if(table_entry.nextState == ERROR ){
        while( table_entry.nextState != DONE ){
            ch = getNextChar(buffer, stream);
            if(ch == EOF){
                token->type = EOF;
                break;
            } 
            table_entry = lexerTable[table_entry.nextState][ch];
            token->lexeme[strlen(token->lexeme)] = ch;
            token->lexeme[strlen(token->lexeme)+1] = '\0';
        }
    }

    
    if((table_entry.tokenType == WHITESPACE) || (table_entry.tokenType == COMMENT) ) table_entry.tokenType = EOF; 
    if(table_entry.tokenType == INVALID ) warn("AN ERROR OCCURED AT %dth LINE IN THE %dth CHAR:\n LEXEME: %s", buffer->line_number, buffer->line_char_pos,token->lexeme );
    
    token->type = table_entry.tokenType;

    

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

    
    TokenRecord* token = malloc(sizeof(TokenRecord)); 
    

    
    do{
        getNextToken(&buffer, stream, token);
        if(token->type == EOF){
            break;
        }
        if(token->type == INVALID){
            return EXIT_FAILURE;
        }
        printf(GREEN"LEXEME:"RED"%s\t"YELLOW"TYPE: %d\n"RESET, token->lexeme, token->type);
    }while(token->type != EOF);
    
    
    //cleanup functions
    free(token);
    deallocateBuffer(&buffer);
    fclose(stream);



    return EXIT_SUCCESS;
}