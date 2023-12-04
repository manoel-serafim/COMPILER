#include "contextualizer.h"
#include "parser.h"



/*--[Syntax Tree Traversal]--*/
/*[path can be taken from front to back(symbol table)]*/
static void traverse_symtab(syntax_t_node* root){
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

}