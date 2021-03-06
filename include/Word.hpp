#ifndef WORD_H
#define WORD_H

#include "Token.hpp"
#include "Tag.hpp"

class Word: public Token
{
public:
    std::string lexeme = std::string("");
    //char *lexeme = "";
    Word(std::string s, int tag) : Token(tag), lexeme(s) {};
    Word(std::string s, int tag, int ln) : Token(tag, ln), lexeme(s) {};
    //Word(char *s, int tag): Token(tag) { lexeme = s; };
    ~Word() {};
};

const Word wordTrue("true", T), wordFalse("false", F), wordInc("++", INC), wordDec("--", DEC), wordEqual("==", EQUAL), wordNEqual("!=", NEQUAL);

#endif