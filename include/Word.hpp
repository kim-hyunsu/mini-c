#ifndef WORD_H
#define WORD_H

#include "Token.hpp"
#include "Tag.hpp"

class Word: public Token
{
public:
    char *lexeme = "";
    Word(char *s, int tag): Token(tag) { lexeme = s; };
    ~Word() {};
};

const Word wordTrue("true", T), wordFalse("false", F), wordInc("++", INC), wordDec("--", DEC);

#endif