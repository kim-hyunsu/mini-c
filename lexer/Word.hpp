#include "Token.hpp"

class Word: public Token
{
public:
    char *lexeme = "";
    Word(char *s, int tag);
    char *toString();
};