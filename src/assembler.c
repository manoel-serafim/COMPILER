#include "assembler.h"



void assemble(quadruple * head)
{
    quadruple* instruction_pointer = (quadruple *) head;

    // Open file for writing
    FILE *file = fopen("app.s", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }


    while (instruction_pointer != NULL)
    {
        switch (instruction_pointer->operation)
        {
            case LOAD_VAR:
                // lw $reg, offset(s0)
                fprintf(file, "lw x%d, %d(x%d)\n", 
                    instruction_pointer->address[0].value, 
                    (instruction_pointer->address[2].value+1)*-4,
                    instruction_pointer->address[1].value);
                    //offset_calc(instruction_pointer->address[1], instruction_pointer->address[2]));
                break;

            case LOAD_VECT:
                // lw $reg, offset(s0) with additional offset
                fprintf(file, "lw x%d, %d(s0)\n", 
                    instruction_pointer->address[0].value, 9);
                    //offset_calc(instruction_pointer->address[1], instruction_pointer->address[2]));
                break;

            case EQ_REL:
            case NOTEQ_REL:
            case LESSEQ_REL:
            case GREATEQ_REL:
            case GREAT_REL:
            case LESS_REL:
            {
                // Handle conditional branch based on comparison
                char* relative_loc = instruction_pointer->next->address[2].data;

                switch (instruction_pointer->operation)
                {
                    case EQ_REL:
                        // beq $reg1, $reg2, immediate_location
                        fprintf(file, "beq x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        break;
                    case NOTEQ_REL:
                        // bne $reg1, $reg2, immediate_location
                        fprintf(file, "bne x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        break;
                    case LESSEQ_REL:
                    // ble $reg1, $reg2, immediate_location
                        fprintf(file, "ble x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        break;
                    case GREATEQ_REL:
                        // bge $reg1, $reg2, immediate_location
                        fprintf(file, "bge x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        break;
                    case GREAT_REL:
                        // bgt $reg1, $reg2, immediate_location
                        fprintf(file, "bgt x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        break;
                    case LESS_REL:
                        // blt $reg1, $reg2, immediate_location
                        fprintf(file, "blt x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        break;
                }
            
                break;
            }
            
            case BRANCH:
                // j <location>
                fprintf(file, "j %s\n", instruction_pointer->address[2].data);
                break;

            case LABEL:
                // Label marker (NOP or empty)
                fprintf(file, "%s:\n", instruction_pointer->address[0].data);
                break;

            case MOVE:
                // mv $dest, $src
                fprintf(file, "mv x%d, x%d\n", 
                    instruction_pointer->address[0].value, 
                    instruction_pointer->address[1].value);
                break;

            case PUSH:
                // addi sp, sp, -4; sw $reg, 0(sp)
                fprintf(file, "addi x2, x2, -4\n");
                fprintf(file, "sw x%d, (x2)\n", instruction_pointer->address[0].value);
                break;

            case POP:
                // lw $dest, 0(sp); addi sp, sp, 4
                fprintf(file, "lw x%d, (x2)\n", instruction_pointer->address[0].value);
                fprintf(file, "addi x2, x2, 4\n");
                break;

            case BRANCH_AND_LINK:
                // jal <location>
                fprintf(file, "jal %s\n", instruction_pointer->address[2].data);
                break;
            
            case ADDI:
                fprintf(file, "addi x%d, x%d, %d\n", instruction_pointer->address[0].value, instruction_pointer->address[1].value, instruction_pointer->address[2].value);
                break;

            case STORE:
                // sw $reg, offset(s0)
                fprintf(file, "sw x%d, %d(x%d)\n", 
                    instruction_pointer->address[0].value, 
                    (instruction_pointer->address[2].value+1)*-4,
                    instruction_pointer->address[1].value);
                break;

            case ADD:
                // add $dest, $src1, $src2
                fprintf(file, "add x%d, x%d, x%d\n", 
                    instruction_pointer->address[0].value, 
                    instruction_pointer->address[1].value, 
                    instruction_pointer->address[2].value);
                break;

            case SUB:
                // sub $dest, $src1, $src2
                fprintf(file, "sub x%d, x%d, x%d\n", 
                    instruction_pointer->address[0].value, 
                    instruction_pointer->address[1].value, 
                    instruction_pointer->address[2].value);
                break;

            case MULT:
                
                fprintf(file, "mul x%d, x%d, x%d\n", instruction_pointer->address[0].value, instruction_pointer->address[1].value, instruction_pointer->address[2].value);
                break;

            case DIV:
                // Divide using jal __div; assumes __div function
                // mv dest, a0 
                fprintf(file, "div x%d, x%d, x%d\n", instruction_pointer->address[0].value, instruction_pointer->address[1].value, instruction_pointer->address[2].value);

                break;

            case RET:
                // ret
                fprintf(file, "ret\n");
                break;

            case LOAD_IMMEDIATE:
                // li $reg, immediate
                fprintf(file, "li x%d, %d\n", 
                    instruction_pointer->address[0].value, 
                    instruction_pointer->address[2].value);
                break;
            case GLOB_MAIN:
                // li $reg, immediate
                fprintf(file, ".globl %s\n", 
                    instruction_pointer->address[2].data);
                break;
        }

        instruction_pointer = instruction_pointer->next;
    }
    fclose(file);
}
