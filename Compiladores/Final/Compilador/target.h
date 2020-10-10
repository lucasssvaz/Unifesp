/*******************************************************/
/* File: target.h                                      */
/* The assembly code to the CMINUS compiler            */
/*******************************************************/

#ifndef _TARGET_H_
#define _TARGET_H_

#include "cgen.h"

typedef enum { o_add, o_addi, o_sub, o_mul, o_div, o_lt, o_lte, o_gt, o_gte, o_beq, o_or, o_move, o_lw, o_li, o_sw, o_jump, o_ret, o_function, o_end, o_param, o_call, o_input, o_output, o_arg, o_label, o_halt, o_param_list, o_nop} OpdKind;

typedef struct ParamListRec {
  int count;
  char* func;
  struct Params *params;
  struct ParamListRec *next;
} * ParamListCount;

typedef struct Params {
  char* name;
  char* scope;
  struct Params *next;
} * ParamsList;

typedef struct VarListRec {
  char *src;
  char *trg;
  char* scope;
  int loc;
  struct VarListRec *next;
} * VarList;

typedef struct LabelListRec {
  char *name;
  int locinit;
  int locend;
  struct LabelListRec *next;
} * LabelList;

typedef struct {
  AddrKind kind;
  union {
    int val;
    char* name;
  } value;
} Operand;

typedef struct {
  OpdKind op;
  Operand opd1, opd2, opd3;
} Inst;

typedef struct OCListRec {
  int location;
  Inst inst;
  struct OCListRec *next;
} * OCList;

void printAssembly(QuadList);

#endif