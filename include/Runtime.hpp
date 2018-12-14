#ifndef RUNTIME_H
#define RUNTIME_H

#include "parser.hpp"
#include "SymbolTable.hpp"
#include "CallStack.hpp"
#include "Value.hpp"

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

  static ParseTree* nextStatement(ParseTree *crnt);
  Value evaluate(ParseTree *tree);
};

#endif