#ifndef __CONTEXTUALIZER_H_
#define __CONTEXTUALIZER_H_
#include "parser.h"


//chained list for referencing variables
typedef struct line_records
{
    int line_pos;
    struct line_records* next;
} refered_in_lines;

typedef struct bucket_record
{
    char* identifier; //var name
    int memloc; //mem location
    refered_in_lines* lines_refered; //list of places referenced
    syntax_t_node* node; //node of syntax tree
    exp_type typed_as; //{INT,VOID}
    struct bucket_record* next;
} var_data_buckets;

#define HASH_TABLE_SIZE 300
typedef struct scope_rec
{
    char* identifier;//function name or global
    var_data_buckets* hash_table[HASH_TABLE_SIZE];
    struct scope_rec* in;
    int nest;
}scope_record;

//head of list
scope_record global_scope;

//scope list parameters inside accessible struct
typedef struct scope_record_definitions
{
    scope_record* list[HASH_TABLE_SIZE];
    int size=0;

}scope_record_stat;

scope_record_stat scopes;








/*--[Semantic Analyzer]--*/
/*[create symbol table and check for correct var typing]*/
void contextualize(syntax_t_node*);

#endif