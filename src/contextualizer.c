#include "contextualizer.h"
#include "parser.h"



/*--[Scope Chain Functions]--*/
static scope_record* new_scope(char* id){
    scope_record* new = malloc(sizeof(struct scope_record));
    new->identifier = id;
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
    scopes.list[scopes.size--]=NULL;
} 


/*--[Symbol Tree hash table functions]*/
/*[extend 4 will mult by four (shifting 100)]*/
static int hash(char* id){
    int extend = 0;
    for(int i=0; id[i] != '\0'; i++){
        extend = (id[i]+ ((extend<<4)))% HASH_TABLE_SIZE;
    }
    return extend;
}


/*--[Lookup Functions]--*/
//within scope
bucket_chain* bucket_lookup(char * id) {

    int hash_value = hash(id);
    bucket_chain* buck_stack = scopes.stack[scopes.stack_size-1]->hash_table[hash_value];

    //traverse bucket stack chain until finding the var_id
    while(strcmp(var_id, buck_stack->identifier)&&(buck_stack != NULL)){
        buck_stack->next;
    }
    return buck_stack;
}


/*--[Symbol Table Insertions (memloc+linenum)]--*/
void line_memloc_insert( int memloc, char* scope_id, char* var_id, exp_type var_type, syntax_t_node* node){
    
    bucket_chain* buck_list = scopes.list[scopes.list_size-1]->hash_table[hash_value];
    
    if(bucket_lookup(var_id)!= NULL){
        //found
        
    }
}











static void delete_scope_after_insert(syntax_t_node* root){

}

/*--[Syntax Tree Traversal]--*/
/*[path can be taken from front to back(symbol table)]*/
static void traverse_symtab(syntax_t_node* root){
    
    //create a new scope for global
    global_scope = new_scope("global");
    //recursive base case: root of subtree =NULL
    if(root != NULL){
        insert_node_ids(root);
        for(int i=0; i<MAXCHILDREN; i++){
            traverse(root->child[i], front_back_funct, back_front_funct)
        }
        back_front_funct(root);
        traverse(root->sibling, front_back_funct, back_front_funct);
    }
}

/*[path can be taken back to front(type check)]*/
static void traverse_tpcheck(syntax_t_node* root, void(* front_back_funct)(syntax_t_node*), void(* back_front_funct)(syntax_t_node*)){
    //recursive base case: root of subtree =NULL
    if(root != NULL){
        front_back_funct(root);
        for(int i=0; i<MAXCHILDREN; i++){
            traverse(root->child[i], front_back_funct, back_front_funct)
        }
        back_front_funct(root);
        traverse(root->sibling, front_back_funct, back_front_funct);
    }
}


/*--[Semantics Analyser]--*/
/*Type check && Symbol Table*/
void contextualize(syntax_t_node* root){
    //build symbol table:
    traverse_symtab(root);

}