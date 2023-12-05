#include "contextualizer.h"
#include "parser.h"
#include "libs.h"

/*--[Scope Chain Functions]--*/
static scope_record* new_scope(char* id){
    scope_record* new = malloc(sizeof(scope_record));
    new->identifier = id;
    return new;
} 
static void add_scope_to_chain(scope_record* scp){
    for(int i=0; i< scopes->list_size; i++){
        if(strcmp(scopes->list[i]->identifier, scp->identifier) == 0){
            scp->nest += 1;
        }
    }
    scopes->stack[scopes->stack_size++] = scp;
    scopes->list[scopes->list_size++]= scp;
}
static void pop_scope(){
    free(scopes->stack[scopes->stack_size]);
    scopes->stack[scopes->stack_size--]=NULL;
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
bucket_record* bucket_lookup(char * id) {

    int hash_value = hash(id);
    bucket_record* buck_stack = scopes->stack[scopes->stack_size-1]->hash_table[hash_value];

    //traverse bucket stack chain until finding the var_id
    while(strcmp(id, buck_stack->identifier)&&(buck_stack != NULL)){
        buck_stack->next;
    }
    return buck_stack;
}
//in all acessible scopes (itself + parent)
bucket_record* bucket_lookup_all_scope(char * id) {
    scope_record* stack_scope = scopes->stack[scopes->stack_size-1];
    int hash_value = hash(id);
    bucket_record* holder = NULL;

    //traverse bucket stack chain until finding the var_id
    while(stack_scope != NULL){
        holder = stack_scope->hash_table[hash_value];
        while(strcmp(id, holder->identifier)&&(holder != NULL)){
            holder->next;
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
    for(int i=0; i<scopes->list_size; i++){
        if(strcmp(id, scopes->list[i]->identifier)==0){
            holder = scopes->list[i];
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
    scope_record* stack_scope = scopes->stack[scopes->stack_size-1];
    bucket_record* bucket = stack_scope->hash_table[hash_value];

    while(stack_scope != NULL){ //while there is a scope
        if(bucket != NULL){ //bucket for ident
            line_record* bucket_line = bucket->lines_refered;
            while(bucket_line->next != NULL){
                bucket_line = bucket_line->next;
            }
            bucket_line->next->next = NULL;
            bucket_line->next = malloc(sizeof(line_record));
            bucket_line->next->line_pos = line_pos;
            return; //added
        }
        stack_scope = stack_scope->in;
    }

}
/*--[Symbol Table Insertions (memloc+linenum)]--*/
void line_memloc_insert( int memloc, char* scope_id, char* var_id, exp_type var_type, syntax_t_node* node){
    
    scope_record* list_scope = scopes->list[scopes->list_size-1];
    scope_record* stack_scope = scopes->stack[scopes->stack_size-1];
    int hash_value = hash(var_id);

    bucket_record* buck_list = list_scope->hash_table[hash_value];
    bucket_record* buck_stack = stack_scope->hash_table[hash_value];
    if(bucket_lookup(var_id)!= NULL){
        //found in the bucket list
        line_record* buck_lines = buck_stack->lines_refered;
        //traverse the lines, get chain edge
        while(buck_lines->next != NULL){
            buck_lines = buck_lines->next;
        }
        buck_lines->next->next = NULL;
        buck_lines->next = malloc(sizeof(line_record));
        buck_lines->next->line_pos = node->position[0];
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




void show_error(syntx_t_node* root, char* err){
    puts(RED"__________________________________________[ CONTEXT ERROR ]_________________________________________");
    printf(RED"\t [!][!]message: %s"RESET, err);
    printf(CYN"\t[!] THE ERROR OCCURRED AT THE %zu-th LINE IN THE %zu-th CHAR [!]\n"RESET, root->position[0], root->position[1]);
    puts(RED"____________________________________________________________________________________________________"RESET);
}


void insert_node_ids(syntax_t_node* root){
    if(root->type == EXP_T){
        switch(root->has.exp.kind){
            
            case VECT_ID_EK:
            case ID_EK:
            // check if is declared in any bucket on all accessible scopes
                if((bucket_record* buck_list = bucket_lookup_all_scope(root->attr.content)) != NULL){
                    //found declaration
                    root->has.exp.type = buck_list->typed_as;
                    add_var_line_in_scope(root->attr.content, root->position[0]);
                }else{
                    //error, trying to reference something not declared
                    show_error(root, "[SYMBOL TABLE ERROR] Undefined reference");
                }
            default:
                break;
        }
    }else if(root->type == STMT_T){
        switch(root->has.stmt){
            case VAR_SK :
        }
    }
}



static void delete_scope_after_insert(syntax_t_node* root){

}


/*--[Syntax Tree Traversal]--*/
/*[path can be taken from front to back(symbol table)]*/
static void traverse_symtab(syntax_t_node* root){
    
    //create a new scope for global
    global_scope = new_scope("global");
    //insert scope
    add_scope_to_chain(global_scope);

    //add default in and out symbol functions
    /*no default functions -> void symtable_setup(void)*/


    //recursive base case: root of subtree =NULL
    if(root != NULL){
        insert_node_ids(root);
        for(int i=0; i<MAXCHILDREN; i++){
            traverse_symtab(root->child[i]);
        }
        traverse_symtab(root->sibling);
    }
}

/*[path can be taken back to front(type check)]*/
static void traverse_tpcheck(syntax_t_node* root){
    //recursive base case: root of subtree =NULL
    if(root != NULL){
        for(int i=0; i<MAXCHILDREN; i++){
            traverse_tpcheck(root->child[i]);
        }
        traverse_tpcheck(root->sibling);
    }
}


/*--[Semantics Analyser]--*/
/*Type check && Symbol Table*/
void contextualize(syntax_t_node* root){
    //build symbol table:
    traverse_symtab(root);

}