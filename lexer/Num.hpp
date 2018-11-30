#include "Token.hpp"
#include "Tag.hpp"

class Num: public Token
{
public:
    int value;
    Num(int v): Token(NUM) { value = v; }
};