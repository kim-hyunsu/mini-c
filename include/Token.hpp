#ifndef TOKEN_H
#define TOKEN_H

class Token
{
public:
    int tag;
    int lineNumber;
    Token(int t) : tag(t) {};
    Token(int t, int ln) : tag(t), lineNumber(ln) {};

    ~Token() {};
};

#endif