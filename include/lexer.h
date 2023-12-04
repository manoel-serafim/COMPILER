#ifndef __LEXER__
#define __LEXER__


#include "macros.h"     //messaging
#include "libs.h"       //libraries
#include "buffer.h"
#include "../utils/bison/parser.tab.h"

/*--[TOKEN DEYYEOFITIONS]--*/
#define LEXEME_SIZE 256

/*--[TOKEN STRUCTS]--*/
typedef struct {
    yytoken_kind_t type;
    char lexeme[LEXEME_SIZE];
} TokenRecord;

/*--[ get_next_token - reuses previous buffer for optimization - returns into the token ]--*/
yytoken_kind_t get_next_token( Buffer* buffer, FILE * stream, TokenRecord * token );


#endif
