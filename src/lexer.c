/*
    TABLE-DRIVEN LEXER
*/

#include "include/lexer.h"


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


    int count;
    do{
        getNextToken(&buffer, stream, token);
        if(token->type == EOF){
            break;
        }
        if(token->type == INVALID){
            return EXIT_FAILURE;
        }
        printf(YELLOW"%d:\t"GREEN"LEXEME:"RED"%s\t"YELLOW"TYPE: %d\n"RESET,count, token->lexeme, token->type);
        count++;
    }while(token->type != EOF);
    
    
    //cleanup functions
    free(token);
    deallocateBuffer(&buffer);
    fclose(stream);



    return EXIT_SUCCESS;
}