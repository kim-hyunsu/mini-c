#include "Token.hpp"
#include "Tag.hpp"

class Word: public Token
{
public:
    char *lexeme = "";
    Word(char *s, int tag): Token(tag) { lexeme = s; }
};

Word t("true", T), f("false", F), inc("++", INC), dec("--", DEC);