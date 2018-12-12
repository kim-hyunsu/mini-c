#ifndef TOKEN_H
#define TOKEN_H

class Token
{
public:
    int tag;
    Token(int t) { tag = t; }
    ~Token() {};
};

#endif