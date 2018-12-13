#include "Runtime.hpp"
#include <iostream>

Runtime::Runtime(Parser *parser) : parser(parser), currentLine(0)
{
  this->symbolTable = SymbolTable();
  this->callStack = CallStack();
}

bool Runtime::next(int lines)
{
  bool end = false;
  // AST ast = NULL;
  for (int i = 0; i < lines - 1; i++)
  {
    // ast = parse(tokens[this->currentLine]);
    // this.currentLine = ast.run();
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