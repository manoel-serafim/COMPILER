#ifndef __CONTEXTUALIZER_H_
#define __CONTEXTUALIZER_H_
#include "parser.h"


//chained list for referencing variables
typedef struct line_records
{
    int line_pos;
    struct line_records* next;
} line_record;

typedef struct bucket_record
{
    char* identifier; //var name
    int memloc; //mem location
    line_record* lines_refered; //list of places referenced
    syntax_t_node* node; //node of syntax tree
    exp_type typed_as; //{INT,VOID}
    struct bucket_record* next;
} bucket_record;

#define HASH_TABLE_SIZE 300 //have to calc the min
typedef struct scope_rec
{
    char* identifier;//function name or global
    bucket_record* hash_table[HASH_TABLE_SIZE];
    struct scope_rec* in;
    int nest;
}scope_record;



//scope list parameters inside accessible struct
typedef struct scope_record_definitions
{
    scope_record* list[HASH_TABLE_SIZE];
    int list_size;
    scope_record* stack[HASH_TABLE_SIZE];
    int stack_size;

}scope_record_stat;

// is declared in main

/*--[Semantic Analyzer]--*/
/*[create symbol table and check for correct var typing]*/
void contextualize(syntax_t_node*);

#endif