#include "include/lexer.h"

ParsingContext glob_context;

/*  [main function - returns status]  */
int main(int argc, char *argv[]) {
    
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


    int count, next_tok;
    do{
        next_tok = get_next_token(glob_context.p_buffer, glob_context.stream, glob_context.p_token_rec);
        if(next_tok == YYEOF){
            break;
        }
        if(next_tok == YYerror){
            return EXIT_FAILURE;
        }
        //parser here
        printf("%dLEX: %s TYPE: %d\n",count, glob_context.p_token_rec->lexeme, next_tok);
        count++;
    }while(next_tok != YYEOF);

    
    deallocate_buffer(glob_context.p_buffer);
    free(glob_context.p_buffer);
    free(glob_context.p_token_rec);
    fclose(glob_context.stream);


    return EXIT_SUCCESS;
}
