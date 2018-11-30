#include "Lexer.hpp"
#include "Word.hpp"
#include "Tag.hpp"

void Lexer::Lexer()
{
    reserve(Word("if", IF));
    reserve(Word("else", ELSE));
    reserve(Word("for", FOR));
    reserve(wordTrue);
    reserve(wordFalse);
    reserve(TYPE.INT);
    reserve(TYPE.BOOL);
    reserve(TYPE.CHAR);
    reserve(TYPE.FLOAT);
    reserve(TYPE.DOUBLE);
}