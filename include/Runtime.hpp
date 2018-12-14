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
  void findProcedures();
  bool findMain();
  bool next(int lines);
  bool runLine();
  string print(string var);
  vector<string> trace(string var);
  TypeObject *getType(ParseTree *tree);

  static ParseTree* nextStatement(ParseTree *crnt);
};

#endif