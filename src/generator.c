#include "parser.h"
#include "generator.h"
#ifndef YYPARSE
#include "../utils/bison/parser.tab.h"
#endif


quadruple* head = malloc(sizeof quadruple);
quadruple* start = head;
address holder;
char * scope = "global";
uint location = 0;




uint_32_t register_status = 0x80060000;
#define SET_BIT(num, pos) ((num) |= (1u << (pos)))
#define RESET_BIT(num, pos) ((num) &= ~(1u << (pos)))



static inline free_register(uint_8_t position){
    RESET_BIT(register_status, position);
}

uint_8_t reserve_register(){

    uint_8_t i;
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
            if(instruction->address[1].type = REGISTER){
                free_register(instruction->address[1].value);
            }
            if(instruction->address[2].type = REGISTER){
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
            adder = malloc(sizeof(quadruple));

            adder->address[1]= instruction->address[0];

            //calc the base addr
            generate(branch->child[0]);

            adder->address[2] = holder;
            adder->operation = PLUS_ALOP;
            adder->address[0].type = REGISTER;
            adder->address[0].value = reserve_register();
            
            add_quadruple(adder); 
            
            //load the vector with the calculated addr
            vect_loader = malloc(sizeof(quadruple));
            //load result register as the operand of the next phase
            vect_loader->address[1]= adder->address[0];

            vect_loader->address[0].type = REGISTER;
            vect_loader->address[0].value = reserve_register();
            
            vect_loader->address[2] = NULL;
            vect_loader->operation = LOAD_VECT;

            
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
            instruction->operation = BRANCH_IF_NOT_EQUAL;

            //no use
            instruction->address[0] = NULL;
            
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
                instruction->address[2].data = name_label("ENDIF_", location);
                instruction->address[2].value = location;

                //Create holder label instruction
                label_instruction = malloc(sizeof(quadruple));
                label_instruction->operation = LABEL;
                label_instruction->address[0]= instruction->address[2];
                label_instruction->address[1]= NULL;
                label_instruction->address[2]= NULL;
                add_quadruple(label_instruction);
            }else{

                //first need to add the jump at the final of the if true to not exec the else
                branch_end_else_instruction = malloc(sizeof(quadruple));

                branch_end_else_instruction->operation = BRANCH;
                branch_end_else_instruction->address[0] = NULL;
                branch_end_else_instruction->address[1] = NULL;
                branch_end_else_instruction->address[2].type = LOCATION;
                //The address 2 will contain the jump addr and will be set latter
                //add the instruction
                add_quadruple(branch_end_else_instruction);
                
                //Here is the start of the else, if false the initial inst goes to here
                instruction->address[2].data = name_label("STARTELSE_",location);
                instruction->address[2].value = location;

                //will then use the location to define the end of the true
                //Create holder label  end iftrue instruction
                label_instruction = malloc(sizeof(quadruple));
                label_instruction->operation = LABEL;
                label_instruction->address[0]= instruction->address[2];
                label_instruction->address[1]= NULL;
                label_instruction->address[2]= NULL;
                add_quadruple(label_instruction);
                
                //will have to generate the code for this else block
                generate(branch->child[2]);

                //in true code, will jump to a label at the final of the elseblock
                branch_end_else_instruction->address[2].data = name_label("ENDELSE_",location);
                branch_end_else_instruction->address[2].value = location;


                //Create holder label  end iftrue instruction
                label_end_else_instruction = malloc(sizeof(quadruple));
                label_end_else_instruction->operation = LABEL;
                label_end_else_instruction->address[0]= branch_end_else_instruction->address[2];
                label_end_else_instruction->address[1]= NULL;
                label_end_else_instruction->address[2]= NULL;
                add_quadruple(label_end_else_instruction);

            }       
            break;

        case WHILE_SK:
            // while start holder label instruction
            label_instruction = malloc(sizeof(quadruple));
            label_instruction->operation = LABEL;
            //This is the label start while
            label_instruction->address[0].type = LOCATION;
            label_instruction->address[0].data = name_label("STARTWHILE_",location);
            label_instruction->address[0].value= location;
            //at the final instruction for this section, we can reference a jump if not equal 
            //to label_instruction->address[0]
            label_instruction->address[1]= NULL;
            label_instruction->address[2]= NULL;
            add_quadruple(label_instruction);

            // beacause it is a while, the condition has to be met
            // gatter which condition is it
            generate(branch->child[0]);
            //see is condition is not met
            //BNE ENDWHILE
            instruction->operation = BRANCH_IF_NOT_EQUAL;
            instruction->address[0]= NULL;
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
            
            branch_start_instruction = malloc(sizeof(quadruple));
            branch_start_instruction->operation = BRANCH;
            branch_start_instruction->address[0]= NULL;
            branch_start_instruction->address[1]= NULL;
            branch_start_instruction->address[2] = label_instruction->address[0];

            add_quadruple(branch_start_instruction);
            //now will jump to start_while label




            //here the finish of the while body 
            //instruction->address[2] is set here to the finish of the while
            instruction->address[2].data = name_label("ENDWHILE_",location);
            instruction->address[2].value = location;
            
            end_while_label_instruction = malloc(sizeof(quadruple));
            end_while_label_instruction->operation = LABEL;
            end_while_label_instruction->address[0]= instruction->address[2];
            end_while_label_instruction->address[1]= NULL;
            end_while_label_instruction->address[2]= NULL;
            add_quadruple(end_while_label_instruction);

            break;
        case RETURN_SK:
            //Has yo return something?
            if(branch->child[0]!=NULL){
                generate(branch->child[0]);


                //has to move all the data to a register;
                instruction->operation = MOVE;
                instruction->address[0].type= REGISTER;
                instruction->address[0].value=reserve_register();
                instruction->address[1]=NULL;
                instruction->address[2]= holder;

                add_quadruple(instruction);

                holder = instruction->address[0];
            }
            break;
        case ASSIGN_SK:

            generate(branch->child[1]);

            break;
        case VAR_SK:
        case VECT_SK:
        case FUNCT_SK:
            
            scope = branch->attr.content;

            if(strcmp(scope, "main")==0){
                start->operation = BRANCH;
                start->address[0] = NULL;
                start->address[1] = NULL;
                start->address[2].type = LOCATION;
                start->address[2].value = location;
                start->address[2].data = name_label(branch->attr.content,location);
                hash_insert(branch->attr.content, &(start->address[2]));
            }

            
            instruction->operation= LABEL;
            instruction->address[0].type = LOCATION;
            instruction->address[0].data = name_label(branch->attr.content,location);
            instruction->address[0].value= location;
            hash_insert(branch->attr.content, instruction->address[0]);
            instruction->address[1]= NULL;
            instruction->address[2]= NULL;
            add_quadruple(instruction);
            
            //params gen
            generate(branch->child[1]);
            //function body gen
            generate(branch->child[2]);

            //should I add anything when finished?
            //need to branch to the link reg 14 is the lr
            jump_lr_instruction = malloc(sizeof(quadruple));
            jump_lr_instruction->operation= MOVE;
            jump_lr_instruction->address[0].type = REGISTER;
            jump_lr_instruction->address[0].value = 15;
            jump_lr_instruction->address[1] = NULL;
            jump_lr_instruction->address[0].type = REGISTER;
            jump_lr_instruction->address[0].value = 14;

            add_quadruple(jump_lr_instruction);

            //addquad HERE
            scope = "global";

            //clean all registers for reuse
            registers = 0x80060000;
            break;

        case CALL_SK:
            uint param_count = 0;
            //if not a function without params
            if(branch->child[0]!=NULL)
            {
                syntax_t_node temp = branch;
                while(temp!= NULL)
                {
                    param_count++;

                    //generate it for each of the args, and counting at the same time
                    switch(temp->type)
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

                    parameter_instruction = malloc(sizeof(quadruple));
                    parameter_instruction->type = PUSH; 
                    parameter_instruction->address[0]=holder;
                    parameter_instruction->address[1]=NULL;
                    parameter_instruction->address[2]=NULL;

                    add_quadruple(parameter_instruction);

                    temp = temp->sibling;

                }
            }


            //In future will have to treat input and output syscalls here

            //add a instruction to jump to the location of the function
            instruction->type = BRANCH_AND_LINK;
            intruction->address[0]= NULL;
            intruction->address[1]= NULL;
            intruction->address[2]= hash_find(branch->child[0].attr.content);
            

            add_quadruple(instruction);

            break;

        case PARAM_SK: 
            // POP all the content that was pushed into the stack
            //generate a POP instruction for each that is here;
            instruction->operation = POP;
            instruction->address[0].type = REGISTER;
            instruction->address[0].value = reserve_register();
            instruction->address[1] = NULL;
            instruction->address[2] = NULL;
            
            add_quadruple(instruction);
            break;

        case VECT_PARAM_SK:
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


