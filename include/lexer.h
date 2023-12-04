#ifndef __LEXER__
#define __LEXER__


#include "macros.h"     //messaging
#include "libs.h"       //libraries
#include "buffer.h"

#include "globals.h"

/*--[TOKEN DEYYEOFITIONS]--*/
#define LEXEME_SIZE 256

/*--[TOKEN STRUCTS]--*/
typedef struct {
    yytoken_kind_t type;
    char lexeme[LEXEME_SIZE];
} TokenRecord;

/*--[GLOBAL STRUCTURES]--*/
typedef struct {
    Buffer* p_buffer;
    FILE* stream;
    TokenRecord* p_token_rec;
} ParsingContext;

extern ParsingContext glob_context;

/*--[ get_next_token - reuses previous buffer for optimization - returns into the token ]--*/
yytoken_kind_t get_next_token( Buffer* buffer, FILE * stream, TokenRecord * token );


#endif
