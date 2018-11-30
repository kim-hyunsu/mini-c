#include <unordered_map>
#include "Word.hpp"
#include <iostream>
#include <fstream>

using namespace std;

static int line = 1;

class Lexer
{
public:
    char peek = ' ';
    unordered_map<char *, Word> words;
    ifstream input;
    void reserve(Word w) { words.insert({w.lexeme, w}); }
    Lexer();
    void readch() { peek = input.peek(); }
    bool readch(char c);
    Token scan();
}