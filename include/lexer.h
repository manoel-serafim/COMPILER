#ifndef __LEXER__
#define __LEXER__


#include "macros.h"     //messaging
#include "libs.h"       //libraries
#include "buffer.h"
#include "globals.h"

/*--[TOKEN DEFINITIONS]--*/
#define LEXEME_SIZE 256

/*--[TOKEN STRUCTS]--*/
typedef struct {
    token_type type;
    char lexeme[LEXEME_SIZE];
} TokenRecord;


/*--[ get_next_token - reuses previous buffer for optimization - returns into the token ]--*/
token_type get_next_token( Buffer* buffer, FILE * stream, TokenRecord * token );

#endif
