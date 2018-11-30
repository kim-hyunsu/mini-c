#include "Token.hpp"
#include "Tag.hpp"

class Word: public Token
{
public:
    char *lexeme = "";
    Word(char *s, int tag): Token(tag) { lexeme = s; }
};

Word wordTrue("true", T), wordFalse("false", F), wordInc("++", INC), wordDec("--", DEC);