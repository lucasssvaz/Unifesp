#include "globals.h"
#include "symtab.h"
#include "util.h"
#include "intercode.h"
#include "analyze.h"
#include "assemblycode.h"


static int tmpOffset = 0;

static void InterCode(TreeNode *tree);

QuadList Quads = NULL;

int location = 0;
int mainLocation;

int nlabel = 0;
int ntemp = 0;
int nparams = -1;

Address aux;
Address var;
Address offset;


const char *operatorName[] = {"ADD", "SUB", "MUL", "DIV", "LT", "LTE", "GT", "GTE", "EQ", "OR", "ASSIGN", "ALLOC", "IMMED", "LOAD", "STORE", "VECTOR", "GOTO", "IF", "RET", "FUNC", "F_END", "PARAM", "CALL", "ARG", "LAB", "HALT"};

Address empty;

/*int nextFreeReg(){
    int i;
    for(i=0;i<MAXREG;i++){
        if(registers[i]==0){
            registers[i]=1;
            return i;
        }
    }

}*/

char *newLabel()
{
  char *label = (char *)malloc((nlabel_size + 3) * sizeof(char));
  sprintf(label, "L%d", nlabel);
  nlabel++;
  return label;
}

char *newRegTemp()
{
  char *temp = (char *)malloc((ntemp_size + 3) * sizeof(char));
  sprintf(temp, "$t%d", ntemp);
  ntemp = (ntemp + 1) % nregtemp;
  return temp;
}

Address CreateAddrEmpty()
{
  Address addr;
  addr.kind = Empty;
  addr.contents.var.name = NULL;
  addr.contents.var.scope = NULL;
  return addr;
}

Address CreateAddrIntConst(int val)
{
  Address addr;
  addr.kind = IntConst;
  addr.contents.val = val;
  return addr;
}

Address CreateAddrString(char *name, char *scope)
{
  Address addr;
  addr.kind = String;
  addr.contents.var.name = (char *)malloc(strlen(name) * sizeof(char));
  strcpy(addr.contents.var.name, name);
  if(scope == NULL){
    addr.contents.var.scope = (char *)malloc(strlen(name) * sizeof(char));
    strcpy(addr.contents.var.scope,name);
  }
  else{
    addr.contents.var.scope = (char *)malloc(strlen(scope) * sizeof(char));
    strcpy(addr.contents.var.scope, scope);
  }
  return addr;
}

void InsertQuad(OpKind op, Address addr1, Address addr2, Address addr3){
    Quad quad;
    quad.op = op;
    quad.addr1 = addr1;
    quad.addr2 = addr2;
    quad.addr3 = addr3;
    QuadList new = (QuadList)malloc(sizeof(struct QuadListRec));
    new->location = location;
    new->quad = quad;
    new->next = NULL;
    if (Quads == NULL){
        Quads = new;
    }
    else{
        QuadList q = Quads;
        while (q->next != NULL)
            q = q->next;
            q->next = new;
    }
    location++;
}

int UpdateQuad(int loc, Address addr1, Address addr2, Address addr3){
    QuadList q = Quads;
    while (q != NULL){
        if (q->location == loc)
            break;
        q = q->next;
    }
    if (q == NULL)
        return 0;
    else{
        q->quad.addr1 = addr1;
        q->quad.addr2 = addr2;
        q->quad.addr3 = addr3;
        return 1;
    }
}

/*void ClearReg(){
    int i;
    for(i=0;i<MAXREG;i++){
        registers[i]=0;
    }
}*/

/*void Children(TreeNode * tree){
    int i;
    for (i=0;i<MAXCHILDREN;i++)
        InterCode(tree->child[i]);
}*/

static void StmtNode(TreeNode *tree)
{
  Address addr1, addr2, addr3;
  Address aux1, aux2;
  int loc1, loc2, loc3;
  char *label;
  char *temp;
  switch (tree->kind.stmt)
  {

  case ifK:

    //tree->child[0] = arg
    //tree->child[1] = if true
    //tree->child[2] = if false
    // condicao if
    InterCode(tree->child[0]);
    addr1 = aux;
    // if false
    loc1 = location;
    InsertQuad(opIF, addr1, empty, empty);
    // if true
    InterCode(tree->child[1]);
    //goes to end
    loc2 = location;
    InsertQuad(opGOTO, empty, empty, empty); //jump else
    // end if
    label = newLabel();
    InsertQuad(opLAB,CreateAddrString(label, tree->scope), empty, empty);
    // if false comes to here
    UpdateQuad(loc1, addr1,CreateAddrString(label, tree->scope), empty);
    // else
    InterCode(tree->child[2]);
    if (tree->child[2] != NULL)
    {
      // goes to the end
      loc3 = location;
      InsertQuad(opGOTO, empty, empty, empty); //sair else
    }
    label = newLabel();
    // final
    InsertQuad(opLAB,CreateAddrString(label, tree->scope), empty, empty);
    UpdateQuad(loc2,CreateAddrString(label, tree->scope), empty, empty);
    if (tree->child[2] != NULL)
      UpdateQuad(loc3,CreateAddrString(label, tree->scope), empty, empty);
    
    break;

  case whileK:
    //tree->child[0] = arg
    //tree->child[1] = body
    // inicio do while
    label = newLabel();
    InsertQuad(opLAB,CreateAddrString(label, tree->scope), empty, empty); //you only know the label in the end of stmt
    // condicao while
    InterCode(tree->child[0]); 
    addr1 = aux;
    // if condition is false
    loc1 = location;
    InsertQuad(opIF, addr1, empty, empty);
    // while
    InterCode(tree->child[1]); //body
    loc3 = location;
    InsertQuad(opGOTO,CreateAddrString(label, tree->scope), empty, empty); //return to statement till the condition is false
    // final
    label = newLabel();
    InsertQuad(opLAB,CreateAddrString(label, tree->scope), empty, empty); //here you know the label
    //if condition is false comes to here
    UpdateQuad(loc1, addr1,CreateAddrString(label, tree->scope), empty);//update quad bc you r in the end 
    break;

  case assignK:
    //tree->child[0] = arg
    //tree->child[1] = body
    // var
    InterCode(tree->child[0]);
    addr1 = aux;
    aux1 = var;
    aux2 = offset;
    // exp
    InterCode(tree->child[1]);
    addr2 = aux;
    InsertQuad(opASSIGN, addr1, addr2, empty);
    InsertQuad(opSTORE, aux1, aux2, addr1);
    break;

  case returnK:
    //tree->child[0] = ret 
    InterCode(tree->child[0]);
    // se tem retorno
    if (tree->child[0] != NULL)
      addr1 = aux;
    //se não tem retorno
    else
      addr1 = empty;
    InsertQuad(opRET, addr1, empty, empty);
    break;

  default:
    break;
  }
}

static void ExpNode(TreeNode *tree)
{
    Address addr1, addr2, addr3;
    int loc1, loc2, loc3;
    char *label;
    char *temp;
    char *s = "";
    switch (tree->kind.exp){
        case constK:
            // printf("ConstK \n");
            addr1 = CreateAddrIntConst(tree->attr.val);
            temp = newRegTemp();
            aux = CreateAddrString(temp, tree->scope);
            InsertQuad(opIMMED, aux, addr1, empty);
            break;

        case idK:
            //printf("IdK \n");
            aux = CreateAddrString(tree->attr.name, tree->scope);
            // printf("tree size: %d \n", tree->size);
            if (tree->child[0] != NULL){
            //printf("entrou no vec \n");
                temp = newRegTemp();
                addr1 = CreateAddrString(temp, tree->scope);
                addr2 = aux;
                InterCode(tree->child[0]);
                InsertQuad(opVEC, addr1, addr2, aux);
                var = addr2;
                offset = aux;
                aux = addr1;
            }
            else{
            // printf("não entrou no vec \n");
                temp = newRegTemp();
                addr1 = CreateAddrString(temp, tree->scope);
                InsertQuad(opLOAD, addr1, aux, empty);
                var = aux;
                offset = empty;
                aux = addr1;
            }
            break;

        case typeK:
            InterCode(tree->child[0]);
            break;

        case funDeclK:
            //printf("FundeclK: %s \n",tree->attr.name);
            // if main
            if (strcmp(tree->attr.name, "main") == 0)
                mainLocation = location;
            if ((strcmp(tree->attr.name, "input") != 0) && 
            (strcmp(tree->attr.name, "output") != 0) &&
            (strcmp(tree->attr.name, "HDtoMI") != 0) &&
            (strcmp(tree->attr.name, "enderecoBase") != 0) && 
            (strcmp(tree->attr.name, "storeReg") != 0) && 
            (strcmp(tree->attr.name, "loadReg") != 0) &&  
            (strcmp(tree->attr.name, "recuperaPC") != 0) && 
            (strcmp(tree->attr.name, "setandoPC") != 0) && 
            (strcmp(tree->attr.name, "inputDoContexto") != 0) && 
            (strcmp(tree->attr.name, "outputDoContexto") != 0) && 
            (strcmp(tree->attr.name, "execucaoDoProcesso") != 0) && 
            (strcmp(tree->attr.name, "pegaInterrupcao") != 0))
            {
                InsertQuad(opFUN, CreateAddrString(tree->attr.name, tree->scope), empty, empty);
                // params
                InterCode(tree->child[0]);
                // dec & expressions
                InterCode(tree->child[1]);
                InsertQuad(opEND, CreateAddrString(tree->attr.name, tree->scope), empty, empty);
            }
            break;

        case ativK:
            //printf("AtivK \n");
            //Address a1 = CreateAddrIntConst(tree->params);
            // é um parametro
            nparams = tree->params;
            while (tree->child[0] != NULL){
                InterCode(tree->child[0]);
                InsertQuad(opPARAM, aux, empty, empty);
                nparams--;
                tree->child[0] = tree->child[0]->sibling;
            }
            nparams = -1;
            temp = newRegTemp();
            aux = CreateAddrString(temp, tree->scope);
            InsertQuad(opCALL, aux, CreateAddrString(tree->attr.name, tree->scope), CreateAddrIntConst(tree->params));
            break;

        case paramK:
            //printf("ParamK \n");
            InsertQuad(opARG, CreateAddrString(tree->attr.name, tree->scope), empty, CreateAddrString(tree->scope,tree->scope));
            break;

        case varDeclK:
            //printf("VardeclK \n");
            if (tree->size != 0){
                InsertQuad(opALLOC, CreateAddrString(tree->attr.name, tree->scope), CreateAddrIntConst(tree->size), CreateAddrString(tree->scope,tree->scope));
            }
            else
                InsertQuad(opALLOC, CreateAddrString(tree->attr.name, tree->scope), CreateAddrIntConst(1), CreateAddrString(tree->scope,tree->scope));
            break;

        case opK:
            // printf("OpK: %d \n",tree->attr.op);
            InterCode(tree->child[0]);
            addr1 = aux;
            InterCode(tree->child[1]);
            addr2 = aux;
            temp = newRegTemp();
            aux = CreateAddrString(temp, tree->scope);
            switch (tree->attr.op)
            {
                case SOM:
                // printf("plus \n");
                    InsertQuad(opADD, aux, addr1, addr2);
                    break;
                case SUB:
                //printf("dif\n");
                    InsertQuad(opSUB, aux, addr1, addr2);
                    break;
                case MUL:
                //printf("mult\n");
                    InsertQuad(opMULT, aux, addr1, addr2);
                    break;
                case DIV:
                //printf("over\n");
                    InsertQuad(opDIV, aux, addr1, addr2);
                    break;
                case LT:
                //printf("lt\n");
                    InsertQuad(opLT, aux, addr1, addr2);
                    break;
                case LTE:
                //printf("leq\n");
                    InsertQuad(opLTE, aux, addr1, addr2);
                    break;
                case GT:
                //printf("gt\n");
                    InsertQuad(opGT, aux, addr1, addr2);
                    break;
                case GTE:
                //printf("greq\n");
                    InsertQuad(opGTE, aux, addr1, addr2);
                    break;
                case CMP:
                //printf("equal\n");
                    InsertQuad(opGTE, aux, addr1, addr2);
                    addr3 = aux;
                    temp = newRegTemp();
                    aux = CreateAddrString(temp, tree->scope);
                    InsertQuad(opLTE, aux, addr1, addr2);
                    addr1 = addr3;
                    addr2 = aux;
                    temp = newRegTemp();
                    aux = CreateAddrString(temp, tree->scope);
                    InsertQuad(opAND, aux, addr1, addr2);
                    break;
                case DIF:
                //printf("dif\n");
                    InsertQuad(opGT, aux, addr1, addr2);
                    addr3 = aux;
                    temp = newRegTemp();
                    aux =CreateAddrString(temp, tree->scope);
                    InsertQuad(opLT, aux, addr1, addr2);
                    addr1 = addr3;
                    addr2 = aux;
                    temp = newRegTemp();
                    aux= CreateAddrString(temp, tree->scope);
                    InsertQuad(opOR, aux, addr1, addr2);
                    break;
                default:
                    break;  
                }
            break;

        default:
            break;
  }
}

static void InterCode(TreeNode *tree)
{
    if (tree != NULL){
        switch (tree->nodekind){
            case stmtK:
                StmtNode(tree);
                break;
            case expK:
                ExpNode(tree);
                break;
             default:
                break;
        }
        if (nparams == -1){
            InterCode(tree->sibling);
        }
        else{
            if (nparams == 0){
                InterCode(tree->sibling);
            }
        }
    }
}

void printInterCode(){
    QuadList q = Quads;
    Address a1, a2, a3;
    while (q != NULL){
        a1 = q->quad.addr1;
        a2 = q->quad.addr2;
        a3 = q->quad.addr3;
        fprintf(codeinter, "(%s, ", operatorName[q->quad.op]);
        switch (a1.kind){
            case Empty:
                fprintf(codeinter, "_");
                break;
            case IntConst:
                fprintf(codeinter, "%d", a1.contents.val);
                break;
            case String:
                fprintf(codeinter, "%s", a1.contents.var.name);
                break;
            default:
                break;
        }
        fprintf(codeinter, ", ");
        switch (a2.kind){
            case Empty:
                fprintf(codeinter, "_");
                break;
            case IntConst:
                fprintf(codeinter, "%d", a2.contents.val);
                break;
            case String:
                fprintf(codeinter, "%s", a2.contents.var.name);
                break;
            default:
                break;
        }
        fprintf(codeinter, ", ");
        switch (a3.kind){
            case Empty:
                fprintf(codeinter, "_");
                break;
            case IntConst:
                fprintf(codeinter, "%d", a3.contents.val);
                break;
            case String:
                fprintf(codeinter, "%s", a3.contents.var.name);
                break;
            default:
                break;
        }
        fprintf(codeinter, ")\n");
        q = q->next;
    }
}

QuadList GenInterCode(TreeNode *syntaxTree){
    empty = CreateAddrEmpty();
    InterCode(syntaxTree);
    InsertQuad(opHLT, empty, empty, empty);
    printInterCode();
    return Quads;
}