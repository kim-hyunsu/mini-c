#include "Runtime.hpp"
#include "../y.tab.h"
#include <iostream>

static SymbolTableEntry getSymbolTableEntry(SymbolTable *symbolTable, std::string name);

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

Value Runtime::evaluate(ParseTree *tree)
{
  Value value = Value();
  switch (tree->tag)
  {
  case EQUAL:
  {
    Value lvalue = this->evaluate(tree->children[0]);
    Value rvalue = this->evaluate(tree->children[1]);
    if (lvalue.type != rvalue.type)
    {
      throw "Type error";
    }
    switch (lvalue.type)
    {
    case TYPE_BOOL:
      value.boolean = lvalue.boolean == rvalue.boolean;
      break;
    case TYPE_INT:
      value.boolean = lvalue.integer == rvalue.integer;
      break;
    case TYPE_FLOAT:
      value.boolean = lvalue.real == rvalue.real;
      break;
    case TYPE_POINTER:
      value.boolean = lvalue.pointer == rvalue.pointer;
      break;
    }
    value.type = TYPE_BOOL;
    break;
  }
  case NEQUAL:
  {
    Value lvalue = this->evaluate(tree->children[0]);
    Value rvalue = this->evaluate(tree->children[1]);
    if (lvalue.type != rvalue.type)
    {
      throw "Type error";
    }
    switch (lvalue.type)
    {
    case TYPE_BOOL:
      value.boolean = lvalue.boolean != rvalue.boolean;
      break;
    case TYPE_INT:
      value.boolean = lvalue.integer != rvalue.integer;
      break;
    case TYPE_FLOAT:
      value.boolean = lvalue.real != rvalue.real;
      break;
    case TYPE_POINTER:
      value.boolean = lvalue.pointer != rvalue.pointer;
      break;
    }
    value.type = TYPE_BOOL;
    break;
  }
  case NUM:
  {
    value.integer = tree->numData;
    value.type = TYPE_INT;
    break;
  }
  case REAL:
  {
    value.real = tree->realData;
    value.type = TYPE_FLOAT;
    break;
  }
  case INC:
  case DEC:
    tree = tree->children[0];
    if (tree->tag != ID || tree->wordData != "subscript")
    {
      throw "Type error";
    }
  case ID:
  {
    SymbolTableEntry ste = getSymbolTableEntry(&this->symbolTable, tree->wordData);
    switch (ste.getType().typ)
    {
    case TYPE_INT:
      value.integer = *(int *)ste.variableAddress;
      value.type = TYPE_INT;
      break;
    case TYPE_FLOAT:
      value.real = *(float *)ste.variableAddress;
      value.type = TYPE_FLOAT;
      break;
    case TYPE_POINTER:
    case TYPE_ARRAY:
      value.pointer = *(void **)ste.variableAddress;
      value.type = TYPE_POINTER;
      break;
    default:
      throw "Type error";
    }
    break;
  }
  case '+':
  {
    Value lvalue = this->evaluate(tree->children[0]);
    Value rvalue = this->evaluate(tree->children[1]);
    if (lvalue.type == TYPE_FLOAT && rvalue.type == TYPE_FLOAT)
    {
      value.real = lvalue.real + rvalue.real;
      value.type = TYPE_FLOAT;
    }
    else if (lvalue.type == TYPE_INT || rvalue.type == TYPE_INT)
    {
      int firstTerm = lvalue.type == TYPE_FLOAT ? (int)lvalue.real : lvalue.integer;
      int secondTerm = rvalue.type == TYPE_FLOAT ? (int)rvalue.real : rvalue.integer;
      value.integer = firstTerm + secondTerm;
      value.type = TYPE_INT;
    }
    else if (lvalue.type == TYPE_POINTER && rvalue.type == TYPE_POINTER)
    {
      throw "type error";
    }
    else if (lvalue.type == TYPE_POINTER || rvalue.type == TYPE_POINTER)
    {
      int firstTerm = lvalue.type == TYPE_POINTER ? (int)lvalue.pointer : lvalue.integer;
      int secondTerm = rvalue.type == TYPE_POINTER ? (int)rvalue.pointer : rvalue.integer;
      value.pointer = (void *)(firstTerm + secondTerm);
      value.type = TYPE_INT;
    }
    else
    {
      throw "type error";
    }
    break;
  }
  case '-':
  {
    Value lvalue = this->evaluate(tree->children[0]);
    Value rvalue = this->evaluate(tree->children[1]);
    if (lvalue.type == TYPE_FLOAT && rvalue.type == TYPE_FLOAT)
    {
      value.real = lvalue.real - rvalue.real;
      value.type = TYPE_FLOAT;
    }
    else if (lvalue.type == TYPE_INT || rvalue.type == TYPE_INT)
    {
      int firstTerm = lvalue.type == TYPE_FLOAT ? (int)lvalue.real : lvalue.integer;
      int secondTerm = rvalue.type == TYPE_FLOAT ? (int)rvalue.real : rvalue.integer;
      value.integer = firstTerm - secondTerm;
      value.type = TYPE_INT;
    }
    else if (lvalue.type == TYPE_POINTER || rvalue.type == TYPE_POINTER)
    {
      unsigned int firstTerm = lvalue.type == TYPE_POINTER ? (int)lvalue.pointer : lvalue.integer;
      unsigned int secondTerm = rvalue.type == TYPE_POINTER ? (int)rvalue.pointer : rvalue.integer;
      value.pointer = (void *)(firstTerm - secondTerm);
      value.type = TYPE_INT;
    }
    else
    {
      throw "type error";
    }
    break;
  }
  case '*':
  {
    Value lvalue = this->evaluate(tree->children[0]);
    Value rvalue = this->evaluate(tree->children[1]);
    if (lvalue.type == TYPE_FLOAT && rvalue.type == TYPE_FLOAT)
    {
      value.real = lvalue.real * rvalue.real;
      value.type = TYPE_FLOAT;
    }
    else if (lvalue.type == TYPE_INT || rvalue.type == TYPE_INT)
    {
      int firstTerm = lvalue.type == TYPE_FLOAT ? (int)lvalue.real : lvalue.integer;
      int secondTerm = rvalue.type == TYPE_FLOAT ? (int)rvalue.real : rvalue.integer;
      value.integer = firstTerm * secondTerm;
      value.type = TYPE_INT;
    }
    else
    {
      throw "type error";
    }
    break;
  }
  case '/':
  {
    Value lvalue = this->evaluate(tree->children[0]);
    Value rvalue = this->evaluate(tree->children[1]);
    if (lvalue.type == TYPE_FLOAT && rvalue.type == TYPE_FLOAT)
    {
      value.real = lvalue.real * rvalue.real;
      value.type = TYPE_FLOAT;
    }
    else if (lvalue.type == TYPE_INT || rvalue.type == TYPE_INT)
    {
      int firstTerm = lvalue.type == TYPE_FLOAT ? (int)lvalue.real : lvalue.integer;
      int secondTerm = rvalue.type == TYPE_FLOAT ? (int)rvalue.real : rvalue.integer;
      value.integer = firstTerm * secondTerm;
      value.type = TYPE_INT;
    }
    else
    {
      throw "type error";
    }
    break;
  }
  case '=':
  {
    Value rvalue = this->evaluate(tree->children[1]);
    std::string variableName = tree->children[0]->wordData;
    int arrayIndex = 0;
    if (variableName == "subscript")
    {
      ParseTree *ltree = tree->children[0];
      ParseTree *rtree = tree->children[1];
      Value arrayIndexValue = this->evaluate(rtree);
      if (ltree->tag != ID || arrayIndexValue.type != TYPE_INT)
      {
        throw "type error";
      }
      variableName = ltree->wordData;
      arrayIndex = arrayIndexValue.integer;
      int index = this->symbolTable.lookup(variableName);
      if (index < 0)
        throw "Not declared";
      this->symbolTable.setArrayEntry(index, arrayIndex, rvalue);
    }
    else
    {
      int index = this->symbolTable.lookup(variableName);
      if (index < 0)
        throw "Not declared";
      this->symbolTable.set(index, rvalue);
    }
    break;
  }
  default:
  {
    if (tree->wordData == "subscript")
    {
      ParseTree *ltree = tree->children[0];
      ParseTree *rtree = tree->children[1];
      Value arrayIndex = this->evaluate(rtree);
      if (ltree->tag != ID || arrayIndex.type != TYPE_INT)
        throw "type error";
      SymbolTableEntry ste = getSymbolTableEntry(&this->symbolTable, ltree->wordData);
      TypeObject type = ste.getType();
      if (type.typ != TYPE_ARRAY)
        throw "type error";
      value.type = type.baseType->typ;
      switch (value.type)
      {
      case TYPE_INT:
        value.integer = ((int *)ste.variableAddress)[arrayIndex.integer];
        break;
      case TYPE_FLOAT:
        value.real = ((float *)ste.variableAddress)[arrayIndex.integer];
        break;
      case TYPE_POINTER:
        value.pointer = ((void **)ste.variableAddress)[arrayIndex.integer];
        break;
      default:
        throw "Type error";
      }
    }
  }
  }
  return value;
}

static SymbolTableEntry getSymbolTableEntry(SymbolTable *symbolTable, std::string name)
{
  int index = symbolTable->lookup(name);
  switch (index)
  {
  case -2: // Invisible
    throw "Invisible";
  case -1: // Not found
    throw "Not found";
  default:
    return symbolTable->get(index);
  }
}