#include "parser.h"
#include "generator.h"



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




quadruple start;
quadruple* head = &start;
address holder;
char * scope = "global";
uint location = 0;



/*
    0x00: 1000
    0x04: 0000 
    0x08: 0000
    0x0c: 0000
    0x10: 0000
    0x14: 0110 
    0x18: 0000
    0x1c: 0000

*/ 
uint32_t register_status = 0x80000600;
#define SET_BIT(num, pos) ((num) |= (1u << (pos)))
#define RESET_BIT(num, pos) ((num) &= ~(1u << (pos)))



static inline int free_register(uint position){
    RESET_BIT(register_status, position);
}

uint8_t reserve_register(){

    uint8_t i;
    for (i = 31; i >= 0; i--) {
        if (!(register_status & (1u << i))) {
            SET_BIT(register_status, i);
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

static quadruple* generate_expression(syntax_t_node* branch)
{

    quadruple* instruction = malloc(sizeof(quadruple));


    switch(branch->has.exp.kind)
    {
        case OP_EK:

            //generate the code needed for the execution of the left operand
            generate(branch->child[0]);
            // glob var_ addr
            instruction->address[1] = holder;

            //the address for the current 
            //generate the code needed for the execution of the right operand
            generate(branch->child[1]);
            instruction->address[2] = holder;

            //now we can write the quadruple back inside of the quadruple list
            //dest is a temporary register 
            instruction->address[0].value = reserve_register();
            instruction->address[0].type = REGISTER;
            //(branch.attr.op, dest, r2, r3)
            instruction->operation = branch->attr.op;

            //if one of the registers of operand where used, now we can free them
            if(instruction->address[1].type == REGISTER){
                free_register(instruction->address[1].value);
            }
            if(instruction->address[2].type == REGISTER){
                free_register(instruction->address[2].value);
            }

            add_quadruple(instruction);
            
            //The holder is the register in which the op will be stored;
            holder = instruction->address[0];
            break;

        case ID_EK:
            instruction->address[1].data = scope;
            instruction->address[1].type = STR;

            instruction->address[2].data = branch->attr.content;
            instruction->address[2].type = STR;

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
            instruction->address[1].data = scope;
            instruction->address[1].type = STR;

            instruction->address[2].data = branch->attr.content;
            instruction->address[2].type = STR;

            instruction->operation = LOAD_VAR;
            instruction->address[0].type = REGISTER;
            instruction->address[0].value = reserve_register();

            add_quadruple(instruction);
            
            //this will have to generate the op to calc the size
            quadruple* adder = malloc(sizeof(quadruple));

            adder->address[1]= instruction->address[0];

            //calc the base addr
            generate(branch->child[0]);

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
            vect_loader->operation = LOAD_VECT;

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
            instruction->operation = BRANCH_IF_NOT_TRUE;

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
                instruction->address[2].data = name_label("ENDIF_", location+1);
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
                instruction->address[2].data = name_label("STARTELSE_",location+1);
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
                branch_end_else_instruction->address[2].data = name_label("ENDELSE_",location+1);
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
            label_instruction->address[0].data = name_label("STARTWHILE_",location+1);
            label_instruction->address[0].value= location+1;
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
            instruction->operation = BRANCH_IF_NOT_TRUE;
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
            instruction->address[2].data = name_label("ENDWHILE_",location+1);
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

                //GET LR;
                instruction->operation = POP;
                instruction->address[0].type= REGISTER;
                instruction->address[0].value=reserve_register();
                instruction->address[1].type = EMPTY;
                instruction->address[2].type = EMPTY;
                add_quadruple(instruction);

                quadruple* push_return_value = malloc(sizeof(quadruple));
                push_return_value->operation = PUSH; 
                push_return_value->address[0]=holder;
                push_return_value->address[1].type = EMPTY;
                push_return_value->address[2].type = EMPTY;
                add_quadruple(push_return_value);

                quadruple* branch_link_reg = malloc(sizeof(quadruple));
                branch_link_reg->operation = BRANCH;
                branch_link_reg->address[0].type = EMPTY;
                branch_link_reg->address[1].type = EMPTY;
                branch_link_reg->address[2].type = REGISTER;
                branch_link_reg->address[2].value = instruction->address[0].value;
                add_quadruple(branch_link_reg);
                
            }
            break;
        case ASSIGN_SK:

            //generate the first part and get addr of the register
            //for VET or for VAR
            generate(branch->child[0]);// NEED AN ADDRESS NOT THE CONTENT TO GET THE ADDR, GET THE HOLDER.addr[2,1]
            //holder has the addr for the reg

            //Now, I know that I have to store the content loaded to reg
            
            // this holds the addr of the variable
            instruction->address[0] = holder;
            instruction->address[1].type = EMPTY;
            

            //this is the content to be assigned, to do that, generate it
            generate(branch->child[1]);
            //register that holds the data or a immediate that holds the const or the return from a call
            instruction->address[2] = holder;
            
            
            // store the content of holder into the address inside the reg [0]
            instruction->operation = STORE;

            add_quadruple(instruction);

            if(instruction->address[0].type=REGISTER){
                free_register(instruction->address[0].value);
            }

            break;
        case VAR_SK:
        case VECT_SK:
            //this two types dont actually do something in the assembly
            //They are used by the program
            break;
        case FUNCT_SK:
            scope = branch->attr.content;

            if(strcmp(scope, "main")==0){
                start.operation = BRANCH;
                start.address[0].type = EMPTY;
                start.address[1].type = EMPTY;
                start.address[2].type = LOCATION;
                start.address[2].value = location+1;
                start.address[2].data = name_label(branch->attr.content,location+1);
                hash_insert(branch->attr.content, &(start.address[2]));
            }

            
            instruction->operation= LABEL;
            instruction->address[0].type = LOCATION;
            instruction->address[0].data = name_label(branch->attr.content,location+1);
            instruction->address[0].value= location+1;
            hash_insert(branch->attr.content, &(instruction->address[0]));
            instruction->address[1].type = EMPTY;
            instruction->address[2].type = EMPTY;
            add_quadruple(instruction);
            
            //params gen
            generate(branch->child[1]);
            //function body gen
            generate(branch->child[2]);

            //should I add anything when finished?
            //need to branch to the link reg 14 is the lr
            quadruple* jump_lr_instruction = malloc(sizeof(quadruple));
            jump_lr_instruction->operation= MOVE;
            jump_lr_instruction->address[0].type = REGISTER;
            jump_lr_instruction->address[0].value = 15;
            jump_lr_instruction->address[1].type = EMPTY;
            jump_lr_instruction->address[0].type = REGISTER;
            jump_lr_instruction->address[0].value = 14;

            add_quadruple(jump_lr_instruction);

            //addquad HERE
            scope = "global";

            //clean all registers for reuse
            register_status = 0x80060000;
            break;

        case CALL_SK:
            uint param_count = 0;

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
                    parameter_instruction->operation = PUSH; 
                    parameter_instruction->address[0]=holder;
                    parameter_instruction->address[1].type = EMPTY;
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
            instruction->address[2]= *(hash_find(branch->attr.content));
            
            add_quadruple(instruction);

            quadruple* pop_ret = malloc(sizeof(quadruple));
            pop_ret->operation = POP;
            pop_ret->address[0].type= REGISTER;
            pop_ret->address[0].value=reserve_register();
            pop_ret->address[1].type = EMPTY;
            pop_ret->address[2].type = EMPTY;
            add_quadruple(pop_ret);

            holder = pop_ret->address[0];

            break;

        case PARAM_SK: 
        case VECT_PARAM_SK:
            // POP all the content that was pushed into the stack
            //generate a POP instruction for each that is here;
            instruction->operation = POP;
            instruction->address[0].type = REGISTER;
            instruction->address[0].value = reserve_register();
            instruction->address[1].type = EMPTY;
            instruction->address[2].type = EMPTY;
            
            add_quadruple(instruction);
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


//printer section

const char* operation_strings[] = {
    "LOAD_VAR",
    "LOAD_VECT",
    "BRANCH_IF_NOT_TRUE",
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
    "LESS_RELOP"
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

    while (current->next != NULL) {
        print_quadruple(current);
        current = current->next;
    }
}

void init_generation(syntax_t_node *  root){
    
    init_hash_table();
    generate(root);
}