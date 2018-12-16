#include "Runtime.hpp"
#include "../y.tab.h"
#include <iostream>
#include <stdio.h>

static SymbolTableEntry getSymbolTableEntry(SymbolTable *symbolTable, std::string name);

Runtime::Runtime(ParseTree *root) : root(root), nextLine(1), currentNode(root)
{
  this->symbolTable = SymbolTable();
  this->callStack = CallStack();
}

// from parse tree find procedures & add to symbol table
void Runtime::findProcedures()
{
  ParseTree *procedures = this->root;
  int num = procedures->children.size();
  for (int i = 0; i < num; i++)
  {
    auto pr = procedures->children[i];
    auto returnType = pr->children[0];
    auto name = pr->children[1];
    auto params = pr->children[2];

    TypeObject *returnBaseType;
    if (returnType->tag == VOID)
      returnBaseType = new TypeObject(TYPE_VOID);
    else if (returnType->tag == INT)
      returnBaseType = new TypeObject(TYPE_INT);
    else if (returnType->tag == FLOAT)
      returnBaseType = new TypeObject(TYPE_FLOAT);
    else
    {
      std::cout << "Procedure return type is wrong." << std::endl;
    }

    TypeObject *returnTypeObject = returnBaseType;
    for (int k = 0; k < returnType->children.size(); k++)
    {
      TypeObject *newType = new TypeObject(TYPE_POINTER);
      newType->baseType = returnTypeObject;
      returnTypeObject = newType;
    }

    std::vector<TypeObject *> parameters;
    for (int k = 0; k < params->children.size(); k++)
    {
      auto param = params->children[k];
      auto type = param->children[0];
      TypeObject *paramType;
      if (type->tag == INT)
        paramType = new TypeObject(TYPE_INT);
      else if (type->tag == FLOAT)
        paramType = new TypeObject(TYPE_FLOAT);
      else
      {
        std::cout << "Procedure parameter type is wrong." << std::endl;
      }

      auto ptr = param->children[1];

      while (ptr->tag != ID)
      {
        ptr = ptr->children[0];
        TypeObject *newType = new TypeObject(TYPE_POINTER);
        newType->baseType = paramType;
        paramType = newType;
      }
      if (ptr->children.size() > 0)
      {
        auto ar = ptr->children[0];
        int arsize = -1;
        if (ar->children.size() > 0)
        {
          arsize = ar->children[0]->numData;
        }
        else
        {
          std::cout << "Array size not specified at line #" << ptr->lineNumber << std::endl;
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

bool Runtime::findMain()
{
  int index = this->symbolTable.lookup("main");
  switch (index)
  {
  case -2: // Invisible
    std::cout << "main is invisble???" << std::endl;
    return false;
  case -1: // Not found
    std::cout << "main function is not found." << std::endl;
    return false;
  default:
    SymbolTableEntry ste = this->symbolTable.get(index);
    this->currentNode = ((ParseTree *)(ste.variableAddress))->children[3];
    std::cout << "main is at : " << ste.variableAddress << std::endl;
    return true;
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

  // block entry
  if (tag == NONTERMINAL && wordData == "statements")
  {
    // make new scope & jump into block
    this->symbolTable.newLevel();
    this->currentNode = children[0];
    this->runLine();
    return false;
  }

  // declaration
  if (tag == INT || tag == FLOAT)
  {
    std::cout << "Declaration." << std::endl;
    if (this->currentNode->children.size() == 0)
    {
      std::cout << "No ID at declaration." << std::endl;
    }
    auto list = this->currentNode->children[0];
    if (list->children.size() == 0)
    {
      std::cout << " No ID at declaration." << std::endl;
    }

    for (int i = 0; i < list->children.size(); i++)
    {
      auto ch = list->children[i];
      TypeObject *varType = new TypeObject(tag == INT ? TYPE_INT : TYPE_FLOAT);
      if (ch->tag == '=')
      {
        // declaration + initialization
        auto lch = ch->children[0];
        auto rch = ch->children[1];

        // TODO: should call 'eval' then initialize variables
      }
      else
      {
        // no declaration
        auto ptr = ch;
        while (ptr->tag != ID)
        {
          ptr = ptr->children[0];
          TypeObject *newType = new TypeObject(TYPE_POINTER);
          newType->baseType = varType;
          varType = newType;
        }
        if (ptr->children.size() == 1)
        {
          // array
          auto chch = ptr->children[0];
          TypeObject *newType = new TypeObject(TYPE_ARRAY);
          if (chch->children.size() == 1 && chch->children[0]->tag == NUM)
          {
            newType->arraySize.push_back(chch->children[0]->numData);
          }
          newType->baseType = varType;
          varType = newType;
        }
        else
        {
          // a simple declaration
        }
        void *mem;
        if (varType->typ == TYPE_ARRAY)
        {
          // should allocate array
          int size = varType->arraySize[0];
          if (varType->baseType->typ == TYPE_INT)
          {
            mem = new int[size]();
          }
          else if (varType->baseType->typ == TYPE_FLOAT)
          {
            mem = new float[size]();
          }
          else if (varType->baseType->typ == TYPE_POINTER)
          {
            mem = new void *[size]();
          }
        }
        else if (varType->typ == TYPE_POINTER)
        {
          mem = new void *();
        }
        else if (varType->typ == TYPE_INT)
        {
          mem = new int();
        }
        else if (varType->typ == TYPE_FLOAT)
        {
          mem = new float();
        }
        this->symbolTable.addNewSymbol(ch->wordData, *varType, mem);
      }
    }

    auto nxt = nextStatement(this->currentNode);
    if (nxt == nullptr)
    {
      // TODO: should return
    }
    else
    {
      this->currentNode = nxt;
    }
  }

  // IF statement
  else if (tag == IF)
  {
    ParseTree *cond;
    ParseTree *then;
    ParseTree *els;

    cond = children[0];
    then = children[1];
    if (children.size() == 3)
    {
      els = children[2];
    }

    // TODO: evaluate expression then jump
    bool condVal = true; // = this->eval(cond);
    if (condVal != 0)
    {
      this->currentNode = then;
    }
    else if (children.size() == 3)
    {
      this->currentNode = els;
    }
    else
    {
      auto nxt = nextStatement(this->currentNode);
      if (nxt == nullptr)
      {
        // TODO: should return
      }
      else
      {
        this->currentNode = nxt;
      }
    }
  }
  else if (tag == FOR)
  {
    auto init = children[0];
    auto cond = children[1];
    auto after = children[2];
    auto stmt = children[3];
  }
  else if (tag == RETURN)
  {
    auto expr = children[0];
    // TODO: eval expression, return it
  }
  else if (tag == PRINTF)
  {
    auto arg = children[0];
    if (children.size() == 1)
    {
      printf(arg->wordData.c_str());
    }
    else if (children.size() == 2)
    {
      auto expr = children[1];
      // TODO: eval expression, print it
      Value v = this->evaluate(expr);
      printf(arg->wordData.c_str(), v.integer);
    }

    auto nxt = nextStatement(this->currentNode);
    if (nxt == nullptr)
    {
      // TODO: should return
    }
    else
    {
      this->currentNode = nxt;
    }
  }
  // accidentaly jumped into next procedure
  else if (tag == NONTERMINAL && wordData == "procedure")
  {
    // TODO : should return (in interpreter space) immediately
  }

  // statement is expression
  else
  {
    std::cout << "evaluate: " << currentNode->tag << std::endl;
    this->evaluate(currentNode);
  }

  if (wordData == "IDtypeDeclaration")
  {
    // TODO
  }

  return end;
}

ParseTree *Runtime::nextStatement(ParseTree *crnt)
{
  auto parent = crnt->parent;
  auto sibling = crnt->nextSibling;

  if (sibling != nullptr)
  {
    return sibling;
  }
  else
  {
    auto pt = crnt;
    while (true)
    {
      if (pt->nextSibling == nullptr && pt->parent != nullptr && !(pt->parent->tag == NONTERMINAL && pt->parent->wordData == "procedure"))
      {
        pt = pt->parent;
      }
    }
    if (pt->parent == nullptr)
    {
      return nullptr;
    }
    if (pt->nextSibling != nullptr)
    {
      return pt->nextSibling;
    }
    else if (pt->parent->tag == NONTERMINAL && pt->parent->wordData == "procedure")
    {
      return nullptr;
    }
  }
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
  case '<':
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
      value.boolean = lvalue.boolean < rvalue.boolean;
      break;
    case TYPE_INT:
      value.boolean = lvalue.integer < rvalue.integer;
      break;
    case TYPE_FLOAT:
      value.boolean = lvalue.real < rvalue.real;
      break;
    case TYPE_POINTER:
      value.boolean = lvalue.pointer < rvalue.pointer;
      break;
    }
    value.type = TYPE_BOOL;
    break;
  }
  case '>':
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
      value.boolean = lvalue.boolean > rvalue.boolean;
      break;
    case TYPE_INT:
      value.boolean = lvalue.integer > rvalue.integer;
      break;
    case TYPE_FLOAT:
      value.boolean = lvalue.real > rvalue.real;
      break;
    case TYPE_POINTER:
      value.boolean = lvalue.pointer > rvalue.pointer;
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
    if (lvalue.type == TYPE_INT && rvalue.type == TYPE_INT)
    {
      value.integer = lvalue.integer + rvalue.integer;
      value.type = TYPE_INT;
    }
    else if (lvalue.type == TYPE_FLOAT || rvalue.type == TYPE_FLOAT)
    {
      float firstTerm = lvalue.type == TYPE_INT ? (float)lvalue.integer : lvalue.real;
      float secondTerm = rvalue.type == TYPE_INT ? (float)rvalue.integer : rvalue.real;
      value.real = firstTerm + secondTerm;
      value.type = TYPE_FLOAT;
    }
    else if (lvalue.type == TYPE_POINTER && rvalue.type == TYPE_POINTER)
    {
      throw "type error";
    }
    /*
    else if (lvalue.type == TYPE_POINTER || rvalue.type == TYPE_POINTER)
    {
      int firstTerm = lvalue.type == TYPE_POINTER ? (int)lvalue.pointer : lvalue.integer;
      int secondTerm = rvalue.type == TYPE_POINTER ? (int)rvalue.pointer : rvalue.integer;
      value.pointer = (void *)(firstTerm + secondTerm);
      value.type = TYPE_INT;
    }
    */
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
    if (lvalue.type == TYPE_INT && rvalue.type == TYPE_INT)
    {
      value.integer = lvalue.integer - rvalue.integer;
      value.type = TYPE_INT;
    }
    else if (lvalue.type == TYPE_FLOAT || rvalue.type == TYPE_FLOAT)
    {
      float firstTerm = lvalue.type == TYPE_INT ? (float)lvalue.integer : lvalue.real;
      float secondTerm = rvalue.type == TYPE_INT ? (float)rvalue.integer : rvalue.real;
      value.real = firstTerm - secondTerm;
      value.type = TYPE_FLOAT;
    }
    /*
    else if (lvalue.type == TYPE_POINTER || rvalue.type == TYPE_POINTER)
    {
      //unsigned int firstTerm = lvalue.type == TYPE_POINTER ? (int)lvalue.pointer : lvalue.integer;
      //unsigned int secondTerm = rvalue.type == TYPE_POINTER ? (int)rvalue.pointer : rvalue.integer;
      //value.pointer = (void *)(firstTerm - secondTerm);
      // should fix later
      value.integer = (int*)lvalue.pointer - (int*)rvalue.pointer;
      value.type = TYPE_INT;
    }
    */
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
    if (lvalue.type == TYPE_INT && rvalue.type == TYPE_INT)
    {
      value.integer = lvalue.integer * rvalue.integer;
      value.type = TYPE_INT;
    }
    else if (lvalue.type == TYPE_FLOAT || rvalue.type == TYPE_FLOAT)
    {
      float firstTerm = lvalue.type == TYPE_INT ? (float)lvalue.integer : lvalue.real;
      float secondTerm = rvalue.type == TYPE_INT ? (float)rvalue.integer : rvalue.real;
      value.real = firstTerm * secondTerm;
      value.type = TYPE_FLOAT;
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
    if (lvalue.type == TYPE_INT && rvalue.type == TYPE_INT)
    {
      value.integer = lvalue.integer / rvalue.integer;
      value.type = TYPE_INT;
    }
    else if (lvalue.type == TYPE_FLOAT || rvalue.type == TYPE_FLOAT)
    {
      float firstTerm = lvalue.type == TYPE_INT ? (float)lvalue.integer : lvalue.real;
      float secondTerm = rvalue.type == TYPE_INT ? (float)rvalue.integer : rvalue.real;
      value.real = firstTerm / secondTerm;
      value.type = TYPE_FLOAT;
    }
    else
    {
      throw "type error";
    }
    break;
  }
  case INC:
  {
    Value rvalue = this->evaluate(tree->children[0]);
    value.type = rvalue.type;
    if (rvalue.type == TYPE_INT)
    {
      value.integer = rvalue.integer;
      rvalue.integer++;
    }
    else if (rvalue.type == TYPE_FLOAT)
    {
      value.real = rvalue.real;
      rvalue.real++;
    }
    else if (rvalue.type == TYPE_POINTER)
    {
      value.pointer = rvalue.pointer;
      rvalue.pointer = (int *)rvalue.pointer + 1;
    }
    else
      throw "Type error";
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
      int line = ltree->lineNumber;
      arrayIndex = arrayIndexValue.integer;
      int index = this->symbolTable.lookup(variableName);
      if (index < 0)
        throw "Not declared";
      this->symbolTable.setArrayEntry(index, arrayIndex, rvalue, line);
    }
    else
    {
      int index = this->symbolTable.lookup(variableName);
      int line = tree->children[0]->lineNumber;
      if (index < 0)
        throw "Not declared";
      this->symbolTable.set(index, rvalue, line);
    }
    break;
  }
  case DEC:
  {
    Value rvalue = this->evaluate(tree->children[0]);
    value.type = rvalue.type;
    if (rvalue.type == TYPE_INT)
    {
      value.integer = rvalue.integer;
      rvalue.integer--;
    }
    else if (rvalue.type == TYPE_FLOAT)
    {
      value.real = rvalue.real;
      rvalue.real--;
    }
    else if (rvalue.type == TYPE_POINTER)
    {
      value.pointer = rvalue.pointer;
      rvalue.pointer = (int *)rvalue.pointer - 1;
    }
    else
      throw "Type error";
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
      int line = ltree->lineNumber;
      arrayIndex = arrayIndexValue.integer;
      int index = this->symbolTable.lookup(variableName);
      if (index < 0)
        throw "Not declared";
      this->symbolTable.setArrayEntry(index, arrayIndex, rvalue, line);
    }
    else
    {
      int index = this->symbolTable.lookup(variableName);
      int line = tree->children[0]->lineNumber;
      if (index < 0)
        throw "Not declared";
      this->symbolTable.set(index, rvalue, line);
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
      int line = ltree->lineNumber;
      arrayIndex = arrayIndexValue.integer;
      int index = this->symbolTable.lookup(variableName);
      if (index < 0)
        throw "Not declared";
      this->symbolTable.setArrayEntry(index, arrayIndex, rvalue, line);
    }
    else
    {
      int index = this->symbolTable.lookup(variableName);
      int line = tree->children[0]->lineNumber;
      if (index < 0)
        throw "Not declared";
      this->symbolTable.set(index, rvalue, line);
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