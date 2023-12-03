%{
#include "../../include/lexer.h"
#include <stdio.h>
ParsingContext glob_context;
#define yylex() get_next_token(glob_context.p_buffer, glob_context.stream, glob_context.p_token_rec)
%}

%token ID NUM IF ELSE WHILE RETURN INT VOID PLUS_ALOP MINUS_ALOP MULT_PRE_ALOP DIV_PRE_ALOP EQ_RELOP NOTEQ_RELOP LESSEQ_RELOP GREATEQ_RELOP GREAT_RELOP LESS_RELOP EQUAL CURLYOP_BRACKET CURLYCL_BRACKET CIRCLEOP_BRACKET CIRCLECL_BRACKET SQUAREOP_BRACKET SQUARECL_BRACKET SEMICOL_PUNCT COMMA_PUNCT WHITESPACE COMMENT STRING


%%

program:
    program token
    | token
    ;

token:
    ID { printf("ID found: %s\n", glob_context.p_token_rec->id); }
    | NUM { printf("Number: %d\n", glob_context.p_token_rec->num); } // Assuming num is a field for number in TokenRecord
    | YYEOF { printf("End of file\n"); }
    ;

%%


int main(int argc, char *argv[]) {
    # if YYDEBUG == 1
    extern int yydebug;
    yydebug = 1;
    #endif

    if (argc != 2) {
        //NOT ENOUGH ARGS
        printf(RED"Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    glob_context.stream = fopen( argv[1] , "r" );
    if (glob_context.stream == NULL) {
        //FOPEN ERROR
        perror(RED"fopen() error"YELLOW);
        return 1;
    }
    glob_context.p_buffer = malloc(sizeof(Buffer));
    allocate_buffer(glob_context.p_buffer, glob_context.stream);


    glob_context.p_token_rec = malloc(sizeof(TokenRecord)); 

    yyparse();

    deallocate_buffer(glob_context.p_buffer);
    free(glob_context.p_buffer);
    free(glob_context.p_token_rec);
    fclose(glob_context.stream);


    return EXIT_SUCCESS;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}