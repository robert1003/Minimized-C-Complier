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
void processProgramNode(AST_NODE *programNode);
void processDeclarationNode(AST_NODE* declarationNode);
void declareIdList(AST_NODE* typeNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize);
void declareFunction(AST_NODE* returnTypeNode);
void processDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize);
void processTypeNode(AST_NODE* typeNode);
void processBlockNode(AST_NODE* blockNode);
void processStmtNode(AST_NODE* stmtNode);
void processGeneralNode(AST_NODE *node);
void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode);
void checkWhileStmt(AST_NODE* whileNode);
void checkForStmt(AST_NODE* forNode);
void checkAssignmentStmt(AST_NODE* assignmentNode);
void checkIfStmt(AST_NODE* ifNode);
void checkWriteFunction(AST_NODE* functionCallNode);
void checkFunctionCall(AST_NODE* functionCallNode);
void processExprRelatedNode(AST_NODE* exprRelatedNode);
void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter, AST_NODE* funcIDNode);
void checkReturnStmt(AST_NODE* returnNode);
void processExprNode(AST_NODE* exprNode);
void processVariableLValue(AST_NODE* idNode);
void processVariableRValue(AST_NODE* idNode);
void processConstValueNode(AST_NODE* constValueNode);
void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue);
int evaluateExprValue(AST_NODE* exprNode);

extern SymbolTable symbolTable;

typedef enum ErrorMsgKind {
    SYMBOL_IS_NOT_TYPE,
    SYMBOL_REDECLARE,
    SYMBOL_CONFLICT,
    SYMBOL_UNDECLARED,
    FUNCTION_REDECLARE,
    NOT_FUNCTION_NAME,
    TRY_TO_INIT_ARRAY,
    PASS_FUNCTION_TO_SCALAR,
    EXCESSIVE_ARRAY_DIM_DECLARATION,
    RETURN_ARRAY,
    VOID_VARIABLE,
    TYPEDEF_VOID_ARRAY,
    PARAMETER_TYPE_UNMATCH,
    TOO_FEW_ARGUMENTS,
    TOO_MANY_ARGUMENTS,
    INCOMPATIBLE_ARRAY_DIMENSION,
    NOT_ASSIGNABLE,
    NOT_ARRAY,
    IS_TYPE_NOT_VARIABLE,
    IS_FUNCTION_NOT_VARIABLE,
    STRING_OPERATION,
    ARRAY_SIZE_NOT_INT,
    ARRAY_SIZE_NEGATIVE,
    ARRAY_SUBSCRIPT_NOT_INT,
    PASS_ARRAY_TO_SCALAR,
    PASS_SCALAR_TO_ARRAY,
    PASS_VOID_TO_SCALAR,
    UNARY_VOID,
    FUNCTION_NOT_RVALUE,
    INIT_VAL_NOT_CONST,
    ARRAY_SIZE_NON_CONST
} ErrorMsgKind;

typedef enum WarningMsgKind {
    DIVIDE_BY_ZERO,
    NON_VOID_RETURN_VOID,
    VOID_RETURN_NON_VOID
} WarningMsgKind;

char witbuf[15];
char* wit(int n){
    int t=13;
    while(n){
        witbuf[t--]=n%10+'0';
        n/=10;
    }
    return witbuf+t+1;
}

void getDimensionOfArray(ArrayProperties *arp,char *buf){
    int dim=arp->dimension,*ptr=arp->sizeInEachDimension;
    for(int i=0;i<dim;i++){
        if(i==0) strcpy(buf,"(*)"),buf+=3;
        else{
            *buf++='[';
            char *tmpdim=wit(*ptr);
            strcpy(buf,tmpdim); buf+=strlen(tmpdim);
            *buf++=']';
        }
    }
    *buf++=0;
}

char buf1[2000],buf2[2000],*buf=buf1,*pbuf=buf2;
char* getNameOfDataType(DATA_TYPE type) {
    char *tmp=buf; buf=pbuf; pbuf=tmp;
    switch(type) {
        case INT_TYPE:
            return "int";
            break;
        case FLOAT_TYPE:
            return "float";
            break;
        case VOID_TYPE:
            return "void";
            break;
        case INT_PTR_TYPE:
            return "int (*)";
            break;
        case FLOAT_PTR_TYPE:
            return "float (*)";
            break;
        default:
            printf("undefined %d\n", type);
            return "undefined";
    }
}

DATA_TYPE getTypeOfSymbolTableEntry(SymbolTableEntry* entry) {
    return entry->attribute->attr.typeDescriptor->properties.dataType;
}

void printErrorMsgSpecial(AST_NODE* node1, char* name2, ErrorMsgKind errorMsgKind) {
    g_anyErrorOccur = 1;
    printf("\033[01;31mError\033[m found in line %d: ", node1->linenumber);
    printf("\033[01;31m");
//#define printf fprintf(stderr,"print error in line %d\n",__LINE__),printf("\033[01;31m"),printf
    switch(errorMsgKind) {
        case PASS_ARRAY_TO_SCALAR:
            printf("invalid conversion from \'%s\' to \'%s\'\n", \
                getNameOfDataType(node1->dataType), name2);
            break;
        case PASS_SCALAR_TO_ARRAY:
            printf("invalid conversion from \'%s\' to \'%s\'\n", \
                getNameOfDataType(node1->dataType), name2);
            break;
        case PASS_FUNCTION_TO_SCALAR:
            printf("invalid conversion from \'%s (*)()\' to \'%s\'\n", \
                getNameOfDataType(retrieveSymbol(node1->semantic_value.identifierSemanticValue.identifierName)->attribute->attr.functionSignature->returnType), name2);
            break;
        default:
            printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
            break;
    }
#undef printf
    printf("\033[m");
    //fprintf(stderr,"\033[m");
}

void printWarningMsg(AST_NODE* node, WarningMsgKind warningMsgKind) {
    g_anyErrorOccur = 1;
    printf("\033[01;35mWarning\033[m found in line %d: ", node->linenumber);
    printf("\033[01;35m");
    switch(warningMsgKind) {
        case DIVIDE_BY_ZERO:
            printf("division by zero\n");
            break;
        case NON_VOID_RETURN_VOID:
            printf("'return' with no value, in function returning non-void\n");
            break;
        case VOID_RETURN_NON_VOID:
            printf("'return' with a value, in function returning void\n");
            break;
        default:
            printf("Unhandled case in void printWarningMsg(AST_NODE* node, WarningMsgKind warningMsgKind)\n");
            break;
    }
    printf("\033[m");
}

void printErrorMsg(AST_NODE* node, ErrorMsgKind errorMsgKind) {
    g_anyErrorOccur = 1;
    printf("\033[01;31mError\033[m found in line %d: ", node->linenumber);
    printf("\033[01;31m");
/* TODO remove debug message */
//#define printf fprintf(stderr,"print error in line %d\n",__LINE__),printf("\033[01;31m"),printf
    switch(errorMsgKind) {
        case SYMBOL_IS_NOT_TYPE:
            printf("unknown type name '%s'\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case SYMBOL_REDECLARE:
            printf("redeclaration of '%s' with no linkage\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case SYMBOL_CONFLICT:
            printf("conflicting types for '%s'\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case FUNCTION_REDECLARE:
            printf("redefinition of '%s'\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case SYMBOL_UNDECLARED:
            printf("'%s' was not declared in this scope\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case NOT_FUNCTION_NAME:
            printf("called object '%s' is not a function or function pointer\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case TRY_TO_INIT_ARRAY:
            printf("array initialization is not supported\n");
            break;
        case EXCESSIVE_ARRAY_DIM_DECLARATION:
            printf("excessive array dimention declaration\n");
            break;
        case IS_FUNCTION_NOT_VARIABLE:
            printf("lvalue required as left operand of assignment\n");
            break;
        case VOID_VARIABLE:
            printf("variable or field '%s' declared void\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case TYPEDEF_VOID_ARRAY:
            printf("declaration of '%s' as array of voids\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case PARAMETER_TYPE_UNMATCH:
            printf("incompatible type for arguments of '%s'\n", (node->nodeType==CONST_VALUE_NODE?node->semantic_value.const1->const_u.sc:node->semantic_value.identifierSemanticValue.identifierName));
            break;
        case TOO_FEW_ARGUMENTS:
            printf("too few arguments to function '%s'\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case TOO_MANY_ARGUMENTS:
            printf("too many arguments to function '%s'\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case INCOMPATIBLE_ARRAY_DIMENSION:
            printf("subscripted value is neither array nor pointer nor vector\n");
            break;
        case NOT_ASSIGNABLE:
            printf("assignment to expression with array type\n");
            break;
        case NOT_ARRAY:
            printf("subscripted value is neither array nor pointer nor vector\n");
            break;
        case IS_TYPE_NOT_VARIABLE: // from gcc
            printf("expected expression before '%s'\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case STRING_OPERATION: // me
            printf("string operations are not supported\n");
            break;
        case ARRAY_SIZE_NOT_INT: // me
            printf("size of array \'%s\' is not an integer\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case ARRAY_SIZE_NEGATIVE:
            printf("size of array \'%s\' is negative\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case ARRAY_SUBSCRIPT_NOT_INT:
            printf("array subscript is not an integer\n");
            break;
        case PASS_VOID_TO_SCALAR:
            printf("void value not ignored as it ought to be\n");
            break;
        case UNARY_VOID:
            printf("invalid use of void expression\n");
            break;
        case FUNCTION_NOT_RVALUE:
            printf("function name cannot be used as rvalue\n");
            break;
        case RETURN_ARRAY:
            printf("'%s' declared as function returning an array\n", node->semantic_value.identifierSemanticValue.identifierName);
            break;
        case INIT_VAL_NOT_CONST:
            printf("initializer element is not constant\n");
            break;
        case ARRAY_SIZE_NON_CONST:
            printf("array size is not a constant expression\n");
            break;
        default:
            printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
            break;
    }
    printf("\033[m");
    //fprintf(stderr,"\033[m");
//#undef printf
}
/* TODO debug message */
//#define printErrorMsg fprintf(stderr,"error line: %d\n",__LINE__),printErrorMsg


void semanticAnalysis(AST_NODE *root) {
    processProgramNode(root);
}


DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2) {
    if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE) {
        return FLOAT_TYPE;
    } else {
        return INT_TYPE;
    }
}


void processProgramNode(AST_NODE *programNode) {
    AST_NODE* ptr = programNode->child;
    while(ptr) {
        if(ptr->nodeType == VARIABLE_DECL_LIST_NODE) processGeneralNode(ptr);
        else processDeclarationNode(ptr);

        if(ptr->dataType == ERROR_TYPE) programNode->dataType = ERROR_TYPE;
        ptr = ptr->rightSibling;
    }
}

void processDeclarationNode(AST_NODE* declarationNode) {
    AST_NODE* type = declarationNode->child;
    processTypeNode(type);
    if(type->dataType == ERROR_TYPE) { declarationNode->dataType = ERROR_TYPE; return; }

    switch(declarationNode->semantic_value.declSemanticValue.kind) {
        case TYPE_DECL:
            declareIdList(declarationNode, TYPE_ATTRIBUTE, 0);
            break;
        case VARIABLE_DECL:
            declareIdList(declarationNode, VARIABLE_ATTRIBUTE, 0);
            break;
        case FUNCTION_DECL:
            declareFunction(declarationNode);
            break;
        case FUNCTION_PARAMETER_DECL:
            declareIdList(declarationNode, VARIABLE_ATTRIBUTE, 1);
            break;
        default:
            assert(0);
    }
}

void processTypeNode(AST_NODE* idNodeAsType) {
    SymbolTableEntry* entry = retrieveSymbol(idNodeAsType->semantic_value.identifierSemanticValue.identifierName);
    if(!entry || entry->attribute->attributeKind != TYPE_DECL) {
        printErrorMsg(idNodeAsType, SYMBOL_IS_NOT_TYPE);
        idNodeAsType->dataType = ERROR_TYPE;
        return;
    }
    idNodeAsType->semantic_value.identifierSemanticValue.symbolTableEntry=entry;
    TypeDescriptor *tmp=entry->attribute->attr.typeDescriptor;
    idNodeAsType->dataType=(tmp->kind==SCALAR_TYPE_DESCRIPTOR?tmp->properties.dataType:tmp->properties.arrayProperties.elementType);
}


void declareIdList(AST_NODE* declarationNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize) {
    AST_NODE* typeNode=declarationNode->child;
    TypeDescriptor *tpdes=typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
    if(isVariableOrTypeAttribute==VARIABLE_ATTRIBUTE&&tpdes->kind==SCALAR_TYPE_DESCRIPTOR&&tpdes->properties.dataType==VOID_TYPE){
        printErrorMsg(typeNode,VOID_VARIABLE);
        declarationNode->dataType=ERROR_TYPE;
        return;
    }
    AST_NODE* ptr=typeNode->rightSibling;
    while(ptr){
        if(declaredLocally(ptr->semantic_value.identifierSemanticValue.identifierName))
        {
            if(getTypeOfSymbolTableEntry(retrieveSymbol(ptr->semantic_value.identifierSemanticValue.identifierName)) == tpdes->properties.dataType) printErrorMsg(ptr, SYMBOL_REDECLARE);
            else printErrorMsg(ptr, SYMBOL_CONFLICT);
            ptr->dataType=ERROR_TYPE;
            declarationNode->dataType=ERROR_TYPE;
        }
        else{
            SymbolAttribute* attr=(SymbolAttribute*)malloc(sizeof(SymbolAttribute));
            attr->attributeKind=isVariableOrTypeAttribute;
            switch(ptr->semantic_value.identifierSemanticValue.kind){
                case NORMAL_ID:
                    attr->attr.typeDescriptor=tpdes;
                    break;
                case WITH_INIT_ID:
                    attr->attr.typeDescriptor=tpdes;
                    processExprRelatedNode(ptr->child);
                    if(ptr->child->dataType == ERROR_TYPE) {
                        ptr->dataType=ERROR_TYPE;
                    }
                    else if(attr->attr.typeDescriptor->kind==ARRAY_TYPE_DESCRIPTOR){
                        printErrorMsg(ptr,TRY_TO_INIT_ARRAY);
                        ptr->dataType=ERROR_TYPE;
                    }
                    else if(ptr->child->dataType == INT_PTR_TYPE || ptr->child->dataType == FLOAT_PTR_TYPE) {
                        printErrorMsgSpecial(ptr->child, getNameOfDataType(tpdes->properties.dataType), PASS_ARRAY_TO_SCALAR);
                        ptr->dataType=ERROR_TYPE;
                    }
                    else if(ptr->child->nodeType == IDENTIFIER_NODE) {
                        SymbolTableEntry* entry = retrieveSymbol(ptr->child->semantic_value.identifierSemanticValue.identifierName);
                        if(entry->attribute->attributeKind == FUNCTION_SIGNATURE) {
                            printErrorMsgSpecial(ptr->child, getNameOfDataType(tpdes->properties.dataType), PASS_FUNCTION_TO_SCALAR);
                            ptr->dataType=ERROR_TYPE;
                        }
                    }
                    else if(ptr->child->nodeType == STMT_NODE) {
                        assert(ptr->child->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT);
                        SymbolTableEntry* entry = retrieveSymbol(ptr->child->child->semantic_value.identifierSemanticValue.identifierName);
                        if(entry->attribute->attr.functionSignature->returnType == VOID_TYPE) {
                            printErrorMsg(ptr->child, PASS_VOID_TO_SCALAR);
                            ptr->dataType=ERROR_TYPE;
                        }
                    }
                    
                    if(symbolTable.currentLevel == 0) {
                        if(!(ptr->child->nodeType == CONST_VALUE_NODE || (ptr->child->nodeType == EXPR_NODE && ptr->child->semantic_value.exprSemanticValue.isConstEval))) {
                            printErrorMsg(ptr->child, INIT_VAL_NOT_CONST);
                            ptr->dataType=ERROR_TYPE;
                        }
                    }

                    break;
                case ARRAY_ID:
                    if(isVariableOrTypeAttribute==TYPE_ATTRIBUTE&&tpdes->kind==SCALAR_TYPE_DESCRIPTOR&&tpdes->properties.dataType==VOID_TYPE){
                        printErrorMsg(ptr,TYPEDEF_VOID_ARRAY);
                        ptr->dataType=ERROR_TYPE;
                        break;
                    }
                    attr->attr.typeDescriptor=(TypeDescriptor*)malloc(sizeof(TypeDescriptor));
                    processDeclDimList(ptr,attr->attr.typeDescriptor,ignoreArrayFirstDimSize);
                    TypeDescriptor *tmp=tpdes;
                    if(ptr->dataType==ERROR_TYPE)
                        free(attr->attr.typeDescriptor);
                    else if(tmp->kind==SCALAR_TYPE_DESCRIPTOR)
                        attr->attr.typeDescriptor->properties.arrayProperties.elementType=tmp->properties.dataType;
                    else if(tmp->kind==ARRAY_TYPE_DESCRIPTOR){
                        int tpdim=tmp->properties.arrayProperties.dimension;
                        int iddim=attr->attr.typeDescriptor->properties.arrayProperties.dimension;
                        if(tpdim+iddim>MAX_ARRAY_DIMENSION){
                            printErrorMsg(ptr,EXCESSIVE_ARRAY_DIM_DECLARATION);
                            free(attr->attr.typeDescriptor);
                            ptr->dataType=ERROR_TYPE;
                        }
                        else{
                            attr->attr.typeDescriptor->properties.arrayProperties.elementType=tmp->properties.arrayProperties.elementType;
                            attr->attr.typeDescriptor->properties.arrayProperties.dimension=tpdim+iddim;
                            memcpy(attr->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension+iddim,tmp->properties.arrayProperties.sizeInEachDimension,tpdim*sizeof(int));
                        }
                    }                    
                    break;
                default:
                    assert(0);
            }
            if(ptr->dataType==ERROR_TYPE){
                free(attr);
                declarationNode->dataType=ERROR_TYPE;
            }
            else
                ptr->semantic_value.identifierSemanticValue.symbolTableEntry=enterSymbol(ptr->semantic_value.identifierSemanticValue.identifierName,attr);
        }
        ptr=ptr->rightSibling;
    }    
}

void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode) {
    if(assignOrExprRelatedNode->nodeType == EXPR_NODE) processExprNode(assignOrExprRelatedNode);
    else {
        if(assignOrExprRelatedNode->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT) checkAssignmentStmt(assignOrExprRelatedNode);
        else if(assignOrExprRelatedNode->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT) checkFunctionCall(assignOrExprRelatedNode);
    }
}

void checkWhileStmt(AST_NODE* whileNode) {
    AST_NODE* condition = whileNode->child; checkAssignOrExpr(condition);
    if(condition->dataType == VOID_TYPE) {
        condition->dataType = ERROR_TYPE;
        printErrorMsg(condition, PASS_VOID_TO_SCALAR);
    }
    AST_NODE* stmt = condition->rightSibling; processStmtNode(stmt);
}

void checkForStmt(AST_NODE* forNode) {
    AST_NODE* assign = forNode->child; processGeneralNode(assign);
    AST_NODE* condition = assign->rightSibling; processGeneralNode(condition);
    if(condition->dataType == VOID_TYPE) {
        condition->dataType = ERROR_TYPE;
        printErrorMsg(condition, PASS_VOID_TO_SCALAR);
    }
    AST_NODE* loop = condition->rightSibling; processGeneralNode(loop);
    AST_NODE* stmt = loop->rightSibling; processStmtNode(stmt);
}

void checkAssignmentStmt(AST_NODE* assignmentNode) {
    AST_NODE* var_ref = assignmentNode->child; processVariableLValue(var_ref);
    AST_NODE* relop_expr = var_ref->rightSibling; processExprRelatedNode(relop_expr);
    if(var_ref->dataType == ERROR_TYPE || relop_expr->dataType == ERROR_TYPE) assignmentNode->dataType = ERROR_TYPE;
    else if(relop_expr->dataType == INT_PTR_TYPE || relop_expr->dataType == FLOAT_PTR_TYPE) {
        assignmentNode->dataType = ERROR_TYPE;
        printErrorMsg(assignmentNode, NOT_ASSIGNABLE);
    }
    else if(relop_expr->dataType == CONST_STRING_TYPE) {
        assignmentNode->dataType = ERROR_TYPE;
        printErrorMsg(assignmentNode, STRING_OPERATION);
    }
    else if(relop_expr->dataType == VOID_TYPE) {
        assignmentNode->dataType = ERROR_TYPE;
        printErrorMsg(assignmentNode, PASS_VOID_TO_SCALAR);
    }
    else assignmentNode->dataType = getBiggerType(var_ref->dataType, relop_expr->dataType);
}

void checkIfStmt(AST_NODE* ifNode) {
    AST_NODE* condition = ifNode->child; checkAssignOrExpr(condition);
    if(condition->dataType == VOID_TYPE) {
        condition->dataType = ERROR_TYPE;
        printErrorMsg(condition, PASS_VOID_TO_SCALAR);
    }
    AST_NODE* stmt1 = condition->rightSibling; processStmtNode(stmt1); // if
    AST_NODE* stmt2 = stmt1->rightSibling; processStmtNode(stmt2); // else
}

void checkWriteFunction(AST_NODE* functionCallNode) {
    AST_NODE* funcIDNode=functionCallNode->child;
    AST_NODE* paramList=funcIDNode->rightSibling;
    processGeneralNode(paramList);
    AST_NODE* param=paramList->child;
    int paramNum=0;
    while(param){
        paramNum++;
        if(param->dataType!=INT_TYPE&&param->dataType!=FLOAT_TYPE&&param->dataType!=CONST_STRING_TYPE){
            if(param->dataType!=ERROR_TYPE) printErrorMsg(param,PARAMETER_TYPE_UNMATCH);
            functionCallNode->dataType=ERROR_TYPE;
        }
        param=param->rightSibling;
    }
    if(paramNum==1&&functionCallNode->dataType!=ERROR_TYPE) functionCallNode->dataType=VOID_TYPE;
    else if(functionCallNode->dataType!=ERROR_TYPE){
        printErrorMsg(funcIDNode,(paramNum>1?TOO_MANY_ARGUMENTS:TOO_FEW_ARGUMENTS));
        functionCallNode->dataType=ERROR_TYPE;
    }
}

void checkFunctionCall(AST_NODE* functionCallNode) {
    AST_NODE* funcIDNode=functionCallNode->child;
    if(strcmp(funcIDNode->semantic_value.identifierSemanticValue.identifierName,"write")==0){
        checkWriteFunction(functionCallNode);
        return;
    }
    SymbolTableEntry* entry=retrieveSymbol(funcIDNode->semantic_value.identifierSemanticValue.identifierName);
    funcIDNode->semantic_value.identifierSemanticValue.symbolTableEntry=entry;
    if(!entry||entry->attribute->attributeKind!=FUNCTION_SIGNATURE){
        printErrorMsg(funcIDNode,(!entry?SYMBOL_UNDECLARED:NOT_FUNCTION_NAME));
        functionCallNode->dataType=funcIDNode->dataType=ERROR_TYPE;
        return;
    }
    AST_NODE* paramList=funcIDNode->rightSibling;
    processGeneralNode(paramList);
    AST_NODE* param=paramList->child;
    Parameter* defparam=entry->attribute->attr.functionSignature->parameterList;
    while(param&&defparam){
        if(param->dataType==ERROR_TYPE) functionCallNode->dataType=ERROR_TYPE;
        else{
            checkParameterPassing(defparam,param,funcIDNode);
            if(param->dataType==ERROR_TYPE) functionCallNode->dataType=ERROR_TYPE;
        }
        param=param->rightSibling;
        defparam=defparam->next;
    }
    if(param||defparam){
        printErrorMsg(funcIDNode,(param?TOO_MANY_ARGUMENTS:TOO_FEW_ARGUMENTS));
        functionCallNode->dataType=ERROR_TYPE;
    }
    else if(functionCallNode->dataType!=ERROR_TYPE)
        functionCallNode->dataType=entry->attribute->attr.functionSignature->returnType;
}

void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter, AST_NODE* funcIDNode) {
    int isptr = (actualParameter->dataType == INT_PTR_TYPE || actualParameter->dataType == FLOAT_PTR_TYPE);
    if(formalParameter->type->kind == ARRAY_TYPE_DESCRIPTOR && !isptr) {
        printErrorMsgSpecial(actualParameter, getNameOfDataType(formalParameter->type->properties.arrayProperties.elementType==INT_TYPE?INT_PTR_TYPE:FLOAT_PTR_TYPE), PASS_SCALAR_TO_ARRAY);
        actualParameter->dataType = ERROR_TYPE;
    }
    else if(formalParameter->type->kind == SCALAR_TYPE_DESCRIPTOR && isptr) {
        printErrorMsgSpecial(actualParameter, getNameOfDataType(formalParameter->type->properties.arrayProperties.elementType), PASS_ARRAY_TO_SCALAR);
        actualParameter->dataType = ERROR_TYPE;
    }
    else if(actualParameter->dataType == CONST_STRING_TYPE) {
        actualParameter->dataType = ERROR_TYPE;
        printErrorMsg(funcIDNode, PARAMETER_TYPE_UNMATCH);
    }
}

void processExprRelatedNode(AST_NODE* exprRelatedNode) {
    switch(exprRelatedNode->nodeType) {
        case EXPR_NODE:
            processExprNode(exprRelatedNode);
            break;
        case STMT_NODE:
            checkFunctionCall(exprRelatedNode);
            break;
        case CONST_VALUE_NODE:
            processConstValueNode(exprRelatedNode);
            break;
        case IDENTIFIER_NODE:
            processVariableRValue(exprRelatedNode);
            break;
        default:
            break;
    }    
}

void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue) {
    if(exprOrConstNode->nodeType == CONST_VALUE_NODE && exprOrConstNode->dataType == INT_TYPE) *iValue = exprOrConstNode->semantic_value.const1->const_u.intval;
    else if(exprOrConstNode->nodeType == CONST_VALUE_NODE && exprOrConstNode->dataType == FLOAT_TYPE) *fValue = exprOrConstNode->semantic_value.const1->const_u.fval;
    else if(exprOrConstNode->nodeType == EXPR_NODE && exprOrConstNode->dataType == INT_TYPE) *iValue = exprOrConstNode->semantic_value.exprSemanticValue.constEvalValue.iValue;
    else if(exprOrConstNode->nodeType == EXPR_NODE && exprOrConstNode->dataType == FLOAT_TYPE) *fValue = exprOrConstNode->semantic_value.exprSemanticValue.constEvalValue.fValue;
    else assert(0);
}

int evaluateExprValue(AST_NODE* exprNode) {
    if(exprNode->semantic_value.exprSemanticValue.kind == BINARY_OPERATION) {
        AST_NODE *lc = exprNode->child, *rc = lc->rightSibling;
        if(lc->dataType == INT_TYPE && rc->dataType == INT_TYPE) {
            exprNode->dataType = INT_TYPE;
            int lv, rv; getExprOrConstValue(lc, &lv, NULL); getExprOrConstValue(rc, &rv, NULL);
            if(exprNode->semantic_value.exprSemanticValue.op.binaryOp==BINARY_OP_DIV&&rv==0){
                printWarningMsg(exprNode,DIVIDE_BY_ZERO);
                return 0;
            }
            int vals[]={lv+rv,lv-rv,lv*rv,lv/rv,lv==rv,lv>=rv,lv<=rv,lv!=rv,lv>rv,lv<rv,lv&&rv,lv||rv};
            exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue=vals[exprNode->semantic_value.exprSemanticValue.op.binaryOp];
        }
        else {
            exprNode->dataType = FLOAT_TYPE;
            float lv, rv; getExprOrConstValue(lc, NULL, &lv); getExprOrConstValue(rc, NULL, &rv);
            if(exprNode->semantic_value.exprSemanticValue.op.binaryOp==BINARY_OP_DIV&&rv==0){
                printWarningMsg(exprNode,DIVIDE_BY_ZERO);
                return 0;
            }
            float vals[]={lv+rv,lv-rv,lv*rv,lv/rv,lv==rv,lv>=rv,lv<=rv,lv!=rv,lv>rv,lv<rv,lv&&rv,lv||rv};
            exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue=vals[exprNode->semantic_value.exprSemanticValue.op.binaryOp];
        }
    }
    else {
        AST_NODE* rc = exprNode->child;
        if(rc->dataType == INT_TYPE) {
            exprNode->dataType = INT_TYPE;
            int rv; getExprOrConstValue(rc, &rv, NULL);
            switch(exprNode->semantic_value.exprSemanticValue.op.unaryOp) {
                case UNARY_OP_POSITIVE:
                    exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = +rv;
                    break;
                case UNARY_OP_NEGATIVE:
                    exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = -rv;
                    break;
                case UNARY_OP_LOGICAL_NEGATION:
                    exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = !rv;
                    break;
                default:
                    printf("unhandled unary operator");                
            }
        }
        else {
            exprNode->dataType = FLOAT_TYPE;
            float rv; getExprOrConstValue(rc, NULL, &rv);
            switch(exprNode->semantic_value.exprSemanticValue.op.unaryOp) {
                case UNARY_OP_POSITIVE:
                    exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = +rv;
                    break;
                case UNARY_OP_NEGATIVE:
                    exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = -rv;
                    break;
                case UNARY_OP_LOGICAL_NEGATION:
                    exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = !rv;
                    break;
                default:
                    printf("unhandled unary operator");
            }
        }
    }
    return 1;
}

void processExprNode(AST_NODE* exprNode) {
    if(exprNode->semantic_value.exprSemanticValue.kind == BINARY_OPERATION) {
        AST_NODE *lc = exprNode->child, *rc = lc->rightSibling;
        processExprRelatedNode(lc); processExprRelatedNode(rc);
        if(lc->dataType == INT_PTR_TYPE || lc->dataType == FLOAT_PTR_TYPE || rc->dataType == INT_PTR_TYPE || rc->dataType == FLOAT_PTR_TYPE) {
            exprNode->dataType = ERROR_TYPE;
            printErrorMsg(exprNode, NOT_ASSIGNABLE);
        }
        else if(lc->dataType == CONST_STRING_TYPE || rc->dataType == CONST_STRING_TYPE) {
            exprNode->dataType = ERROR_TYPE;
            printErrorMsg(exprNode, STRING_OPERATION);
        }
        else if(lc->dataType == ERROR_TYPE || rc->dataType == ERROR_TYPE) exprNode->dataType = ERROR_TYPE;
        else if(lc->dataType==VOID_TYPE||rc->dataType==VOID_TYPE){
            printErrorMsg(exprNode,PASS_VOID_TO_SCALAR);
            exprNode->dataType=ERROR_TYPE;
        }
        else {
            exprNode->dataType = getBiggerType(lc->dataType, rc->dataType);
            if((lc->nodeType == CONST_VALUE_NODE || (lc->nodeType == EXPR_NODE && lc->semantic_value.exprSemanticValue.isConstEval)) && \
                (rc->nodeType == CONST_VALUE_NODE || (rc->nodeType == EXPR_NODE && rc->semantic_value.exprSemanticValue.isConstEval))) {
                    exprNode->semantic_value.exprSemanticValue.isConstEval = evaluateExprValue(exprNode);
                }
        }
    }
    else {
        AST_NODE *rc = exprNode->child; processExprRelatedNode(rc);
        if(rc->dataType == INT_PTR_TYPE || rc->dataType == FLOAT_PTR_TYPE) {
            exprNode->dataType = ERROR_TYPE;
            printErrorMsg(exprNode, NOT_ASSIGNABLE);
        }
        else if(rc->dataType == CONST_STRING_TYPE) {
            exprNode->dataType = ERROR_TYPE;
            printErrorMsg(exprNode, STRING_OPERATION);
        }
        else if(rc->dataType == ERROR_TYPE) exprNode->dataType = ERROR_TYPE;
        else if(rc->dataType==VOID_TYPE){
            printErrorMsg(exprNode,UNARY_VOID);
            exprNode->dataType=ERROR_TYPE;
        }
        else {
            exprNode->dataType = rc->dataType;
            if(rc->nodeType == CONST_VALUE_NODE || (rc->nodeType == EXPR_NODE && rc->semantic_value.exprSemanticValue.isConstEval)) {
                exprNode->semantic_value.exprSemanticValue.isConstEval = evaluateExprValue(exprNode);
            }
        }
    }
}

void processVariableLValue(AST_NODE* idNode) {
#define error(msg) printErrorMsg(idNode,msg),idNode->dataType=ERROR_TYPE
    SymbolTableEntry* entry=retrieveSymbol(idNode->semantic_value.identifierSemanticValue.identifierName);
    if(!entry){
        error(SYMBOL_UNDECLARED);
        return;
    }
    idNode->semantic_value.identifierSemanticValue.symbolTableEntry=entry;
    if(entry->attribute->attributeKind==TYPE_ATTRIBUTE||entry->attribute->attributeKind==FUNCTION_SIGNATURE){
        error((entry->attribute->attributeKind==TYPE_ATTRIBUTE?IS_TYPE_NOT_VARIABLE:IS_FUNCTION_NOT_VARIABLE));
        return;
    }
    TypeDescriptor* tpdes=entry->attribute->attr.typeDescriptor;
    if(idNode->semantic_value.identifierSemanticValue.kind==NORMAL_ID){
        if(tpdes->kind==ARRAY_TYPE_DESCRIPTOR) error(NOT_ASSIGNABLE);
        else idNode->dataType=tpdes->properties.dataType;
    }
    else if(idNode->semantic_value.identifierSemanticValue.kind==ARRAY_ID){
        int dim=0;
        AST_NODE* ptr=idNode->child;
        while(ptr){
            dim++;
            processExprRelatedNode(ptr);
            if(ptr->dataType==ERROR_TYPE) idNode->dataType=ERROR_TYPE;
            else if(ptr->dataType==FLOAT_TYPE) error(ARRAY_SUBSCRIPT_NOT_INT);
            ptr=ptr->rightSibling;
        }
        if(tpdes->kind==SCALAR_TYPE_DESCRIPTOR) error(NOT_ARRAY);
        else{
            if(dim>tpdes->properties.arrayProperties.dimension) error(INCOMPATIBLE_ARRAY_DIMENSION);
            else if(dim<tpdes->properties.arrayProperties.dimension) error(NOT_ASSIGNABLE);
            else if(idNode->dataType!=ERROR_TYPE) idNode->dataType=tpdes->properties.arrayProperties.elementType;
        }
    }
}

void processVariableRValue(AST_NODE* idNode) {
    SymbolTableEntry *entry=retrieveSymbol(idNode->semantic_value.identifierSemanticValue.identifierName);
    if(!entry){
        error(SYMBOL_UNDECLARED);
        return;
    }
    idNode->semantic_value.identifierSemanticValue.symbolTableEntry=entry;
    if(entry->attribute->attributeKind==TYPE_ATTRIBUTE){
        error(IS_TYPE_NOT_VARIABLE);
        return;
    }
    else if(entry->attribute->attributeKind==FUNCTION_SIGNATURE){
        error(FUNCTION_NOT_RVALUE);
        return;
    }
    TypeDescriptor* tpdes=idNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
    if(idNode->semantic_value.identifierSemanticValue.kind==NORMAL_ID){
        if(tpdes->kind==ARRAY_TYPE_DESCRIPTOR)
            idNode->dataType=(tpdes->properties.arrayProperties.elementType==INT_TYPE?INT_PTR_TYPE:FLOAT_PTR_TYPE);
        else idNode->dataType=tpdes->properties.dataType;
    }
    else if(idNode->semantic_value.identifierSemanticValue.kind==ARRAY_ID){
        if(tpdes->kind==SCALAR_TYPE_DESCRIPTOR) error(NOT_ARRAY);
        else{
            int dim=0;
            AST_NODE* ptr=idNode->child;
            while(ptr){
                dim++;
                processExprRelatedNode(ptr);
                if(ptr->dataType==ERROR_TYPE) idNode->dataType=ERROR_TYPE;
                else if(ptr->dataType==FLOAT_TYPE) error(ARRAY_SUBSCRIPT_NOT_INT);
                ptr=ptr->rightSibling;
            }
            if(idNode->dataType!=ERROR_TYPE){
                if(dim==tpdes->properties.arrayProperties.dimension) idNode->dataType=tpdes->properties.arrayProperties.elementType;
                else if(dim>tpdes->properties.arrayProperties.dimension) error(INCOMPATIBLE_ARRAY_DIMENSION);
                else idNode->dataType=(tpdes->properties.arrayProperties.elementType==INT_TYPE?INT_PTR_TYPE:FLOAT_PTR_TYPE);
            }
        }
    }
}
#undef error

void processConstValueNode(AST_NODE* constValueNode) {
    switch(constValueNode->semantic_value.const1->const_type) {
        case INTEGERC:
            constValueNode->dataType = INT_TYPE;
            constValueNode->semantic_value.exprSemanticValue.constEvalValue.iValue = constValueNode->semantic_value.const1->const_u.intval;
            break;
        case FLOATC:
            constValueNode->dataType = FLOAT_TYPE;
            constValueNode->semantic_value.exprSemanticValue.constEvalValue.fValue = constValueNode->semantic_value.const1->const_u.fval;
            break;
        case STRINGC:
            constValueNode->dataType = CONST_STRING_TYPE;
            break;
        default:
            constValueNode->dataType = ERROR_TYPE;
            printf("unhandled const value type");
    }
}

void checkReturnStmt(AST_NODE* returnNode){
    AST_NODE* pNode=returnNode->parent;
    DATA_TYPE rettp=NONE_TYPE;
    while(pNode){
        if(pNode->nodeType==DECLARATION_NODE){
            if(pNode->semantic_value.declSemanticValue.kind==FUNCTION_DECL) rettp=pNode->child->dataType;
            else assert(0);
            break;
        }
        pNode=pNode->parent;
    }
    int errorflag=0;
    if(returnNode->child->nodeType==NUL_NODE){
        if(rettp!=VOID_TYPE) errorflag=1;
    }
    else{
        processExprRelatedNode(returnNode->child);

        if(rettp == VOID_TYPE && returnNode->child->dataType != VOID_TYPE) errorflag = 2;
        else if(rettp != VOID_TYPE && returnNode->child->dataType == VOID_TYPE) errorflag = 3;
    }
    
    if(errorflag==1){
        printWarningMsg(returnNode, NON_VOID_RETURN_VOID);
        returnNode->dataType=rettp;
    }
    else if(errorflag==2){
        printWarningMsg(returnNode, VOID_RETURN_NON_VOID);
        returnNode->dataType=rettp;
    }
    else if(errorflag==3) {
        printErrorMsg(returnNode, PASS_VOID_TO_SCALAR);
        returnNode->dataType=ERROR_TYPE;
    }
}

void processBlockNode(AST_NODE* blockNode) {
    openScope();
    AST_NODE* ptr = blockNode->child;
    while(ptr) {
        processGeneralNode(ptr);
        ptr = ptr->rightSibling;
    }    
    closeScope();
}

void processStmtNode(AST_NODE* stmtNode) {
    if(stmtNode->nodeType == BLOCK_NODE) processBlockNode(stmtNode);
    else if(stmtNode->nodeType == NUL_NODE) return;
    else {
        switch(stmtNode->semantic_value.stmtSemanticValue.kind) {
            case WHILE_STMT:
                checkWhileStmt(stmtNode);
                break;
            case FOR_STMT:
                checkForStmt(stmtNode);
                break;
            case ASSIGN_STMT:
                checkAssignmentStmt(stmtNode);
                break;
            case IF_STMT:
                checkIfStmt(stmtNode);
                break;
            case FUNCTION_CALL_STMT:
                checkFunctionCall(stmtNode);
                break;
            case RETURN_STMT:
                checkReturnStmt(stmtNode);
                break;
            default:
                stmtNode->dataType = ERROR_TYPE;
                printf("unhandled stmtNode type\n");
                break;
        }
    }
}

void processGeneralNode(AST_NODE *node) {
    if(node->nodeType == VARIABLE_DECL_LIST_NODE || 
    node->nodeType == STMT_LIST_NODE || 
    node->nodeType == NONEMPTY_ASSIGN_EXPR_LIST_NODE || 
    node->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE) {
        AST_NODE* ptr = node->child;
        int error=0;
        while(ptr) {
            if(node->nodeType == VARIABLE_DECL_LIST_NODE) processDeclarationNode(ptr);
            else if(node->nodeType == STMT_LIST_NODE) processStmtNode(ptr);
            else if(node->nodeType == NONEMPTY_ASSIGN_EXPR_LIST_NODE) checkAssignOrExpr(ptr);
            else if(node->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE) processExprRelatedNode(ptr);
            if(ptr->dataType == ERROR_TYPE) error=1;
            node->dataType = ptr->dataType;
            ptr = ptr->rightSibling;
        }
        if(error) node->dataType=ERROR_TYPE;
    }
    else if(node->nodeType == NUL_NODE) { /* do nothing */ }
    else {
        printf("unhandled general node type");
        node->dataType = ERROR_TYPE;
    }
}

void processDeclDimList(AST_NODE* idNode, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize) {
    AST_NODE* ptr = idNode->child; typeDescriptor->kind = ARRAY_TYPE_DESCRIPTOR;
    int dim = 0;
    if(ignoreFirstDimSize && ptr->nodeType == NUL_NODE) {
        typeDescriptor->properties.arrayProperties.sizeInEachDimension[dim++] = 0;
        ptr = ptr->rightSibling;
    }
    while(ptr) {
        if(dim >= MAX_ARRAY_DIMENSION) {
            printErrorMsg(idNode, EXCESSIVE_ARRAY_DIM_DECLARATION);
            idNode->dataType = ERROR_TYPE;
            break;
        }
        processExprRelatedNode(ptr);
        if(ptr->dataType == ERROR_TYPE) idNode->dataType = ERROR_TYPE;
        else if(ptr->dataType == FLOAT_TYPE) {
            idNode->dataType = ERROR_TYPE;
            printErrorMsg(idNode, ARRAY_SIZE_NOT_INT);
        }
        else if(!ptr->semantic_value.exprSemanticValue.isConstEval){
            idNode->dataType=ERROR_TYPE;
            printErrorMsg(idNode, ARRAY_SIZE_NON_CONST);
        }
        else if(ptr->semantic_value.exprSemanticValue.constEvalValue.iValue < 0) {
            idNode->dataType = ERROR_TYPE;
            printErrorMsg(idNode, ARRAY_SIZE_NEGATIVE);
        }
        else {
            typeDescriptor->properties.arrayProperties.sizeInEachDimension[dim] = ptr->semantic_value.exprSemanticValue.constEvalValue.iValue;
        }
        dim++; ptr = ptr->rightSibling;
    }
    typeDescriptor->properties.arrayProperties.dimension = dim;
}

#define error(node,msg) printErrorMsg(node,msg),node->dataType=ERROR_TYPE,err=1;
void declareFunction(AST_NODE* declarationNode) {
    AST_NODE *ret = declarationNode->child, *name = ret->rightSibling;
    int err = 0, enter=0;
    if(ret->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)
        error(name,RETURN_ARRAY);
    if(declaredLocally(name->semantic_value.identifierSemanticValue.identifierName)) error(name,FUNCTION_REDECLARE);
    SymbolAttribute* attr=(SymbolAttribute*)malloc(sizeof(SymbolAttribute));
    attr->attributeKind=FUNCTION_SIGNATURE;
    attr->attr.functionSignature=(FunctionSignature*)malloc(sizeof(FunctionSignature));
    attr->attr.functionSignature->returnType=ret->dataType;
    attr->attr.functionSignature->parameterList=NULL;
    if(!err) enterSymbol(name->semantic_value.identifierSemanticValue.identifierName,attr),enter=1;
    openScope();
    AST_NODE *paramList=name->rightSibling,*ptr=paramList->child;
    int paramNum=0;
    Parameter *tail=NULL;
    while(ptr){
        paramNum++;
        processDeclarationNode(ptr);
        AST_NODE* param=ptr->child->rightSibling;
        if(ptr->dataType==ERROR_TYPE) err=1;
        else if(!err){
            Parameter *cur=(Parameter*)malloc(sizeof(Parameter));
            cur->next=NULL;
            cur->parameterName=param->semantic_value.identifierSemanticValue.identifierName;
            cur->type=param->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
            if(!tail) tail=attr->attr.functionSignature->parameterList=cur;
            else tail=tail->next=cur;
        }
        ptr=ptr->rightSibling;
    }
    attr->attr.functionSignature->parametersCount=paramNum;
    if(err&&attr){
        Parameter *ptr=attr->attr.functionSignature->parameterList,*tmp;
        while(ptr){
            tmp=ptr->next; free(ptr); ptr=tmp;
        }
        free(attr->attr.functionSignature);
        free(attr);
    }
    if(!err){
        AST_NODE *block=paramList->rightSibling,*ptr=block->child;
        while(ptr){
            processGeneralNode(ptr);
            ptr=ptr->rightSibling;
        }
    }
    closeScope();
    if(err&&enter){
        declarationNode->dataType=ERROR_TYPE;
        if(enter) removeSymbol(name->semantic_value.identifierSemanticValue.identifierName);
    }
}
#undef error
