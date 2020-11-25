/****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the CMINUS compiler                          */
/****************************************************/

#include "globals.h"
#include "cgen.h"
#include "target.h"
#include <fcntl.h>

QuadList head = NULL;

int location = 0;
int mainLocation;
int param = 0;
int cont = 0;
Address adrcall[100];
int call = 0;
int childsibling = 0;

int nlabel = 0;
int ntemp = 1;

Address aux;
Address var;
Address offset;
Address empty;

const char *operatorName[] = {"addition", "subtraction", "multiplication", "division", "lt", "lte", "gt", "gte", "equal", "or", "assign", "alloc", "immed", "load", "store", "vector", "goto", "if_f", "return", "function", "end", "param", "call", "arg", "label", "halt", "paramlist", "child", "sibling"};

char *newLabel()
{
  char *label = (char *)malloc((nlabel_size + 3) * sizeof(char));
  sprintf(label, "L%d", nlabel);
  nlabel++;
  return label;
}

char *newTemp()
{
  char *temp = (char *)malloc((ntemp_size + 3) * sizeof(char));
  sprintf(temp, "$t%d", ntemp);
  ntemp = (ntemp + 1) % 64;
  if (ntemp == 0) ntemp++;
  cont++;
  return temp;
}

Address addr_createEmpty()
{
  Address addr;
  addr.kind = Empty;
  addr.contents.var.name = NULL;
  addr.contents.var.scope = NULL;
  return addr;
}

Address addr_createIntConst(int val)
{
  Address addr;
  addr.kind = IntConst;
  addr.contents.val = val;
  return addr;
}

Address addr_createString(char *name, char *scope)
{
  Address addr;
  addr.kind = String;
  addr.contents.var.name = (char *)malloc(strlen(name) * sizeof(char));
  strcpy(addr.contents.var.name, name);
  addr.contents.var.scope = (char *)malloc(strlen(scope) * sizeof(char));
  strcpy(addr.contents.var.scope, scope);
  return addr;
}

void quad_insert(OpKind op, Address addr1, Address addr2, Address addr3)
{
  Quad quad;
  quad.op = op;
  quad.addr1 = addr1;
  quad.addr2 = addr2;
  quad.addr3 = addr3;
  QuadList new = (QuadList)malloc(sizeof(struct QuadListRec));
  new->location = location;
  new->quad = quad;
  new->next = NULL;
  if (head == NULL)
  {
    head = new;
  }
  else
  {
    QuadList q = head;
    while (q->next != NULL)
      q = q->next;
    q->next = new;
  }
  location++;
}

int quad_update(int loc, Address addr1, Address addr2, Address addr3)
{
  QuadList q = head;
  while (q != NULL)
  {
    if (q->location == loc)
      break;
    q = q->next;
  }
  if (q == NULL)
    return 0;
  else
  {
    q->quad.addr1 = addr1;
    q->quad.addr2 = addr2;
    q->quad.addr3 = addr3;
    return 1;
  }
}

static void insertNode(TreeNode *t)
{
  TreeNode *p1, *p2, *p3, *paux;
  Address addr1, addr2, addr3, auxcall;
  Address aux1, aux2;
  int loc1, loc2, loc3, i;
  char *label;
  char *temp;
  char *s = "";

  while (t != NULL)
  {
    /*if (childsibling == 1)
      quad_insert(opCHILD, empty, empty, empty);
    if (childsibling == 0)
      quad_insert(opSIBLING, empty, empty, empty);
    if (childsibling == 2)
      quad_insert(opCHILD, empty, empty, aux);
    if (childsibling == 3)
      quad_insert(opSIBLING, empty, empty, aux);*/
    if (t->flag == 0)
    {
      t->flag = 1;
      switch (t->nodekind)
      {
      case StmtK:
        switch (t->kind.stmt)
        {
        case IfK:
          p1 = t->child[0];
          p2 = t->child[1];
          p3 = t->child[2];
          insertNode(p1);
          addr1 = aux;
          loc1 = location;
          quad_insert(opIFF, addr1, empty, empty);
          insertNode(p2);
          loc2 = location;
          quad_insert(opGOTO, empty, empty, empty);
          label = newLabel();
          quad_insert(opLAB, addr_createString(label, t->attr.scope), empty, empty);
          quad_update(loc1, addr1, addr_createString(label, t->attr.scope), empty);
          insertNode(p3);
          if (p3 != NULL)
          {
            loc3 = location;
            quad_insert(opGOTO, empty, empty, empty);
          }
          label = newLabel();
          quad_insert(opLAB, addr_createString(label, t->attr.scope), empty, empty);
          quad_update(loc2, addr_createString(label, t->attr.scope), empty, empty);
          if (p3 != NULL)
            quad_update(loc3, addr_createString(label, t->attr.scope), empty, empty);
          break;

        case WhileK:
          p1 = t->child[0];
          p2 = t->child[1];
          label = newLabel();
          quad_insert(opLAB, addr_createString(label, t->attr.scope), empty, empty);
          insertNode(p1);
          addr1 = aux;
          loc1 = location;
          quad_insert(opIFF, addr1, empty, empty);
          insertNode(p2);
          loc3 = location;
          quad_insert(opGOTO, addr_createString(label, t->attr.scope), empty, empty);
          label = newLabel();
          quad_insert(opLAB, addr_createString(label, t->attr.scope), empty, empty);
          quad_update(loc1, addr1, addr_createString(label, t->attr.scope), empty);
          break;

        case AssignK:
          p1 = t->child[0];
          p2 = t->child[1];
          insertNode(p1);
          addr1 = aux;
          aux1 = var;
          aux2 = offset;
          insertNode(p2);
          addr2 = aux;
          quad_insert(opASSIGN, addr1, addr2, empty);
          quad_insert(opSTORE, aux1, aux2, addr1);
          break;

        case VariableK:
          quad_insert(opALLOC, addr_createString(t->attr.name, t->attr.scope), addr_createIntConst(1), addr_createString(t->attr.scope, t->attr.scope));
          break;

        case FunctionK:
          if (strcmp(t->attr.name, "main") == 0)
            mainLocation = location;
          if ((strcmp(t->attr.name, "input") != 0) && (strcmp(t->attr.name, "output") != 0))
          {
            quad_insert(opFUN, addr_createString(t->attr.name, t->attr.scope), empty, empty);
            p1 = t->child[0];
            p2 = t->child[1];
            insertNode(p1);
            insertNode(p2);
            quad_insert(opEND, addr_createString(t->attr.name, t->attr.scope), empty, empty);
          }
          break;

        case CallK:
          p1 = t->child[0];
          paux = p1;
          int cont1 = 0;
          call = 1;
          while(paux != NULL){
            paux = paux->sibling;
            cont1++;
          }
          auxcall = addr_createIntConst(cont1);
          quad_insert(opPARAMLIST, auxcall, empty, empty);
          while (p1 != NULL)
          {
            //auxcall = addr_createIntConst(cont1);
            //quad_insert(opPARAM, empty, empty, auxcall);
            childsibling=2;
            //quad_insert(opPARAM, aux, empty, empty);
            //paux = p1;
            insertNode(p1);
            quad_insert(opPARAM, aux, empty, empty);
            childsibling=3;
            p1 = p1->sibling;
            //cont1++;
          }
          call = 0;
          /*while(cont1>0){
          //auxcall=addr_createIntConst(cont1);
          quad_insert(opPARAM, adrcall[cont - cont1], empty, empty);
          cont1--;
        }*/
          temp = newTemp();
          aux = addr_createString(temp, t->attr.scope);
          quad_insert(opCALL, addr_createString(t->attr.name, t->attr.scope), auxcall, aux);
          break;

        case ReturnK:
          p1 = t->child[0];
          insertNode(p1);
          if (p1 != NULL)
            addr1 = aux;
          else
            addr1 = empty;
          quad_insert(opRET, addr1, empty, empty);
          break;

        default:
          break;
        }
        break;

      case ExpK:
        switch (t->kind.exp)
        {
        case OpK:
          p1 = t->child[0];
          p2 = t->child[1];
          insertNode(p1);
          addr1 = aux;
          insertNode(p2);
          addr2 = aux;
          temp = newTemp();
          aux = addr_createString(temp, t->attr.scope);
          switch (t->attr.op)
          {
          case PLUS:
            quad_insert(opADD, addr1, addr2, aux);
            break;
          case MINUS:
            quad_insert(opSUB, addr1, addr2, aux);
            break;
          case TIMES:
            quad_insert(opMULT, addr1, addr2, aux);
            break;
          case OVER:
            quad_insert(opDIV, addr1, addr2, aux);
            break;
          case LT:
            quad_insert(opLT, addr1, addr2, aux);
            break;
          case LTE:
            quad_insert(opLET, addr1, addr2, aux);
            break;
          case GT:
            quad_insert(opGT, addr1, addr2, aux);
            break;
          case GTE:
            quad_insert(opGET, addr1, addr2, aux);
            break;
          case EQ:
            quad_insert(opAND, addr1, addr2, aux);
            break;
          case NE:
            quad_insert(opGT, addr1, addr2, aux);
            addr3 = aux;
            temp = newTemp();
            aux = addr_createString(temp, t->attr.scope);
            quad_insert(opLT, addr1, addr2, aux);
            addr1 = addr3;
            addr2 = aux;
            temp = newTemp();
            aux = addr_createString(temp, t->attr.scope);
            quad_insert(opOR, addr1, addr2, aux);
            break;
          default:
            break;
          }
          break;

        case ConstK:
          addr1 = addr_createIntConst(t->attr.val);
          temp = newTemp();
          aux = addr_createString(temp, s);
          quad_insert(opIMMED, addr1, aux, empty);
          break;

        case IdK:
          aux = addr_createString(t->attr.name, t->attr.scope);
          p1 = t->child[0];
          if (p1 != NULL)
          {
            temp = newTemp();
            addr1 = addr_createString(temp, t->attr.scope);
            addr2 = aux;
            insertNode(p1);
            quad_insert(opVEC, addr1, addr2, aux);
            var = addr2;
            offset = aux;
            aux = addr1;
          }
          else
          {
            temp = newTemp();
            addr1 = addr_createString(temp, t->attr.scope);
            quad_insert(opLOAD, aux, addr1, empty);
            var = aux;
            offset = empty;
            aux = addr1;
            adrcall[cont] = aux;
            cont++;
          }
          break;

        case VectorK:
          quad_insert(opALLOC, addr_createString(t->attr.name, t->attr.scope), addr_createIntConst(t->attr.val), addr_createString(t->attr.scope, t->attr.scope));
          break;

        case TypeK:
          break;

        default:
          break;
        }
        break;
      }
    }
    for (i = 0; i < MAXCHILDREN; i++)
    {
      childsibling = 1;
      insertNode(t->child[i]);
    }
    if (call == 0)
    {
      childsibling = 0;
      t = t->sibling;
    }
    else
    {
      t = NULL;
    }
  }
}

void printCode()
{
  QuadList q = head;
  Address a1, a2, a3;
  int ind = 1;
  listing = code;
  while (q != NULL)
  {
    a1 = q->quad.addr1;
    a2 = q->quad.addr2;
    a3 = q->quad.addr3;
    fprintf(listing, "(%s, ", operatorName[q->quad.op]);
    switch (a1.kind)
    {
    case Empty:
      fprintf(listing, "_");
      break;
    case IntConst:
      fprintf(listing, "%d", a1.contents.val);
      break;
    case String:
      fprintf(listing, "%s", a1.contents.var.name);
      break;
    default:
      break;
    }
    fprintf(listing, ", ");
    switch (a2.kind)
    {
    case Empty:
      fprintf(listing, "_");
      break;
    case IntConst:
      fprintf(listing, "%d", a2.contents.val);
      break;
    case String:
      fprintf(listing, "%s", a2.contents.var.name);
      break;
    default:
      break;
    }
    fprintf(listing, ", ");
    switch (a3.kind)
    {
    case Empty:
      fprintf(listing, "_");
      break;
    case IntConst:
      fprintf(listing, "%d", a3.contents.val);
      break;
    case String:
      fprintf(listing, "%s", a3.contents.var.name);
      break;
    default:
      break;
    }
    fprintf(listing, ")\n");
    q = q->next;
    ind++;
  }
}

QuadList codeGen(TreeNode *syntaxTree, char *codefile)
{
  int k;
  char *s = malloc(strlen(codefile) + 7);
  strcpy(s, "File: ");
  strcat(s, codefile);
  fprintf(listing, "%s\n", s);
  empty = addr_createEmpty();
  for (k = 0; k < 100; k++)
    adrcall[k] = empty;
  insertNode(syntaxTree);
  quad_insert(opHLT, empty, empty, empty);
  printCode();
  listing = stdout;
  return head;
}