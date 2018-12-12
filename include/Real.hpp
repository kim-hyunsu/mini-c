#include "Token.hpp"
#include "Tag.hpp"

class Real: public Token
{
public:
    double value;
    Real(double v): Token(REAL) { value = v; }
    ~Real() {};
};