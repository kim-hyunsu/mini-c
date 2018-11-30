#include <unordered_map>
#include "Word.hpp"

using namespace std;

static int line = 1;

class Lexer
{
public:
    char peek = ' ';
    unordered_map<char *, Word> words;
    void reserve(Word w) { words.insert({w.lexeme, w}); }
    Lexer();
}