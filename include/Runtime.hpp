#ifndef RUNTIME_H
#define RUNTIME_H

#include "parser.hpp"
#include "SymbolTable.hpp"
#include "CallStack.hpp"

class Runtime
{
private:
  ParseTree *root;
  SymbolTable symbolTable;
  CallStack callStack;
  int nextLine;
  ParseTree *currentNode;

public:
  Runtime(ParseTree *root);
  bool next(int lines);
  bool runLine();
  string print(string var);
  vector<string> trace(string var);
  bool getBoolean(ParseTree *tree);
  int getInteger(ParseTree *tree);
  double getReal(ParseTree *tree);
  TypeObject getType(ParseTree *tree);
};

#endif