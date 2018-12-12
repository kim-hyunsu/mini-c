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
    unordered_map<std::string, Word> words;
    //unordered_map<char *, Word> words;
    ifstream input;
    void reserve(Word w) { words.insert({w.lexeme, Word(w)}); }
    Lexer();
    void readch() { peek = input.peek(); input.ignore(); }
    bool readch(char c);
    Token scan();
};