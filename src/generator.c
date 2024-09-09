#include "parser.h"
#include "generator.h"



//printer section

const char* operation_strings[] = {
    "LOAD_VAR",
    "LOAD_VECT",
    "BRANCH_IF",
    "BRANCH",
    "LABEL",
    "MOVE",
    "PUSH",
    "POP",
    "BRANCH_AND_LINK",
    "STORE",
    "PLUS_ALOP",
    "MINUS_ALOP",
    "MULT_PRE_ALOP",
    "DIV_PRE_ALOP",
    "EQ_RELOP",
    "NOTEQ_RELOP",
    "LESSEQ_RELOP",
    "GREATEQ_RELOP",
    "GREAT_RELOP",
    "LESS_RELOP",
    "RET",
    "LOAD_IMMEDIATE",
    "ADDI",
    "GLOB_MAIN"
};

void print_address(address addr) {
    switch (addr.type) {
        case LOCATION:
            printf(", %s", addr.data);
            break;
        case STR:
            printf(", %s", addr.data);
            break;
        case REGISTER:
            printf(", R%d", addr.value);
            break;
        case IMMEDIATE:
            printf(", %d", addr.value);
            break;
        case EMPTY:
            printf(", _");
            break;
        default:
            printf("Unknown Address Type");
            break;
    }
}

void print_quadruple(quadruple* quad) {
    printf("%u::\t", quad->location);
    printf("%s", operation_strings[quad->operation - LOAD_VAR]);
    for (int i = 0; i < 3; ++i) {
            
        print_address(quad->address[i]);
       
    }
    printf("\n");
        
    
}

void print_quadruple_linked_list(quadruple init) {
    quadruple* current = &init;

    while (current != NULL) {
        print_quadruple(current);
        current = current->next;
    }
}


// Define the hash table structure
#define HASH_SIZE 211 // Size of the hash table

typedef struct {
    char *key;
    address* addr;
    int used; // Flag to check if the slot is used
} hash_entry;

// Hash function
unsigned int hash_function(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }
    return hash % HASH_SIZE;
}
hash_entry* hash_table = NULL;
// Function to initialize the hash table
void init_hash_table() {
    hash_entry *table = (hash_entry *)malloc(HASH_SIZE * sizeof(hash_entry));
   
    for (int i = 0; i < HASH_SIZE; i++) {
        table[i].key = NULL;
        table[i].addr = NULL;
        table[i].used = 0;
    }
    hash_table= table;
}

// Function to insert a key-value pair into the hash table
void hash_insert(char *key, address* address) {
    unsigned int index = hash_function(key);
    while (hash_table[index].used) { // Linear probing
        index = (index + 1) % HASH_SIZE;
    }
    hash_table[index].key = strdup(key);
    hash_table[index].addr = address;
    hash_table[index].used = 1;
}

// Function to search for a key in the hash table and return the associated address
address* hash_find(char *key) {
    unsigned int index = hash_function(key);
    while (hash_table[index].used) {
        if (strcmp(hash_table[index].key, key) == 0) {
            return hash_table[index].addr;
        }
        index = (index + 1) % HASH_SIZE;
    }
    // If key not found, return a default address
    address* ext_funct = malloc(sizeof(address));
    ext_funct->type = LOCATION;
    ext_funct->data = key;
    ext_funct->value = 0;
    return ext_funct;
}

// Function to deallocate memory used by the hash table
void free_hash_table(hash_entry *table) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (table[i].used) {
            free(table[i].key);
            free(table[i].addr);
        }
    }
    free(table);
}



typedef struct {
    char str[128];  // The string (key)
    unsigned int position;  // The position (value)
} loc_var_hash_frame;

// Hash table to store variables and their positions
loc_var_hash_frame local_var_to_frame[256];
unsigned int currentPosition = 0;  // Start position for frame pointer
unsigned int local_var_to_frame_size = 0;
uint32_t local_var_count= 0; 


// Function to find the position of a string in the hash table
int find_in__loc_var_hash_table(const char* str) {
    for (unsigned int i = 0; i < local_var_to_frame_size; ++i) {
        if (strcmp(local_var_to_frame[i].str, str) == 0) {
            return local_var_to_frame[i].position;  // Return the position if found
        }
    }
    return -1;  // Return -1 if not found
}
void clean_hash_loc_var_table() {
    // Reset the hash table size and position counter
    local_var_to_frame_size = 0;
    currentPosition = 0;

    // Optionally, clear the contents of the hash table entries
    for (unsigned int i = 0; i < 256; ++i) {
        memset(local_var_to_frame[i].str, 0, 128);  // Clear the string
        local_var_to_frame[i].position = 0;  // Reset the position
    }
}

// Function to allocate register and return position in the frame pointer
unsigned int alloc_reg(const char* str) {
    int pos = find_in__loc_var_hash_table(str);
    if (pos != -1) {
        return pos;  // Return the existing position if the string is already in the hash table
    }

    local_var_count+=4;

    // If the string is not in the table, add it with the next position
    strncpy(local_var_to_frame[local_var_to_frame_size].str, str, 128);
    local_var_to_frame[local_var_to_frame_size].position = currentPosition;
    currentPosition++;  // Increment the position for the next variable
    local_var_to_frame_size++;    // Increase the size of the hash table

    return currentPosition - 1;  // Return the newly assigned position
}






quadruple start;
quadruple* head = &start;
address holder;
char * scope = "global";
uint location = 0;
uint parameter_c = 0;



/*
    0x00: 1110
    0x04: 0000 
    0x08: 1011
    0x0c: 1111
    0x10: 1100
    0x14: 0000 
    0x18: 0000
    0x1c: 0000

*/ 
uint32_t register_status = 0xe0bfc000 | 0x00001f00;

/*
    0x00: 0000
    0x04: 0000 
    0x08: 0000
    0x0c: 0000
    0x10: 0001
    0x14: 1111 
    0x18: 0000
    0x1c: 0000

*/ 
uint32_t unalt_saved_regs = 0xffffe0ff;
#define SET_BIT(num, pos) ((num) |= (1u << (pos)))
#define RESET_BIT(num, pos) ((num) &= ~(1u << (pos)))



static inline int free_register(uint position){
    
    RESET_BIT(register_status, position);
    register_status = register_status | 0xe0bfc000 | 0x00001f00;
}

static inline int free_saved_register(uint position){
    RESET_BIT(unalt_saved_regs, position);
    unalt_saved_regs = unalt_saved_regs | 0xffffe0ff;
}

uint8_t reserve_register(){
    
    uint8_t i;
    for (i = 31; i >= 0; i--) {
        if (!(register_status & (1u << i))) {
            SET_BIT(register_status, i);
            return i;
        }
    }
    return -1;

}

uint8_t reserve_saved_register(){

    uint8_t i;
    for (i = 31; i >= 0; i--) {
        if (!(unalt_saved_regs & (1u << i))) {
            SET_BIT(unalt_saved_regs, i);
            return i;
        }
    }

}

void add_quadruple(quadruple* inst){
    
    head->location = location;
    head->next = inst;
    head = head->next;
    location++;

}



const int inverse_relation[] = {
    NOTEQ_REL,
    EQ_REL,
    GREAT_REL,
    LESS_REL,
    LESSEQ_REL,
    GREATEQ_REL,
};
static quadruple* generate_expression(syntax_t_node* branch)
{
    quadruple* instruction = malloc(sizeof(quadruple));
    switch(branch->has.exp.kind)
    {
        case OP_EK:

            //generate the code needed for the execution of the left operand
            generate(branch->child[0]);
            // glob var_ addr
            
            if(holder.type == IMMEDIATE)
            {
                quadruple* mvi1 = malloc(sizeof(quadruple));
                mvi1->operation = LOAD_IMMEDIATE;
                mvi1->address[0].type = REGISTER;
                mvi1->address[0].value = reserve_saved_register();
                mvi1->address[1].type = EMPTY;
                mvi1->address[2] = holder;

                add_quadruple(mvi1);
                holder = mvi1->address[0];
            }

            instruction->address[1] = holder;
            //the address for the current 
            //generate the code needed for the execution of the right operand
            generate(branch->child[1]);

            if(holder.type == IMMEDIATE)
            {
                quadruple* mvi2 = malloc(sizeof(quadruple));
                mvi2->operation = LOAD_IMMEDIATE;
                mvi2->address[0].type = REGISTER;
                mvi2->address[0].value = reserve_saved_register();
                mvi2->address[1].type = EMPTY;
                mvi2->address[2] = holder;

                add_quadruple(mvi2);
                holder = mvi2->address[0];
            }

            instruction->address[2] = holder;

            //now we can write the quadruple back inside of the quadruple list
            //dest is a temporary register 
            
            
            if( branch->attr.op >= EQ_REL && branch->attr.op <= LESS_REL)
            {
                instruction->operation = inverse_relation[branch->attr.op-EQ_REL];
                instruction->address[0].type = EMPTY;
            }
            else
            {
                instruction->address[0].value = reserve_register();
                instruction->address[0].type = REGISTER;
                //(branch.attr.op, dest, r2, r3)
                instruction->operation = branch->attr.op;
            }



            
            

            //if one of the registers of operand where used, now we can free them
            if(instruction->address[1].type == REGISTER){
                free_saved_register(instruction->address[1].value);
            }
            if(instruction->address[2].type == REGISTER){
                free_saved_register(instruction->address[2].value);
            }

            add_quadruple(instruction);
            
            //The holder is the register in which the op will be stored;
            holder = instruction->address[0];
            break;

        case ID_EK:
            char* result_id = malloc(sizeof(char)*128);
            snprintf(result_id, 128U, "%s_%s", scope, branch->attr.content);
            uint32_t offset_id = alloc_reg(result_id);


            instruction->address[1].value = 8;
            instruction->address[1].type = REGISTER;

            instruction->address[2].data = result_id;
            instruction->address[2].type = STR;
            instruction->address[2].value = offset_id;

            instruction->operation = LOAD_VAR;
            instruction->address[0].type = REGISTER;
            instruction->address[0].value = reserve_register();
            
            add_quadruple(instruction);

            holder = instruction->address[0];

            break;
        case NUM_EK:
            holder.type = IMMEDIATE;
            holder.value = branch->attr.val;

            break;

        case TYPE_EK:
            generate(branch->child[0]);
            break;

        case VECT_ID_EK:
            char* result_vec = malloc(sizeof(char)*128);
            snprintf(result_vec, 128U, "%s_%s", scope, branch->attr.content);
            uint32_t offset_vec = alloc_reg(result_vec);


            instruction->address[1].value = 8;
            instruction->address[1].type = REGISTER;

            instruction->address[2].data = result_vec;
            instruction->address[2].type = STR;
            instruction->address[2].value = offset_vec;

            instruction->operation = LOAD_VAR;
            instruction->address[0].type = REGISTER;
            instruction->address[0].value = reserve_register();

            add_quadruple(instruction);
            
            //this will have to generate the op to calc the size
            quadruple* adder = malloc(sizeof(quadruple));

            adder->address[1]= instruction->address[0];

            //calc the base addr
            generate(branch->child[0]);
            /*
            printf("%x\n", register_status);
            
            
            quadruple* li4 = malloc(sizeof(quadruple));
            li4->address[1].type = EMPTY;
            li4->address[2].type = IMMEDIATE;
            li4->address[2].value = 4;
            li4->operation = LOAD_IMMEDIATE;
            li4->address[0].type = REGISTER;
            
            li4->address[0].value = reserve_register();
            add_quadruple(li4); 

            quadruple* multind = malloc(sizeof(quadruple));
            multind->address[1].value = li4->address[0].value;
            multind->address[1].type = REGISTER;
            multind->address[2] = holder;
            multind->operation = MULT;
            multind->address[0].type = REGISTER;
            multind->address[0].value = reserve_register();
            add_quadruple(multind); 
            free_register(multind->address[1].value);
*/
            adder->address[2] = holder;
            adder->operation = ADD;
            adder->address[0].type = REGISTER;
            adder->address[0].value = reserve_register();
            
            add_quadruple(adder); 
            
            //load the vector with the calculated addr
            quadruple* vect_loader = malloc(sizeof(quadruple));
            //load result register as the operand of the next phase
            vect_loader->address[1]= adder->address[0];

            vect_loader->address[0].type = REGISTER;
            vect_loader->address[0].value = reserve_register();
            
            vect_loader->address[2].type = EMPTY;
            vect_loader->operation = LOAD_VAR;

            //get the addr of the referenced vector [base] + [offset]
            add_quadruple(vect_loader);

            free_register(vect_loader->address[1].value);

            holder = vect_loader->address[0];

            break;


            break;
        default:
			break;
    }

}

char* name_label(char* type, uint location){

    int location_digits = snprintf(NULL, 0, "%u", location); // Get the number of digits
    
    // Calculate the total length of the resulting string
    size_t len = strlen(type) + location_digits + 1; // +1 for the null terminator
    
    char* label = (char*)malloc(sizeof(char) * (len + 1)); // +1 for the null terminator
    
    // Format the label string
    sprintf(label, "%s%u", type, location);
    
    return label;
}


static address generate_statement( syntax_t_node* branch )
{
    quadruple* instruction = malloc(sizeof(quadruple));
    switch(branch->has.stmt)
    {
        case IF_SK:
            //calculating the conditional part of the if
            generate(branch->child[0]);
            //conditional part, this holder is a boolean
            instruction->address[1] = holder;

            //if_condition_false will branch to a not yet disclosed location
            uint* end_of_if = malloc(sizeof(uint));
            
            //the pointer to the BNE dest will have to be stored
            instruction->address[2].type = LOCATION;
            //this will be set after all if body: 
            //instruction->address[2].data
            //instruction->address[2].value

            //instruction that will branch to the else or to the finish if e1 is false
            instruction->operation = BRANCH_IF;
            

            //no use
            instruction->address[0].type = EMPTY;
            
            //The instruction can be added even if not finished yet (pointer magic)
            add_quadruple(instruction);
           
            
            //free reg for reuse
            if(instruction->address[1].type == REGISTER){
                free_register(instruction->address[1].value);
            }

            //generates the if body
            generate(branch->child[1]);

            //check if there is an else body
            if(branch->child[2] == NULL){
                instruction->address[2].data = malloc(sizeof(char)*128);
                sprintf(instruction->address[2].data, ".L%d", location+1);
                instruction->address[2].value = location+1;

                //Create holder label instruction
                quadruple* label_instruction = malloc(sizeof(quadruple));
                label_instruction->operation = LABEL;
                label_instruction->address[0]= instruction->address[2];
                label_instruction->address[1].type = EMPTY;
                label_instruction->address[2].type = EMPTY;
                add_quadruple(label_instruction);
            }else{

                //first need to add the jump at the final of the if true to not exec the else
                quadruple* branch_end_else_instruction = malloc(sizeof(quadruple));

                branch_end_else_instruction->operation = BRANCH;
                branch_end_else_instruction->address[0].type = EMPTY;
                branch_end_else_instruction->address[1].type = EMPTY;
                branch_end_else_instruction->address[2].type = LOCATION;
                //The address 2 will contain the jump addr and will be set latter
                //add the instruction
                add_quadruple(branch_end_else_instruction);
                
                //Here is the start of the else, if false the initial inst goes to here
                instruction->address[2].data = malloc(sizeof(char)*128);
                sprintf(instruction->address[2].data, ".L%d", location+1);
                instruction->address[2].value = location+1;

                //will then use the location to define the end of the true
                //Create holder label  end iftrue instruction
                quadruple* label_instruction = malloc(sizeof(quadruple));
                label_instruction->operation = LABEL;
                label_instruction->address[0]= instruction->address[2];
                label_instruction->address[1].type = EMPTY;
                label_instruction->address[2].type = EMPTY;
                add_quadruple(label_instruction);
                
                //will have to generate the code for this else block
                generate(branch->child[2]);

                //in true code, will jump to a label at the final of the elseblock
                branch_end_else_instruction->address[2].data = malloc(sizeof(char)*128);
                sprintf(branch_end_else_instruction->address[2].data, ".L%d", location+1);
                branch_end_else_instruction->address[2].value = location+1;


                //Create holder label  end iftrue instruction
                quadruple* label_end_else_instruction = malloc(sizeof(quadruple));
                label_end_else_instruction->operation = LABEL;
                label_end_else_instruction->address[0]= branch_end_else_instruction->address[2];
                label_end_else_instruction->address[1].type = EMPTY;
                label_end_else_instruction->address[2].type = EMPTY;
                add_quadruple(label_end_else_instruction);

            }       
            break;

        case WHILE_SK:
            // while start holder label instruction
            quadruple* label_instruction = malloc(sizeof(quadruple));
            label_instruction->operation = LABEL;
            //This is the label start while
            label_instruction->address[0].type = LOCATION;
            label_instruction->address[0].data = malloc(sizeof(char)*128);
            sprintf(label_instruction->address[0].data, ".L%d", location+1);
            label_instruction->address[0].value = location+1;
            
            //at the final instruction for this section, we can reference a jump if not equal 
            //to label_instruction->address[0]
            label_instruction->address[1].type = EMPTY;
            label_instruction->address[2].type = EMPTY;
            add_quadruple(label_instruction);

            // beacause it is a while, the condition has to be met
            // gatter which condition is it
            generate(branch->child[0]);
            //see is condition is not met
            //BNE ENDWHILE
            instruction->operation = BRANCH_IF;
            instruction->address[0].type = EMPTY;
            instruction->address[1]= holder;
            instruction->address[2].type = LOCATION;
            //BNE ENDWHILE
            add_quadruple(instruction);

            if(instruction->address[1].type == REGISTER){
                free_register(instruction->address[1].value);
            }

            //sec gen the while corp
            generate(branch->child[1]);

            //BRANCH TO initial to check
            
            quadruple* branch_start_instruction = malloc(sizeof(quadruple));
            branch_start_instruction->operation = BRANCH;
            branch_start_instruction->address[0].type = EMPTY;
            branch_start_instruction->address[1].type = EMPTY;
            branch_start_instruction->address[2] = label_instruction->address[0];

            add_quadruple(branch_start_instruction);
            //now will jump to start_while label




            //here the finish of the while body 
            //instruction->address[2] is set here to the finish of the while
            instruction->address[2].data = malloc(sizeof(char)*128);
            sprintf(instruction->address[2].data, ".L%d", location+1);
            instruction->address[2].value = location+1;
            
            quadruple* end_while_label_instruction = malloc(sizeof(quadruple));
            end_while_label_instruction->operation = LABEL;
            end_while_label_instruction->address[0]= instruction->address[2];
            end_while_label_instruction->address[1].type = EMPTY;
            end_while_label_instruction->address[2].type = EMPTY;
            add_quadruple(end_while_label_instruction);

            break;
        case RETURN_SK:
            //Has yo return something?
            if(branch->child[0]!=NULL){
                generate(branch->child[0]);
                
                //First pop the Link from stack
                // Then push the data to be returned into the stack
                // Then branch to the popped
                
                quadruple* move_sp_fp = malloc(sizeof(quadruple));
                move_sp_fp->operation = MOVE; 
                move_sp_fp->address[0].type = REGISTER;
                move_sp_fp->address[0].value=2;
                move_sp_fp->address[1].type = REGISTER;
                move_sp_fp->address[1].value=8;
                move_sp_fp->address[2].type = EMPTY;
                add_quadruple(move_sp_fp);

                quadruple* pop_fp = malloc(sizeof(quadruple));
                pop_fp->operation = POP; 
                pop_fp->address[0].type = REGISTER;
                pop_fp->address[0].value=8;
                pop_fp->address[1].type = EMPTY;
                pop_fp->address[2].type = EMPTY;
                add_quadruple(pop_fp);
                 
                quadruple* pop_ra = malloc(sizeof(quadruple));
                pop_ra->operation = POP; 
                pop_ra->address[0].type = REGISTER;
                pop_ra->address[0].value=1;
                pop_ra->address[1].type = EMPTY;
                pop_ra->address[2].type = EMPTY;
                add_quadruple(pop_ra);

                

                quadruple* push_return_value = malloc(sizeof(quadruple));
                push_return_value->operation = MOVE; 
                push_return_value->address[0].type = REGISTER;
                push_return_value->address[0].value = 10;
                if(holder.type == IMMEDIATE && holder.value != 0)
                {
                    quadruple* mvi_vi = malloc(sizeof(quadruple));
                    mvi_vi->operation = LOAD_IMMEDIATE;
                    mvi_vi->address[0].type = REGISTER;
                    mvi_vi->address[0].value = reserve_register();
                    mvi_vi->address[1].type = EMPTY;
                    mvi_vi->address[2] = holder;

                    add_quadruple(mvi_vi);
                    holder = mvi_vi->address[0];
                    
                }
                else{
                    free_register(holder.value);
                }
                push_return_value->address[1] = holder;
                push_return_value->address[2].type = EMPTY;
                add_quadruple(push_return_value);

                

                //GET LR;
                instruction->operation = RET;
                instruction->address[0].type= EMPTY;
                instruction->address[1].type = EMPTY;
                instruction->address[2].type = EMPTY;
                add_quadruple(instruction);
                
            }
            break;
        case ASSIGN_SK:

            //this is the content to be assigned, to do that, generate it
            //register that holds the data or a immediate that holds the const or the return from a call
                
            //generate the first part and get addr of the register
            //for VET or for VAR
            //generate(branch->child[0]);// NEED AN ADDRESS NOT THE CONTENT TO GET THE ADDR, GET THE HOLDER.addr[2,1]
            //holder has the addr for the reg

            if(branch->child[0]->has.exp.kind == VECT_ID_EK)
            {
                char* result_vec_as = malloc(sizeof(char)*128);
                snprintf(result_vec_as, 128U, "%s_%s", scope, branch->child[0]->attr.content);
                uint32_t offset_vec_as = alloc_reg(result_vec_as);


                instruction->address[1].value = 8;
                instruction->address[1].type = REGISTER;

                instruction->address[2].data = result_vec_as;
                instruction->address[2].type = STR;
                instruction->address[2].value = offset_vec_as;

                instruction->operation = LOAD_VAR;
                instruction->address[0].type = REGISTER;
                instruction->address[0].value = reserve_register();

                add_quadruple(instruction);
                
                //this will have to generate the op to calc the size
                quadruple* adder_as = malloc(sizeof(quadruple));

                adder_as->address[1]= instruction->address[0];

                //calc the base addr
                generate(branch->child[0]->child[0]);

                adder_as->address[2] = holder;
                if(holder.type == IMMEDIATE){
                    adder_as->operation = ADDI;
                }else{
                    adder_as->operation = ADD;
                }
                
                adder_as->address[0].type = REGISTER;
                adder_as->address[0].value = reserve_register();
                
                add_quadruple(adder_as); 
                
                free_register(adder_as->address[1].value);
                if ( adder_as->address[2].type == REGISTER)
                {
                    free_register(adder_as->address[2].value);
                }
                free_register(adder_as->address[1].value);

                //Where to put is calculated : adder->address[0]
                
                //load the vector with the calculated addr
                quadruple* vect_store = malloc(sizeof(quadruple));
                //load result register as the operand of the next phase
                vect_store->address[1]= adder_as->address[0];
                generate(branch->child[1]);

                if(holder.type == IMMEDIATE){
                    quadruple* mvi_v = malloc(sizeof(quadruple));
                    mvi_v->operation = LOAD_IMMEDIATE;
                    mvi_v->address[0].type = REGISTER;
                    mvi_v->address[0].value = reserve_register();
                    mvi_v->address[1].type = EMPTY;
                    mvi_v->address[2] = holder;

                    add_quadruple(mvi_v);
                    holder = mvi_v->address[0];
                }

                vect_store->address[0] = holder;
                
                vect_store->address[2].type = EMPTY;
                vect_store->operation = STORE;

                //get the addr of the referenced vector [base] + [offset]
                add_quadruple(vect_store);

                free_register(vect_store->address[0].value);
                
                
                free_register(vect_store->address[1].value);

                // the part where the assign happens
                


            }else {

                char* result_as = malloc(sizeof(char)*128);
                snprintf(result_as, 128U, "%s_%s", "global", branch->child[0]->attr.content);
                //Now, I know that I have to store the content loaded to reg
                int pos = find_in__loc_var_hash_table(result_as);
                if(pos == -1){
                    snprintf(result_as, 128U, "%s_%s", scope, branch->child[0]->attr.content);
                }
                uint32_t offset_as = alloc_reg(result_as);
                // this holds the addr of the variable
                instruction->address[1].type = REGISTER;
                instruction->address[1].value = 8;
                instruction->address[2].type = STR;
                instruction->address[2].data = result_as;
                instruction->address[2].value = offset_as;
                
                generate(branch->child[1]);

                if(holder.type == IMMEDIATE){
                    quadruple* mvi = malloc(sizeof(quadruple));
                    mvi->operation = LOAD_IMMEDIATE;
                    mvi->address[0].type = REGISTER;
                    mvi->address[0].value = reserve_register();
                    mvi->address[1].type = EMPTY;
                    mvi->address[2] = holder;

                    add_quadruple(mvi);
                    holder = mvi->address[0];
                }
                instruction->address[0] = holder;
                // store the content of holder into the address inside the reg [0]
                instruction->operation = STORE;

                add_quadruple(instruction);

                if(instruction->address[0].type=REGISTER){
                    free_register(instruction->address[0].value);
                }
                if(instruction->address[1].type=REGISTER){
                    free_register(instruction->address[1].value);
                }
            }
            break;
        case VAR_SK:
            //this two types dont actually do something in the assembly
            //They are used by the program
            break;
        case VECT_SK:
            // this is the part to alloc,
            
            if(strcmp(scope, "global")==0){
                //add to .data
                char* glob_c = malloc(sizeof(char)*128);
                //root->attr.array_specs.identifier,
                // root->attr.array_specs.size
                snprintf(glob_c, 128U, "%s_%s", "global", branch->attr.content);
                uint32_t offset_glob = alloc_reg(glob_c);
                local_var_count-=4;
                //DATA_SECT
                //.data

            }else{

                /*alloc spaces on the stack, then, send the sp start to the init
                send the sp to the funct_var by alloc var
                alloc spaces for variables stacking
                mv stack start to the top*/

                char* result_vect_dcl = malloc(sizeof(char)*128);
                uint32_t offset_vect_dcl;

                for(int index = 0; index < branch->attr.array_specs.size; index++)
                {
                    snprintf(result_vect_dcl, 128U, "%s_%s_%d", scope, branch->attr.array_specs.identifier, index);
                    offset_vect_dcl = alloc_reg(result_vect_dcl);
                }
                snprintf(result_vect_dcl, 128U, "%s_%s", scope, branch->attr.array_specs.identifier);
                offset_vect_dcl = alloc_reg(result_vect_dcl);

                quadruple* fpoff = malloc(sizeof(quadruple));
                fpoff->operation= ADDI;
                fpoff->address[0].type = REGISTER;
                fpoff->address[0].value = reserve_register();
                fpoff->address[1].type = REGISTER;
                fpoff->address[1].value = 8;
                fpoff->address[2].type = IMMEDIATE;
                fpoff->address[2].value = -(offset_vect_dcl*4);
                add_quadruple(fpoff);
                
                instruction->operation = STORE;
                instruction->address[0].type = REGISTER;
                instruction->address[0].value = fpoff->address[0].value; // Need to contain s0+offsetinit


                instruction->address[1].type = REGISTER;
                instruction->address[1].value = 8;
                instruction->address[2].type = STR;
                instruction->address[2].data = result_vect_dcl;
                instruction->address[2].value = offset_vect_dcl;
                add_quadruple(instruction);
                free_register(fpoff->address[0].value);

                
                //add to sp, for it not to interfere with this local var

                //in epilogue, add a new counter variable with an add
                //add an instruction that finishes being complete in the epilogue, add it even though not have value to add yet, this is local vars ref
                //keep calc

                
                }
            
            break;
        case FUNCT_SK:
            scope = branch->attr.content;

            if(strcmp(scope, "main")==0){
                start.operation = GLOB_MAIN;
                start.address[0].type = EMPTY;
                start.address[1].type = EMPTY;
                start.address[2].type = LOCATION;
                start.address[2].value = location+1;
                start.address[2].data = strdup(branch->attr.content);
                hash_insert(branch->attr.content, &(start.address[2]));
            }

            
            instruction->operation= LABEL;
            instruction->address[0].type = LOCATION;
            instruction->address[0].data = strdup(branch->attr.content);
            instruction->address[0].value= location+1;
            hash_insert(branch->attr.content, &(instruction->address[0]));
            instruction->address[1].type = EMPTY;
            instruction->address[2].type = EMPTY;
            add_quadruple(instruction);
            
            //params gen
            
            
            //prologue


            quadruple* push_ra = malloc(sizeof(quadruple));
            push_ra->operation= PUSH;
            push_ra->address[0].type = REGISTER;
            push_ra->address[0].value = 1;
            push_ra->address[1].type = EMPTY;
            push_ra->address[2].type = EMPTY;

            add_quadruple(push_ra);

            quadruple* push_fp = malloc(sizeof(quadruple));
            push_fp->operation= PUSH;
            push_fp->address[0].type = REGISTER;
            push_fp->address[0].value = 8;
            push_fp->address[1].type = EMPTY;
            push_fp->address[2].type = EMPTY;

            add_quadruple(push_fp);

            quadruple* assign_fp_sp = malloc(sizeof(quadruple));
            assign_fp_sp->operation= MOVE;
            assign_fp_sp->address[0].type = REGISTER;
            assign_fp_sp->address[0].value = 8;
            assign_fp_sp->address[1].type = REGISTER;
            assign_fp_sp->address[1].value = 2;
            assign_fp_sp->address[2].type = EMPTY;
            add_quadruple(assign_fp_sp);


            
            

            quadruple* add_sp_localvars = malloc(sizeof(quadruple));
            add_sp_localvars->operation= ADDI;
            add_sp_localvars->address[0].type = REGISTER;
            add_sp_localvars->address[0].value = 2;
            add_sp_localvars->address[1].type = REGISTER;
            add_sp_localvars->address[1].value = 2;
            add_sp_localvars->address[2].type = IMMEDIATE;
            add_quadruple(add_sp_localvars);


            

            generate(branch->child[1]);
            parameter_c = 0;
            
            //function body gen
            generate(branch->child[2]);

            if( (*(branch->child[0])).has.exp.type == VOID_T )
            {
                quadruple* mv_sp_fp_void = malloc(sizeof(quadruple));
                mv_sp_fp_void->operation = MOVE; 
                mv_sp_fp_void->address[0].type = REGISTER;
                mv_sp_fp_void->address[0].value=2;
                mv_sp_fp_void->address[1].type = REGISTER;
                mv_sp_fp_void->address[1].value=8;
                mv_sp_fp_void->address[2].type = EMPTY;
                add_quadruple(mv_sp_fp_void);

                quadruple* pop_fp_void = malloc(sizeof(quadruple));
                pop_fp_void->operation = POP; 
                pop_fp_void->address[0].type = REGISTER;
                pop_fp_void->address[0].value=8;
                pop_fp_void->address[1].type = EMPTY;
                pop_fp_void->address[2].type = EMPTY;
                add_quadruple(pop_fp_void);
                 
                quadruple* pop_ra_void = malloc(sizeof(quadruple));
                pop_ra_void->operation = POP; 
                pop_ra_void->address[0].type = REGISTER;
                pop_ra_void->address[0].value=1;
                pop_ra_void->address[1].type = EMPTY;
                pop_ra_void->address[2].type = EMPTY;
                add_quadruple(pop_ra_void);
                

                //GET LR;
                quadruple* ret = malloc(sizeof(quadruple));
                ret->operation = RET;
                ret->address[0].type= EMPTY;
                ret->address[1].type = EMPTY;
                ret->address[2].type = EMPTY;
                add_quadruple(ret);
            }


            add_sp_localvars->address[2].value = (int)-(local_var_count);
            local_var_count = 0;
            clean_hash_loc_var_table();

            //should I add anything when finished?
            //need to branch to the link reg 14 is the lr
            //epilogue

            //addquad HERE
            scope = "global";

            //clean all registers for reuse
            register_status = 0xe0bfc000 | 0x00001f00;
            break;

        case CALL_SK:
            uint param_count = 0;
            parameter_c = 0;

            // maybe in the future, the first thing will be to push the LINK REGISTER TO THE STACK,
            //before the pops ?
            //if not a function without params
            if(branch->child[0]!=NULL)
            {
                syntax_t_node* temp = branch->child[0];
                while(temp!= NULL)
                {
                    param_count++;

                    //generate it for each of the args, and counting at the same time
                    switch(temp->type)
                    {
                        case EXP_T:
                            generate_expression(temp);
                            break;
                        case STMT_T:
                            generate_statement(temp);
                            break;
                        default:
                            break;
                    }

                    //can be pushing the ret
                    //var addr
                    //vect addr
                    //const
                    quadruple* parameter_instruction = malloc(sizeof(quadruple));
                    parameter_instruction->operation = MOVE; 
                    parameter_instruction->address[0].type=REGISTER;
                    parameter_instruction->address[0].value = 10+param_count-1;
                    parameter_instruction->address[1]= holder;
                    parameter_instruction->address[2].type = EMPTY;

                    add_quadruple(parameter_instruction);

                    temp = temp->sibling;

                }
            }


            //In future will have to treat input and output syscalls here

            //add a instruction to jump to the location of the function
            instruction->operation = BRANCH_AND_LINK;
            instruction->address[0].type = EMPTY;
            instruction->address[1].type = EMPTY;
            instruction->address[2].type = STR;
            instruction->address[2].data= (*(hash_find(branch->attr.content))).data;
            
            add_quadruple(instruction);
            
            if(strcmp(instruction->address[2].data, "output") == 0)
            {

            }else
            {
                quadruple* pop_ret = malloc(sizeof(quadruple));
                pop_ret->operation = MOVE;
                pop_ret->address[0].type= REGISTER;
                pop_ret->address[0].value=reserve_register();
                pop_ret->address[1].type = REGISTER;
                pop_ret->address[1].value= 10;
                pop_ret->address[2].type = EMPTY;
                add_quadruple(pop_ret);

                holder = pop_ret->address[0];
            }
            

            break;

        case PARAM_SK: 

            //I have the scope and the var name;
            //now I need to concat the two of them,
            //send this str to a function called alloc_reg
            //If the str was already sent into this function, it will send the position
            //the position is an uint that represents the position in the frame pointer,
            //the position is incremented each time a new str is sent to alloc_reg
            //a hash table is incremented with the key = the str sent to the alloc_reg, and the value = position;
            //if the str sent to alloc_reg already is in the hash_table, alloc_reg returns the value, 
            //if not, it inserts the str as a key and the position as a value 
            char* result = malloc(sizeof(char)*128);
            snprintf(result, 128U, "%s_%s", scope, branch->attr.content);
            uint32_t offset = alloc_reg(result);
            
            instruction->operation = STORE;
            instruction->address[0].type = REGISTER;
            instruction->address[0].value = 10+parameter_c++;
            instruction->address[1].type = REGISTER;
            instruction->address[1].value = 8;
            instruction->address[2].type = STR;
            instruction->address[2].data = result;
            instruction->address[2].value = offset;

            

            add_quadruple(instruction);
            //add to sp, for it not to interfere with this local var

            //in epilogue, add a new counter variable with an add
            //add an instruction that finishes being complete in the epilogue, add it even though not have value to add yet, this is local vars ref
            //keep calc

            break;
        case VECT_PARAM_SK:


            //I have the scope and the var name;
            //now I need to concat the two of them,
            //send this str to a function called alloc_reg
            //If the str was already sent into this function, it will send the position
            //the position is an uint that represents the position in the frame pointer,
            //the position is incremented each time a new str is sent to alloc_reg
            //a hash table is incremented with the key = the str sent to the alloc_reg, and the value = position;
            //if the str sent to alloc_reg already is in the hash_table, alloc_reg returns the value, 
            //if not, it inserts the str as a key and the position as a value 
            char* result_vect_param = malloc(sizeof(char)*128);
            snprintf(result_vect_param, 128U, "%s_%s", scope, branch->attr.array_specs.identifier);
            uint32_t offset_vect_param = alloc_reg(result_vect_param);
            
            instruction->operation = STORE;
            instruction->address[0].type = REGISTER;
            instruction->address[0].value = 10+parameter_c++;
            instruction->address[1].type = REGISTER;
            instruction->address[1].value = 8;
            instruction->address[2].type = STR;
            instruction->address[2].data = result_vect_param;
            instruction->address[2].value = offset_vect_param;

            

            add_quadruple(instruction);
            //add to sp, for it not to interfere with this local var

            //in epilogue, add a new counter variable with an add
            //add an instruction that finishes being complete in the epilogue, add it even though not have value to add yet, this is local vars ref
            //keep calc

            break;


    }

}



quadruple* generate(syntax_t_node* syntax_root){
    
    if(syntax_root != NULL)
    {        
        /*switch case here*/
        switch(syntax_root->type)
        {
            case EXP_T:
                generate_expression(syntax_root);
                break;
            case STMT_T:
                generate_statement(syntax_root);
                break;
            default:
				break;
        }
        generate(syntax_root->sibling);
    }
}



void init_generation(syntax_t_node *  root){
    
    init_hash_table();
    generate(root);
}