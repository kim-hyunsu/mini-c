#ifndef LEXER_H
#define LEXER_H

#include <unordered_map>
#include "Word.hpp"
#include <iostream>
#include <fstream>

int yylex();

using namespace std;

class Lexer
{
public:
    char peek = ' ';
    unordered_map<std::string, Word> words;
    //unordered_map<char *, Word> words;
    ifstream input;

    int currentLineNumber;

    std::string wordData;
    double realData;
    int numData;

    void reserve(Word w) { words.insert({w.lexeme, Word(w)}); }
    Lexer();
    void readch() { peek = input.peek(); input.ignore(); }
    bool readch(char c);
    Token scan();
};

#endif