#include "Lexer.hpp"
#include "Word.hpp"
#include "Tag.hpp"
#include "Num.hpp"
#include "Real.hpp"
#include <cctype>
#include <string>

using namespace std;

Lexer::Lexer() : currentLineNumber(1)
{
    reserve(Word("if", IF));
    reserve(Word("else", ELSE));
    reserve(Word("for", FOR));
    reserve(Word((const Word &)wordTrue));
    reserve(Word((const Word &)wordFalse));
    
    reserve(Word("int", INT));
    reserve(Word("float", FLOAT));
    reserve(Word("void", VOID));
    
    reserve(Word("return", RETURN));
    reserve(Word("printf", PRINTF));
    
    /*
    reserve(TYPE.INT);
    reserve(TYPE.BOOL);
    reserve(TYPE.CHAR);
    reserve(TYPE.FLOAT);
    reserve(TYPE.DOUBLE);
    */
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
        else if(peek == '\n') currentLineNumber += 1;
        else break;
    }

    switch(peek) {
    case '\"': {
        std::string printfStr = "";
        while (true) {
            readch();
            if (peek != '\"') {
                if (peek == '\\') {
                    readch();
                    if (peek == 'a') {
                        printfStr += '\a';
                    } 
                    else if (peek == 'b') {
                        printfStr += '\b';
                    }
                    else if (peek == 'r') {
                        printfStr += '\r';
                    }
                    else if (peek == 'n') {
                        printfStr += '\n';
                    }
                    else if (peek == '\\') {
                        printfStr += '\\';
                    }
                    continue;
                }
                printfStr += peek;
            }
            else {
                readch();
                break;
            }
        }
        this->wordData = printfStr;
        return Word(printfStr, PRINTFARG, this->currentLineNumber);
        }
    case '+':
        if(readch('+')) {
            this->wordData = wordInc.lexeme;
            return Word(wordInc.lexeme, wordInc.tag, this->currentLineNumber);
        }
        else
            return Token('+', this->currentLineNumber);
    case '-':
        if(readch('-')) {
            this->wordData = wordDec.lexeme;
            return Word(wordDec.lexeme, wordDec.tag, this->currentLineNumber);
        }
        else
            return Token('-', this->currentLineNumber);
    case '=':
        if (readch('=')) {
            this->wordData = wordEqual.lexeme;
            return Word(wordEqual.lexeme, wordEqual.tag, this->currentLineNumber);
        }
        else
            return Token('=', this->currentLineNumber);
    case '!':
        if (readch('=')) {
            this->wordData = wordNEqual.lexeme;
            return Word(wordNEqual.lexeme, wordNEqual.tag, this->currentLineNumber);
        }
        else
            return Token('!', this->currentLineNumber);
    }
    
    
    if('0' <= peek && peek <= '9')
    {
        int v = 0;
        do
        {
            v = 10 * v + peek - '0';
            readch();
        } while('0' <= peek && peek <= '9');
        if(peek != '.') {
            this->numData = v;
            return Num(v, this->currentLineNumber);
        }

        double x = v, d = 10;

        for( ; ; )
        {
            readch();

            if('0' > peek || peek > '9')
                break;
    
            x = x + (peek - '0') / d;
            d *= 10;
        }

        this->realData = x;
        return Real(x, this->currentLineNumber);
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
            auto f = words.find(s);

            if (f == words.end())
                throw out_of_range("out of range");

            this->wordData = f->first;
            Word w = f->second;
            w.lineNumber = this->currentLineNumber;
            //Word w = words[s];
            return w;
        }
        catch(const out_of_range& oor)
        {
            this->wordData = s;
            Word w = Word(s, ID, this->currentLineNumber);
            words.insert({s, w});
            return w;
        }
    }

    Token tok = Token(peek, this->currentLineNumber);
    peek = ' ';
    return tok;
}