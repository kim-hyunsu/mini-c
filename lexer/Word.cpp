#include "Word.hpp"

Word::Word(char *s, int tag): Token(tag)
{
    lexeme = s;
}

char *Word::toString()
{
    return lexeme;
}
