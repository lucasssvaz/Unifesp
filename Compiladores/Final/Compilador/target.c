#include "globals.h"
#include "target.h"
#include "cgen.h"
#include "math.h"
#define REG 4
#define INST 32

const char *operatorNameLabel[] = {"addition", "subtraction", "multiplication", "division", "lt", "lte", "gt", "gte", "equal", "or", "assign", "alloc", "immed", "load", "store", "vector", "goto", "if_f", "return", "function", "end", "param", "call", "arg", "label", "halt", "paramlist"};
const char *operatorNameInstruction[] = {"add", "addi", "sub", "mul", "div", "lt", "lte", "gt", "gte", "beq", "or", "move", "lw", "li", "sw", "jump", "ret", "function", "end", "param", "call", "input", "output", "arg", "label", "halt", "param_list"};
char *regMem[] = {"$v0", "$v1", "$v2", "$v3"};
char *none = "none";

char *_param;
char *function;
char *_call;

OCList ochead;
VarList varhead = NULL;
LabelList labelhead = NULL;
ParamListCount paramcounthead = NULL;

int regmem = 0;
int mem = 0;
int instline = 1;
int bne = 0;
int callsign = 0;

int getRegister(char *reg)
{
    int c = strlen(reg) - 3;
    int i = 48, v = 2, j, k = 0;
    for (j = c; j > -1; j--)
    {
        while (reg[v] != i && i < 58)
            i++;
        k = k + ((i - 48) * (pow(10, j)));
        v++;
        i = 48;
    }
    if (strchr(reg, 'v') == NULL)
        return k;
    else
        return k + 28;
}

int getRFunct(OpdKind op)
{
    switch (op)
    {
    case o_add:
        return 0;
        break;
    case o_sub:
        return 1;
        break;
    case o_mul:
        return 2;
        break;
    case o_div:
        return 3;
        break;
    case o_or:
        return 7;
        break;
    case o_lt:
        return 9;
        break;
    default:
        return 0;
        break;
    }
}

int getOpcode(OpdKind op)
{
    switch (op)
    {
    case o_add:
    case o_sub:
    case o_mul:
    case o_div:
    case o_or:
    case o_lt:
        return 1;
        break;
    case o_addi:
    case o_li:
    case o_move:
        return 2;
        break;
    case o_lw:
        return 3;
        break;
    case o_sw:
        return 4;
        break;
    case o_beq:
        return 7;
        break;
    case o_nop:
    case o_label:
    case o_param:
    case o_param_list:
        return 0;
        break;
    case o_jump:
    case o_call:
    case o_ret:
    case o_end:
        return 8;
        break;
    case o_input:
        return 9;
        break;
    case o_output:
        return 5;
        break;
    case o_halt:
        return 11;
        break;
    case o_function:
        return -2;
        break;
    default:
        return -1;
        break;
    }
}

void printBinary(int num, int c)
{
    int binary[INST];
    int n, i = 31, offset;

    while (num != 0)
    {
        n = num % 2;
        binary[i] = n;
        num = num / 2;
        i--;
    }
    i++;
    offset = INST - i;
    c = c - offset;
    while (c > 0)
    {
        fprintf(code, "0");
        c--;
    }
    while (i < 32)
    {
        fprintf(code, "%d", binary[i]);
        i++;
    }
}

void createVarTemp(char *source, char *target, char *scope, int loc)
{
    VarList var = (VarList)malloc(sizeof(struct VarListRec));
    var->src = (char *)malloc(strlen(source) * sizeof(char));
    strcpy(var->src, source);
    var->trg = (char *)malloc(strlen(target) * sizeof(char));
    strcpy(var->trg, target);
    var->scope = (char *)malloc(strlen(scope) * sizeof(char));
    strcpy(var->scope, scope);
    var->loc = loc;
    if (varhead == NULL)
    {
        varhead = var;
    }
    else
    {
        VarList v = varhead;
        while (v->next != NULL)
            v = v->next;
        v->next = var;
    }
}

VarList findVar(char *name, char *scope)
{
    VarList v = varhead;
    while ((v != NULL))
    {
        if ((strcmp(name, v->src) == 0) && (strcmp(scope, v->scope) == 0))
            return v;
        v = v->next;
    }
    return NULL;
}

VarList findVarTarget(char *name, char *scope)
{
    VarList v = varhead;
    while ((v != NULL))
    {
        if ((strcmp(name, v->trg) == 0) && (strcmp(scope, v->scope) == 0))
            return v;
        v = v->next;
    }
    return NULL;
}

VarList findVarScope(char *scope)
{
    VarList v = varhead;
    while ((v != NULL))
    {
        if (strcmp(scope, v->scope) == 0 && v->loc == -1)
            return v;
        v = v->next;
    }
    return NULL;
}

void createLabel(char *name, int locinit, int locend)
{
    LabelList label = (LabelList)malloc(sizeof(struct LabelListRec));
    label->name = (char *)malloc(strlen(name) * sizeof(char));
    strcpy(label->name, name);
    label->locinit = locinit;
    label->locend = locend;
    if (labelhead == NULL)
    {
        labelhead = label;
    }
    else
    {
        LabelList l = labelhead;
        while (l->next != NULL)
            l = l->next;
        l->next = label;
    }
}

LabelList findLabel(char *name)
{
    LabelList l = labelhead;
    while ((l != NULL))
    {
        if (strcmp(name, l->name) == 0)
            return l;
        l = l->next;
    }
    return NULL;
}

void createParamList(int count)
{
    ParamListCount plist = (ParamListCount)malloc(sizeof(struct ParamListRec));
    plist->count = count;
    plist->func = none;
    if (paramcounthead == NULL)
    {
        paramcounthead = plist;
        plist->next = NULL;
    }
    else
    {
        ParamListCount p = paramcounthead;
        plist->next = p;
        plist->params = NULL;
        paramcounthead = plist;
    }
}

ParamListCount findParamList(char *name)
{
    ParamListCount p = paramcounthead;
    while ((p != NULL))
    {
        if (strcmp(name, p->func) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

void insertInstruction(OpdKind op, Operand opd1, Operand opd2, Operand opd3)
{
    Inst inst;
    inst.op = op;
    inst.opd1 = opd1;
    inst.opd2 = opd2;
    inst.opd3 = opd3;
    OCList new = (OCList)malloc(sizeof(struct OCListRec));
    new->location = instline;
    new->inst = inst;
    new->next = NULL;
    if (ochead == NULL)
    {
        ochead = new;
    }
    else
    {
        OCList o = ochead;
        while (o->next != NULL)
            o = o->next;
        o->next = new;
    }
    instline++;
}

OCList searchByLocation(int loc)
{
    OCList oc = ochead;
    while (oc != NULL)
    {
        if ((oc->location) == loc)
        {
            return oc;
        }
        oc = oc->next;
    }
    return NULL;
}

Operand createEmpty()
{
    Operand opd;
    opd.kind = Empty;
    opd.value.name = NULL;
    opd.value.val = -1;
    return opd;
}

Operand createIntConst(int val)
{
    Operand opd;
    opd.kind = IntConst;
    opd.value.val = val;
    return opd;
}

Operand createString(char *name)
{
    Operand opd;
    opd.kind = String;
    opd.value.name = (char *)malloc(strlen(name) * sizeof(char));
    strcpy(opd.value.name, name);
    return opd;
}

void printAssembly(QuadList q)
{
    Address a1, a2, a3;
    Operand o1, o2, o3;
    _param = (char *)malloc(sizeof(char) * 10);
    LabelList label;
    OCList oclist;
    ParamListCount plist;
    VarList variable, variable1;
    OpdKind op;
    int plistcount = 0, plistind = 0, plistchange;
    while (q != NULL)
    {
        a1 = q->quad.addr1;
        a2 = q->quad.addr2;
        a3 = q->quad.addr3;

        if (strcmp(operatorNameLabel[q->quad.op], "addition") == 0)
        {
            o1 = createString(a1.contents.var.name);
            o2 = createString(a2.contents.var.name);
            if (a3.kind == IntConst)
            {
                o3 = createIntConst(a3.contents.val);
                op = o_addi;
            }
            else if (a3.kind != IntConst)
            {
                o3 = createString(a3.contents.var.name);
                op = o_add;
            }
            insertInstruction(op, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "subtraction") == 0)
        {
            o1 = createString(a1.contents.var.name);
            o2 = createString(a2.contents.var.name);
            o3 = createString(a3.contents.var.name);
            insertInstruction(o_sub, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "multiplication") == 0)
        {
            o1 = createString(a1.contents.var.name);
            o2 = createString(a2.contents.var.name);
            o3 = createString(a3.contents.var.name);
            insertInstruction(o_mul, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "division") == 0)
        {
            o1 = createString(a1.contents.var.name);
            o2 = createString(a2.contents.var.name);
            o3 = createString(a3.contents.var.name);
            insertInstruction(o_div, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "lt") == 0)
        {
            if (bne != 1)
            {
                o1 = createString(a1.contents.var.name);
                o2 = createString(a2.contents.var.name);
                o3 = createString(a3.contents.var.name);
                insertInstruction(o_lt, o1, o2, o3);
            }
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "lte") == 0)
        {
            o1 = createString(a1.contents.var.name);
            o2 = createString(a2.contents.var.name);
            o3 = createString(a3.contents.var.name);
            insertInstruction(o_lte, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "gt") == 0)
        {
            bne = 1;
            o1 = createString(a1.contents.var.name);
            o2 = createString(a2.contents.var.name);
            o3 = createEmpty();
            insertInstruction(o_beq, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "gte") == 0)
        {
            o1 = createString(a1.contents.var.name);
            o2 = createString(a2.contents.var.name);
            o3 = createString(a3.contents.var.name);
            insertInstruction(o_gte, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "equal") == 0)
        {
            o1 = createString(a1.contents.var.name);
            o2 = createString(a2.contents.var.name);
            o3 = createEmpty();
            insertInstruction(o_beq, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "or") == 0)
        {
            if (bne != 1)
            {
                o1 = createString(a1.contents.var.name);
                o2 = createString(a2.contents.var.name);
                o3 = createString(a3.contents.var.name);
                insertInstruction(o_or, o1, o2, o3);
            }
            else
                bne = 0;
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "assign") == 0)
        {
            if (callsign == 0)
            {
                o2 = createString(a1.contents.var.name);
                o1 = createString(a2.contents.var.name);
                o3 = createEmpty();
                insertInstruction(o_move, o1, o2, o3);
            }
            else
            {
                o2 = createString(a1.contents.var.name);
                o1 = createString("$v0");
                o3 = createEmpty();
                insertInstruction(o_move, o1, o2, o3);
                callsign=0;
            }
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "alloc") == 0)
        {
            if (strcmp(a3.contents.var.name, "main") != 0)
                createVarTemp(a1.contents.var.name, none, a3.contents.var.name, -1);
            else
            {
                createVarTemp(a1.contents.var.name, none, a3.contents.var.name, mem);
                mem++;
            }

        }
        else if (strcmp(operatorNameLabel[q->quad.op], "immed") == 0)
        {
            o2 = createString(a2.contents.var.name);
            o3 = createIntConst(a1.contents.val);
            o1 = createEmpty();
            insertInstruction(o_li, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "load") == 0)
        {
            variable = findVar(a1.contents.var.name, function);
            if (variable != NULL)
            {
                o1 = createString(a1.contents.var.name);
                o2 = createString(a2.contents.var.name);
                o3 = createIntConst(variable->loc);
                strcpy(variable->trg, a2.contents.var.name);
                strcpy(_param, a2.contents.var.name);
                insertInstruction(o_lw, o1, o2, o3);
            }
            else
            {
            }

        }
        else if (strcmp(operatorNameLabel[q->quad.op], "store") == 0)
        {
            variable = findVar(a1.contents.var.name, function);
            o2 = createString(a3.contents.var.name);
            o1 = createString(a1.contents.var.name);
            o3 = createIntConst(variable->loc);
            insertInstruction(o_sw, o1, o2, o3);
            strcpy(variable->trg, a3.contents.var.name);

        }
        else if (strcmp(operatorNameLabel[q->quad.op], "vector") == 0)
        {
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "goto") == 0)
        {
            label = findLabel(a1.contents.var.name);
            if (label != NULL)
            {
                o1 = createString(label->name);

                o2 = createEmpty();
                o3 = createEmpty();
                insertInstruction(o_jump, o1, o2, o3);
            }
            else
            {
                o1 = createString(a1.contents.var.name);
                o2 = createEmpty();
                o3 = createEmpty();
                insertInstruction(o_jump, o1, o2, o3);
            }
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "if_f") == 0)
        {
            oclist = searchByLocation(instline - 1);
            o3 = createString(a2.contents.var.name);
            oclist->inst.opd3 = o3;
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "return") == 0)
        {
            o2 = createString("$v0");
            o1 = createString(a1.contents.var.name);
            o3 = createEmpty();
            insertInstruction(o_move, o1, o2, o3);
            o1 = createString(function);
            o2 = createString("$v0");
            o3 = createEmpty();
            insertInstruction(o_ret, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "function") == 0)
        {
            o1 = createString(a1.contents.var.name);
            o2 = createEmpty();
            o3 = createEmpty();
            createLabel(a1.contents.var.name, instline, -1);
            insertInstruction(o_function, o1, o2, o3);
            function = (char *)malloc(strlen(a1.contents.var.name) * sizeof(char));
            strcpy(function, a1.contents.var.name);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "end") == 0)
        {
            o1 = createString(a1.contents.var.name);
            o2 = createEmpty();
            o3 = createEmpty();
            label = findLabel(a1.contents.var.name);
            if (label != NULL)
                label->locend = instline;
            else
                fprintf(listing, "error");

            insertInstruction(o_end, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "param") == 0)
        {
            plistchange = 0;
            if (plistcount == 0)
            {
                plistind++;
                plistchange = 1;
            }
            plist = paramcounthead;
            int pi = plistind;
            while (pi != 0)
            {
                plist = plist->next;
                pi--;
            }
            if (plistchange == 1)
            {
                plistcount = plist->count;
            }
            ParamsList par = plist->params;
            ParamsList parameter = (ParamsList)malloc(sizeof(struct Params));
            variable = findVarTarget(a1.contents.var.name, function);
            parameter->name = variable->src;
            parameter->scope = variable->scope;
            o1 = createString(a1.contents.var.name);
            o2 = createEmpty();
            o3 = createEmpty();
            insertInstruction(o_param, o1, o2, o3);
            if (par == NULL)
            {
                plist->params = parameter;
                parameter->next = NULL;
            }
            else
            {
                while (par->next != NULL)
                {
                    par = par->next;
                }
                par->next = parameter;
                parameter->next = NULL;
            }
            plistcount--;
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "call") == 0)
        {
            plist = paramcounthead;
            if (strcmp(a1.contents.var.name, "input") == 0)
            {
                _call = (char *)malloc(strlen(a1.contents.var.name) * sizeof(char));
                strcpy(_call, a1.contents.var.name);
                plist->func = _call;
                o2 = createString(a3.contents.var.name);
                o1 = createEmpty();
                o3 = createEmpty();
                insertInstruction(o_input, o1, o2, o3);
            }
            else if (strcmp(a1.contents.var.name, "output") == 0)
            {
                //!
                _call = malloc(sizeof(strlen(a1.contents.var.name)));
                strcpy(_call, a1.contents.var.name);
                plist->func = _call;
                o2 = createString(_param);
                o1 = createEmpty();
                o3 = createEmpty();
                insertInstruction(o_output, o1, o2, o3);
            }
            else
            {
                label = findLabel(a1.contents.var.name);
                _call = malloc(sizeof(strlen(a1.contents.var.name)));
                strcpy(_call, a1.contents.var.name);
                plist->func = _call;
                o1 = createString(a1.contents.var.name);
                o2 = createIntConst(a2.contents.val);
                o3 = createString("$v0");
                insertInstruction(o_call, o1, o2, o3);
                label->locend = instline;
                callsign = 1;
            }
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "arg") == 0)
        {
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "label") == 0)
        {
            o1 = createString(a1.contents.var.name);
            o2 = createEmpty();
            o3 = createEmpty();
            createLabel(a1.contents.var.name, instline, -1);
            insertInstruction(o_label, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "halt") == 0)
        {
            o1 = createEmpty();
            o2 = createEmpty();
            o3 = createEmpty();
            insertInstruction(o_halt, o1, o2, o3);
        }
        else if (strcmp(operatorNameLabel[q->quad.op], "paramlist") == 0)
        {

            plistcount = a1.contents.val;
            createParamList(a1.contents.val);
            o1 = createIntConst(a1.contents.val);
            o2 = createEmpty();
            o3 = createEmpty();
            insertInstruction(o_param_list, o1, o2, o3);
        }
        q = q->next;
    }


    label = findLabel("main");
    printBinary(8, 5);
    printBinary(label->locinit, 27);
    fprintf(code, "\n");

    int opcode, nregister, funct, comma, moveflag, callflag, returnflag, regflag;
    fprintf(listing, "\n");
    oclist = ochead;
    while (oclist != NULL)
    {
        callflag = 0;
        moveflag = 0;
        returnflag = 0;
        regflag = 0;
        comma = 1;
        opcode = getOpcode(oclist->inst.op);
        o1 = oclist->inst.opd1;
        o2 = oclist->inst.opd2;
        o3 = oclist->inst.opd3;
        if (opcode != -1)
        {
            if (opcode == 8 && (strcmp(o1.value.name, "main") == 0))
                opcode = 0;
            fprintf(listing, "%d:", oclist->location);
            if (opcode != -2 && (strcmp(operatorNameInstruction[oclist->inst.op], "label")))
                fprintf(listing, " %s", operatorNameInstruction[oclist->inst.op]);
            else if (strcmp(operatorNameInstruction[oclist->inst.op], "label"))
            {
                strcpy(function, o1.value.name);
                if (strcmp(o1.value.name, "main") != 0)
                {
                    ParamListCount p = findParamList(o1.value.name);
                    ParamsList par = p->params;
                    while (par != NULL)
                    {
                        variable = findVar(par->name, par->scope);
                        variable1 = findVarScope(o1.value.name);
                        variable1->loc = variable->loc;
                        par = par->next;
                    }
                }
            }
            if (opcode != -2)
                printBinary(opcode, 5);
            else
                printBinary(0, 5);
            if (strcmp(operatorNameInstruction[oclist->inst.op], "li") == 0 || strcmp(operatorNameInstruction[oclist->inst.op], "output") == 0 || strcmp(operatorNameInstruction[oclist->inst.op], "input") == 0)
                comma = 0;
            if (strcmp(operatorNameInstruction[oclist->inst.op], "move") == 0)
                moveflag = 1;
            if (strcmp(operatorNameInstruction[oclist->inst.op], "ret") == 0 || strcmp(operatorNameInstruction[oclist->inst.op], "end") == 0)
                returnflag = 1;
            if (strcmp(operatorNameInstruction[oclist->inst.op], "ret") == 0)
            {
                comma = 0;
                regflag = 1;
            }
            if (strcmp(operatorNameInstruction[oclist->inst.op], "call") == 0)
            {
                label = findLabel(o1.value.name);
                callflag = 1;
            }
            if (strcmp(operatorNameInstruction[oclist->inst.op], "label") == 0)
            {
                fprintf(listing, " %s:", o1.value.name);
                o1 = createEmpty();
            }
            switch (o1.kind)
            {
            case Empty:
                if (opcode != -1)
                    printBinary(0, 5);
                break;
            case IntConst:
                if (opcode == 4)
                    printBinary(o1.value.val, 5);
                if (opcode == 0)
                    printBinary(0, 5);
                fprintf(listing, " %d", o1.value.val);
                break;
            case String:
                if (opcode != -1 && opcode != 8 && opcode != 3 && opcode != 4 && opcode != 0)
                {
                    nregister = 0;
                    if (strchr(o1.value.name, '$') != NULL)
                        nregister = getRegister(o1.value.name);
                    printBinary(nregister, 5);
                }
                else if (opcode == 8)
                    label = findLabel(o1.value.name);
                else if (opcode == 3 || opcode == 4 || opcode == 0)
                {
                    printBinary(0, 5);
                    comma = 0;
                }
                if (opcode != 3 && opcode != 4 && opcode != -2 && opcode != 1 && moveflag == 0 && regflag == 0)
                    fprintf(listing, " %s", o1.value.name);
                if (moveflag == 1)
                    fprintf(listing, " %s", o2.value.name);
                if (opcode == -2)
                    fprintf(listing, " %s:", o1.value.name);
                if (opcode == 1)
                    fprintf(listing, " %s", o3.value.name);
                break;
            default:
                break;
            }
            switch (o2.kind)
            {
            case Empty:
                if (opcode != -1 && opcode != 8)
                    printBinary(0, 5);
                break;
            case IntConst:
                if (opcode == 2)
                    printBinary(o2.value.val, 17);
                fprintf(listing, ", %d", o2.value.val);
                break;
            case String:
                if (opcode != -1 && regflag == 0)
                {
                    nregister = 0;
                    if (strchr(o2.value.name, '$') != NULL)
                        nregister = getRegister(o2.value.name);
                    printBinary(nregister, 5);
                }
                if (comma == 1)
                    fprintf(listing, ",");
                if (opcode != 1 && moveflag == 0)
                    fprintf(listing, " %s", o2.value.name);
                else if (opcode == 1)
                    fprintf(listing, " %s", o1.value.name);
                if (moveflag == 1)
                    fprintf(listing, " %s", o1.value.name);
                break;
            default:
                break;
            }
            switch (o3.kind)
            {
            case Empty:
                if (opcode != -1 && opcode != 8 && opcode != 2 && opcode != 0 && opcode != 9 && opcode != 5 && opcode != 11 && opcode != -2)
                    printBinary(0, 5);
                else if (opcode == 8 && returnflag == 0)
                    printBinary(label->locinit, 27);
                else if (opcode == 8 && returnflag == 1)
                    printBinary(label->locend, 27);
                else if (opcode == 2 || opcode == 0 || opcode == 5 || opcode == 9 || opcode == 11 || opcode == -2)
                    printBinary(0, 17);
                break;
            case IntConst:
                if (opcode == 3 || opcode == 4)
                {
                    variable = findVar(o1.value.name, function);
                    if (variable->loc == -1)
                    {
                        variable->loc = mem;
                        mem++;
                    }
                    o3.value.val = variable->loc;
                }
                if (opcode == 2 || opcode == 4 || opcode == 3)
                    printBinary(o3.value.val, 17);
                if (opcode == 4 || opcode == 3)
                    fprintf(listing, ", 0(%d)", o3.value.val);
                else
                    fprintf(listing, ", %d", o3.value.val);
                break;
            case String:
                if (opcode != -1 && opcode != 2 && opcode != 7 && callflag == 0)
                {
                    nregister = 0;
                    if (strchr(o3.value.name, '$') != NULL)
                        nregister = getRegister(o3.value.name);
                    printBinary(nregister, 5);
                }
                else if (opcode == 7)
                {
                    label = findLabel(o3.value.name);
                    printBinary(label->locinit, 17);
                }
                if (opcode != 1)
                    fprintf(listing, ", %s", o3.value.name);
                else
                    fprintf(listing, ", %s", o2.value.name);
                if (callflag == 1)
                    printBinary(label->locinit, 27);
                break;
            default:
                break;
            }
            if (opcode == 1)
            {
                funct = getRFunct(oclist->inst.op);
                printBinary(funct, 12);
            }
            fprintf(listing, "\n");
            fprintf(code, "\n");
        }
        oclist = oclist->next;
    }

}
