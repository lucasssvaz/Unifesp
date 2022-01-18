#include "globals.h"
#include "symtab.h"
#include "intercode.h"
#include "assemblycode.h"

const char * opcodes[] =  { "nop", "halt", "add", "addi",
                            "sub", "subi", "mult", "divi", "mod",
                            "and", "or", "not", "xor",
                            "slt", "sgt", "sle", "sge",
                            "shl", "shr", "move", "ret", "ldi",
                            "beq", "bne", "jmp", "jal", "in",
                            "out", "str", "load", "jr", 
                            "HDtoMI", "readSO", "readPROC","writeSO", 
                            "writePROC", "armazenandoPC"};

const char * opcodeBins[] =  {  "001100", "001001", "000000", "110000",
                                "010010", "111101", "001011", "001000", "001010",
                                "000001", "001101", "110110", "010011",
                                "010000", "001111", "010101", "010100",
                                "110111", "111000", "110100", "100101", "100011",
                                "000010", "000111", "100110", "100001", "100000",
                                "100100", "111110", "110010", "100010", 
                                "111111", "111111", "111111", "111111",
                                "111111", "111111"}; 

const char * regBins[] = {  "000000", "000001", "000010", "000011", "000100", "000101", "000110", "000111", "001000", "001001", "001010", "001011", "001100", "001101", "001110",
                            "001111", "010000", "010001", "010010", "010011", "010100", "010101", "010110", "010111", "011000", "011001", "011010", "011011", "011100", "011101",
                            "011110", "011111", "100000", "100001", "100010", "100011", "100100", "100101", "100110", "100111", "101000", "101001", "101010", "101011", "101100",
                            "101101", "101110", "101111", "110000", "110001", "110010", "110011", "110100", "110101", "110110", "110111", "111000", "111001", "111010", "111011",
                            "111100", "111101", "111110", "111111" };


char * getImediate (int im, int size) {
    int i = 0;
    char * bin = (char *) malloc(size + 2);
    size --;
    for (unsigned bit = 1u << size; bit != 0; bit >>= 1) {
        bin[i++] = (im & bit) ? '1' : '0';
    }
    bin[i] = '\0';
    return bin;
}

char * assembly2binary (Instruction i) {
    char * bin = (char *) malloc((32 + 4 + 2) * sizeof(char));
    //formato 1
      if (i.format == format1) {
          //MIPS rs rt rd <- rd rs rt ASSEMBLY
        sprintf(bin, "%s%s%s%s%s", opcodeBins[i.opcode], regBins[i.reg1], regBins[i.reg2], regBins[i.reg3], "00000000");
    }
    //formato 2
    else if (i.format == format2) {
        if(i.opcode == move)
             sprintf(bin, "%s%s%s%s", opcodeBins[i.opcode], regBins[i.reg1], regBins[i.reg2], "00000000000000");
        else if(i.opcode == str || i.opcode == load || i.opcode == addi)
            sprintf(bin, "%s%s%s%s", opcodeBins[i.opcode], regBins[i.reg1], regBins[i.reg2], getImediate(i.im, 14));
        else
            sprintf(bin, "%s%s%s%s", opcodeBins[i.opcode], regBins[i.reg1], regBins[i.reg2], getImediate(i.im, 14));
    }
    //formato 3
    else if (i.format == format3) {
        if(i.opcode == ldi  || i.opcode == armazenandoPC ) 
            sprintf(bin, "%s%s%s", opcodeBins[i.opcode], regBins[i.reg1], getImediate(i.im, 20));
        else if(i.opcode == in)
            sprintf(bin, "%s%s%s", opcodeBins[i.opcode], regBins[i.reg1], "00000000000000000000");
        else
         sprintf(bin, "%s%s%s", opcodeBins[i.opcode], regBins[i.reg1], getImediate(i.im, 20));
    }
    else {
        sprintf(bin, "%s%s", opcodeBins[i.opcode], getImediate(i.im, 26));
    }
    return bin;
}

void GenBinary (AssemblyCode head, int size) {
    AssemblyCode a = head;
    char * bin;
    while (a != NULL) {
        if (a->kind == instr) {
            // fprintf(c, "\tassign Memoria[%d]\t=\t32'b", a->lineno);
            //fprintf(bcode,"Memory[%d] = 32'b", a->lineno);
            bin = assembly2binary(a->line.instruction);
            // fprintf(c, "%s\n", bin);
            fprintf(bcode,"%s //%s\n", bin, opcodes[a->line.instruction.opcode]);
        }
        /*
        else {
            fprintf(bcode,"//%s\n", a->line.label);
        }
        */
        a = a->next;
    }

}