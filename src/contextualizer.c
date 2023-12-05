#include "contextualizer.h"
#include "parser.h"

/*--[Scope Chain Functions]--*/
static scope_record* new_scope(char* id){
    scope_record* new = malloc(sizeof(struct scope_record));
    new->identifier = id;
    return new;
} 
static void add_scope_to_chain(scope_record* scp){
    for(int i=0; i< scopes.size; i++){
        if(strcmp(scopes.list[i]->identifier, scp->identifier) == 0){
            scp->nest += 1;
        }
    }
    scopes.list[scopes.size++]= scp;
}
static void delete_edge_scope (){
    free(scopes.list[scopes.size]);
    scopes.list[scopes.size--]=NULL;
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