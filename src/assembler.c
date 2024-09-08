#include "assembler.h"


#include <stdint.h>

#include <stdint.h>

void generate_binary(FILE *file, quadruple *instruction_pointer) {
    uint32_t binary = 0;

    switch (instruction_pointer->operation) {
        case POP:
            binary = (0x03 << 0) |                            // opcode for LOAD
                     (instruction_pointer->address[0].value << 7) |  // rd
                     (0x2 << 12) |                            // funct3 for LW
                     (2 << 15) | // rs1
                     (0 << 20);
            binary = htobe32(binary);
            fwrite(&binary, sizeof(binary), 1, file);
            binary = ( 4 << 20) |  // imm
                     (2 << 15) |  // rs1
                     (0x0 << 12) |                                   // funct3 for ADDI
                     (2 << 7) |   // rd
                     (0x13);  // opcode for I-type instructions


            break;
        case PUSH:
            
            binary = ( 4 << 20) |  // imm
                     (2 << 15) |  // rs1
                     (0x0 << 12) |                                   // funct3 for ADDI
                     (2 << 7) |   // rd
                     (0x13);  // opcode for I-type instructions
            binary = htobe32(binary);
            fwrite(&binary, sizeof(binary), 1, file);

            binary = (((instruction_pointer->address[2].value + 1) * -4 & 0xFE0) << 25) |  // imm[11:5]
                     (instruction_pointer->address[0].value << 20) |                       // rs2
                     (2 << 15) |                       // rs1
                     (0x2 << 12) |                                                        // funct3 for SW
                     ((0 ) << 7) |    // imm[4:0]
                     (0x23);  // opcode for STORE


        case LOAD_VAR:
            // lw x[rd], offset(x[rs1])
            binary = (0x03) |                                 // opcode for LOAD
                     (instruction_pointer->address[0].value << 7) |  // rd
                     (0x2 << 12) |                            // funct3 for LW
                     (instruction_pointer->address[1].value << 15) | // rs1
                     ((instruction_pointer->address[2].value + 1) * -4 << 20); // imm
            
            break;

        case LOAD_VECT:
            // lw x[rd], offset(s0)
            binary = (0x03) |                                 // opcode for LOAD
                     (instruction_pointer->address[0].value << 7) |  // rd
                     (0x2 << 12) |                            // funct3 for LW
                     (16 << 15) |                             // s0 (x16)
                     (9 << 20);                               // imm (9 in this case)
            
            break;

        case STORE:
            // sw x[rs2], offset(x[rs1])
            binary = (((((instruction_pointer->address[2].value + 1) * -4) & 0xFE0)>>5) << 25) |  // imm[11:5]
                     (instruction_pointer->address[0].value << 20) |                       // rs2
                     (instruction_pointer->address[1].value << 15) |                       // rs1
                     (0x2 << 12) |                                                        // funct3 for SW
                     (((instruction_pointer->address[2].value + 1) * -4 & 0x1F) << 7) |    // imm[4:0]
                     (0x23);  // opcode for STORE
            
            break;

        case ADD:
            // add x[rd], x[rs1], x[rs2]
            binary = (0x00 << 25) |                                 // funct7 for ADD
                     (instruction_pointer->address[2].value << 20) |  // rs2
                     (instruction_pointer->address[1].value << 15) |  // rs1
                     (0x0 << 12) |                                  // funct3 for ADD
                     (instruction_pointer->address[0].value << 7) |   // rd
                     (0x33);  // opcode for R-type instructions
            
            break;

        case SUB:
            // sub x[rd], x[rs1], x[rs2]
            binary = (0x20 << 25) |                                 // funct7 for SUB
                     (instruction_pointer->address[2].value << 20) |  // rs2
                     (instruction_pointer->address[1].value << 15) |  // rs1
                     (0x0 << 12) |                                  // funct3 for SUB
                     (instruction_pointer->address[0].value << 7) |   // rd
                     (0x33);  // opcode for R-type
            
            break;

        case MULT:
            // mul x[rd], x[rs1], x[rs2]
            binary = (0x01 << 25) |                                 // funct7 for MUL
                     (instruction_pointer->address[2].value << 20) |  // rs2
                     (instruction_pointer->address[1].value << 15) |  // rs1
                     (0x0 << 12) |                                  // funct3 for MUL
                     (instruction_pointer->address[0].value << 7) |   // rd
                     (0x33);  // opcode for R-type
            
            break;

        case DIV:
            // div x[rd], x[rs1], x[rs2]
            binary = (0x1 << 25) |                                 // funct7 for DIV
                     (instruction_pointer->address[2].value << 20) |  // rs2
                     (instruction_pointer->address[1].value << 15) |  // rs1
                     (0x4 << 12) |                                  // funct3 for DIV
                     (instruction_pointer->address[0].value << 7) |   // rd
                     (0x33);  // opcode for R-type
            
            break;

        case ADDI:
            // addi x[rd], x[rs1], imm
            binary = (instruction_pointer->address[2].value << 20) |  // imm
                     (instruction_pointer->address[1].value << 15) |  // rs1
                     (0x0 << 12) |                                   // funct3 for ADDI
                     (instruction_pointer->address[0].value << 7) |   // rd
                     (0x13);  // opcode for I-type instructions
            
            break;

        case BRANCH_AND_LINK:
            // jal x[rd], imm
            // Binary: imm | rd(5) | opcode(7)
            binary = (0x6F) |                                        // opcode for JAL
                     (0 << 7) |  // rd
                     ((instruction_pointer->address[2].value & 0xFFFFF) << 12);  // imm
            
            break;

        case EQ_REL:
            // beq x[rs1], x[rs2], imm
            binary = ((instruction_pointer->address[2].value & 0xFE0) << 25) |  // imm[11:5]
                     (instruction_pointer->address[1].value << 15) |            // rs1
                     (instruction_pointer->address[0].value << 20) |            // rs2
                     (0x0 << 12) |                                              // funct3 for BEQ
                     ((instruction_pointer->address[2].value & 0x1F) << 7) |    // imm[4:0]
                     (0x63);  // opcode for conditional branches
            
            break;

        case NOTEQ_REL:
            // bne x[rs1], x[rs2], imm
            binary = ((instruction_pointer->address[2].value & 0xFE0) << 25) |  // imm[11:5]
                     (instruction_pointer->address[1].value << 15) |            // rs1
                     (instruction_pointer->address[0].value << 20) |            // rs2
                     (0x1 << 12) |                                              // funct3 for BNE
                     ((instruction_pointer->address[2].value & 0x1F) << 7) |    // imm[4:0]
                     (0x63);  // opcode for conditional branches
            
            break;

        case BRANCH:
            // j imm
            // Binary: imm | opcode(7)
            binary = (instruction_pointer->address[2].value << 12) |  // imm
                     (0x6F);                                         // opcode for J-type (JAL)
            
            break;

        case RET:
            // ret
            // Equivalent to jalr x0, x1, 0
            binary = (0x0 << 20) |  // imm = 0
                     (1 << 15) |    // rs1 = x1 (return address)
                     (0x0 << 12) |  // funct3
                     (0 << 7) |     // rd = x0 (discard result)
                     (0x67);        // opcode for JALR
            
            break;

        case LOAD_IMMEDIATE:
            // li x[rd], imm (equivalent to addi x[rd], x0, imm)
            binary = (instruction_pointer->address[2].value << 20) |  // imm
                     (0x0 << 15) |                                    // rs1 = x0
                     (0x0 << 12) |                                    // funct3 for ADDI
                     (instruction_pointer->address[0].value << 7) |   // rd
                     (0x13);  // opcode for I-type instructions
            
            break;

        case MOVE:
            // mv x[rd], x[rs1] (equivalent to addi x[rd], x[rs1], 0)
            binary = (0x0 << 20) |                                    // imm = 0
                     (instruction_pointer->address[1].value << 15) |  // rs1
                     (0x0 << 12) |                                    // funct3 for ADDI
                     (instruction_pointer->address[0].value << 7) |   // rd
                     (0x13);  // opcode for I-type instructions
            
            break;
        case LABEL:
            return;

        case LESS_REL:
            // blt x[rs1], x[rs2], imm
            binary = ((instruction_pointer->address[2].value & 0xFE0) << 25) |  // imm[11:5]
                     (instruction_pointer->address[1].value << 15) |            // rs1
                     (instruction_pointer->address[0].value << 20) |            // rs2
                     (0x4 << 12) |                                              // funct3 for BLT
                     ((instruction_pointer->address[2].value & 0x1F) << 7) |    // imm[4:0]
                     (0x63);  // opcode for conditional branches
            binary = htobe32(binary);
            
            break;

        case GREAT_REL:
            // bgt x[rs1], x[rs2], imm
            binary = ((instruction_pointer->address[2].value & 0xFE0) << 25) |  // imm[11:5]
                     (instruction_pointer->address[1].value << 15) |            // rs1
                     (instruction_pointer->address[0].value << 20) |            // rs2
                     (0x5 << 12) |                                              // funct3 for BGT
                     ((instruction_pointer->address[2].value & 0x1F) << 7) |    // imm[4:0]
                     (0x63);  // opcode for conditional branche
            break;
        case LESSEQ_REL:
            // ble x[rs1], x[rs2], imm
            binary = ((instruction_pointer->address[2].value & 0xFFFFF000) >> 12) |  // imm[12:1]
                     (instruction_pointer->address[1].value << 15) |               // rs1
                     (instruction_pointer->address[0].value << 20) |               // rs2
                     (0x4 << 12) |                                                 // funct3 for BLE
                     (0x63);  // opcode for conditional branches
            fwrite(&binary, sizeof(binary), 1, file);
            break;

        case GREATEQ_REL:
            // bge x[rs1], x[rs2], imm
            binary = ((instruction_pointer->address[2].value & 0xFFFFF000) >> 12) |  // imm[12:1]
                     (instruction_pointer->address[1].value << 15) |               // rs1
                     (instruction_pointer->address[0].value << 20) |               // rs2
                     (0x5 << 12) |                                                 // funct3 for BGE
                     (0x63);  // opcode for conditional branches
            fwrite(&binary, sizeof(binary), 1, file);
            break;
    }
    binary = htobe32(binary);
    fwrite(&binary, sizeof(binary), 1, file);
}


void assemble(quadruple * head)
{
    quadruple* instruction_pointer = (quadruple *) head;

    // Open file for writing
    FILE *file = fopen("app.s", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *bin_file = fopen("app.bin", "w");
    if (bin_file == NULL) {
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
                    generate_binary(bin_file, instruction_pointer);
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
                        generate_binary(bin_file, instruction_pointer);
                        break;
                    case NOTEQ_REL:
                        // bne $reg1, $reg2, immediate_location
                        fprintf(file, "bne x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        generate_binary(bin_file, instruction_pointer);
                        break;
                    case LESSEQ_REL:
                    // ble $reg1, $reg2, immediate_location
                        fprintf(file, "ble x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        generate_binary(bin_file, instruction_pointer);
                        break;
                    case GREATEQ_REL:
                        // bge $reg1, $reg2, immediate_location
                        fprintf(file, "bge x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        generate_binary(bin_file, instruction_pointer);
                        break;
                    case GREAT_REL:
                        // bgt $reg1, $reg2, immediate_location
                        fprintf(file, "bgt x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        generate_binary(bin_file, instruction_pointer);
                        break;
                    case LESS_REL:
                        // blt $reg1, $reg2, immediate_location
                        fprintf(file, "blt x%d, x%d, %s\n", 
                            instruction_pointer->address[1].value, 
                            instruction_pointer->address[2].value, 
                            relative_loc);
                        generate_binary(bin_file, instruction_pointer);
                        break;
                }
            
                break;
            }
            
            case BRANCH:
                // j <location>
                fprintf(file, "j %s\n", instruction_pointer->address[2].data);
                generate_binary(bin_file, instruction_pointer);
                break;

            case LABEL:
                // Label marker (NOP or empty)
                fprintf(file, "%s:\n", instruction_pointer->address[0].data);
                generate_binary(bin_file, instruction_pointer);
                break;

            case MOVE:
                // mv $dest, $src
                fprintf(file, "mv x%d, x%d\n", 
                    instruction_pointer->address[0].value, 
                    instruction_pointer->address[1].value);
                generate_binary(bin_file, instruction_pointer);
                break;

            case PUSH:
                // addi sp, sp, -4; sw $reg, 0(sp)
                fprintf(file, "addi x2, x2, -4\n");
                fprintf(file, "sw x%d, 0(x2)\n", instruction_pointer->address[0].value);
                generate_binary(bin_file, instruction_pointer);
                break;

            case POP:
                // lw $dest, 0(sp); addi sp, sp, 4
                fprintf(file, "lw x%d, 0(x2)\n", instruction_pointer->address[0].value);
                fprintf(file, "addi x2, x2, 4\n");
                generate_binary(bin_file, instruction_pointer);
                break;

            case BRANCH_AND_LINK:
                // jal <location>
                fprintf(file, "jal %s\n", instruction_pointer->address[2].data);
                generate_binary(bin_file, instruction_pointer);
                break;
            
            case ADDI:
                fprintf(file, "addi x%d, x%d, %d\n", instruction_pointer->address[0].value, instruction_pointer->address[1].value, instruction_pointer->address[2].value);
                generate_binary(bin_file, instruction_pointer);
                break;

            case STORE:
                // sw $reg, offset(s0)
                fprintf(file, "sw x%d, %d(x%d)\n", 
                    instruction_pointer->address[0].value, 
                    (instruction_pointer->address[2].value+1)*-4,
                    instruction_pointer->address[1].value);
                generate_binary(bin_file, instruction_pointer);
                break;

            case ADD:
                // add $dest, $src1, $src2
                fprintf(file, "add x%d, x%d, x%d\n", 
                    instruction_pointer->address[0].value, 
                    instruction_pointer->address[1].value, 
                    instruction_pointer->address[2].value);
                generate_binary(bin_file, instruction_pointer);
                break;

            case SUB:
                // sub $dest, $src1, $src2
                fprintf(file, "sub x%d, x%d, x%d\n", 
                    instruction_pointer->address[0].value, 
                    instruction_pointer->address[1].value, 
                    instruction_pointer->address[2].value);
                generate_binary(bin_file, instruction_pointer);
                break;

            case MULT:
                
                fprintf(file, "mul x%d, x%d, x%d\n", instruction_pointer->address[0].value, instruction_pointer->address[1].value, instruction_pointer->address[2].value);
                generate_binary(bin_file, instruction_pointer);
                break;

            case DIV:
                // Divide using jal __div; assumes __div function
                // mv dest, a0 
                fprintf(file, "div x%d, x%d, x%d\n", instruction_pointer->address[0].value, instruction_pointer->address[1].value, instruction_pointer->address[2].value);
                generate_binary(bin_file, instruction_pointer);

                break;

            case RET:
                // ret
                fprintf(file, "ret\n");
                generate_binary(bin_file, instruction_pointer);
                break;

            case LOAD_IMMEDIATE:
                // li $reg, immediate
                fprintf(file, "li x%d, %d\n", 
                    instruction_pointer->address[0].value, 
                    instruction_pointer->address[2].value);
                generate_binary(bin_file, instruction_pointer);
                break;
            case GLOB_MAIN:
                // li $reg, immediate
                fprintf(file, ".globl %s\n", 
                    instruction_pointer->address[2].data);
                generate_binary(bin_file, instruction_pointer);
                break;
        }

        instruction_pointer = instruction_pointer->next;
    }
    fclose(file);
    fclose(bin_file);
}
  