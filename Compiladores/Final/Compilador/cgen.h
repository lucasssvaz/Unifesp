/*******************************************************/
/* File: cgen.h                                        */
/* The code generator interface to the CMINUS compiler */
/*******************************************************/

#ifndef _CGEN_H_
#define _CGEN_H_

#define nlabel_size 3
#define ntemp_size 3

typedef enum {  opADD, opSUB, opMULT, opDIV, opLT, opLET, opGT, opGET, opAND, opOR, opASSIGN, opALLOC, opIMMED, opLOAD, opSTORE, opVEC, opGOTO, opIFF, opRET, opFUN, opEND, opPARAM, opCALL, opARG, opLAB, opHLT, opPARAMLIST, opCHILD, opSIBLING } OpKind;
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

QuadList codeGen(TreeNode * syntaxTree, char * codefile);

#endif
