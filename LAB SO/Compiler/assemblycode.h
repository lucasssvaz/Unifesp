#ifndef _ASSEMBLYCODE_H_
#define _ASSEMBLYCODE_H_

#include "intercode.h"

#define nregisters 64
#define nregtemp 40
#define nregparam 10

// Armazenamento dos Registradores: 0-63.
// Displays: 64-71
#define sploc 72  // tam 64
#define gploc 136 // tam 56
#define raloc 192 // tam 64

// ID DO PROGRAMA
extern int progloc; // (0: SO; 1:3 - Programas)
// POSICAO DA MEMORIA
#define nmem 256
#define ninst 512

#define cycles_div 2500
#define cycles_1s 50000000/(2*cycles_div)

typedef enum {  nop, halt, add, addi, bgt, sub, subi, mul, divi, mod, and, or, not, xor, muli, slt, sgt,
                sle, sge, blt, shl, shr, move, ret,
                li, beq, bne, j, jal, in, out, sw, lw, jr, ctx} InstrKind;
typedef enum {  format1, format2, format3, format4 } InstrFormat;
typedef enum {  instr, lbl } LineKind;
typedef enum {  simple, vector, address } VarKind;
typedef enum {$zero, $t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7, $t8,
              $t9, $t10, $t11, $t12, $t13, $t14, $t15, $t16, $t17, $t18,
              $t19, $t20, $t21, $t22, $t23, $t24, $t25, $t26, $t27, $t28,
              $t29, $t30, $t31, $t32, $t33, $t34, $t35, $t36, $t37, $t38,
              $t39, $r0, $r1, $r2, $r3, $r4, $r5, $r6, $r7, $r8,
              $r9, $sp, $gp, $jmp, $ra, $ret, $br, $ctx, $k7, $k8,
              $k9, $ax1, $ax2, $crt } Reg;

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