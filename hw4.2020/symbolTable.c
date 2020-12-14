#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
// This file is for reference only, you are not required to follow the implementation. //

int HASH(char * str) {
	int idx=0;
	while (*str){
		idx = idx << 1;
		idx+=*str;
		str++;
	}
	return (idx & (HASH_TABLE_SIZE-1));
}

SymbolTableEntry* newSymbolTableEntry(int nestingLevel)
{
    SymbolTableEntry* symbolTableEntry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    symbolTableEntry->nextInHashChain = NULL;
    symbolTableEntry->prevInHashChain = NULL;
    symbolTableEntry->nextInSameLevel = NULL;
    symbolTableEntry->sameNameInOuterLevel = NULL;
    symbolTableEntry->attribute = NULL;
    symbolTableEntry->name = NULL;
    symbolTableEntry->nestingLevel = nestingLevel;
    return symbolTableEntry;
}

void removeFromHashChain(int hashIndex, SymbolTableEntry* entry) {
    if(entry->prevInHashChain) entry->prevInHashChain->nextInHashChain = entry->nextInHashChain;
    else nextInHashChain:symbolTable.hashTable[hashIndex] = entry->nextInHashChain;
    entry->nextInHashChain&&(entry->nextInHashChain->prevInHashChain=entry->prevInHashChain);
    entry->prevInHashChain = entry->nextInHashChain = NULL;
}

void enterIntoHashChain(int hashIndex, SymbolTableEntry* entry) {
    if(symbolTable.hashTable[hashIndex]) {
        entry->nextInHashChain = symbolTable.hashTable[hashIndex];
        symbolTable.hashTable[hashIndex]->prevInHashChain = entry;
    }
    symbolTable.hashTable[hashIndex] = entry;
}

void initializeSymbolTable() {
    symbolTable.currentLevel = 0;
    symbolTable.scopeDisplayElementCount = 42;
    symbolTable.scopeDisplay = (SymbolTableEntry**)calloc(symbolTable.scopeDisplayElementCount,sizeof(SymbolTableEntry*));
    memset(symbolTable.hashTable,0,sizeof(symbolTable.hashTable));
    SymbolAttribute* cur;
    #define insertTypeSymbol(var_name,var_type) cur=(SymbolAttribute*)malloc(sizeof(SymbolAttribute));\
                                cur->attributeKind=TYPE_ATTRIBUTE;\
                                cur->attr.typeDescriptor = (TypeDescriptor*)malloc(sizeof(TypeDescriptor));\
                                cur->attr.typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;\
                                cur->attr.typeDescriptor->properties.dataType = var_type;\
                                enterSymbol(var_name,cur);

    #define insertFuncSymbol(func_name,func_type) cur=(SymbolAttribute*)malloc(sizeof(SymbolAttribute));\
                                cur->attributeKind=FUNCTION_SIGNATURE;\
                                cur->attr.functionSignature = (FunctionSignature*)malloc(sizeof(FunctionSignature));\
                                cur->attr.functionSignature->returnType = func_type;\
                                cur->attr.functionSignature->parameterList = NULL;\
                                cur->attr.functionSignature->parametersCount = 0;\
                                enterSymbol(func_name,cur);

    insertTypeSymbol(SYMBOL_TABLE_INT_NAME,INT_TYPE);
    insertTypeSymbol(SYMBOL_TABLE_FLOAT_NAME,FLOAT_TYPE);
    insertTypeSymbol(SYMBOL_TABLE_VOID_NAME,VOID_TYPE);
    insertFuncSymbol(SYMBOL_TABLE_SYS_LIB_READ,INT_TYPE);
    insertFuncSymbol(SYMBOL_TABLE_SYS_LIB_FREAD,FLOAT_TYPE);
    #undef insertTypeSymbol
    #undef insertFuncSymbol
}

void symbolTableEnd() {
    for(int i = 0 ; i < symbolTable.scopeDisplayElementCount ; ++i) {
        if(symbolTable.scopeDisplay[i]) free(symbolTable.scopeDisplay[i]);
    }
    free(symbolTable.scopeDisplay); 
    /*
    for(int i = 0 ; i < HASH_TABLE_SIZE ; ++i) {
        if(symbolTable.hashTable[i]) free(symbolTable.hashTable[i]);
    }
    */
}

SymbolTableEntry* retrieveSymbol(char* symbolName) {
    int hashval = HASH(symbolName);
    SymbolTableEntry* ptr = symbolTable.hashTable[hashval];
    while(ptr && strcmp(ptr->name, symbolName) != 0) ptr = ptr->nextInHashChain;
    return ptr;
}

SymbolTableEntry* enterSymbol(char* symbolName, SymbolAttribute* attribute) {
    int hashval = HASH(symbolName);
    SymbolTableEntry* ptr = symbolTable.hashTable[hashval];
    SymbolTableEntry* now = newSymbolTableEntry(symbolTable.currentLevel);
    now->attribute = attribute;
    now->name = symbolName;
    
    while(ptr) {
        if(strcmp(ptr->name, symbolName) == 0) {
            if(ptr->nestingLevel == symbolTable.currentLevel) {
                printf("name %s is redecalred at the same level\n", symbolName);
                free(now);
                return NULL;
            }
            else {
                removeFromHashChain(hashval, ptr);
                now->sameNameInOuterLevel = ptr;
                break;
            }
        }
        else ptr = ptr->nextInHashChain;
    }
    enterIntoHashChain(hashval, now);
    now->nextInSameLevel = symbolTable.scopeDisplay[symbolTable.currentLevel];
    symbolTable.scopeDisplay[symbolTable.currentLevel] = now;
}

//remove the symbol from the current scope
void removeSymbol(char* symbolName) {  
    int hashval = HASH(symbolName);
    SymbolTableEntry* ptr = symbolTable.hashTable[hashval];
    // remove from hashtable
    while(ptr) {
        if(strcmp(ptr->name, symbolName) == 0) {
            if(ptr->nestingLevel != symbolTable.currentLevel) {
                printf("trying to remove a name %s that is not declared at the same level\n", symbolName);
                return;
            }
            else {
                removeFromHashChain(hashval, ptr);
                if(ptr->sameNameInOuterLevel) enterIntoHashChain(hashval, ptr->sameNameInOuterLevel);
                break;
            }
        }
        else ptr = ptr->nextInHashChain;
    }
    if(!ptr) {
        printf("trying to remove a name %s that is not declared at anywhere\n", symbolName);
        return;
    }
    // remove from scope chain
    ptr = symbolTable.scopeDisplay[symbolTable.currentLevel];
    SymbolTableEntry* prev = NULL;
    while(ptr && strcmp(ptr->name, symbolName) != 0) prev = ptr, ptr = ptr->nextInSameLevel;
    assert(ptr);
    if(prev) prev->nextInSameLevel = ptr->nextInSameLevel;
    else symbolTable.scopeDisplay[symbolTable.currentLevel] = ptr->nextInSameLevel;
    free(ptr);
}

int declaredLocally(char* symbolName) {
    int hashval = HASH(symbolName);
    SymbolTableEntry* ptr = symbolTable.hashTable[hashval];
    while(ptr && strcmp(ptr->name, symbolName) != 0) ptr = ptr->nextInHashChain;
    if(ptr) return ptr->nestingLevel == symbolTable.currentLevel;
    return 0;
}

void openScope() {
    symbolTable.currentLevel++;
    // allocate new space if no more spaces
    if(symbolTable.currentLevel == symbolTable.scopeDisplayElementCount) {
        symbolTable.scopeDisplay = (SymbolTableEntry**)realloc(symbolTable.scopeDisplay,symbolTable.scopeDisplayElementCount*2*sizeof(SymbolTableEntry*));
        memset(symbolTable.scopeDisplay+symbolTable.scopeDisplayElementCount,0,symbolTable.scopeDisplayElementCount*sizeof(SymbolTableEntry*));
        symbolTable.scopeDisplayElementCount *= 2;
    }
}

void closeScope() {
    if(symbolTable.currentLevel < 0) {
        printf("trying to close a negative level\n");
        return;
    }
    // remove entries in current scope
    SymbolTableEntry* ptr = symbolTable.scopeDisplay[symbolTable.currentLevel];
    while(ptr) {
        int hashval = HASH(ptr->name);
        removeFromHashChain(hashval, ptr);
        if(ptr->sameNameInOuterLevel) enterIntoHashChain(hashval, ptr->sameNameInOuterLevel);
        SymbolTableEntry* tmp = ptr;
        ptr = ptr->nextInSameLevel;
        free(tmp);
    }
    symbolTable.scopeDisplay[symbolTable.currentLevel] = NULL;
    symbolTable.currentLevel--;
}
