#include "macros.h"     //messaging
#include "libs.h"       //libraries
#include "minperf.h"    //minimal perfect hash lookup



/*--[BUFFER DEFINITIONS]--*/
#define BUFF_SIZE 256

/*--[BUFFER STRUCTS]--*/
typedef struct {
    char *data;
    size_t loaded_size;
    size_t position;
    size_t line_number;
    size_t line_char_pos;
} Buffer;


/*--[BUFFER FUNCTIONS]--*/

size_t load_buffer(Buffer *buffer, FILE *file) {
    size_t read_size = fread(buffer->data, sizeof(char), BUFF_SIZE, file);
    if (ferror(file)) {
        perror(RED"ferror() error"YELLOW);
        exit(EXIT_FAILURE);
    }
    buffer->data[read_size] = '\0';
    buffer->position = 0;
    return read_size;
}

void allocate_buffer(Buffer *buffer, FILE *file) {
    buffer->data = (char *)calloc(BUFF_SIZE+1, sizeof(char));
    if (buffer->data == NULL) {
        perror(RED"calloc() error"YELLOW);
        exit(EXIT_FAILURE);
    }
    buffer->loaded_size = load_buffer(buffer, file);
    buffer->position = 0;
    buffer->line_number = 1;
    buffer->line_char_pos = 0;
}

void deallocate_buffer(Buffer *buffer) {
    free(buffer->data);
    buffer->data = NULL; // Set pointer to NULL after freeing
}



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



/*--[LEXER TABLE]--*/
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




/*--[ LEXER FUNCTIONS ]--*/
/*--[ get_next_char - returns next char in buffer and manage its memory ]--*/
char get_next_char(Buffer *buffer, FILE* file) {

    char current_char = buffer->data[buffer->position];
    if (current_char == '\0') {
        if (buffer->loaded_size < BUFF_SIZE){
            return EOF;
        }
        buffer->position = 0;
        buffer->loaded_size = load_buffer(buffer, file);
        current_char = buffer->data[buffer->position];
    }

    if (current_char == '\n') {
        buffer->line_number++;
        buffer->line_char_pos = 0;
    }

    buffer->position++;
    buffer->line_char_pos++;

    return current_char;
}

/*--[ get_next_token - reuses previous buffer for optimization - returns into the token ]--*/
void get_next_token( Buffer* buffer, FILE * stream, TokenRecord * token ){

    char ch;
    LexerTableEntry table_entry = { START, -1, true };
    memset(token->lexeme, 0, sizeof token->lexeme); //clean lexeme

    
    while( table_entry.next_state != DONE && table_entry.next_state != ERROR ){ 

        ch = get_next_char(buffer, stream);
        //adhoc for end of file
        if(ch == EOF){
            token->type = EOF;
            break;
        }
        if(ch < 0 || ch > 127){
            //Outside of lower ASCII range
            if(table_entry.next_state== IN_COMMENT){
                continue;
            }else{
                warn("ERROR: character outside of ASCII range allowed");
                token->type = INVALID;
                return;
            }
        }

        table_entry = lexerTable[table_entry.next_state][ch];

        if (table_entry.next_state == DONE && (table_entry.token_type == COMMENT || table_entry.token_type == WHITESPACE )){
            table_entry.next_state = START;
            memset(token->lexeme, 0, sizeof token->lexeme); //clean lexeme
            continue;
        }

        //if this whas a lookahead , do not consume it
        if( table_entry.consumed == false ) {
            buffer->position--;
            buffer->line_char_pos--;
        }else{
            token->lexeme[strlen(token->lexeme)] = ch;
            token->lexeme[strlen(token->lexeme)+1] = '\0';
        }

    }

    //in error get the rest of the lexeme
    if(table_entry.next_state == ERROR ){
        while( table_entry.next_state != DONE ){
            ch = get_next_char(buffer, stream);
            if(ch == EOF){
                token->type = EOF;
                break;
            } 
            table_entry = lexerTable[table_entry.next_state][ch];
            token->lexeme[strlen(token->lexeme)] = ch;
            token->lexeme[strlen(token->lexeme)+1] = '\0';
        }
    }

    
    if((table_entry.token_type == WHITESPACE) || (table_entry.token_type == COMMENT) ) table_entry.token_type = EOF; 
    //check if id is keyword
    if( table_entry.token_type == ID ){
        const struct keyword* key = in_word_set(token->lexeme, strlen(token->lexeme));
        if(key != NULL){
            table_entry.token_type =  key->type;
        }

    }
    if(table_entry.token_type == INVALID ) warn("AN ERROR OCCURED AT %dth LINE IN THE %dth CHAR:\n LEXEME: %s", buffer->line_number, buffer->line_char_pos,token->lexeme ); //show
    
    token->type = table_entry.token_type;
}





/**/
void indicate_error(Buffer* buffer){

    warn("AN ERROR OCCURRED AT LINE: %zu IN THE %zu-th CHAR:\n", buffer->line_number, buffer->line_char_pos);
        
    // Print the actual line
    size_t line_start = 0;
    while (line_start < buffer->loaded_size && buffer->data[line_start] != '\n') {
        line_start++;
    }
    
    size_t line_end = line_start + 1;
    while (line_end < buffer->loaded_size && buffer->data[line_end] != '\n') {
        line_end++;
    }
    // Print the error line
    for (size_t i = line_start; i < line_end; ++i) {
        putchar(buffer->data[i]);
    }
    putchar('\n');
    
}




