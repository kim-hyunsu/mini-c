#ifndef TAG_H
#define TAG_H

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
    FUNC
};

inline int tokenType(int tag) {
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
        return 0;
    default:
        return 1;
    }
};

#endif