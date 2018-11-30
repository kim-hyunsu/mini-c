#include "Tag.hpp"
#include "Token.hpp"

class Real: public Token
{
public:
    double value;
    Real(double v): Token(REAL) { value = v; }
};