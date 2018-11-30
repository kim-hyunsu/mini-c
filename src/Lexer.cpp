#include "Lexer.hpp"
#include "Word.hpp"
#include "Tag.hpp"
#include "Num.hpp"
#include "Real.hpp"
#include <cctype>
#include <string>

using namespace std;

Lexer::Lexer()
{
    reserve(Word("if", IF));
    reserve(Word("else", ELSE));
    reserve(Word("for", FOR));
    reserve(Word((const Word &)wordTrue));
    reserve(Word((const Word &)wordFalse));
    reserve(TYPE.INT);
    reserve(TYPE.BOOL);
    reserve(TYPE.CHAR);
    reserve(TYPE.FLOAT);
    reserve(TYPE.DOUBLE);
}

bool Lexer::readch(char c)
{
    readch();
    if(peek != c) return false;
    peek = ' ';
    return true;
}

Token Lexer::scan()
{
    for(; ; readch())
    {
        if(peek == ' ' || peek == '\t') continue;
        else if(peek == '\n') line = line + 1;
        else break;
    }
    switch(peek) {
    case '+':
        if(readch('+'))
            return Word(wordInc.lexeme, wordInc.tag);
        else
            return Token('+');
    case '-':
        if(readch('-'))
            return Word(wordDec.lexeme, wordDec.tag);
        else
            return Token('-');
    }
    if('0' <= peek && peek <= '9')
    {
        int v = 0;
        do
        {
            v = 10 * v + peek - '0';
            readch();
        } while('0' <= peek && peek <= '9');
        if(peek != '.')
            return Num(v);

        double x = v, d = 10;

        for( ; ; )
        {
            readch();

            if('0' > peek || peek > '9')
                break;
            
            x = x + (peek - '0') / d;
            d *= 10;
        }

        return Real(x);
    }
    if(isalpha(peek) || peek == '_')
    {
        string str;
        do
        {
            str.push_back(peek);
            readch();
        } while(isalpha(peek) || isdigit(peek) || peek == '_');
        char *s = (char *)str.c_str();
        try
        {
            Word w = words[s];
            return w;
        }
        catch(const out_of_range& oor)
        {
            Word w = Word(s, ID);
            words.insert({s, w});
            return w;
        }
    }

    Token tok = Token(peek);
    peek = ' ';
    return tok;
}