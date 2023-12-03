#include <lexer.h>
#include "minperf.h"    //minimal perfect hash lookup



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
    IN_MULT_OR_COMM,
    DONE,
    ERROR
} LexerState;

/*--[LEXER TABLE STRUCTS]--*/
typedef struct {
    LexerState next_state;
    yytoken_kind_t token_type;
    bool consume; // Should advance input?
    bool store;
} LexerTableEntry;


/*--[LEXER TABLE]--*/
// 128 because of the 128 ASCII chars
/*--[ LexTable - using meaningfull vars not only ints ]--*/
LexerTableEntry lexerTable[18][128] = { 
    /*--[ only accepting delimiters that make sense ]--*/
    [START] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...127] = { ERROR, YYerror, false, false },
        /*--[RULES]--*/
        ['a'...'z'] = { IN_ID, ID, true, true },
        ['A'...'Z'] = { IN_ID, ID, true, true },
        ['_'] = { IN_ID, ID, true, true },
        ['$'] = { IN_ID, ID, true, true },
        ['0'...'9'] = { IN_NUM, NUM, true, true },
        ['/'] = { IN_DIV_OR_COMM, DIV_PRE_ALOP, true, true }, 
        ['+'] = { DONE, PLUS_ALOP, true, true }, 
        ['-'] = { DONE, MINUS_ALOP, true, true }, 
        ['*'] = { DONE, IN_MULT_OR_COMM, true, true }, 
        ['<'] = { IN_LESS_OR_LEQ, LESS_RELOP, true, true }, 
        ['>'] = { IN_GREAT_OR_GEQ, GREAT_RELOP, true, true }, 
        ['='] = { IN_EQ_OR_EQRELOP, EQUAL, true, true }, 
        ['!'] = { IN_NOTRELOP, NOTEQ_RELOP, true, true }, //NO LOOKAHEAD STATE
        [';'] = { DONE, SEMICOL_PUNCT, true, true }, //NO LOOKAHEAD 
        [','] = { DONE, COMMA_PUNCT, true, true }, //NO LOOKAHEAD
        ['"'] = { IN_STRING, STRING, true, true }, // NO LOOKAHEAD STATE
        ['('] = { DONE, CIRCLEOP_BRACKET, true, true }, 
        [')'] = { DONE, CIRCLECL_BRACKET, true, true },
        ['{'] = { DONE, CURLYOP_BRACKET, true, true },
        ['}'] = { DONE, CURLYCL_BRACKET, true, true },
        ['['] = { DONE, SQUAREOP_BRACKET, true, true },
        [']'] = { DONE, SQUARECL_BRACKET, true, true },
        [' '] = { START, WHITESPACE, true, false },
        ['\t'] = { START, WHITESPACE, true, false },
        ['\n'] = { START, WHITESPACE, true, false },
        ['\0'] = {DONE, YYEOF, true, false }, //finished

    },

    // IN_ID state
    [IN_ID] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...127] = { ERROR, YYerror, false, false },

        /*--[RULES]--*/
        ['a'...'z'] = { IN_ID, ID, true, true },
        ['A'...'Z'] = { IN_ID, ID, true, true },
        ['0'...'9'] = { IN_ID, ID, true, true },
        ['_'] = { IN_ID, ID, true, true },
        ['$'] = { IN_ID, ID, true, true },

        /*--[DELIMITERS-identifier]--*/
        //arithmetic
        ['+'] = { DONE, ID, false, false }, 
        ['-'] = { DONE, ID, false, false }, 
        ['*'] = { DONE, ID, false, false },
        ['/'] = { DONE, ID, false, false },
        //relational 
        ['<'] = { DONE, ID, false, false }, 
        ['>'] = { DONE, ID, false, false }, 
        ['='] = { DONE, ID, false, false }, 
        ['!'] = { DONE, ID, false, false },
        //punctual 
        [';'] = { DONE, ID, false, false },
        [','] = { DONE, ID, false, false },
        //macros
        ['"'] = { DONE, ID, false, false },
        //in/out functions/arrays
        ['('] = { DONE, ID, false, false },
        [')'] = { DONE, ID, false, false },
        ['{'] = { DONE, ID, false, false },
        ['}'] = { DONE, ID, false, false },
        ['['] = { DONE, ID, false, false },
        [']'] = { DONE, ID, false, false },
        //whitespace
        [' '] = { DONE, ID, true, false },
        ['\t'] ={ DONE, ID, true, false },
        ['\n'] ={ DONE, ID, true, false },
        ['\0'] = { DONE, ID, true, false }
    },

    // IN_NUM state
    [IN_NUM] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...127] = { ERROR, YYerror, false, false },

        /*--[RULES]--*/
        ['0'...'9'] = { IN_NUM, NUM, true, true },

        /*--[DELIMITERS-number]--*/
        //arithmetic
        ['+'] = { DONE, NUM, false, false }, 
        ['-'] = { DONE, NUM, false, false }, 
        ['*'] = { DONE, NUM, false, false },
        ['/'] = { DONE, NUM, false, false },
        //relational 
        ['<'] = { DONE, NUM, false, false }, 
        ['>'] = { DONE, NUM, false, false }, 
        ['='] = { DONE, NUM, false, false }, 
        ['!'] = { DONE, NUM, false, false },
        //punctual 
        [';'] = { DONE, NUM, false, false },
        [','] = { DONE, NUM, false, false },
        //in/out functions/arrays
        //['('] = { DONE, ID, false },
        [')'] = { DONE, NUM, false, false },
        //['{'] = { DONE, ID, false },
        ['}'] = { DONE, NUM, false, false },
        //['['] = { DONE, ID, false },
        [']'] = { DONE, NUM, false, false },
        //whitespace
        [' '] = { DONE, NUM, true, false },
        ['\t'] ={ DONE, NUM, true, false },
        ['\n'] ={ DONE, NUM, true, false },
        ['\0'] = { DONE, NUM, true, false }

    },

    // IN_DIV_OR_COMM 
    [IN_DIV_OR_COMM] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...127] = { ERROR, YYerror, false, false }, 
        
        /*--[RULES]--*/
        ['*'] = { IN_COMMENT, COMMENT, true, true },
        
        /*--[DELIMITERS-division]--*/
        //alphanumerical
        ['0'...'9'] = { DONE, DIV_PRE_ALOP, false, false }, 
        ['a'...'z'] = { DONE, DIV_PRE_ALOP, false, false }, 
        ['A'...'Z'] = { DONE, DIV_PRE_ALOP, false, false }, 
        ['_'] = { IN_ID, DIV_PRE_ALOP, false, false },
        ['$'] = { IN_ID, DIV_PRE_ALOP, false, false },
        //whitespace
        [' '] = { DONE, DIV_PRE_ALOP, true, false },
        ['\t'] ={ DONE, DIV_PRE_ALOP, true, false },
        ['\n'] ={ DONE, DIV_PRE_ALOP, true, false },
        ['\0'] = { DONE, DIV_PRE_ALOP, true, false},
        //parentheses
        ['('] = { DONE, DIV_PRE_ALOP, false }
        

        
    },
    // IN_COMMENT state
    [IN_COMMENT] = {
        /*--[DEFAULTING TO STAY FOR ALL CHARS]--*/
        ['\0'...127] = { IN_COMMENT, COMMENT, true, true },

        /*--[RULES]--*/
        ['*'] = { IN_BLOCK_COMMENT, COMMENT, true, true },
        ['\0'] = { ERROR, YYerror, true, false}
        
    },
    // IN_BLOCK_COMMENT state
    [IN_BLOCK_COMMENT] = {
        ['\0'...127] = { IN_COMMENT, COMMENT, true, true },

        /*--[RULES]--*/
        ['/'] = { START, COMMENT, true, true }, // Go back to the initial state to get the next token
        ['*'] = { IN_BLOCK_COMMENT, COMMENT, true, true },
        ['\0'] = { ERROR, YYerror, true, false}

    },

    // IN_LESS_OR_LEQ state
    [IN_LESS_OR_LEQ] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...127] = { ERROR, YYerror, false, false },

        /*--[RULES]--*/
        ['='] = { DONE, LESSEQ_RELOP, true, true },

        /*--[DELIMITERS-less]--*/
        //alphabetical
        ['a'...'z'] = { DONE, LESS_RELOP, false, false },
        ['A'...'Z'] = { DONE, LESS_RELOP, false, false },
        ['0'...'9'] = { DONE, LESS_RELOP, false, false },
        ['_'] = { DONE, LESS_RELOP, false, false },
        ['$'] = { DONE, LESS_RELOP, false, false },
        //string relational
        ['"'] = { DONE, LESS_RELOP, false, false },
        //whitespace
        [' '] = { DONE, LESS_RELOP, true, false },
        ['\t'] ={ DONE, LESS_RELOP, true, false },
        ['\n'] ={ DONE, LESS_RELOP, true, false },
        ['\0'] = { DONE, LESS_RELOP, true, false},
        //pharentheses
        ['('] = { DONE, LESS_RELOP, false }


    },
    // IN_LESS_OR_LEQ state
    [IN_GREAT_OR_GEQ] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...127] = { ERROR, YYerror, false, false },

        /*--[RULES]--*/
        ['='] = { DONE, GREATEQ_RELOP, true, true },

        /*--[DELIMITERS-greater]--*/
        //alphabetical
        ['a'...'z'] = { DONE, GREAT_RELOP, false, false },
        ['A'...'Z'] = { DONE, GREAT_RELOP, false, false },
        ['0'...'9'] = { DONE, GREAT_RELOP, false, false },
        ['_'] = { DONE, GREAT_RELOP, false, false },
        ['$'] = { DONE, GREAT_RELOP, false, false },
        //string relational
        ['"'] = { DONE, GREAT_RELOP, false, false },
        //whitespace
        [' '] = { DONE, GREAT_RELOP, true, false },
        ['\t'] ={ DONE, GREAT_RELOP, true, false },
        ['\n'] ={ DONE, GREAT_RELOP, true, false },
        ['\0'] = { DONE, GREAT_RELOP, true, false},
        //pharentheses
        ['('] = { DONE, GREAT_RELOP, false }
        

    },
    // IN_EQRELOP
    [IN_EQ_OR_EQRELOP] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...127] = { ERROR, YYerror, false, false },

        /*--[RULES]--*/
        ['='] = { DONE, EQ_RELOP, true, true },

        /*--[DELIMITERS-equal]--*/
        //alphabetical
        ['a'...'z'] = { DONE, EQUAL, false, false },
        ['A'...'Z'] = { DONE, EQUAL, false, false },
        ['0'...'9'] = { DONE, EQUAL, false, false },
        ['_'] = { DONE, EQUAL, false, false },
        ['$'] = { DONE, EQUAL, false, false },
        //string relational
        ['"'] = { DONE, EQUAL, false, false },
        //whitespace
        [' '] = { DONE, EQUAL, true, false },
        ['\t'] ={ DONE, EQUAL, true, false },
        ['\n'] ={ DONE, EQUAL, true, false },
        ['\0'] = { DONE, EQUAL, true, false},
        //pharentheses
        ['('] = { DONE, EQ_RELOP, false }


    },

    [IN_NOTRELOP] = {
        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...127] = { ERROR, YYerror, false, false },

        /*--[RULES]--*/
        ['='] = { DONE, NOTEQ_RELOP, true, true },

    },
    [IN_STRING] = {
        /*--[DEFAULTING TO IN_STRING]--*/
        ['\0'...127] = { IN_STRING, STRING, true, true },
        ['"'] = { DONE, STRING, true, true },
        ['\0'] = { ERROR, YYerror, true, false }

    },
    [IN_MULT_OR_COMM] = {

        /*--[DEFAULTING TO ERROR]--*/
        ['\0'...127] = { ERROR, YYerror, false, false },

        /*--[DELIMITERS-error]--*/
        //alphabetical
        ['a'...'z'] = { DONE, MULT_PRE_ALOP, false, false },
        ['A'...'Z'] = { DONE, MULT_PRE_ALOP, false, false },
        ['0'...'9'] = { DONE, MULT_PRE_ALOP, false, false },
        ['_'] = { DONE, MULT_PRE_ALOP, false, false },
        ['$'] = { DONE, MULT_PRE_ALOP, false, false },
        //in/out functions/arrays
        ['('] = { DONE, MULT_PRE_ALOP, false, false },
        [')'] = { DONE, MULT_PRE_ALOP, false, false },
        //whitespace
        [' '] = { DONE, MULT_PRE_ALOP, true, false },
        ['\t'] ={ DONE, MULT_PRE_ALOP, true, false },
        ['\n'] ={ DONE, MULT_PRE_ALOP, true, false },
        ['\0'] = { DONE, MULT_PRE_ALOP, true, false},

    },
    // DONE state
    [DONE] = {},
    [ERROR]= {
        /*--[GET THE REST OF THE LEXEME]--*/
        /*--[DEFAULTING TO STAY IN ERROR]--*/
        ['\0'...127] = { ERROR, YYerror, true, true },

        /*--[DELIMITERS-error]--*/
        //arithmetic
        ['+'] = { DONE, YYerror, false, false }, 
        ['-'] = { DONE, YYerror, false, false }, 
        ['*'] = { DONE, YYerror, false, false },
        ['/'] = { DONE, YYerror, false, false },
        //relational 
        ['<'] = { DONE, YYerror, false, false }, 
        ['>'] = { DONE, YYerror, false, false }, 
        ['='] = { DONE, YYerror, false, false }, 
        ['!'] = { DONE, YYerror, false, false },
        //punctual 
        [';'] = { DONE, YYerror, false, false },
        [','] = { DONE, YYerror, false, false },
        //macros
        ['"'] = { DONE, YYerror, false, false },
        //in/out functions/arrays
        ['('] = { DONE, YYerror, false, false },
        [')'] = { DONE, YYerror, false, false },
        ['{'] = { DONE, YYerror, false, false },
        ['}'] = { DONE, YYerror, false, false },
        ['['] = { DONE, YYerror, false, false },
        [']'] = { DONE, YYerror, false, false },
        //whitespace
        [' '] = { DONE, YYerror, true, false },
        ['\t'] ={ DONE, YYerror, true, false },
        ['\n'] ={ DONE, YYerror, true, false },
        ['\0'] = { DONE, YYerror, false, false}

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
        if(fgetpos(file, &(buffer->line_pos)) != 0){
            perror("fgetpos() error");
            //will not return error as it will only be a problem if there is an error
        }
    }

    buffer->position++;
    buffer->line_char_pos++;

    return current_char;
}

char unget_next_char( Buffer* buffer){
    buffer->position--;
    buffer->line_char_pos--;
    // if it is \n the DFA will always consume
}

void indicate_error(Buffer* buffer, LexerTableEntry table_entry, FILE* stream, TokenRecord* token){
    puts(RED"--[ LEXICAL ERROR ]--");
    int in_line_placement = buffer->line_char_pos;
    fpos_t line_placement = buffer->line_pos; 
    printf(CYN"\t[!] THE ERROR OCCURRED AT THE %zu-th LINE IN THE %zu-th CHAR [!]\n"RESET, buffer->line_number, buffer->line_char_pos);
    

    char ch;
    //Continue traversing the DFA to get the error lexeme while not in a delimiter
    while( table_entry.next_state != DONE ){
        ch = get_next_char(buffer, stream);
        if(ch == EOF){
            break;
        } 
        table_entry = lexerTable[table_entry.next_state][ch];
        if( table_entry.store == true ) {
            token->lexeme[strlen(token->lexeme)] = ch;
            token->lexeme[strlen(token->lexeme)+1] = '\0';
        }
    }
    token->type = table_entry.token_type;
    printf(YELLOW"\t[!] LEXEME: "RED"%s "YELLOW"[!]\n", token->lexeme);



    //print the line where the error occured:
    if( fsetpos( stream, &(buffer->line_pos) ) != 0 ) {
      perror( "fsetpos error" );
    }
    load_buffer(buffer, stream);
    printf("%s", "\t");
    while (ch != '\n' ) {
        ch = get_next_char(buffer, stream);
        if(buffer->position <= in_line_placement){
            printf(RED"%c"RESET, ch);
        }else if(buffer->position < in_line_placement+strlen(token->lexeme)){
            printf(YELLOW"%c"RESET, ch);
        }else{
            printf("%c",ch);
        }
    }
    //indicator
    printf("%s","\t");
    while(in_line_placement-1 > 0){
        printf("%s", " ");
        in_line_placement--;
    }
    puts("^]--char that caused the error");
    
    puts(RED"}");
}

/*--[ get_next_token - reuses previous buffer for optimization - returns into the token ]--*/
yytoken_kind_t get_next_token( Buffer* buffer, FILE * stream, TokenRecord * token ){
    puts("GETTING TOK");
    char ch;
    LexerTableEntry table_entry = { START, -1, true };
    while( table_entry.next_state != DONE && table_entry.next_state != ERROR ){
        if(table_entry.next_state == START) memset(token->lexeme, 0, sizeof token->lexeme);
        
        ch = get_next_char(buffer, stream);
        //adhoc for end of file
        if(ch == EOF){
            //end of file entry
            ch = '\0'; 
        }else if(ch < 0 || ch > 127){
            //Outside of lower ASCII range
            if(table_entry.next_state== IN_COMMENT){
                continue;
            }else{
                indicate_error(buffer, table_entry, stream, token);
                token->type = YYerror;
                return YYerror;
            }
        }
        table_entry = lexerTable[table_entry.next_state][ch];
        
        //if this whas a lookahead , do not consume it
        if( table_entry.consume == false ) {
            unget_next_char(buffer);
        }
        if( table_entry.store == true ) {
            token->lexeme[strlen(token->lexeme)] = ch;
            token->lexeme[strlen(token->lexeme)+1] = '\0';
        }
    }

  
    if(table_entry.next_state == ERROR ) {
        indicate_error(buffer, table_entry, stream, token);
        return YYerror;
    }
    //check if id is keyword
    if( table_entry.token_type == ID ){
        const struct keyword* key = in_word_set(token->lexeme, strlen(token->lexeme));
        if(key != NULL){
            table_entry.token_type =  key->type;
        }

    }
    
    
    token->type = table_entry.token_type;

    return token->type;
}