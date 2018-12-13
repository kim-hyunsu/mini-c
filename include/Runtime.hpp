#ifndef RUNTIME_H
#define RUNTIME_H

#include "parser.hpp"
#include "SymbolTable.hpp"
#include "CallStack.hpp"

class Runtime
{
private:
  Parser *parser;
  SymbolTable symbolTable;
  CallStack callStack;
  int currentLine;

public:
  Runtime(Parser *parser);
  bool next(int lines);
  string print(string var);
  vector<string> trace(string var);
};

#endif