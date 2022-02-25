// In memory of Le4ndrones

#include "globals.h"
#include "symtab.h"
#include "assemblycode.h"
#include "intercode.h"
#include <math.h>

const char *operatorNameInstruction[] = {"nop", "halt", "add", "addi", "bgt", "sub", "subi", "mul", "divi", "mod", "and", "or", "not", "xor", "muli",
                                        "slt", "sgt", "sle", "sge", "blt", "shl", "shr", "move", "ret", "li", "beq", "bne", "j", "jal", "in", "out", 
                                        "sw", "lw", "jr", "ctx"};

const char *regNames[] = {"$zero", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8",
                          "$t9", "$t10", "$t11", "$t12", "$t13", "$t14", "$t15", "$t16", "$t17", "$t18",
                          "$t19", "$t20", "$t21", "$t22", "$t23", "$t24", "$t25", "$t26", "$t27", "$t28",
                          "$t29", "$t30", "$t31", "$t32", "$t33", "$t34", "$t35", "$t36", "$t37", "$t38",
                          "$t39", "$r0", "$r1", "$r2", "$r3", "$r4", "$r5", "$r6", "$r7", "$r8",
                          "$r9", "$sp", "$gp", "$jmp", "$ra", "$ret", "$br", "$ctx", "$k7", "$k8",
                          "$k9", "$ax1", "$ax2", "$crt"};

AssemblyCode codehead = NULL;
FunList funlisthead = NULL;

int line;
int nscopes = 0;
int curmemloc = 0;
int curparam = 0;
int curarg = 0;
int narg = 0;
int jmpmain = 0;

void insertFun(char *id)
{
    FunList new = (FunList)malloc(sizeof(struct FunListRec));
    new->id = (char *)malloc(strlen(id) * sizeof(char));
    strcpy(new->id, id);
    new->size = 0;
    new->memloc = curmemloc;
    new->next = NULL;
    if (funlisthead == NULL)
    {
        funlisthead = new;
    }
    else
    {
        FunList f = funlisthead;
        while (f->next != NULL)
            f = f->next;
        f->next = new;
    }
    nscopes++;
}

void insertVar(char *scope, char *id, int size, VarKind kind)
{
    //  printf("entrou no insert var: scope:%s \n",scope);
    FunList f = funlisthead;

    while (f != NULL && strcmp(f->id, scope) != 0)
        f = f->next;

    if (f == NULL)
    {
        //  printf("f igual a null \n");
        insertFun(scope);
        f = funlisthead;
        while (f != NULL && strcmp(f->id, scope) != 0)
            f = f->next;
    }
    VarList new = (VarList)malloc(sizeof(struct VarListRec));
    new->id = (char *)malloc(strlen(id) * sizeof(char));
    strcpy(new->id, id);
    new->size = size;
    new->memloc = f->size;
    curmemloc = curmemloc + size;
    new->kind = kind;
    new->next = NULL;
    if (f->vars == NULL)
    {
        f->vars = new;
    }
    else
    {
        //  printf("entrou no else \n");
        VarList v = f->vars;
        while (v->next != NULL)
            v = v->next;
        v->next = new;
    }

    f->size = f->size + size;
    // printf("f->Size:%d \n",f->size);
    // printf("saiu \n");
}

void insertLabel(char *label)
{
    AssemblyCode new = (AssemblyCode)malloc(sizeof(struct AssemblyCodeRec));
    new->lineno = line;
    new->kind = lbl;
    new->line.label = (char *)malloc(strlen(label) * sizeof(char));
    strcpy(new->line.label, label);
    new->next = NULL;
    if (codehead == NULL)
    {
        codehead = new;
    }
    else
    {
        AssemblyCode a = codehead;
        while (a->next != NULL)
            a = a->next;
        a->next = new;
    }
}

void insertInstruction(InstrFormat format, InstrKind opcode, Reg reg1, Reg reg2, Reg reg3, int im, char *imlbl)
{
    Instruction i;
    i.format = format;
    i.opcode = opcode;
    i.reg1 = reg1;
    i.reg2 = reg2;
    i.reg3 = reg3;
    i.im = im;
    i.imlbl = NULL;
    if (imlbl != NULL)
    {
        i.imlbl = (char *)malloc(strlen(imlbl) * sizeof(char));
        strcpy(i.imlbl, imlbl);
    }
    AssemblyCode new = (AssemblyCode)malloc(sizeof(struct AssemblyCodeRec));
    new->lineno = line;
    new->kind = instr;
    new->line.instruction = i;
    new->next = NULL;
    if (codehead == NULL)
    {
        codehead = new;
    }
    else
    {
        AssemblyCode a = codehead;
        while (a->next != NULL)
            a = a->next;
        a->next = new;
    }
    line++;
}

void instructionFormat1(InstrKind opcode, Reg reg1, Reg reg2, Reg reg3)
{
    insertInstruction(format1, opcode, reg1, reg2, reg3, 0, NULL);
}

void instructionFormat2(InstrKind opcode, Reg reg1, Reg reg2, int im, char *imlbl)
{
    insertInstruction(format2, opcode, reg1, reg2, $zero, im, imlbl);
}

void instructionFormat3(InstrKind opcode, Reg reg1, int im, char *imlbl)
{
    insertInstruction(format3, opcode, reg1, $zero, $zero, im, imlbl);
}

void instructionFormat4(InstrKind opcode, int im, char *imlbl)
{
    insertInstruction(format4, opcode, $zero, $zero, $zero, im, imlbl);
}

Reg getParamReg()
{
    return (Reg)1 + nregtemp + curparam;
}

Reg getArgReg()
{
    return (Reg)1 + nregtemp + curarg;
}

Reg getReg(char *regName)
{
    for (int i = 0; i < nregisters; i++)
    {
        if (strcmp(regName, regNames[i]) == 0)
            return (Reg)i;
    }
    return $zero;
}

int getLabelLine(char *label)
{
    AssemblyCode a = codehead;
    while (a->next != NULL)
    {
        if (a->kind == lbl && strcmp(a->line.label, label) == 0)
            return a->lineno;
        a = a->next;
    }
    return -1;
}

VarKind checkType(QuadList l)
{
    QuadList aux = l;
    Quad q = aux->quad;
    aux = aux->next;
    while (aux != NULL && aux->quad.op != opEND)
    {
        if (aux->quad.op == opVEC && strcmp(aux->quad.addr2.contents.var.name, q.addr1.contents.var.name) == 0)
            return address;
        aux = aux->next;
    }
    return simple;
}

int getVarMemLoc(char *id, char *scope)
{

    FunList f = funlisthead;
    while (f != NULL && strcmp(f->id, scope) != 0)
        f = f->next;
    if (f == NULL)
        return -1;
    VarList v = f->vars;

    while (v != NULL)
    {

        if (strcmp(v->id, id) == 0)
            return v->memloc;
        v = v->next;
    }
    return -1;
}

VarKind getVarKind(char *id, char *scope)
{
    FunList f = funlisthead;
    while (f != NULL && strcmp(f->id, scope) != 0)
        f = f->next;
    if (f == NULL)
    {
        return simple;
    }
    VarList v = f->vars;
    while (v != NULL)
    {
        if (strcmp(v->id, id) == 0)
            return v->kind;
        v = v->next;
    }
    return simple;
}

int getFunSize(char *id)
{
    FunList f = funlisthead;
    while (f != NULL && strcmp(f->id, id) != 0)
        f = f->next;
    if (f == NULL)
        return -1;
    return f->size;
}

void initCode(QuadList head)
{
    QuadList l = head;
    Quad q;

    instructionFormat3(li, $ctx, progloc, NULL);
    instructionFormat3(li, $sp, sploc + nmem * progloc, NULL);
    instructionFormat3(li, $gp, gploc + nmem * progloc, NULL);
    instructionFormat3(li, $ra, raloc + nmem * progloc, NULL);
    insertFun("Global");
}

void generateInstruction(QuadList l)
{
    Quad q;
    Address a1, a2, a3;
    int aux;
    VarKind v;

    while (l != NULL)
    {

        q = l->quad;
        a1 = q.addr1;
        a2 = q.addr2;
        a3 = q.addr3;
        switch (q.op)
        {

        case opADD:
            instructionFormat1(add, getReg(a1.contents.var.name), getReg(a2.contents.var.name), getReg(a3.contents.var.name));
            break;

        case opSUB:
            instructionFormat1(sub, getReg(a1.contents.var.name), getReg(a2.contents.var.name), getReg(a3.contents.var.name));
            break;

        case opMULT:
            instructionFormat1(mul, getReg(a1.contents.var.name), getReg(a2.contents.var.name), getReg(a3.contents.var.name));
            break;

        case opDIV:
            instructionFormat1(divi, getReg(a1.contents.var.name), getReg(a2.contents.var.name), getReg(a3.contents.var.name));
            break;

        case opLT:
            instructionFormat1(slt, getReg(a1.contents.var.name), getReg(a2.contents.var.name), getReg(a3.contents.var.name));
            break;

        case opLTE:
            instructionFormat1(sle, getReg(a1.contents.var.name), getReg(a2.contents.var.name), getReg(a3.contents.var.name));
            break;

        case opGT:
            instructionFormat1(sgt, getReg(a1.contents.var.name), getReg(a2.contents.var.name), getReg(a3.contents.var.name));
            break;

        case opGTE:
            instructionFormat1(sge, getReg(a1.contents.var.name), getReg(a2.contents.var.name), getReg(a3.contents.var.name));
            break;

        case opAND:
            //printf("entrou no and \n");
            instructionFormat1(and, getReg(a1.contents.var.name), getReg(a2.contents.var.name), getReg(a3.contents.var.name));
            break;

        case opOR:
            // printf("entrou no or \n");
            instructionFormat1(or, getReg(a1.contents.var.name), getReg(a2.contents.var.name), getReg(a3.contents.var.name));
            break;

        case opASSIGN:
            //printf("entrou no op assign \n");
            instructionFormat2(move, getReg(a1.contents.var.name), getReg(a2.contents.var.name), 0, NULL);
            break;

        case opALLOC:
            //   printf("entrou no alloc, a2:%d \n",a2.contents.val);
            if (a2.contents.val == 1)
                //    printf("entrou no alloc:%s \n",a3.contents.var.name);
                insertVar(a3.contents.var.name, a1.contents.var.name, a2.contents.val, simple);
            else
                insertVar(a3.contents.var.name, a1.contents.var.name, a2.contents.val, vector);
            //  printf("saiu do alloc \n");
            break;

        case opIMMED:
            // printf("entrou no imed \n");
            instructionFormat3(li, getReg(a1.contents.var.name), a2.contents.val, NULL);

            break;

        case opLOAD:

            //printf("a2.contents.var.scope: %s \n", a2.contents.var.scope);
            aux = getVarMemLoc(a2.contents.var.name, a2.contents.var.scope);
            // printf("%d \n", aux);
            if (aux == -1)
            {
                v = getVarKind(a2.contents.var.name, "Global");
                aux = getVarMemLoc(a2.contents.var.name, "Global");
                if (v == vector)
                {
                    instructionFormat2(addi, getReg(a1.contents.var.name), $gp, aux, NULL); //guarda a posição da memória onde está a posição do vetor + gp
                }
                else
                {
                    instructionFormat2(lw, getReg(a1.contents.var.name), $gp, aux, NULL);
                }
            }
            else
            {
                v = getVarKind(a2.contents.var.name, a2.contents.var.scope);
                if (v == vector)
                {
                    instructionFormat2(addi, getReg(a1.contents.var.name), $sp, aux, NULL);
                }
                else
                {
                    instructionFormat2(lw, getReg(a1.contents.var.name), $sp, aux, NULL);
                }
            }
            break;

        case opSTORE:
            aux = getVarMemLoc(a1.contents.var.name, a1.contents.var.scope);
            if (aux == -1)
            {
                aux = getVarMemLoc(a1.contents.var.name, "Global");
                if (a2.kind == String)
                    instructionFormat2(sw, getReg(a3.contents.var.name), getReg(a2.contents.var.name), aux, NULL);
                else
                    instructionFormat2(sw, getReg(a3.contents.var.name), $gp, aux, NULL);
            }
            else
            {
                if (a2.kind == String)
                    instructionFormat2(sw, getReg(a3.contents.var.name), getReg(a2.contents.var.name), aux, NULL);
                else
                    instructionFormat2(sw, getReg(a3.contents.var.name), $sp, aux, NULL);
            }
            break;

        case opVEC:
            v = getVarKind(a2.contents.var.name, a2.contents.var.scope); //a2.contents.var.scope;
            if (v == simple)
                v = getVarKind(a2.contents.var.name, "Global");
            aux = getVarMemLoc(a2.contents.var.name, a2.contents.var.scope); // a2.contents.var.scope);
            if (v == vector)
            {
                if (aux == -1)
                {
                    aux = getVarMemLoc(a2.contents.var.name, "Global");
                    instructionFormat1(add, getReg(a3.contents.var.name), getReg(a3.contents.var.name), $gp);
                }
                else
                {
                    instructionFormat1(add, getReg(a3.contents.var.name), getReg(a3.contents.var.name), $sp);
                }
                instructionFormat2(lw, getReg(a1.contents.var.name), getReg(a3.contents.var.name), aux, NULL);
            }
            else
            {
                instructionFormat2(lw, getReg(a1.contents.var.name), $sp, aux, NULL);
                instructionFormat1(add, getReg(a3.contents.var.name), getReg(a3.contents.var.name), getReg(a1.contents.var.name));
                instructionFormat2(lw, getReg(a1.contents.var.name), getReg(a3.contents.var.name), 0, NULL);
            }
            //   printf("saiu do vec \n");
            break;

        case opGOTO:
            //printf("entrou no goto \n");
            instructionFormat4(j, -1, a1.contents.var.name);
            break;

        case opIF:
            //  printf("entrou no iffalse \n");
            instructionFormat3(li, $br, -1, a2.contents.var.name);
            instructionFormat1(beq, $br, getReg(a1.contents.var.name), $zero);
            break;

        case opRET:
            //  printf("entrou no return \n");
            if (a1.kind == String)
                instructionFormat2(move, $ret, getReg(a1.contents.var.name), 0, NULL);
            instructionFormat2(addi, $ra, $ra, -1, NULL);
            instructionFormat2(lw, $jmp, $ra, 0, NULL);
            instructionFormat3(jr, $jmp, 0, NULL);
            //instructionFormat4(ret, 0, NULL);
            break;

        case opFUN:
            if (jmpmain == 0)
            {
                instructionFormat4(j, -1, "main");
                jmpmain = 1;
            }
            insertLabel(a1.contents.var.name);
            insertFun(a1.contents.var.name);
            curarg = 0;
            break;

        case opEND:
            if (strcmp(a1.contents.var.name, "main") == 0)
            {
                instructionFormat4(j, -1, "end");
            }
            else
            {
                instructionFormat2(addi, $ra, $ra, -1, NULL);
                instructionFormat2(lw, $jmp, $ra, 0, NULL);
                instructionFormat3(jr, $jmp, 0, NULL);
                //instructionFormat4(ret, 0, NULL);
            }
            break;

        case opPARAM:
            instructionFormat2(move, getParamReg(), getReg(a1.contents.var.name), 0, NULL);
            curparam++;
            break;

        case opCALL: //funciona junto com o ret

            if (strcmp(a2.contents.var.name, "execProc") == 0)
            {
                instructionFormat2(move, $ax2, getParamReg() - 1, 0, NULL);

                for (int i = 1; i < 61; ++i)
                    instructionFormat2(sw, i, $zero, i, NULL);

                instructionFormat3(li, $ax1, nmem, NULL);
                instructionFormat1(mul, $ax1, $ax2, $ax1);
                for (int i = 1; i < 61; ++i)
                    instructionFormat2(lw, i, $ax1, i, NULL);

                instructionFormat3(ctx, $ax2, 0, NULL);
                instructionFormat2(move, getReg(a1.contents.var.name), $crt, 0, NULL);
            }
            else if (strcmp(a2.contents.var.name, "input") == 0)
            {
                instructionFormat3(in, getReg(a1.contents.var.name), 0, NULL);
            }
            else if (strcmp(a2.contents.var.name, "yield") == 0)
            {
                instructionFormat3(li, $ax1, nmem, NULL);
                instructionFormat1(mul, $ax1, $ctx, $ax1);
                for (int i = 1; i < 61; ++i)
                    instructionFormat2(sw, i, $ax1, i, NULL);
                
                instructionFormat3(li, $ax1, $zero, NULL);
                for (int i = 1; i < 61; ++i)
                    instructionFormat2(lw, i, $ax1, i, NULL);

                instructionFormat3(li, $crt, 0, NULL);
                instructionFormat3(ctx, $zero, 0, NULL);
            }
            else if (strcmp(a2.contents.var.name, "output") == 0)
            {
                instructionFormat3(out, getParamReg()-1, 0, NULL);
                instructionFormat4(nop, 0, NULL);
            }
            else if (strcmp(a2.contents.var.name, "sleep") == 0)
            {
                instructionFormat3(li, $ax2, cycles_1s, NULL);
                instructionFormat1(mul, $ax1, getParamReg() - 1, $ax2);
                instructionFormat3(li, $br, line + 2, NULL);
                instructionFormat3(li, $ax2, 6, NULL);
                instructionFormat2(addi, $ax2, $ax2, 2, NULL);
                instructionFormat1(blt, $br, $ax2, $ax1);
            }
            else
            {
                aux = getFunSize(a1.contents.var.scope);
                instructionFormat2(addi, $sp, $sp, aux, NULL);
                instructionFormat3(li, $jmp, line + 4, NULL); //jump 4 instructions
                instructionFormat2(sw, $jmp, $ra, 0, NULL);
                instructionFormat2(addi, $ra, $ra, 1, NULL); //changing scope
                instructionFormat4(j, -1, a2.contents.var.name); 
                instructionFormat2(move, getReg(a1.contents.var.name), $ret, 0, NULL); //ret receives the operator result
                instructionFormat2(addi, $sp, $sp, -aux, NULL); //remove from the heap
            }
            narg = a3.contents.val;
            curparam = 0;
            break;

        case opARG:
            //printf("entrou no opARG \n");
            insertVar(a3.contents.var.name, a1.contents.var.name, 1, checkType(l));
            //printf("saiu do insertvar \n");
            instructionFormat2(sw, getArgReg(), $sp, getVarMemLoc(a1.contents.var.name, a3.contents.var.name), NULL);
            curarg++;
            break;

        case opLAB:
            //printf("entrou no label \n");
            insertLabel(a1.contents.var.name);
            break;

        case opHLT:     // halt alterado
            insertLabel("end");

            if (progloc > 0)
            {
                for (int i = 1; i < 61; ++i)
                    instructionFormat2(lw, i, $zero, i, NULL);

                instructionFormat3(li, $crt, 1, NULL);
                instructionFormat3(ctx, $zero, 0, NULL);
            }    
            else
            {
                instructionFormat4(halt, 0, NULL);
            }

            break;

        default:
            instructionFormat4(nop, 0, NULL);
            break;
        }
        //  printf("vai pro proximo \n");
        l = l->next;
    }
}

void generateInstructions(QuadList head)
{
    generateInstruction(head);
    AssemblyCode a = codehead;
    while (a != NULL)
    {
        if (a->kind == instr)
        {
            if (a->line.instruction.opcode == j || a->line.instruction.opcode == li || a->line.instruction.opcode == jal)
                if (a->line.instruction.imlbl != NULL)
                    a->line.instruction.im = getLabelLine(a->line.instruction.imlbl);
        }
        a = a->next;
    }
}

void printAssembly()
{
    AssemblyCode a = codehead;
    printf("\nC- Assembly Code\n");
    while (a != NULL)
    {
        if (a->kind == instr)
        {
            if (a->line.instruction.format == format1)
            {
                fprintf(acode,"%d:\t%s %s, %s, %s\n", a->lineno, operatorNameInstruction[a->line.instruction.opcode], regNames[a->line.instruction.reg1],
                       regNames[a->line.instruction.reg2], regNames[a->line.instruction.reg3]);
            }
            else if (a->line.instruction.format == format2)
            {
                if (a->line.instruction.opcode == move)
                    fprintf(acode,"%d:\t%s %s, %s\n", a->lineno, operatorNameInstruction[a->line.instruction.opcode], regNames[a->line.instruction.reg1],
                           regNames[a->line.instruction.reg2]);
                else
                    fprintf(acode,"%d:\t%s %s, %s, %d\n", a->lineno, operatorNameInstruction[a->line.instruction.opcode], regNames[a->line.instruction.reg1],
                           regNames[a->line.instruction.reg2], a->line.instruction.im);
            }
            else if (a->line.instruction.format == format3)
            {
                if (a->line.instruction.opcode == jr || a->line.instruction.opcode == in || a->line.instruction.opcode == out || a->line.instruction.opcode == ctx)
                    fprintf(acode,"%d:\t%s %s\n", a->lineno, operatorNameInstruction[a->line.instruction.opcode], regNames[a->line.instruction.reg1]);
                else
                    fprintf(acode,"%d:\t%s %s, %d\n", a->lineno, operatorNameInstruction[a->line.instruction.opcode], regNames[a->line.instruction.reg1],
                           a->line.instruction.im);
            }
            else
            {
                if (a->line.instruction.opcode == halt || a->line.instruction.opcode == nop || a->line.instruction.opcode == ret)
                    fprintf(acode,"%d:\t%s\n", a->lineno, operatorNameInstruction[a->line.instruction.opcode]);
                else
                    fprintf(acode,"%d:\t%s %d\n", a->lineno, operatorNameInstruction[a->line.instruction.opcode], a->line.instruction.im);
            }
        }
        else
        {
            fprintf(acode,".%s\n", a->line.label);
        }
        a = a->next;
    }
}

AssemblyCode GenAssembly(QuadList head)
{
    line = ninst * progloc;
    initCode(head);
    generateInstructions(head);
    printAssembly();
    return codehead;
}

int getSize()
{
    return line - 1;
}