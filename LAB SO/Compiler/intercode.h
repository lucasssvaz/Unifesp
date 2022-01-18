#include "globals.h"
#include "symtab.h"
#include "util.h"

#ifndef _INTERCODE_H_
#define _INTERCODE_H_

#define nlabel_size 3
#define ntemp_size 3

typedef enum {  opADD, opSUB, opMULT, opDIV, opLT, opLTE, opGT, opGTE, opAND, opOR, opASSIGN, opALLOC, opIMMED, opLOAD, opSTORE, opVEC, opGOTO, opIF, opRET, opFUN, opEND, opPARAM, opCALL, opARG, opLAB, opHLT} OpKind;

typedef enum {  Empty, IntConst, String } AddrKind;

typedef struct {
  AddrKind kind;
  union {
    int val;
    struct {
      char * name;
      char * scope;
    } var;
  } contents;
} Address;

typedef struct {
  OpKind op;
  Address addr1, addr2, addr3;
} Quad;

typedef struct QuadListRec {
  int location;
  Quad quad;
  struct QuadListRec * next;
} * QuadList;

QuadList GenInterCode(TreeNode *syntaxTree);

#endif
