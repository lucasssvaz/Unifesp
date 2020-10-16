#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t, void (* preProc) (TreeNode *), void (* postProc) (TreeNode *) )
{
    if (t != NULL)
    {
        preProc(t);
        {
            int i;
            for (i=0; i < MAXCHILDREN; i++)
                traverse(t->child[i], preProc, postProc);
        }
        postProc(t);
        traverse(t->sibling, preProc, postProc);
    }
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Semantic error in %s at line %d: %s\n",t->attr.name,t->lineno,message);
    Error = TRUE;
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
    else return;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into
 * the symbol table
 */
static void insertNode( TreeNode * t)
{ switch (t->nodekind)
    { case StmtK:
        switch (t->kind.stmt)
        { case VariableK:
            if (st_lookup(t->attr.name, t->attr.scope) == -1 && st_lookup(t->attr.name, "global") == -1)
                st_insert(t->attr.name,t->lineno,location++, t->attr.scope, "variable", "integer");
            else
                typeError(t,"Error 4-1: Variable has been already declared.");
            break;
        case FunctionK:
            if (st_lookup(t->attr.name, t->attr.scope) == -1 && st_lookup(t->attr.name, "global") == -1)
            {
                if(t->type == Integer)
                    st_insert(t->attr.name,t->lineno,location++, t->attr.scope,"function", "integer");
                else
                    st_insert(t->attr.name,t->lineno,location++, t->attr.scope,"function", "void");
            }
            else
                typeError(t,"Error 4-2: Function has been already declared.");
            break;
        case CallK:
            if (st_lookup(t->attr.name, t->attr.scope) == -1 && st_lookup(t->attr.name, "global") == -1)
                typeError(t,"Error 5: Function has not been declared.");
            else
                st_insert(t->attr.name,t->lineno,location++, t->attr.scope, "call", "-");
            break;
        case ReturnK:
            break;
        default:
            break;
        }
        break;
    case ExpK:
        switch (t->kind.exp)
        { case IdK:
            if (st_lookup(t->attr.name, t->attr.scope) == -1 && st_lookup(t->attr.name, "global") == -1)
                typeError(t,"Error 1-1: ID was not declared.");
            else
                st_insert(t->attr.name,t->lineno,0, t->attr.scope, "variable", "integer");
            break;
        case VectorK:
            if (st_lookup(t->attr.name, t->attr.scope) == -1 && st_lookup(t->attr.name, "global") == -1)
                typeError(t,"Error 1-2: Vector was not declared");
            else
                st_insert(t->attr.name,t->lineno,0, t->attr.scope, "vector", "integer");
            break;
        case VectorIdK:
            if (st_lookup(t->attr.name, t->attr.scope) == -1 && st_lookup(t->attr.name, "global") == -1)
                typeError(t,"Error 1-3: Vector index was not declared");
            else
                st_insert(t->attr.name,t->lineno,0, t->attr.scope, "vector index", "integer");
            break;
        case TypeK:
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}



/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ st_insert("input",0,location++, "global", "function", "integer"); // specification
    st_insert("output",0,location++, "global", "function", "void"); // specification
    traverse(syntaxTree,insertNode,nullProc);
    if(st_lookup("main", "global") == -1)
    { printf("Error 6: Main was not declared.");
        Error = TRUE;
    }
    if (TraceAnalyze)
    { fprintf(listing,"\nSymbol table:\n\n");
        printSymTab(listing);
    }
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ switch (t->nodekind)
    { case StmtK:
        switch (t->kind.stmt)
        {
        case AssignK:
            if(t->child[1] && t->child[1]->kind.stmt == CallK)
            {
                if((strcmp(st_lookup_type(t->child[1]->attr.name, t->child[1]->attr.scope), "void") == 0) || (strcmp(st_lookup_type(t->child[1]->attr.name, "global"), "void") == 0))
                    typeError(t->child[1],"Error 2: Invalid attribution, void has no return.");
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;

    }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{
    traverse(syntaxTree,nullProc,checkNode);
}
