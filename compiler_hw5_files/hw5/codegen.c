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
extern DATA_TYPE getTypeOfSymbolTableEntry(SymbolTableEntry*);

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
void genProgramNode(AST_NODE *programNode);
void genDeclarationNode(AST_NODE* declarationNode);
void genDeclareIdList(AST_NODE* typeNode);
void genGlobalDeclareIdList(AST_NODE* declarationNode);
void genDeclareFunction(AST_NODE* declarationNode);
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
void genArraySubscript(AST_NODE* ptr);
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

typedef struct gbl_str{
    char label[10],*str;
    struct gbl_str* next;
}gbl_str;

typedef union{
    int val;
    float fval;
    struct{
        int lo:12;
    };
    struct{
        unsigned :12,hi:20;
    };
}Int;

int get_reg(SymbolTableEntry *entry,reg_var var);

extern SymbolTable symbolTable;
int g_cnt = 5;
FILE* output;
reg regs[65];
int nreg=0,offset,arsize,arpos,meow=1;
unsigned long long mask;
gbl_str *str_head=NULL;
#define fprintf if(meow) fprintf

char* get_label(char *str){
    gbl_str *tmp=str_head;
    while(tmp){
        if(strcmp(tmp->str,str)==0) return tmp->label;
        tmp=tmp->next;
    }
    tmp=(gbl_str*)malloc(sizeof(gbl_str));
    sprintf(tmp->label,".LC%d",g_cnt++);
    tmp->str=str;
    tmp->next=str_head;
    str_head=tmp;
    return tmp->label;
}

char* reg_names[]={"zero","ra","sp","gp","tp","t0","t1","t2","fp","s1","a0","a1","a2","a3","a4","a5","a6","a7","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6",
                        "ft0","ft1","ft2","ft3","ft4","ft5","ft6","ft7","fs0","fs1","fa0","fa1","fa2","fa3","fa4","fa5","fa6","fa7","fs2","fs3","fs4","fs5","fs6","fs7","fs8","fs9","fs10","fs11","ft8","ft9","ft10","ft11"};

char* get_reg_name(int id){
    return reg_names[id];
}

void gen_loadimm(int reg,Int tmp){
    if(tmp.lo<0) tmp.hi++;
    if(tmp.hi) {
        fprintf(output, "\tlui %s, %u\n", get_reg_name(regs[reg].id), tmp.hi);
        fprintf(output, "\taddi %s, %s, %d\n", get_reg_name(regs[reg].id), get_reg_name(regs[reg].id), tmp.lo);
    }
    else {
        fprintf(output, "\taddi %s, %s, %d\n", get_reg_name(regs[reg].id), get_reg_name(0), tmp.lo);
    }

}

void clear_reg(int i){
    regs[i].dirty=0; regs[i].status=STATUS_UNUSE; regs[i].entry=NULL;
}

void load_reg(int i,int off,int ireg){
    int breg=8;
    if(off>2048){
        int reg=get_reg(NULL,VAR_INT); Int tmp; tmp.val=off;
        gen_loadimm(reg,tmp); regs[reg].status=STATUS_DONE;
        fprintf(output,"\tsub %s,%s,%s\n",get_reg_name(regs[reg].id),get_reg_name(breg),get_reg_name(regs[reg].id));
        breg=regs[reg].id; off=0;
    }
    if(ireg<0){
        if(regs[i].id<32){
            fprintf(output,"\tlw %s,%d(%s)\n",get_reg_name(regs[i].id),-off,get_reg_name(breg));
        }
        else{
            fprintf(output,"\tflw %s,%d(%s)\n",get_reg_name(regs[i].id),-off,get_reg_name(breg));
        }
    }
    else{
        if(regs[i].id<32){
            fprintf(output,"\tadd %s,%s,%s\n",get_reg_name(regs[ireg].id),get_reg_name(regs[ireg].id),get_reg_name(breg));
            fprintf(output,"\tlw %s,%d(%s)\n",get_reg_name(regs[i].id),-off,get_reg_name(regs[ireg].id));
        }
        else{
            fprintf(output,"\tadd %s,%s,%s\n",get_reg_name(regs[ireg].id),get_reg_name(regs[ireg].id),get_reg_name(breg));
            fprintf(output,"\tflw %s,%d(%s)\n",get_reg_name(regs[i].id),-off,get_reg_name(regs[ireg].id));
        }
    }
}

void store_reg(int i,int off,int ireg){
    int breg=8;
    if(off>2048){
        int reg=get_reg(NULL,VAR_INT); Int tmp; tmp.val=off;
        gen_loadimm(reg,tmp); regs[reg].status=STATUS_DONE;
        fprintf(output,"\tsub %s,%s,%s\n",get_reg_name(regs[reg].id),get_reg_name(breg),get_reg_name(regs[reg].id));
        breg=regs[reg].id; off=0;
    }
    if(ireg<0){
        if(regs[i].id<32){
            fprintf(output,"\tsw %s,%d(%s)\n",get_reg_name(regs[i].id),-off,get_reg_name(breg));
        }
        else{
            fprintf(output,"\tfsw %s,%d(%s)\n",get_reg_name(regs[i].id),-off,get_reg_name(breg));
        }
    }
    else{
        if(regs[i].id<32){
            fprintf(output,"\tadd %s,%s,%s\n",get_reg_name(regs[ireg].id),get_reg_name(regs[ireg].id),get_reg_name(breg));
            fprintf(output,"\tsw %s,%d(%s)\n",get_reg_name(regs[i].id),-off,get_reg_name(regs[ireg].id));
        }
        else{
            fprintf(output,"\tadd %s,%s,%s\n",get_reg_name(regs[ireg].id),get_reg_name(regs[ireg].id),get_reg_name(breg));
            fprintf(output,"\tfsw %s,%d(%s)\n",get_reg_name(regs[i].id),-off,get_reg_name(regs[ireg].id));
        }
    }
}

void load_global_reg(int i,char* idname,int ireg){
    int tmpreg=get_reg(NULL,VAR_INT); regs[tmpreg].status=STATUS_DONE;
    if(ireg<0){
        if(regs[i].id<32){
            fprintf(output,"\tlui %s,%%hi(%s)\n",get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\tlw %s,%%lo(%s)(%s)\n",get_reg_name(regs[i].id),idname,get_reg_name(regs[tmpreg].id));
        }
        else{
            fprintf(output,"\tlui %s,%%hi(%s)\n",get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\tflw %s,%%lo(%s)(%s)\n",get_reg_name(regs[i].id),idname,get_reg_name(regs[tmpreg].id));
        }
    }
    else{
        if(regs[i].id<32){
            fprintf(output,"\tlui %s,%%hi(%s)\n",get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\taddi %s,%s,%%lo(%s)\n",get_reg_name(regs[tmpreg].id),get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\tadd %s,%s,%s\n",get_reg_name(regs[tmpreg].id),get_reg_name(regs[tmpreg].id),get_reg_name(regs[ireg].id));
            fprintf(output,"\tlw %s,0(%s)\n",get_reg_name(regs[i].id),get_reg_name(regs[tmpreg].id));
        }
        else{
            fprintf(output,"\tlui %s,%%hi(%s)\n",get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\taddi %s,%s,%%lo(%s)\n",get_reg_name(regs[tmpreg].id),get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\tadd %s,%s,%s\n",get_reg_name(regs[tmpreg].id),get_reg_name(regs[tmpreg].id),get_reg_name(regs[ireg].id));
            fprintf(output,"\tflw %s,0(%s)\n",get_reg_name(regs[i].id),get_reg_name(regs[tmpreg].id));
        }
    }
    clear_reg(tmpreg);
}

void store_global_reg(int i,char* idname,int ireg){
    int tmpreg=get_reg(NULL,VAR_INT); regs[tmpreg].status=STATUS_DONE;
    if(ireg<0){
        if(regs[i].id<32){
            fprintf(output,"\tlui %s,%%hi(%s)\n",get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\tsw %s,%%lo(%s)(%s)\n",get_reg_name(regs[i].id),idname,get_reg_name(regs[tmpreg].id));
        }
        else{
            fprintf(output,"\tlui %s,%%hi(%s)\n",get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\tfsw %s,%%lo(%s)(%s)\n",get_reg_name(regs[i].id),idname,get_reg_name(regs[tmpreg].id));
        }
    }
    else{
        if(regs[i].id<32){
            fprintf(output,"\tlui %s,%%hi(%s)\n",get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\taddi %s,%s,%%lo(%s)\n",get_reg_name(regs[tmpreg].id),get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\tadd %s,%s,%s\n",get_reg_name(regs[tmpreg].id),get_reg_name(regs[tmpreg].id),get_reg_name(regs[ireg].id));
            fprintf(output,"\tsw %s,0(%s)\n",get_reg_name(regs[i].id),get_reg_name(regs[tmpreg].id));
        }
        else{
            fprintf(output,"\tlui %s,%%hi(%s)\n",get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\taddi %s,%s,%%lo(%s)\n",get_reg_name(regs[tmpreg].id),get_reg_name(regs[tmpreg].id),idname);
            fprintf(output,"\tadd %s,%s,%s\n",get_reg_name(regs[tmpreg].id),get_reg_name(regs[tmpreg].id),get_reg_name(regs[ireg].id));
            fprintf(output,"\tfsw %s,0(%s)\n",get_reg_name(regs[i].id),get_reg_name(regs[tmpreg].id));
        }
    }
    clear_reg(tmpreg);
}

void clean_reg(int i){
    if(regs[i].entry&&regs[i].dirty){
        if(regs[i].entry->offset){
            if(regs[i].entry->offset<=offset){
                store_reg(i, regs[i].entry->offset,-1);
                /*
                if(getTypeOfSymbolTableEntry(regs[i].entry)==INT_TYPE) fprintf(output,"\tsw %s,-%d(fp)\n",get_reg_name(regs[i].id),regs[i].entry->offset);
                else fprintf(output,"\tfsw %s,-%d(fp)\n",get_reg_name(regs[i].id),regs[i].entry->offset);
                */
            }
        }
        else{
            store_global_reg(i,regs[i].entry->name,-1);
        }
    }
    if(regs[i].entry) regs[i].entry->bindreg=-1;
    clear_reg(i);
}

void flush_regs(){
    for(int i=0;i<nreg;i++) clean_reg(i);
}

void clear_expired_regs(){
    for(int i=0;i<nreg;i++){
        if(regs[i].status!=STATUS_UNUSE&&regs[i].entry&&regs[i].entry->offset>offset){
            regs[i].entry->bindreg=-1;
            clear_reg(i);
        }
    }
}

void gen_head(char *name) {
    fprintf(output,"\t.text\n\t.align 1\n\t.globl %s\n\t.type %s, @function\n%s:\n",name,name,name);
    if(strcmp(name, "MAIN") == 0){
        fprintf(output,"\tfmv.w.x %s,%s\n",get_reg_name(32),get_reg_name(0));
    }
    flush_regs();
}

void gen_prologue(char *name){
    fprintf(output,"\tsd ra,-8(sp)\n\tsd fp,-16(sp)\n\taddi fp,sp,-16\n\taddi sp,sp,-16\n");
    if(arsize>2048){
        int reg=get_reg(NULL,VAR_INT); Int tmp; tmp.val=arsize;
        gen_loadimm(reg,tmp); regs[reg].status=STATUS_DONE;
        fprintf(output,"\tsub sp,sp,%s\n",get_reg_name(regs[reg].id));
    }
    else fprintf(output,"\taddi sp,sp,-%d\n",arsize);
}

void gen_epilogue(char *name){
    fprintf(output,"\tld ra,8(fp)\n\taddi sp,fp,16\n\tld fp,0(fp)\n\tjr ra\n\t.size %1$s, .-%1$s\n", name);
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
    for(int i=1;i<=7;i++) initreg(i+32,TYPE_CALLER,VAR_FLOAT);
    for(int i=8;i<=9;i++) initreg(i+32,TYPE_CALLEE,VAR_FLOAT);
    for(int i=18;i<=27;i++) initreg(i+32,TYPE_CALLEE,VAR_FLOAT);
    for(int i=28;i<=31;i++) initreg(i+32,TYPE_CALLER,VAR_FLOAT);
}

void bind_reg(int i,SymbolTableEntry *entry){
    regs[i].entry=entry; entry->bindreg=i;
    if(entry->offset) load_reg(i, entry->offset,-1);
    else load_global_reg(i,entry->name,-1);
}

#define filter(cond) for(int i=0;i<nreg;i++){\
    if(cond){\
        clean_reg(i);\
        if(entry) bind_reg(i,entry);\
        regs[i].status=STATUS_USING;\
        mask|=(1ull<<i);\
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
        if(entry->bindreg >= 0){
            regs[entry->bindreg].status=STATUS_USING;
            return entry->bindreg;
        }
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

void save_caller_regs(){
    for(int i=0;i<nreg;i++){
        if(regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_DONE) clean_reg(i);
        else if(regs[i].entry&&!regs[i].entry->offset&&regs[i].status==STATUS_DONE) clean_reg(i); // global variable side effect
    }
    /* TODO restore using global variable */
    for(int i=0;i<nreg;i++){
        if(regs[i].entry&&!regs[i].entry->offset){
            if(regs[i].dirty){
                store_global_reg(i,regs[i].entry->name,-1);
                regs[i].dirty=0;
            }
        }
        else if(regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_USING){
            if(!regs[i].entry){
                offset+=4; if(offset>arsize) arsize+=4;
                store_reg(i, offset,-1);
                /*
                fprintf(output,"\tsw %s,-%d(fp)\n",get_reg_name(regs[i].id),offset);
                */
            }
            else if(regs[i].dirty){
                store_reg(i,regs[i].entry->offset,-1);
                regs[i].dirty=0;
            }
        }
    }
}

void restore_caller_regs(){
    for(int i=nreg-1;i>=0;i--){
        if(regs[i].entry&&!regs[i].entry->offset){
            load_global_reg(i,regs[i].entry->name,-1);
        }
        if(regs[i].type==TYPE_CALLER&&regs[i].status==STATUS_USING){
            if(regs[i].entry)
                load_reg(i,regs[i].entry->offset,-1);
            else{
                load_reg(i, offset,-1);
                /*
                fprintf(output,"\tlw %s,-%d(fp)\n",get_reg_name(regs[i].id),offset);
                */
                offset-=4;
            }
        }
    }
}

int count_callee_saved(){
    int cnt=0;
    for(int i=0;i<nreg;i++)
        if((mask&(1ull<<i))&&regs[i].type==TYPE_CALLEE) cnt++;
    return cnt;
}

void save_callee_regs(){
    for(int i=0;i<nreg;i++){
        if((mask&(1ull<<i))&&regs[i].type==TYPE_CALLEE){
            offset+=4; if(offset>arsize) arsize+=4;
            store_reg(i,offset,-1);
            /*
            fprintf(output,"\tsw %s,-%d(fp)\n",get_reg_name(regs[i].id),offset);
            */
            clear_reg(i);
        }
    }
}

void restore_callee_regs(){
    for(int i=nreg-1;i>=0;i--){
        if((mask&(1ull<<i))&&regs[i].type==TYPE_CALLEE){
            load_reg(i, offset,-1);
            /*
            fprintf(output,"\tlw %s,-%d(fp)\n",get_reg_name(regs[i].id),offset);
            */
            offset-=4;
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
    assert(type->dataType != ERROR_TYPE);

    switch(declarationNode->semantic_value.declSemanticValue.kind) {
        case TYPE_DECL:
            //genDeclareIdList(declarationNode);
            break;
        case VARIABLE_DECL:
            genDeclareIdList(declarationNode);
            break;
        case FUNCTION_DECL:
            genDeclareFunction(declarationNode);
            break;
        case FUNCTION_PARAMETER_DECL:
            genDeclareIdList(declarationNode);
            break;
        default:
            assert(0);
    }
}
void genDeclareIdList(AST_NODE* declarationNode) {
    if(declarationNode->semantic_value.declSemanticValue.kind==TYPE_DECL) return;
	AST_NODE* typeNode = declarationNode->child;
    TypeDescriptor *tpdes = typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
    AST_NODE* ptr = typeNode->rightSibling;
    while(ptr) {
        char* name = ptr->semantic_value.identifierSemanticValue.identifierName;
        SymbolTableEntry *entry=ptr->semantic_value.identifierSemanticValue.symbolTableEntry;
        if(ptr->semantic_value.identifierSemanticValue.kind==WITH_INIT_ID) {
            // float and int are handled together
            entry->offset=offset+=4;
            genExprRelatedNode(ptr->child);
            int reg_val = ptr->child->regnumber;
            store_reg(reg_val, offset,-1); regs[reg_val].status=STATUS_DONE;
        }
        else if(entry->attribute->attr.typeDescriptor->kind==ARRAY_TYPE_DESCRIPTOR){
            /* TODO multi dimension */
            int length=entry->attribute->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension[0];
            entry->offset=offset+=4*length;
        }
        else entry->offset=offset+=4;
        if(offset > arsize) arsize=offset;
        ptr = ptr->rightSibling;
    }
}
void genGlobalDeclareIdList(AST_NODE* declarationNode)  {
    if(declarationNode->semantic_value.declSemanticValue.kind==TYPE_DECL) return;
    AST_NODE* typeNode = declarationNode->child;
    TypeDescriptor *tpdes = typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;

    AST_NODE* ptr = typeNode->rightSibling;
    while(ptr) {
        char* name = ptr->semantic_value.identifierSemanticValue.identifierName;
        fprintf(output, "\t.globl  %s\n", name);
        SymbolTableEntry *entry=ptr->semantic_value.identifierSemanticValue.symbolTableEntry;
        entry->offset=0;
        int val;
        float f;
        if(ptr->semantic_value.identifierSemanticValue.kind==WITH_INIT_ID) {
            f = ptr->child->semantic_value.const1->const_u.fval;
            val = (typeNode->dataType == INT_TYPE ? ptr->child->semantic_value.const1->const_u.intval : *(unsigned*)&f);
            fprintf(output, "\t.section  .sdata\n\t.align  2\n");
            fprintf(output, "\t.type %s, @object\n", name);
            fprintf(output, "\t.size %s, 4\n", name);
            fprintf(output, "%s:\n", name);
            fprintf(output, "\t.word %d\n", val);
        }
        else if(entry->attribute->attr.typeDescriptor->kind==ARRAY_TYPE_DESCRIPTOR){
            int length=entry->attribute->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension[0];
            fprintf(output, "\t.section  .sbss\n\t.align  2\n");
            fprintf(output, "\t.type %s, @object\n", name);
            fprintf(output, "\t.size %s, %d\n", name,length*4);
            fprintf(output, "%s:\n", name);
            fprintf(output, "\t.zero %d\n",length*4);
        }
        else{
            fprintf(output, "\t.section  .sbss\n\t.align  2\n");
            fprintf(output, "\t.type %s, @object\n", name);
            fprintf(output, "\t.size %s, 4\n", name);
            fprintf(output, "%s:\n", name);
            fprintf(output, "\t.zero 4\n");
        }
        ptr = ptr->rightSibling;
    }
}
void genDeclareFunction(AST_NODE* declarationNode) {
	AST_NODE *ret = declarationNode->child, *name = ret->rightSibling, *paramList=name->rightSibling, *ptr=paramList->child;
    meow=0; offset=0; arsize=0; mask=0;
    int s_gcnt=g_cnt;
    flush_regs();
    symbolTable.currentLevel++;
    while(ptr) {
        genDeclarationNode(ptr);
        ptr=ptr->rightSibling;
    }
    AST_NODE *block = paramList->rightSibling; 
    genBlockNode(block);
    symbolTable.currentLevel--;
    arsize+=count_callee_saved()*4;
    while(arsize&15) arsize+=4;
    flush_regs(); offset=0;
    meow=1; g_cnt=s_gcnt;
    gen_head(name->semantic_value.identifierSemanticValue.identifierName);
    gen_prologue(name->semantic_value.identifierSemanticValue.identifierName);
    symbolTable.currentLevel++;
    save_callee_regs();
    while(ptr) {
        genDeclarationNode(ptr);
        ptr=ptr->rightSibling;
    }

    block = paramList->rightSibling; 
    genBlockNode(block);
    symbolTable.currentLevel--;
    flush_regs();
    fprintf(output,"%s_EXIT_:\n",name->semantic_value.identifierSemanticValue.identifierName);
    restore_callee_regs();
    gen_epilogue(name->semantic_value.identifierSemanticValue.identifierName);
}
void genDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize) {
	// giver TODO nothing
}
void genBlockNode(AST_NODE* blockNode) {
    int _offset = offset;
    symbolTable.currentLevel++;
    AST_NODE* ptr = blockNode->child;
    while(ptr) {
        genGeneralNode(ptr);
        ptr = ptr->rightSibling;
    }
    symbolTable.currentLevel--;
    offset = _offset;
    clear_expired_regs();
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
            if(node->nodeType == VARIABLE_DECL_LIST_NODE) (symbolTable.currentLevel?genDeclarationNode(ptr): genGlobalDeclareIdList(ptr));
            else if(node->nodeType == STMT_LIST_NODE) genStmtNode(ptr);
            else if(node->nodeType == NONEMPTY_ASSIGN_EXPR_LIST_NODE) genAssignOrExpr(ptr);
            else if(node->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE) genExprRelatedNode(ptr);

            assert(ptr->dataType != ERROR_TYPE);
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
        else { 
            if(assignOrExprRelatedNode->nodeType == IDENTIFIER_NODE) genVariableRValue(assignOrExprRelatedNode);
            else if(assignOrExprRelatedNode->nodeType==CONST_VALUE_NODE) genConst(assignOrExprRelatedNode);
            else assert(0);
            int reg0 = get_reg(NULL, VAR_INT);
            if(assignOrExprRelatedNode->dataType == INT_TYPE) {
                fprintf(output, "\tsnez %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[assignOrExprRelatedNode->regnumber].id));
            }
            else {
                fprintf(output, "\tfeq.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[assignOrExprRelatedNode->regnumber].id), get_reg_name(32));
                fprintf(output, "\tseqz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
            }
            regs[assignOrExprRelatedNode->regnumber].status = STATUS_DONE;
            assignOrExprRelatedNode->regnumber = reg0;
        }
    }
}
void genWhileStmt(AST_NODE* whileNode) {
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
    flush_regs();
    fprintf(output, "_WHILE_%d:\n", cnt); 
    flush_regs();
    genAssignOrExpr(condition);
    flush_regs();
    fprintf(output, "\tbeqz %s, _EXIT_%d\n", get_reg_name(regs[condition->regnumber].id), cnt);
    genStmtNode(stmt);
    flush_regs();
    fprintf(output, "\tj _WHILE_%d\n", cnt);
    fprintf(output, "_EXIT_%d:\n", cnt);
    flush_regs();
}
void genForStmt(AST_NODE* forNode) {
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
    flush_regs();
    fprintf(output, "_FOR_%d:\n", cnt);
    flush_regs();
    genGeneralNode(condition);
    flush_regs();
    fprintf(output, "\tbeqz %s, _EXIT_%d\n", get_reg_name(regs[condition->regnumber].id), cnt);
    genStmtNode(stmt); 
    genGeneralNode(loop);
    flush_regs();
    fprintf(output, "\tj _FOR_%d\n", cnt);
    fprintf(output, "_EXIT_%d:\n", cnt);
    flush_regs();
}
void genAssignmentStmt(AST_NODE* assignmentNode) {
    AST_NODE *var_ref = assignmentNode->child, *relop_expr = var_ref->rightSibling;
    genExprRelatedNode(relop_expr);
    genVariableLValue(var_ref);
    if(var_ref->regnumber==-1){
        genArraySubscript(var_ref->child);
        SymbolTableEntry *entry=var_ref->semantic_value.identifierSemanticValue.symbolTableEntry;
        int ireg=var_ref->child->regnumber,rreg=relop_expr->regnumber;
        if(var_ref->dataType == INT_TYPE&&relop_expr->dataType==FLOAT_TYPE) {
            int ttmp = get_reg(NULL, VAR_INT); regs[rreg].status = STATUS_DONE;
            fprintf(output, "\tfcvt.s.w %s, %s\n", get_reg_name(regs[ttmp].id), get_reg_name(regs[rreg].id));
            rreg = ttmp;
        }
        else if(var_ref->dataType==FLOAT_TYPE&&relop_expr->dataType==INT_TYPE){
            int ttmp = get_reg(NULL, VAR_FLOAT); regs[rreg].status = STATUS_DONE;
            fprintf(output, "\tfcvt.s.x %s, %s\n", get_reg_name(regs[ttmp].id), get_reg_name(regs[rreg].id));
            rreg = ttmp;
        }
        if(entry->offset) store_reg(rreg,entry->offset,ireg);
        else store_global_reg(rreg,entry->name,ireg);
        regs[ireg].status=STATUS_DONE; regs[rreg].status=STATUS_DONE;
    }
    else{
        int lreg = var_ref->regnumber, rreg = relop_expr->regnumber;
        if(var_ref->dataType == INT_TYPE) {
            if(relop_expr->dataType == FLOAT_TYPE) {
                int ttmp = get_reg(NULL, VAR_INT); regs[rreg].status = STATUS_DONE;
                fprintf(output, "\tfcvt.s.w %s, %s\n", get_reg_name(regs[ttmp].id), get_reg_name(regs[rreg].id));
                rreg = ttmp;
            }
            fprintf(output, "\tmv %s, %s\n", get_reg_name(regs[lreg].id), get_reg_name(regs[rreg].id));
        }
        else {
            if(relop_expr->dataType == INT_TYPE) {
                int ttmp = get_reg(NULL, VAR_FLOAT); regs[rreg].status = STATUS_DONE;
                fprintf(output, "\tfcvt.s.x %s, %s\n", get_reg_name(regs[ttmp].id), get_reg_name(regs[rreg].id));
                rreg = ttmp;
            }
            fprintf(output, "\tfmv.s %s, %s\n", get_reg_name(regs[lreg].id), get_reg_name(regs[rreg].id));
        }
        regs[var_ref->regnumber].dirty = 1;
        regs[var_ref->regnumber].status=regs[rreg].status=STATUS_DONE;
    }
}
void genIfStmt(AST_NODE* ifNode) {
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
    flush_regs();
    fprintf(output, "_IF_%d:\n", cnt);
    flush_regs();
    genAssignOrExpr(condition);
    flush_regs();
    fprintf(output, "\tbeqz %s, _ELSE_%d\n", get_reg_name(regs[condition->regnumber].id), cnt);
    genStmtNode(if_stmt);
    flush_regs();
    fprintf(output, "\tj _EXIT_%d\n", cnt);
    fprintf(output, "_ELSE_%d:\n", cnt);
    flush_regs();
    genStmtNode(else_stmt);
    flush_regs();
    fprintf(output, "_EXIT_%d:\n", cnt);
    flush_regs();
}

void genWriteFunction(AST_NODE* functionCallNode) {
    genGeneralNode(functionCallNode->child->rightSibling);
	AST_NODE *param=functionCallNode->child->rightSibling->child;
    if(param->dataType==INT_TYPE){
        int reg=param->regnumber;
        fprintf(output,"\tmv a0,%s\n",get_reg_name(regs[reg].id)); regs[reg].status=STATUS_DONE;
        save_caller_regs();
        fprintf(output,"\tjal _write_int\n");
        restore_caller_regs();

    }
    else if(param->dataType==FLOAT_TYPE){
        int reg=param->regnumber;
        fprintf(output,"\tfmv.s fa0,%s\n",get_reg_name(regs[reg].id)); regs[reg].status=STATUS_DONE;
        save_caller_regs();
        fprintf(output,"\tjal _write_float\n");
        restore_caller_regs();
    }
    else if(param->dataType==CONST_STRING_TYPE){
        if(meow){
            char *label=get_label(param->semantic_value.const1->const_u.sc);
            int reg=get_reg(NULL,VAR_INT); regs[reg].status=STATUS_DONE;
            fprintf(output,"\tlui %s,%%hi(%s)\n",get_reg_name(regs[reg].id),label);
            fprintf(output,"\taddi a0,%s,%%lo(%s)\n",get_reg_name(regs[reg].id),label);
            save_caller_regs();
            fprintf(output,"\tcall _write_str\n");
            restore_caller_regs();
        }
    }
    else assert(0);
}
void genFunctionCall(AST_NODE* functionCallNode) {
    AST_NODE *funcIDNode = functionCallNode->child;
    char *name = funcIDNode->semantic_value.identifierSemanticValue.identifierName;
    if(strcmp(name, "write")==0) {
        genWriteFunction(functionCallNode);
    }
    else if(strcmp(name, "read") == 0) {
        save_caller_regs();
        fprintf(output, "\tcall _read_int\n");
        restore_caller_regs();
    }
    else if(strcmp(name, "fread") == 0) {
        save_caller_regs();
        fprintf(output, "\tcall _read_float\n");
        restore_caller_regs();
    }
    else {
        save_caller_regs();
        fprintf(output, "\tcall %s\n", name);
        restore_caller_regs();
    }

    if(functionCallNode->dataType != VOID_TYPE) {
        int reg = get_reg(NULL, (functionCallNode->dataType == INT_TYPE ? VAR_INT : VAR_FLOAT));
        if(functionCallNode->dataType == INT_TYPE) {
            fprintf(output, "\tmv %s, %s\n", get_reg_name(regs[reg].id), get_reg_name(10));
        }
        else {
            fprintf(output, "\tfmv.s %s, %s\n", get_reg_name(regs[reg].id), get_reg_name(10 + 32));
        }
        functionCallNode->regnumber = reg;
    }
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
	// DOTO
}
void genReturnStmt(AST_NODE* returnNode) {
    AST_NODE* pNode=returnNode->parent;
    while(pNode){
        if(pNode->nodeType==DECLARATION_NODE) break;
        pNode=pNode->parent;
    }

    genExprRelatedNode(returnNode->child);
    int reg = returnNode->child->regnumber;
    regs[returnNode->child->regnumber].status=STATUS_DONE;
    if(returnNode->child->dataType == INT_TYPE) {
        fprintf(output, "\tmv %s, %s\n", get_reg_name(10), get_reg_name(regs[reg].id));
    }
    else if(returnNode->child->dataType == FLOAT_TYPE) {
        fprintf(output, "\tfmv.s %s, %s\n", get_reg_name(10 + 32), get_reg_name(regs[reg].id));
    }
    flush_regs();
    fprintf(output, "\tj %s_EXIT_\n", pNode->child->rightSibling->semantic_value.identifierSemanticValue.identifierName);
}
void genConst(AST_NODE* node) {
    // TODO: improve precision
    if(node->dataType == CONST_STRING_TYPE) return;
    reg_var type = node->dataType == INT_TYPE ? VAR_INT : VAR_FLOAT;
    int reg;
    reg = get_reg(NULL, VAR_INT);
    Int tmp;
    if(type == INT_TYPE) {
        tmp.val = (node->nodeType == EXPR_NODE ? node->semantic_value.exprSemanticValue.constEvalValue.iValue : node->semantic_value.const1->const_u.intval);
    }
    else {
        float fval = (node->nodeType == EXPR_NODE ? node->semantic_value.exprSemanticValue.constEvalValue.fValue : node->semantic_value.const1->const_u.fval);
        tmp.fval = fval;
    }
    gen_loadimm(reg,tmp);

    if(type == VAR_FLOAT) {
        int regg = get_reg(NULL, VAR_FLOAT); regs[reg].status=STATUS_DONE;
        fprintf(output, "\tfmv.w.x %s, %s\n", get_reg_name(regs[regg].id), get_reg_name(regs[reg].id));
        reg = regg;
    }
    
    node->regnumber = reg;
}
void genExprNode(AST_NODE* exprNode) {
	if(exprNode->semantic_value.exprSemanticValue.kind == BINARY_OPERATION) {
        AST_NODE *lc = exprNode->child, *rc = lc->rightSibling;
    
        int lconst = lc->nodeType == CONST_VALUE_NODE || (lc->nodeType == EXPR_NODE && lc->semantic_value.exprSemanticValue.isConstEval);
        int rconst = rc->nodeType == CONST_VALUE_NODE || (rc->nodeType == EXPR_NODE && rc->semantic_value.exprSemanticValue.isConstEval);

        genExprRelatedNode(lc);
        genExprRelatedNode(rc);

        reg_var type = exprNode->dataType == INT_TYPE ? VAR_INT : VAR_FLOAT;
        int reg1 = lc->regnumber, reg2 = rc->regnumber;

        if(type == VAR_INT) {
            int reg0 = get_reg(NULL, type);
            exprNode->regnumber = reg0;
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
                    fprintf(output, "\tseqz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_GT:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tsgtz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_LE:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tsgtz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    fprintf(output, "\tseqz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_LT:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tsltz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_NE:
                    fprintf(output, "\tsub %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tsnez %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                case BINARY_OP_OR:
                    fprintf(output, "\tbnez %s, _OR_true_%d\n", get_reg_name(regs[reg1].id), g_cnt);
                    fprintf(output, "\tbeqz %s, _OR_false_%d\n", get_reg_name(regs[reg2].id), g_cnt);
                    fprintf(output, "_OR_true_%d:\n", g_cnt);
                    fprintf(output, "\tli %s, 1\n", get_reg_name(regs[reg0].id));
                    fprintf(output, "j _OR_end_%d\n", g_cnt);
                    fprintf(output, "_OR_false_%d:\n", g_cnt);
                    fprintf(output, "\tli %s, 0\n", get_reg_name(regs[reg0].id));
                    fprintf(output, "_OR_end_%d:\n", g_cnt++);
                    break;
                case BINARY_OP_AND:
                    fprintf(output, "\tbeqz %s, _AND_false_%d\n", get_reg_name(regs[reg1].id), g_cnt);
                    fprintf(output, "\tbeqz %s, _AND_false_%d\n", get_reg_name(regs[reg2].id), g_cnt);
                    fprintf(output, "_AND_true_%d:\n", g_cnt);
                    fprintf(output, "\tli %s, 1\n", get_reg_name(regs[reg0].id));
                    fprintf(output, "j _AND_end_%d\n", g_cnt);
                    fprintf(output, "_AND_false_%d:\n", g_cnt);
                    fprintf(output, "\tli %s, 0\n", get_reg_name(regs[reg0].id));
                    fprintf(output, "_AND_end_%d:\n", g_cnt++);
                    break;
                default:
                    assert(0);
            }
        }
        else {
            int reg0, reg11, reg22;
            switch(exprNode->semantic_value.exprSemanticValue.op.binaryOp) {
                case BINARY_OP_ADD:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_FLOAT);
                    fprintf(output, "\tfadd.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_SUB:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_FLOAT);
                    fprintf(output, "\tfsub.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_MUL:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_FLOAT);
                    fprintf(output, "\tfmul.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_DIV:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_FLOAT);
                    fprintf(output, "\tfdiv.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                // DOTO XXX giver will fix it
                case BINARY_OP_OR:
                    // TODO: float 0 in feq.s
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_INT);
                    reg11 = get_reg(NULL, VAR_INT);
                    reg22 = get_reg(NULL, VAR_INT);
                    fprintf(output, "\tfeq.s %s, %s, %s\n", get_reg_name(regs[reg11].id), get_reg_name(regs[reg1].id), get_reg_name(32));
                    fprintf(output, "\tfeq.s %s, %s, %s\n", get_reg_name(regs[reg22].id), get_reg_name(regs[reg2].id), get_reg_name(32));
                    fprintf(output, "\tbeqz %s, _OR_true_%d\n", get_reg_name(regs[reg11].id), g_cnt);
                    fprintf(output, "\tbnez %s, _OR_false_%d\n", get_reg_name(regs[reg22].id), g_cnt);
                    fprintf(output, "_OR_true_%d:\n", g_cnt);
                    fprintf(output, "\tli %s, 1\n", get_reg_name(regs[reg0].id));
                    fprintf(output, "j _OR_end_%d\n", g_cnt);
                    fprintf(output, "_OR_false_%d:\n", g_cnt);
                    fprintf(output, "\tli %s, 0\n", get_reg_name(regs[reg0].id));
                    fprintf(output, "_OR_end_%d:\n", g_cnt++);
                    regs[reg11].status=STATUS_DONE; regs[reg22].status=STATUS_DONE;
                    break;
                case BINARY_OP_AND:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_INT);
                    reg11 = get_reg(NULL, VAR_INT);
                    reg22 = get_reg(NULL, VAR_INT);
                    fprintf(output, "\tfeq.s %s, %s, %s\n", get_reg_name(regs[reg11].id), get_reg_name(regs[reg1].id), get_reg_name(32));
                    fprintf(output, "\tfeq.s %s, %s, %s\n", get_reg_name(regs[reg22].id), get_reg_name(regs[reg2].id), get_reg_name(32));
                    fprintf(output, "\tbnez %s, _AND_false_%d\n", get_reg_name(regs[reg11].id), g_cnt);
                    fprintf(output, "\tbnez %s, _AND_false_%d\n", get_reg_name(regs[reg22].id), g_cnt);
                    fprintf(output, "_AND_true_%d:\n", g_cnt);
                    fprintf(output, "\tli %s, 1\n", get_reg_name(regs[reg0].id));
                    fprintf(output, "j _AND_end_%d\n", g_cnt);
                    fprintf(output, "_AND_false_%d:\n", g_cnt);
                    fprintf(output, "\tli %s, 0\n", get_reg_name(regs[reg0].id));
                    fprintf(output, "_AND_end_%d:\n", g_cnt++);
                    regs[reg11].status=STATUS_DONE; regs[reg22].status=STATUS_DONE;
                    break;                    
                case BINARY_OP_EQ:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_INT);
                    fprintf(output, "\tfeq.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_GE:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_INT);
                    // reg1 and reg2 are reversed
                    fprintf(output, "\tflt.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg2].id), get_reg_name(regs[reg1].id));
                    break;
                case BINARY_OP_GT:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_INT);
                    // reg1 and reg2 are reversed
                    fprintf(output, "\tfle.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg2].id), get_reg_name(regs[reg1].id));
                    break;
                case BINARY_OP_LE:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_INT);
                    fprintf(output, "\tfle.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_LT:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_INT);
                    fprintf(output, "\tflt.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    break;
                case BINARY_OP_NE:
                    exprNode->regnumber = reg0 = get_reg(NULL, VAR_INT);
                    fprintf(output, "\tfeq.s %s, %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg1].id), get_reg_name(regs[reg2].id));
                    fprintf(output, "\tseqz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id));
                    break;
                default:
                    assert(0);
            }
        }
        regs[reg1].status=STATUS_DONE; regs[reg2].status=STATUS_DONE;
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
            int reg0 = get_reg(NULL, (op == UNARY_OP_NEGATIVE ? type : VAR_INT));
            
            if(type == VAR_INT) {
                if(op == UNARY_OP_NEGATIVE) {
                    fprintf(output, "\tneg %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg].id));
                }
                else {
                    fprintf(output, "\tseqz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg].id)); // UNARY_OP_LOGICAL_NEGATION
                }
            }
            else {
                if(op == UNARY_OP_NEGATIVE) {
                    fprintf(output, "\tfneg.s %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg].id));
                }
                else {
                    fprintf(output, "\tfeq.s %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg].id));
                    fprintf(output, "\tseqz %s, %s\n", get_reg_name(regs[reg0].id), get_reg_name(regs[reg0].id)); // UNARY_OP_LOGICAL_NEGATION
                }
            }

            exprNode->regnumber = reg0;
        }
        regs[reg].status=STATUS_DONE;
    }
}
void genArraySubscript(AST_NODE* ptr){
    /* TODO multi dimension */
    genExprRelatedNode(ptr); 
    int ireg=get_reg(NULL,VAR_INT); regs[ptr->regnumber].status=STATUS_DONE;
    fprintf(output,"\tslli %s,%s,2\n",get_reg_name(regs[ireg].id),get_reg_name(regs[ptr->regnumber].id));
    ptr->regnumber=ireg;
}
void genVariableLValue(AST_NODE* idNode) {
    if(idNode->semantic_value.identifierSemanticValue.kind==ARRAY_ID) idNode->regnumber=-1;
    else genVariableRValue(idNode);
}
void genVariableRValue(AST_NODE* idNode) {
	SymbolTableEntry *entry=idNode->semantic_value.identifierSemanticValue.symbolTableEntry;
    TypeDescriptor* tpdes=idNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
    if(idNode->semantic_value.identifierSemanticValue.kind==ARRAY_ID){
        /* giver TODO */
        genArraySubscript(idNode->child);
        int ireg=idNode->child->regnumber; 
        idNode->regnumber=get_reg(NULL,tpdes->properties.arrayProperties.elementType==INT_TYPE?VAR_INT:VAR_FLOAT);
        if(entry->offset) load_reg(idNode->regnumber,entry->offset,ireg);
        else load_global_reg(idNode->regnumber,entry->name,ireg);
        regs[ireg].status=STATUS_DONE;
    }
    else{
        DATA_TYPE tp=tpdes->properties.dataType;
        idNode->regnumber=get_reg(entry,tp==INT_TYPE?VAR_INT:VAR_FLOAT);
    }
}

void codegen(AST_NODE *root) {
    initregs();
    output = fopen("output.s", "w");
    fprintf(output,"\t.section .sdata,\"aw\"\n\t.section .sbss,\"aw\",@nobits\n");
    genProgramNode(root);
    fprintf(output,"\t.section .rodata\n");
    while(str_head){
        gbl_str *cur=str_head; str_head=str_head->next;
        fprintf(output,"\t.align 3\n");
        fprintf(output,"%s:\n",cur->label);
        cur->str[strlen(cur->str)-1]=0;
        fprintf(output,"\t.string \"%s\\000\"\n",cur->str+1);
        free(cur);
    }
    //fprintf(output,"\t.indent \"GCC: (GNU) 10.2.0\"\n\t.section .note.GNU-stack,\"\",@progbits\n");
    fclose(output);
}

