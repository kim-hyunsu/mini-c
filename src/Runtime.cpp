#include "Runtime.hpp"
#include <iostream>

static SymbolTableEntry getSymbolTableEntry(SymbolTable *symbolTable, std::string name);

Runtime::Runtime(ParseTree *root) : root(root), nextLine(1), currentNode(root)
{
  this->symbolTable = SymbolTable();
  this->callStack = CallStack();
}

// from parse tree find procedures & add to symbol table
void Runtime::findProcedures() {
  ParseTree *procedures = this->root;
  int num = procedures->children.size();
  for (int i = 0; i < num; i++) {
    auto pr = procedures->children[i];
    auto returnType = pr->children[0];
    auto name = pr->children[1];
    auto params = pr->children[2];

    TypeObject *returnBaseType;
    if (returnType->tag == VOID) returnBaseType = new TypeObject(TYPE_VOID);
    else if (returnType->tag == INT) returnBaseType = new TypeObject(TYPE_INT);
    else if (returnType->tag == FLOAT) returnBaseType = new TypeObject(TYPE_FLOAT);
    else { std::cout << "Procedure return type is wrong." << std::endl;}

    TypeObject *returnTypeObject = returnBaseType;
    for (int k = 0; k < returnType->children.size(); k++) {
      TypeObject *newType = new TypeObject(TYPE_POINTER);
      newType->baseType = returnTypeObject;
      returnTypeObject = newType;
    }

    std::vector<TypeObject*> parameters;
    for (int k = 0; k < params->children.size(); k++) {
      auto param = params->children[k];
      auto type = param->children[0];
      TypeObject *paramType;
      if (type->tag == INT) paramType = new TypeObject(TYPE_INT);
      else if (type->tag == FLOAT) paramType = new TypeObject(TYPE_FLOAT);
      else { std::cout << "Procedure parameter type is wrong." << std::endl;}
      
      auto ptr = param->children[1];

      while (ptr->tag != ID) {
        ptr = ptr->children[0];
        TypeObject *newType = new TypeObject(TYPE_POINTER);
        newType->baseType = paramType;
        paramType = newType;
      }
      if (ptr->children.size() > 0) {
        auto ar = ptr->children[0];
        int arsize = -1;
        if (ar->children.size() > 0) {
          arsize = ar->children[0]->numData;
        }
        TypeObject *newType = new TypeObject(TYPE_ARRAY);
        newType->arraySize.push_back(arsize);
        newType->baseType = paramType;
        paramType = newType;
      }
      parameters.push_back(paramType);
    }
    TypeObject functionType = TypeObject(TYPE_FUNCTION);
    functionType.returnType = returnTypeObject;
    functionType.parameterTypes = parameters;
    this->symbolTable.addNewSymbol(name->wordData, functionType, pr);

    std::cout << "Procedure found : " << name->wordData << " " << pr << std::endl;

    std::cout << functionType.printType() << std::endl;
  }  
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
      int lvalue = this->getInteger(left);
      int rvalue = this->getInteger(right);
      return tree->tag == EQUAL ? lvalue == rvalue : lvalue != rvalue;
    case TYPE_FLOAT:
      double lvalue = this->getReal(left);
      double rvalue = this->getReal(right);
      return tree->tag == EQUAL ? lvalue == rvalue : lvalue != rvalue;
    case TYPE_ARRAY:
    case TYPE_POINTER:
      void *lpointer = this->getPointer(left);
      void *rpointer = this->getPointer(right);
      return tree->tag == EQUAL ? lpointer == rpointer : lpointer != rpointer;
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
  switch (tree->tag)
  {
  case NUM:
    return tree->numData;
  case INC:
  case DEC:
    tree = tree->children[0];
    if (tree->tag != ID)
    {
      throw "Type error";
    }
  case ID:
    SymbolTableEntry ste = getSymbolTableEntry(&this->symbolTable, tree->wordData);
    if (ste.getType().typ != TYPE_INT)
    {
      throw "Type error";
    }
    return *(int *)ste.variableAddress;
    // case '+':
    //   TypeObject *ltype = this->getType(tree->children[0]);
    //   TypeObject *rtype = this->getType(tree->children[1]);
  }
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