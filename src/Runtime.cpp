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

bool Runtime::getBoolean(ParseTree *tree)
{
  if (tree->tag == EQUAL || tree->tag == NEQUAL)
  {
    if (tree->children.size() != 2)
    {
      throw "Invalid syntax";
    }
    ParseTree *left = tree->children[0];
    ParseTree *right = tree->children[1];
    TypeObject *type = this->getType(left);
    if (type->typ != this->getType(right)->typ)
    {
      throw "Type error";
    }
    switch (type->typ)
    {
    case TYPE_INT:
      int left_val = this->getInteger(left);
      int right_val = this->getInteger(right);
      return left_val == right_val;
    case TYPE_FLOAT:
      double left_val = this->getReal(left);
      double right_val = this->getReal(right);
      return left_val == right_val;
    case TYPE_ARRAY:
    case TYPE_POINTER:
      void *left_p = this->getPointer(left);
      void *right_p = this->getPointer(right);
      return left_p == right_p;
    default:
      throw "Type error";
    }
  }
  else
  {
    throw "Type error";
  }
}

int Runtime::getInteger(ParseTree *tree)
{
}

double Runtime::getReal(ParseTree *tree)
{
}

void *Runtime::getPointer(ParseTree *tree)
{
}

TypeObject *Runtime::getType(ParseTree *tree)
{
}