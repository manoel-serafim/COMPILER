#include "contextualizer.h"
#include "parser.h"
#include "libs.h"
#include "macros.h"

scope_record* global_scope;
scope_record_stat scopes; 

/*--[Scope Chain Functions]--*/
static scope_record* new_scope(char* id){
    scope_record* new = malloc(sizeof(scope_record));
    new->identifier = id;
    new->nest=0;
    return new;
} 
static void add_scope_to_chain(scope_record* scp){
    for(int i=0; i< scopes.list_size; i++){
        if(strcmp(scopes.list[i]->identifier, scp->identifier) == 0){
            scp->nest += 1;
        }
    }
    scopes.stack[scopes.stack_size++] = scp;
    scopes.list[scopes.list_size++]= scp;
}
static void pop_scope(){
    free(scopes.stack[scopes.stack_size]);
    scopes.stack[scopes.stack_size--]=NULL;
} 


/*--[Symbol Tree hash table functions]*/
/*[extend 4 will mult by four (shifting b'100)]*/
static int hash(char* id){
    int extend = 0;
    for(int i=0; id[i] != '\0'; i++){
        extend = (id[i]+ (extend<<4))% HASH_TABLE_SIZE;
    }
    return extend;
}


/*--[Lookup Functions]--*/
//within scope

//in all acessible scopes (itself + parent)
bucket_record* bucket_lookup_all_scope(char * id) {
    scope_record* stack_scope = scopes.stack[scopes.stack_size-1];
    int hash_value = hash(id);
    bucket_record* holder = NULL;

    //traverse bucket stack chain until finding the var_id
    while(stack_scope != NULL){
        holder = stack_scope->hash_table[hash_value];
        while((holder != NULL) && (strcmp(id, holder->identifier) != 0)){
            holder = holder->next;
        }
        if(holder == NULL){
            stack_scope = stack_scope->in;
        }else{
            break;
        }
    }
    return holder; 
}
/*scope lookup*/
scope_record* scope_lookup(char* id){
    //create holder scope
    scope_record* holder = NULL;
    for(int i=0; i<scopes.list_size; i++){
        if(strcmp(id, scopes.list[i]->identifier)==0){
            holder = scopes.list[i];
            break;
        }
    }
    return holder;
}

/*--[Insertion Functions]--*/

void add_line_to_bucket(bucket_record* bucket, syntax_t_node* node){
    bucket->lines_refered = malloc(sizeof(line_record));
    bucket->lines_refered->line_pos = node->position[0];
    bucket->lines_refered->next = NULL;
}

void add_var_line_in_scope(char* id, int line_pos){
    int hash_value = hash(id);
    scope_record* stack_scope = scopes.stack[scopes.stack_size-1];
    bucket_record* bucket = stack_scope->hash_table[hash_value];

    while(stack_scope != NULL){ //while there is a scope
        if(bucket != NULL){ //bucket for ident
            line_record* bucket_line = bucket->lines_refered;
            while(bucket_line->next != NULL){
                bucket_line = bucket_line->next;
            }
            
            bucket_line->next = malloc(sizeof(line_record));
            bucket_line->next->line_pos = line_pos;
            bucket_line->next->next = NULL;
            return; //added
        }
        stack_scope = stack_scope->in;
    }

}
/*--[Symbol Table Insertions (memloc+linenum)]--*/
void line_memloc_insert( int memloc, char* scope_id, char* var_id, syntax_t_node* node){
    exp_type var_type = node->child[0]->has.exp.type;
    scope_record* list_scope = scopes.list[scopes.list_size-1];
    scope_record* stack_scope = scopes.stack[scopes.stack_size-1];
    if(var_id == NULL){
        var_id = "0";
    }
    int hash_value = hash(var_id);

    bucket_record* buck_list = list_scope->hash_table[hash_value];
    bucket_record* buck_stack = stack_scope->hash_table[hash_value];
    while((buck_stack != NULL) && (strcmp(var_id, buck_stack->identifier)!= 0)){
        buck_stack->next;
    }
    
    if(buck_stack != NULL){
        //found in the bucket list
        line_record* buck_lines = buck_stack->lines_refered;
        //traverse the lines, get chain edge
        while(buck_lines->next != NULL){
            buck_lines = buck_lines->next;
        }
        //buck_lines->next->next = NULL;
        buck_lines->next = malloc(sizeof(line_record));
        buck_lines->next->line_pos = node->position[0];
        buck_lines->next->next = NULL;
    }else{//not found
        //add
        //setup of list scope
        buck_list = malloc(sizeof(bucket_record));
        buck_list->identifier = var_id;
        buck_list->node = node;
        buck_list->typed_as =  var_type;
        buck_list->memloc = memloc;
        add_line_to_bucket(buck_list, node);
        buck_list->next = stack_scope->hash_table[hash_value];
        list_scope->hash_table[hash_value] = buck_list;

        
        //setup of stack scope
        buck_stack = malloc(sizeof(bucket_record));
        buck_stack->identifier = var_id;
        buck_stack->node = node;
        buck_stack->typed_as =  var_type;
        buck_stack->memloc = memloc;
        add_line_to_bucket(buck_stack, node);
        buck_stack->next = stack_scope->hash_table[hash_value];
        stack_scope->hash_table[hash_value] = buck_stack;

    }
}




void show_error(syntax_t_node* root, char* err){
    puts(RED"__________________________________________[ CONTEXT ERROR ]_________________________________________");
    printf(RED"\t [!][!]message: %s"RESET, err);
    printf(CYN"\t[!] THE ERROR OCCURRED AT THE %zu-th LINE IN THE %zu-th CHAR [!]\n"RESET, root->position[0], root->position[1]);
    puts(RED"____________________________________________________________________________________________________"RESET);
}


int is_first_statement = 0;
#define IS_FIRST is_first_statement=1
#define NOT_FIRST is_first_statement=0
int loc=0;

void insert_node_ids(syntax_t_node* root){
    if(root->type == EXP_T){
        switch(root->has.exp.kind){
            case VECT_ID_EK:
            case ID_EK:
            {
                bucket_record* buck_list = bucket_lookup_all_scope(root->attr.content);
                // check if is declared in any bucket on all accessible scopes
                if( buck_list != NULL){
                    //found declaration
                    root->has.exp.type = buck_list->typed_as;
                    add_var_line_in_scope(root->attr.content, root->position[0]);
                }
                else{
                    //error, trying to reference something not declared
                    show_error(root, "[SYMBOL TABLE ERROR] Undefined Reference");
                }
                break;
            }
            default:
                break;
        }
    }else if(root->type == STMT_T){
        switch(root->has.stmt){
            case CALL_SK:
            {
                //check if decl is unique
                if(scope_lookup(root->attr.content) == NULL ){
                    show_error(root, "[SYMBOL TABLE ERROR] Call to invalid function");
                    break;
                }
                char* scp_id = (scopes.stack[scopes.stack_size-1])->identifier;
                line_memloc_insert(loc++, scp_id, root->attr.content, root);
                break;
                
            }
            case VAR_SK:
            {
                printf("%s", root->attr.content);
                //check if decl is unique
                if(scope_lookup(root->attr.content) != NULL ){
                    show_error(root, "[SYMBOL TABLE ERROR] Variable Declaration with Function Name");
                    break;
                }
                //check if decl is unique
                if(bucket_lookup_all_scope(root->attr.content) != NULL){
                    show_error(root, "[SYMBOL TABLE ERROR] Variable Redefinition");
                    break;
                }
                //check if is void
                if (root->child[0]->has.exp.type == VOID_T) {
                  show_error(root, "[TYPE ERROR] Wrong Type For Variable");
                  break;
                }
                char* scp_id = (scopes.stack[scopes.stack_size-1])->identifier;
                line_memloc_insert(loc++, scp_id, root->attr.content, root);
                break;

            }    
            case VECT_SK:
            {
                //check if decl is unique
                if(bucket_lookup_all_scope(root->attr.array_specs.identifier) != NULL){
                    show_error(root, "[SYMBOL TABLE ERROR] Vector Variable Redefinition");
                    break;
                }
                //check if is void
                if (root->child[0]->has.exp.type == VOID_T) {
                  show_error(root, "[TYPE ERROR] Wrong Type For Vector Variable");
                  break;
                }
                
                char* scp_id = (scopes.stack[scopes.stack_size-1])->identifier;
                line_memloc_insert(loc++, scp_id, root->attr.array_specs.identifier, root);
                break;
            }
            case FUNCT_SK:
            {   
                //mem is ofseted by scope addr
                loc = 0; //memory location zero for scope start
                //function scope should be new
                if(scope_lookup(root->attr.content) != NULL){
                    show_error(root, "[SYMBOL TABLE ERROR] Function Redefinition");
                    break;
                }
                char* scp_id = (scopes.stack[scopes.stack_size-1])->identifier;
                //if in global scope
                if(strcmp(scp_id, "global") == 0){
                    //insert line ref
                    line_memloc_insert(loc++, scp_id, root->attr.content, root);
                }

                scope_record* new = new_scope(root->attr.content);
                new->in = scopes.stack[scopes.stack_size-1];
                add_scope_to_chain(new);
                IS_FIRST;
                break;
            }
            case PARAM_SK:
            {
                if (root->child[0]->has.exp.type == VOID_T) {
                  show_error(root, "[TYPE ERROR] Wrong Type For Function Parameter");
                  break;
                }
                if(scope_lookup(root->attr.content) != NULL){
                    show_error(root, "[SYMBOL TABLE ERROR] Redeclaration of Parameter");
                    break;
                }
                
                if(is_first_statement = 0){
                    scope_record* new = new_scope((scopes.stack[scopes.stack_size-1])->identifier);
                    new->in = scopes.stack[scopes.stack_size-1];
                    add_scope_to_chain(new);
                }
                NOT_FIRST;

                char* scp_id = (scopes.stack[scopes.stack_size-1])->identifier;
                line_memloc_insert(loc++, scp_id, root->attr.content, root);
                break;
            }

            case VECT_PARAM_SK:
            {
                if (root->child[0]->has.exp.type == VOID_T) {
                  show_error(root, "[TYPE ERROR] Wrong Type For Function Vector Parameter");
                  break;
                }
                if(scope_lookup(root->attr.array_specs.identifier) != NULL){
                    show_error(root, "[SYMBOL TABLE ERROR] Redeclaration of Vector Parameter");
                    break;
                }
                
                if(is_first_statement = 0){
                    scope_record* new = new_scope((scopes.stack[scopes.stack_size-1])->identifier);
                    new->in = scopes.stack[scopes.stack_size-1];
                    add_scope_to_chain(new);
                }
                NOT_FIRST;

                char* scp_id = (scopes.stack[scopes.stack_size-1])->identifier;
                line_memloc_insert(loc++, scp_id, root->attr.array_specs.identifier, root);
                break;
            }
            default:
                break;
        }
    }
}


/*
static void delete_scope_after_insert(syntax_t_node* root){

}*/


/*--[Syntax Tree Traversal]--*/
/*[path can be taken from front to back(symbol table)]*/
static void traverse_symtab(syntax_t_node* root){

    //recursive base case: root of subtree =NULL
    if(root != NULL){
        insert_node_ids(root);
        for(int i=0; i<MAXCHILDREN; i++){
            traverse_symtab(root->child[i]);
        }
        traverse_symtab(root->sibling);
    }
}


/*--[Semantics Analyser]--*/
/*Type check && Symbol Table*/
void contextualize(syntax_t_node* root){
    //create a new scope for global
    global_scope = new_scope("global");
    //insert scope
    add_scope_to_chain(global_scope);

    //add default in and out symbol functions
    /*no default functions -> void symtable_setup(void)*/
    //build symbol table:
    traverse_symtab(root);

}




void print_symbol_tab(){
    puts("\n\n");
    for(int i = 1; i<scopes.list_size; i++){
        //print scope
        scope_record* holder = scopes.list[i];
        printf(CYN"\nSCOPE ID: %s \t \n",holder->identifier);
        printf(GREEN"__________________________________________________________\n"RESET);
        puts(GREEN" IDENT\tMEM_OFFSET\tTYPE\t\tDATA_TYPE\tLINES"YELLOW);
        bucket_record** buckets = holder->hash_table;
        for(int j=1; j<HASH_TABLE_SIZE;j++){
            if(buckets[j] != NULL ){
                bucket_record* buck_hash = buckets[j];
                syntax_t_node* node = buck_hash->node;
                while(buck_hash != NULL && buck_hash->lines_refered->next != NULL){
                    line_record* lines = buck_hash->lines_refered;
                    
                    //var name
                    printf("%s\t",buck_hash->identifier);
                    //memloc
                    printf("%d\t\t",buck_hash->memloc);

            
                    switch (node->has.exp.type)
                    {
                    case VOID_T:
                        printf("%s","VOID\t");
                        break;
                    case INT_T:
                        printf("%s","INTEGER\t");
                        break;
                    case CONST_T:
                        printf("%s","CONSTANT\t");
                        break;
                    default:
                        break;
                    }
                    
                    

                    if( node->type == STMT_T){
                        switch(node->has.stmt){
                            case CALL_SK:
                                printf("\tFUNCT CALL");
                                break;
                            case FUNCT_SK:
                                printf("\tFUNCT DECL");
                                break;
                            case VAR_SK:
                                printf("\tVAR DECL");
                                break;
                            case VECT_SK:
                                printf("\tVECT DECL");
                                break;
                            case PARAM_SK:
                                printf("\tPARAM DEF");
                                break;
                            case VECT_PARAM_SK:
                                printf("\tVECT PARAM DEF");
                                break;
                            }
                    }else{
                        printf("%s","\t");
                    }
                    printf("%s[","\t");
                    while (lines->next != NULL) {
                      printf("%d ", lines->line_pos);
                      lines = lines->next;
                    }

                    puts("] ");
                    buck_hash= buck_hash->next;
                }
            }
        }
    }
}