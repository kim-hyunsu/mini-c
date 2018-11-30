#include "Token.hpp"

Token::Token(int t)
{
    tag = t;
}

char *Token::toString()
{
    return (char *)&(Token::tag);
}