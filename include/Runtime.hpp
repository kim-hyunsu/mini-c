#ifndef RUNTIME_H
#define RUNTIME_H

#include "parser.hpp"
#include "SymbolTable.hpp"
#include "CallStack.hpp"
#include "Value.hpp"

#define VALUE(T, V) \
  ((T) != TYPE_BOOL ? ((T) != TYPE_INT ? (V).real : (V).integer) : (V).boolean)

class Runtime
{
private:
  ParseTree *root;
  SymbolTable symbolTable;
  CallStack callStack;
  int nextLine;
  ParseTree *currentNode;
  bool forBlockEnd = false; // true only immediately after in-loop block ends

public:
  Runtime(ParseTree *root);
  void findProcedures();
  bool findMain();
  bool next(int lines);
  bool runLine();
  string print(string var);
  vector<string> trace(string var);

  ParseTree *nextStatement(ParseTree *crnt);

  Value evaluate(ParseTree *tree);
};

#endif