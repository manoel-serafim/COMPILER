/*
    TABLE-DRIVEN LEXER
*/
#include "../../include/lexer.h"
/*  [main function - returns status]  */
int main(int argc, char *argv[]) {

    if (argc != 2) {
        //NOT ENOUGH ARGS
        printf(RED"Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE * stream = fopen( argv[1] , "r" );
    if (stream == NULL) {
        //FOPEN ERROR
        perror(RED"fopen() error"YELLOW);
        return 1;
    }
    
    Buffer buffer;
    allocate_buffer(&buffer, stream);

    
    TokenRecord* token = malloc(sizeof(TokenRecord)); 


    int count;
    do{
        get_next_token(&buffer, stream, token);
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
    deallocate_buffer(&buffer);
    fclose(stream);



    return EXIT_SUCCESS;
}
