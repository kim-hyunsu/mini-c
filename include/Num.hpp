#include "Token.hpp"
#include "Tag.hpp"

class Num: public Token
{
public:
    int value;
    Num(int v): Token(NUM) { value = v; }
    Num(int v, int ln): Token(NUM, ln) { value = v; }
    ~Num() {};
};