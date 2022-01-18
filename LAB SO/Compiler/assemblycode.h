#ifndef _ASSEMBLYCODE_H_
#define _ASSEMBLYCODE_H_

#include "intercode.h"

#define nregisters 64
#define nregtemp 40
#define nregparam 10

// Armazenamento dos Registradores: 0-31.
#define sploc 32  // tam 32 
#define gploc 160 // tam 16
#define raloc 224 // tam 16

//ID DO PROGRAMA
#define progloc 0 // (0: SO; 1:10 - Programas)
//POSICAO DA MEMORIA
#define nmem 288

typedef enum {  nop, halt, add, addi, sub, subi, mult, divi, mod, and, or, not, xor, slt, sgt,
                sle, sge, shl, shr, move, ret,
                ldi, beq, bne, jmp, jal, in, out, str, load, jr, 
                HDtoMI, readSO, readPROC, writeSO, writePROC, armazenandoPC} InstrKind;
typedef enum {  format1, format2, format3, format4 } InstrFormat;
typedef enum {  instr, lbl } LineKind;
typedef enum {  simple, vector, address } VarKind;
typedef enum {$zero, $t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7, $t8,
              $t9, $t10, $t11, $t12, $t13, $t14, $t15, $t16, $t17, $t18,
              $t19, $t20, $t21, $t22, $t23, $t24, $t25, $t26, $t27, $t28,
              $t29, $t30, $t31, $t32, $t33, $t34, $t35, $t36, $t37, $t38,
              $t39, $r0, $r1, $r2, $r3, $r4, $r5, $r6, $r7, $r8,
              $r9, $sp, $gp, $jmp, $ra, $ret, $br, $k6, $k7, $k8,
              $k9, $k10, $k11, $k12 } Reg;

typedef struct {
    InstrFormat format;
    InstrKind opcode;
    Reg reg1;
    Reg reg2;
    Reg reg3;
    int im;
    char * imlbl;
} Instruction;

typedef struct AssemblyCodeRec {
    int lineno;
    LineKind kind;
    union {
        Instruction instruction;
        char * label;
    } line;
    struct AssemblyCodeRec * next;
} * AssemblyCode;

typedef struct VarListRec {
    char * id;
    int size;
    int memloc;
    VarKind kind;
    struct VarListRec * next;
} * VarList;

typedef struct FunListRec {
    char * id;
    int size;
    int memloc;
    VarList vars;
    struct FunListRec * next;
} * FunList;


AssemblyCode GenAssembly(QuadList);


int getSize();

#endif