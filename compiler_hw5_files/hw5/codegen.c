#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <assert.h>
#include "header.h"
#include "symbolTable.h"
// This file is for reference only, you are not required to follow the implementation. //
// You only need to check for errors stated in the hw4 document. //
// TODO remove assert
#define assert
extern int g_anyErrorOccur;

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
void genProgramNode(AST_NODE *programNode);
void genDeclarationNode(AST_NODE* declarationNode);
void genDeclareIdList(AST_NODE* typeNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize);
void genDeclareFunction(AST_NODE* returnTypeNode);
void genDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize);
void genTypeNode(AST_NODE* typeNode);
void genBlockNode(AST_NODE* blockNode);
void genStmtNode(AST_NODE* stmtNode);
void genGeneralNode(AST_NODE *node);
void genAssignOrExpr(AST_NODE* assignOrExprRelatedNode);
void genWhileStmt(AST_NODE* whileNode);
void genForStmt(AST_NODE* forNode);
void genAssignmentStmt(AST_NODE* assignmentNode);
void genIfStmt(AST_NODE* ifNode);
void genWriteFunction(AST_NODE* functionCallNode);
void genFunctionCall(AST_NODE* functionCallNode);
void genExprRelatedNode(AST_NODE* exprRelatedNode);
void genParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter, AST_NODE* funcIDNode);
void genReturnStmt(AST_NODE* returnNode);
void genExprNode(AST_NODE* exprNode);
void genVariableLValue(AST_NODE* idNode);
void genVariableRValue(AST_NODE* idNode);
void genExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue);
void genConst(AST_NODE* node);
int genEvaluateExprValue(AST_NODE* exprNode);

typedef enum{
    STATUS_UNUSE,
    STATUS_USING,
    STATUS_DONE
}reg_status;

typedef enum{
    TYPE_CALLEE,
    TYPE_CALLER
}reg_type;

typedef enum{
    VAR_INT,
    VAR_FLOAT
}reg_var;

typedef struct{
    int id,dirty;
    reg_type type;
    reg_var var;
    reg_status status;
    SymbolTableEntry *entry;    
}reg;

extern SymbolTable symbolTable;
int g_cnt = 0;
FILE* output;
reg regs[65];
int nreg=0;

void gen_head(char *name) {
    printf(".text\n%s:\n",name);
}

const char* reg_names[]={"Zero","ra","sp","gp","tp","t0","t1","t2","fp","s1","a0","a1","a2","a3","a4","a5","a6","a7","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6",
                        "ft0","ft1","ft2","ft3","ft4","ft5","ft6","ft7","fs0","fs1","fa0","fa1","fa2","fa3","fa4","fa5","fa6","fa7","fs2","fs3","fs4","fs5","fs6","fs7","fs8","fs9","fs10","fs11","ft8","ft9","ft10","ft11"};
const char* get_reg_name(int id){
    return reg_names[id];
}

void clear_reg(int i){
    regs[i].dirty=0; regs[i].status=STATUS_UNUSE; regs[i].entry=NULL;
}

void initreg(int id,reg_type type,reg_var var){
    regs[nreg].id=id; regs[nreg].type=type; regs[nreg].var=var;
    clear_reg(id); nreg++;
}

void initregs(){
    for(int i=5;i<=7;i++) initreg(i,TYPE_CALLER,VAR_INT);
    for(int i=9;i<=9;i++) initreg(i,TYPE_CALLEE,VAR_INT);
    for(int i=18;i<=27;i++) initreg(i,TYPE_CALLEE,VAR_INT);
    for(int i=28;i<=31;i++) initreg(i,TYPE_CALLER,VAR_INT);
    for(int i=0;i<=7;i++) initreg(i,TYPE_CALLER,VAR_FLOAT);
    for(int i=8;i<=9;i++) initreg(i,TYPE_CALLEE,VAR_FLOAT);
    for(int i=18;i<=27;i++) initreg(i,TYPE_CALLEE,VAR_FLOAT);
    for(int i=28;i<=31;i++) initreg(i,TYPE_CALLER,VAR_FLOAT);
}

void clean_reg(int i){
    if(regs[i].entry&&regs[i].dirty)
        fprintf(output,"\tsw %s,-%d(fp)\n",get_reg_name(regs[i].id),regs[i].entry->offset);
    if(regs[i].entry) regs[i].entry->bindreg=-1;
    clear_reg(i);
}

void bind_reg(int i,SymbolTableEntry *entry){
    regs[i].entry=entry; entry->bindreg=i;
    fprintf(output,"\tlw %s,-%d(fp)\n",get_reg_name(regs[i].id),entry->offset);
}

#define filter(cond) for(int i=0;i<nreg;i++){\
    if(cond){\
        clean_reg(i);\
        if(entry) bind_reg(i,entry);\
        regs[i].status=STATUS_USING;\
        return i;\
    }\
}
int get_reg(SymbolTableEntry *entry,reg_var var){
    if(!entry){
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_DONE&&!regs[i].entry);
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_UNUSE);
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_DONE);
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLEE&&regs[i].status==STATUS_DONE&&!regs[i].entry);
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLEE&&regs[i].status==STATUS_UNUSE);
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLEE&&regs[i].status==STATUS_DONE);
        assert(0);
    }
    else{
        if(entry->bindreg) return entry->bindreg;
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLEE&&regs[i].status==STATUS_DONE&&!regs[i].entry);
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLEE&&regs[i].status==STATUS_UNUSE);
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLEE&&regs[i].status==STATUS_DONE);
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_DONE&&!regs[i].entry);
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_UNUSE);
        filter(regs[i].var==var&&regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_DONE);
        assert(0);
    }
}
#undef filter

void flush_regs(){
    for(int i=0;i<nreg;i++) clean_reg(i);
}

void* save_caller_regs(int *offset){
    for(int i=0;i<nreg;i++){
        if(regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_DONE) clean_reg(i);
    }
    void* ret=malloc(sizeof(reg)*nreg);
    memcpy(ret,regs,sizeof(reg)*nreg);
    for(int i=0;i<nreg;i++){
        if(regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_USING){
            if(!regs[i].entry){
                fprintf(output,"\tsw %s,-%d(fp)\n",get_reg_name(regs[i].id),*offset);
                *offset+=4;
            }
            clean_reg(i);
        }
    }
    return ret;
}

void restore_caller_regs(void* saved,int *offset){
    memcpy(regs,saved,sizeof(reg)*nreg);
    free(saved);
    for(int i=nreg-1;i>=0;i--){
        if(regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_USING){
            if(regs[i].entry)
                bind_reg(i,regs[i].entry);
            else{
                *offset-=4;
                fprintf(output,"\tlw %s,-%d(fp)\n",get_reg_name(regs[i].id),*offset);
            }
        }
    }
}

void* save_callee_regs(int *offset,unsigned mask){
    void* ret=malloc(sizeof(reg)*nreg);
    memcpy(ret,regs,sizeof(reg)*nreg);
    for(int i=0;i<nreg;i++){
        if((mask&(1u<<i))&&regs[i].type==TYPE_CALLEE&&regs[i].status!=STATUS_UNUSE){
            fprintf(output,"\tsw %s,-%d(fp)\n",get_reg_name(regs[i].id),*offset);
            *offset+=4;
            clear_reg(i);
        }
    }
    return ret;
}

void restore_callee_regs(void* saved,int *offset,int mask){
    memcpy(regs,saved,sizeof(reg)*nreg);
    free(saved);
    for(int i=nreg-1;i>=0;i--){
        if((mask&(1u<<i))&&regs[i].type==TYPE_CALLEE&&regs[i].status!=STATUS_UNUSE){
            *offset-=4;
            fprintf(output,"\tlw %s,-%d(fp)\n",get_reg_name(regs[i].id),*offset);
        }
    }
}

void genProgramNode(AST_NODE *programNode) {
	AST_NODE* ptr = programNode->child;
    while(ptr) {
        if(ptr->nodeType == VARIABLE_DECL_LIST_NODE) genGeneralNode(ptr);
        else genDeclarationNode(ptr);

        assert(ptr->dataType != ERROR_TYPE);
        ptr = ptr->rightSibling;
    }
}
void genDeclarationNode(AST_NODE* declarationNode) {
	AST_NODE* type = declarationNode->child;
    genTypeNode(type);
    assert(type->dataType != ERROR_TYPE);

    switch(declarationNode->semantic_value.declSemanticValue.kind) {
        case TYPE_DECL:
            genDeclareIdList(declarationNode, TYPE_ATTRIBUTE, 0);
            break;
        case VARIABLE_DECL:
            genDeclareIdList(declarationNode, VARIABLE_ATTRIBUTE, 0);
            break;
        case FUNCTION_DECL:
            genDeclareFunction(declarationNode);
            break;
        case FUNCTION_PARAMETER_DECL:
            genDeclareIdList(declarationNode, VARIABLE_ATTRIBUTE, 1);
            break;
        default:
            assert(0);
    }
}
void genDeclareIdList(AST_NODE* typeNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize) {
	
}
void genDeclareFunction(AST_NODE* returnTypeNode) {
	
}
void genDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize) {
	
}
void genTypeNode(AST_NODE* typeNode) {
	
}
void genBlockNode(AST_NODE* blockNode) {
    openScope();
    flush_regs();
    AST_NODE* ptr = blockNode->child;
    while(ptr) {
        genGeneralNode(ptr);
        ptr = ptr->rightSibling;
    }
    closeScope();
    flush_regs();
}
void genStmtNode(AST_NODE* stmtNode) {
    if(stmtNode->nodeType == BLOCK_NODE) genBlockNode(stmtNode);
    else if(stmtNode->nodeType == NUL_NODE) return;
    else {
        switch(stmtNode->semantic_value.stmtSemanticValue.kind) {
            case WHILE_STMT:
                genWhileStmt(stmtNode);
                break;
            case FOR_STMT:
                genForStmt(stmtNode);
                break;
            case ASSIGN_STMT:
                genAssignmentStmt(stmtNode);
                break;
            case IF_STMT:
                genIfStmt(stmtNode);
                break;
            case FUNCTION_CALL_STMT:
                genFunctionCall(stmtNode);
                break;
            case RETURN_STMT:
                genReturnStmt(stmtNode);
                break;      
            default:
                assert(0 && "unhandled stmtNode type");
        }
    }
}
void genGeneralNode(AST_NODE *node) {
    if(node->nodeType == VARIABLE_DECL_LIST_NODE || 
    node->nodeType == STMT_LIST_NODE || 
    node->nodeType == NONEMPTY_ASSIGN_EXPR_LIST_NODE || 
    node->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE) {
        AST_NODE* ptr = node->child;
        while(ptr) {
            if(node->nodeType == VARIABLE_DECL_LIST_NODE) genDeclarationNode(ptr);
            else if(node->nodeType == STMT_LIST_NODE) genStmtNode(ptr);
            else if(node->nodeType == NONEMPTY_ASSIGN_EXPR_LIST_NODE) genAssignOrExpr(ptr);
            else if(node->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE) genExprRelatedNode(ptr);
            
            assert(ptr->dataType != ERROR_TYPE);
            node->dataType = ptr->dataType;
            ptr = ptr->rightSibling;
        }
    }
}
void genAssignOrExpr(AST_NODE* assignOrExprRelatedNode) {
	if(assignOrExprRelatedNode->nodeType == EXPR_NODE) genExprNode(assignOrExprRelatedNode);
    else {
        if(assignOrExprRelatedNode->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT)
            genAssignmentStmt(assignOrExprRelatedNode);
        else if(assignOrExprRelatedNode->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT)
            genFunctionCall(assignOrExprRelatedNode);
    }
}
void genWhileStmt(AST_NODE* whileNode) {
    // TODO: convert float to int
    /*
    _WHILE_%d:
        genAssignOrExpr(condition)
        beqz %s, _EXIT_%d
        genStmtNode(stmt)
        j _WHILE_%d
    _EXIT_%d:
    */
    int cnt = g_cnt++;
	AST_NODE *condition = whileNode->child, *stmt = condition->rightSibling;
    fprintf(output, "_WHILE_%d:\n", cnt); 
    genAssignOrExpr(condition);
    fprintf(output, "\tbeqz %s, _EXIT_%d\n", get_reg_name(regs[condition->regnumber].id), cnt);
    genStmtNode(stmt);
    fprintf(output, "\tj _WHILE_%d\n", cnt);
    fprintf(output, "_EXIT_%d:\n", cnt);
}
void genForStmt(AST_NODE* forNode) {
    // TODO: convert float to int
    /*
        genGeneralNode(assign)
    _FOR_%d:
        genGEneralNode(condition)
        beqz %s, _EXIT_%d
        genStmtNode(stmt)
        genStmtNode(loop)
        j _FOR_%d
    _EXIT_%d:
    */
    int cnt = g_cnt++;
    AST_NODE *assign = forNode->child, *condition = assign->rightSibling, \
        *loop = condition->rightSibling, *stmt = loop->rightSibling;
    genGeneralNode(assign);
    fprintf(output, "_FOR_%d:\n", cnt);
    genGeneralNode(condition);
    fprintf(output, "\tbeqz %s, _EXIT_%d\n", get_reg_name(regs[condition->regnumber].id), cnt);
    genStmtNode(stmt); 
    genStmtNode(loop);
    fprintf(output, "\tj _FOR_%d\n", cnt);
    fprintf(output, "_EXIT_%d:\n", cnt);
}
void genAssignmentStmt(AST_NODE* assignmentNode) {
    AST_NODE *var_ref = assignmentNode->child, *relop_expr = var_ref->rightSibling;
    genVariableLValue(var_ref);
    genExprRelatedNode(relop_expr);
    int lreg = regs[var_ref->regnumber].id, rreg = regs[relop_expr->regnumber].id;
    regs[var_ref->regnumber].dirty = 1;
    fprintf(output, "\tmv %s, %s\n", get_reg_name(lreg), get_reg_name(rreg));
}
void genIfStmt(AST_NODE* ifNode) {
    // TODO: convert float to int
    /*
    _IF_%d:
        genAssignOrExpr(condition)
        beqz %s, _ELSE_%d
        genStmtNode(if_stmt)
        j _EXIT_%d
    _ELSE_%d:
        genStmtNode(else_stmt)
    _EXIT_%d:
    */
    int cnt = g_cnt++;
	AST_NODE *condition = ifNode->child, *if_stmt = condition->rightSibling, *else_stmt = if_stmt->rightSibling;
    fprintf(output, "_IF_%d:\n", cnt);
    genAssignOrExpr(condition);
    fprintf(output, "\tbeqz %s, _ELSE_%d\n", get_reg_name(regs[condition->regnumber].id), cnt);
    genStmtNode(if_stmt);
    fprintf(output, "\tj _EXIT_%d\n", cnt);
    fprintf(output, "_ELSE_%d:\n", cnt);
    genStmtNode(else_stmt);
    fprintf(output, "_EXIT_%d\n", cnt);
}

void genWriteFunction(AST_NODE* functionCallNode) {
	
}
void genFunctionCall(AST_NODE* functionCallNode) {
	
}
void genExprRelatedNode(AST_NODE* exprRelatedNode) {
	switch(exprRelatedNode->nodeType) {
        case EXPR_NODE:
            if(exprRelatedNode->semantic_value.exprSemanticValue.isConstEval) genConst(exprRelatedNode);
            else genExprNode(exprRelatedNode);
            break;
        case STMT_NODE:
            genFunctionCall(exprRelatedNode);
            break;
        case CONST_VALUE_NODE:
            genConst(exprRelatedNode);
            break;
        case IDENTIFIER_NODE:
            genVariableRValue(exprRelatedNode);
            break;
        default:
            break;
    }
}
void genParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter, AST_NODE* funcIDNode) {
	// TODO
}
void genReturnStmt(AST_NODE* returnNode) {
    genExprRelatedNode(returnNode->child);
    int reg = regs[returnNode->child->regnumber].id;
    if(returnNode->child->dataType == INT_TYPE)
        fprintf(output, "\tmv %s %s\n", get_reg_name(10), get_reg_name(reg));
    else
        fprintf(output, "\tmv %s %s\n", get_reg_name(10 + 32), get_reg_name(reg));
}
void genConst(AST_NODE* node) {
    reg_var type = node->dataType == INT_TYPE ? VAR_INT : VAR_FLOAT;
    int reg;
    reg = get_reg(NULL, type);
    if(type == INT_TYPE) {
        unsigned ival = (node->nodeType == EXPR_NODE ? node->semantic_value.exprSemanticValue.constEvalValue.iValue : node->semantic_value.const1->const_u.intval);
        if(ival >> 12) {
            fprintf(output, "\tlui %s, %d\n", get_reg_name(regs[reg].id), ival >> 12); 
            fprintf(output, "\taddi %s, %s, %d\n", get_reg_name(regs[reg].id), get_reg_name(regs[reg].id), ival & ((1 << 12) - 1));
        }
        else fprintf(output, "\taddi %s, %s, %d\n", get_reg_name(regs[reg].id), get_reg_name(0), ival);
    }
    else {
        float ival = (node->nodeType == EXPR_NODE ? node->semantic_value.exprSemanticValue.constEvalValue.fValue : node->semantic_value.const1->const_u.fval);
        // TODO: float
    }
    node->regnumber = reg;
}
void genExprNode(AST_NODE* exprNode) {
	if(exprNode->semantic_value.exprSemanticValue.kind == BINARY_OPERATION) {
        AST_NODE *lc = exprNode->child, *rc = lc->rightSibling;
    
        exprNode->dataType = getBiggerType(lc->dataType, rc->dataType);
        int lconst = lc->nodeType == CONST_VALUE_NODE || (lc->nodeType == EXPR_NODE && lc->semantic_value.exprSemanticValue.isConstEval);
        int rconst = rc->nodeType == CONST_VALUE_NODE || (rc->nodeType == EXPR_NODE && rc->semantic_value.exprSemanticValue.isConstEval);

        genExprRelatedNode(lc);
        genExprRelatedNode(rc);

        reg_var type = exprNode->dataType == INT_TYPE ? VAR_INT : VAR_FLOAT;
        int reg1 = lc->regnumber, reg2 = rc->regnumber;

        regs[reg1].status=STATUS_DONE; regs[reg2].status=STATUS_DONE;
        int reg0 = get_reg(NULL, type);

        if(type == VAR_INT) {
            switch(exprNode->semantic_value.exprSemanticValue.op.binaryOp) {
                case BINARY_OP_ADD:
                    fprintf(output, "\tadd %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_SUB:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_MUL:
                    fprintf(output, "\tmul %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_DIV:
                    fprintf(output, "\tdiv %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_EQ:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tseqz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_GE:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tsltz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    fprintf(output, "\tnot %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_GT:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tsgtz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_LE:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tsgtz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    fprintf(output, "\tnot %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_LT:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tsgtz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_NE:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tsnez %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_OR:
                    fprintf(output, "\tor %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_AND:
                    fprintf(output, "\tand %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                default:
                    assert(0);
            }
        }
        else {
            // TODO float
        }
    }
    else {
        AST_NODE *rc = exprNode->child; 
        genExprRelatedNode(rc);

        int reg = rc->regnumber;
        reg_var type = exprNode->dataType == INT_TYPE ? VAR_INT : VAR_FLOAT;

        UNARY_OPERATOR op = exprNode->semantic_value.exprSemanticValue.op.unaryOp;
        if(op == UNARY_OP_POSITIVE) {
            exprNode->regnumber = reg;
        }
        else {
            int reg0 = get_reg(NULL, type);
            if(type == VAR_INT) {
                if(op == UNARY_OP_NEGATIVE) fprintf(output, "\tneg %s %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg].id));
                else fprintf(output, "\tsnez %s %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg].id)); // UNARY_OP_LOGICAL_NEGATION
            }
            else {
                if(op == UNARY_OP_NEGATIVE);
                else; // UNARY_OP_LOGICAL_NEGATION
            }
        }
    }
}
void genVariableLValue(AST_NODE* idNode) {
	genVariableRValue(idNode);
}
void genVariableRValue(AST_NODE* idNode) {
	SymbolTableEntry *entry=retrieveSymbol(idNode->semantic_value.identifierSemanticValue.identifierName);
    idNode->semantic_value.identifierSemanticValue.symbolTableEntry=entry;
    TypeDescriptor* tpdes=idNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
    if(idNode->semantic_value.identifierSemanticValue.kind==ARRAY_ID||tpdes->kind==ARRAY_TYPE_DESCRIPTOR){
        /* giver TODO */
        assert(0);
    }
    else{
        int creg=get_reg(entry,tpdes->properties.dataType==INT_TYPE?VAR_INT:VAR_FLOAT);
        idNode->regnumber=creg;
    }
}

void codegen(AST_NODE *root) {
    initregs();
    output = fopen("output.s", "w");
    genProgramNode(root);
    fclose(output);
}

