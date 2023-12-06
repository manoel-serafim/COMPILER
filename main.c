#include "include/lexer.h"
#include "include/parser.h"
#include "include/contextualizer.h"

ParsingContext glob_context;


/*  [main function - returns status]  */
int main(int argc, char *argv[]) {
    printf("%s",GREEN"_______________________________________________________\n"RESET);
    puts(GREEN"STARTING TO COMPILE ..."RESET);

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
    
   
    syntax_t_node* syntax_root = parse();
    print_syntax_tree(syntax_root);
    /*printar arvore*/


    if(syntax_root!=NULL){
        printf("%s",GREEN"_______________________________________________________\n"RESET);
        puts(GREEN"SYNTAX ANALYSIS COMPLETE"RESET);
        contextualize(syntax_root);
        print_symbol_tab();
        printf("%s",GREEN"_______________________________________________________\n"RESET);
        puts(GREEN"SEMANTIC ANALYSIS COMPLETE"RESET);
    }
    
    
    //cleanup functions
    free(glob_context.p_token_rec);
    free(glob_context.p_buffer);
    fclose(glob_context.stream);



    return EXIT_SUCCESS;
}
