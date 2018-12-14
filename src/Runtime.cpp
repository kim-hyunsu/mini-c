#include "Runtime.hpp"
#include <iostream>

Runtime::Runtime(ParseTree *root) : root(root), nextLine(1), currentNode(root)
{
  this->symbolTable = SymbolTable();
  this->callStack = CallStack();
}

bool Runtime::next(int lines)
{
  bool end = false;
  for (int i = 0; i < lines; i++)
  {
    end = this->runLine();
  }
  return end;
}

bool Runtime::runLine()
{
  bool end = false;
  int tag = this->currentNode->tag;
  int numData = this->currentNode->numData;
  double realData = this->currentNode->realData;
  std::string wordData = this->currentNode->wordData;
  std::vector<ParseTree *> children = this->currentNode->children;
  if (wordData == "IDtypeDeclaration")
  {
    // TODO
  }

  return end;
}

string Runtime::print(string var)
{
  string value;
  int index = this->symbolTable.lookup(var);
  switch (index)
  {
  case -2: // Invisible
    value = "Invisible variable";
    break;
  case -1: // Not found
    value = "N/A";
    break;
  default:
    SymbolTableEntry ste = this->symbolTable.get(index);
    value = ste.getValue();
  }
  return value;
}

vector<string> Runtime::trace(string var)
{
  vector<string> history;
  int index = this->symbolTable.lookup(var);
  switch (index)
  {
  case -2: // Invisible
    history.push_back("Invisible variable");
    break;
  case -1: // Not found
    history.push_back("N/A");
    break;
  default:
    SymbolTableEntry ste = this->symbolTable.get(index);
    history = ste.getHistory(var);
  }
  return history;
}