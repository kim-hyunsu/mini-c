#ifndef TAG_H
#define TAG_H

#include "ParseTree.hpp"
#include "../y.tab.h"

/*
enum Tag
{
    GREATER = 256,
    LESS,
    T,
    F,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    MINUS,
    ASSIGN,
    POINTER,
    ARRAY,
    ADDR,
    INC,
    DEC,
    BASIC,
    IF,
    ELSE,
    FOR,
    TEMP,
    INDEX, 
    NUM,
    REAL,
    ID,
    COMMA,
    FUNC,
    
    INT,
    FLOAT,
    VOID
};
*/

inline int tokenType(int tag) {
    if (tag < 256) {
        return -1;
    }
    switch (tag) {
    case NUM:
        return NUM;
    case REAL:
        return REAL;
    case INC:
    case DEC:
    case BASIC:
    case IF:
    case ELSE:
    case FOR:
    case TEMP:
    case ID:
    case FUNC:
    case INT:
    case FLOAT:
    case VOID:
        return 0;
    case NONTERMINAL:
        return 2;
    default:
        return 1;
    }
};

#endif