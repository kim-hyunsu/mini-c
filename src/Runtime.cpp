#include "Runtime.hpp"
#include "../y.tab.h"
#include <iostream>
#include <stdio.h>

static SymbolTableEntry *getSymbolTableEntry(SymbolTable *symbolTable, std::string name);

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
    SymbolTableEntry *ste = this->symbolTable.get(index);
    this->currentNode = ((ParseTree *)(ste->variableAddress))->children[3];
    std::cout << "main is at : " << ste->variableAddress << std::endl;
    return true;
  }
}

bool Runtime::next(int lines)
{
  bool end = false;
  if (this->end == true) return this->end;
  try
  {
    for (int i = 0; i < lines; i++)
    {
      end = this->runLine();
    }
  }
  catch (exception &e)
  {
    std::cout << "ERROR!" << std::endl;
  }
  if (end == true) this->end = true;
  return end;
}

bool Runtime::runLine()
{
  if (functionCall == true) functionCall = false;
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
    return end;
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

        Value rval = this->evaluate(rch);
        if (functionCall == true) return false;

        auto ptr = lch;
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
        this->symbolTable.addNewSymbol(lch->wordData, *varType, mem);
        int idx = this->symbolTable.lookup(lch->wordData);
        if (!isSameType(varType, rval.type))
        {
          if (varType->typ == TYPE_FLOAT && rval.type->typ == TYPE_INT)
          {
            rval.type->typ = TYPE_FLOAT;
            rval.real = (float)rval.integer;
          }
          else {
            std::cout << "initialization type mismatch" << std::endl;
          }
        }
        this->symbolTable.set(idx, rval, lch->lineNumber);
      }
      else
      {
        // no initialization
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
    if (nxt == this->currentNode)
    {
      return true;
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
    Value condVal = this->evaluate(cond);
    if (functionCall == true) return false;

    if (condVal.boolean)
    {
      std::cout << "IF : then" << std::endl;
      this->currentNode = then;
    }
    else if (children.size() == 3)
    {
      std::cout << "IF : else" << std::endl;
      this->currentNode = els;
    }
    else
    {
      auto nxt = nextStatement(this->currentNode);
      if (nxt == this->currentNode)
      {
        return true;
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

    if (!forBlockEnd)
    {
      Value initVal = this->evaluate(init);
      if (functionCall == true) return false;
    }
    else
    {
      Value afterVal = this->evaluate(after);
      if (functionCall == true) return false;
      forBlockEnd = false;
    }
    Value condVal = this->evaluate(cond);
    if (functionCall == true) return false;

    if (condVal.boolean)
    {
      std::cout << "for loop" << std::endl;
      this->currentNode = stmt;
    }
    else
    {
      std::cout << "for loop end" << std::endl;
      this->currentNode = nextStatement(this->currentNode);
    }
  }
  else if (tag == RETURN)
  {
    if (children.size() == 1) {
      auto expr = children[0];
      Value returnVal = this->evaluate(expr);
      if (functionCall == true) return false;
      auto function = this->currentNode;

      // find returnType
      while (!(function->tag == NONTERMINAL && function->wordData == "procedure")) {
        function = function->parent;
      }
      auto functionName = function->children[1]->wordData;
      int index = this->symbolTable.lookup(functionName);
      auto ste = this->symbolTable.get(index);
      auto returnType = ste->getType()->returnType;
      if (!isSameType(returnType, returnVal.type)) {
        if (returnType->typ == TYPE_FLOAT && returnVal.type->typ == TYPE_INT) {
          returnVal.type->typ = TYPE_FLOAT;
          returnVal.real = (float)returnVal.integer;
        }
        else {
          std::cout << "return type does not match" << std::endl;
          throw "type error";
        }
      }

      this->returnValue = returnVal;
      this->returned = true;
      auto returnInfo = this->callStack.deleteEntry();
      this->currentNode = returnInfo.first;
      this->symbolTable.deleteProcedure(returnInfo.second);
    }
    else {
      // return nothing
      auto expr = children[0];
      Value returnVal = this->evaluate(expr);
      if (functionCall == true) return false;
      auto function = this->currentNode;
      
      this->returnValue = Value();
      this->returned = true;
      auto returnInfo = this->callStack.deleteEntry();
      this->currentNode = returnInfo.first;
      this->symbolTable.deleteProcedure(returnInfo.second);
    }
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
      if (functionCall == true) return false;
      printf(arg->wordData.c_str(), v.integer);
    }

    auto nxt = nextStatement(this->currentNode);
    if (nxt == this->currentNode)
    {
      return true;
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
    this->evaluate(currentNode);
    if (functionCall == true) return false;
    auto nxt = nextStatement(this->currentNode);
    if (nxt == this->currentNode)
    {
      return true;
    }
    else
    {
      this->currentNode = nxt;
    }
  }

  if (wordData == "IDtypeDeclaration")
  {
    // TODO
  }

  ParseTree::clearTempValue(this->currentNode);
  return end;
}

ParseTree *Runtime::nextStatement(ParseTree *crnt)
{
  auto parent = crnt->parent;
  auto sibling = crnt->nextSibling;

  if (parent == nullptr)
  {
    std::cout << "nextStatement called from root! something is very wrong." << std::endl;
    return crnt;
  }
  else
  {
    auto ptag = parent->tag;
    switch (ptag)
    {
    case NONTERMINAL:
    {
      std::string pname = parent->wordData;
      if (pname == "statements")
      {
        if (sibling != nullptr)
        {
          return sibling;
        }
        else
        {
          bool dLevel = this->symbolTable.deleteLevel();
          if (dLevel == true) {
            this->end = true;
            return crnt;
          }

          return nextStatement(parent);
        }
      }
    }
    case IF:
    {
      if (crnt == parent->children[1])
      {
        // this is then block's end
        return nextStatement(parent);
      }
      else
      {
        // this is else block's end
        return nextStatement(parent);
      }
    }
    case FOR:
    {
      this->forBlockEnd = true;
      return parent;
    }
    }
  }
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
  std::cout << "print: " << var << std::endl;
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
    SymbolTableEntry *ste = this->symbolTable.get(index);
    value = ste->getValue();
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
    SymbolTableEntry *ste = this->symbolTable.get(index);
    history = ste->getHistory(var);
  }
  return history;
}

Value Runtime::evaluate(ParseTree *tree)
{
  if (tree->evaluated) {
    std::cout << "already evaluated" << std::endl;
    return tree->value;
  }
  std::cout << "evaluate: ";
  Value value;
  switch (tree->tag)
  {
  case EQUAL:
  {
    std::cout << "==" << std::endl;
    Value lvalue = this->evaluate(tree->children[0]);
    if (functionCall == true) return Value();
    Value rvalue = this->evaluate(tree->children[1]);
    if (functionCall == true) return Value();
    //if (!isSameType(lvalue.type, rvalue.type))
    //{
    //  throw "Type error";
    //}
    switch (lvalue.type->typ)
    {
    case TYPE_BOOL:
      value.boolean = lvalue.boolean == lvalue.boolean;
      break;
    case TYPE_INT:
      value.boolean = lvalue.integer == rvalue.integer;
      break;
    case TYPE_FLOAT:
      value.boolean = lvalue.real == rvalue.real;
      break;
    case TYPE_POINTER:
    case TYPE_ARRAY:
      value.boolean = lvalue.pointer == rvalue.pointer;
      break;
    }
    value.type = new TypeObject(TYPE_BOOL);
    break;
  }
  case NEQUAL:
  {
    std::cout << "!=" << std::endl;
    Value lvalue = this->evaluate(tree->children[0]);
    if (functionCall == true) return Value();
    Value rvalue = this->evaluate(tree->children[1]);
    if (functionCall == true) return Value();
    //if (!isSameType(lvalue.type, rvalue.type))
    //{
    //  throw "Type error";
    //}
    switch (lvalue.type->typ)
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
    case TYPE_ARRAY:
      value.boolean = lvalue.pointer != rvalue.pointer;
      break;
    }
    value.type = new TypeObject(TYPE_BOOL);
    break;
  }
  case '<':
  {
    std::cout << "<" << std::endl;
    Value lvalue = this->evaluate(tree->children[0]);
    if (functionCall == true) return Value();
    Value rvalue = this->evaluate(tree->children[1]);
    if (functionCall == true) return Value();
    //if (!isSameType(lvalue.type, rvalue.type))
    //{
    //  throw "Type error";
    //}
    switch (lvalue.type->typ)
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
    case TYPE_ARRAY:
      value.boolean = lvalue.pointer < rvalue.pointer;
      break;
    }
    value.type = new TypeObject(TYPE_BOOL);
    break;
  }
  case '>':
  {
    std::cout << ">" << std::endl;
    Value lvalue = this->evaluate(tree->children[0]);
    if (functionCall == true) return Value();
    Value rvalue = this->evaluate(tree->children[1]);
    if (functionCall == true) return Value();
    //if (!isSameType(lvalue.type, rvalue.type))
    //{
    //  throw "Type error";
    //}
    switch (lvalue.type->typ)
    {
    case TYPE_BOOL:
    case TYPE_INT:
    case TYPE_FLOAT:
      value.boolean = VALUE(lvalue.type->typ, lvalue) > VALUE(rvalue.type->typ, rvalue);
      break;
    case TYPE_POINTER:
    case TYPE_ARRAY:
      value.boolean = lvalue.pointer > rvalue.pointer;
      break;
    }
    std::cout << "value.boolean" << value.boolean << std::endl;
    value.type = new TypeObject(TYPE_BOOL);
    break;
  }
  case NUM:
  {
    std::cout << tree->numData << std::endl;
    value.integer = tree->numData;
    value.type = new TypeObject(TYPE_INT);
    break;
  }
  case REAL:
  {
    std::cout << tree->realData << std::endl;
    value.real = tree->realData;
    value.type = new TypeObject(TYPE_FLOAT);
    break;
  }
  case ID:
  {
    std::cout << tree->wordData << std::endl;
    SymbolTableEntry *ste = getSymbolTableEntry(&this->symbolTable, tree->wordData);
    TypeObject *type = ste->getType();
    value.type = type;
    value.ste = ste;
    value.line = tree->lineNumber;
    value.address = ste->variableAddress;
    switch (type->typ)
    {
    case TYPE_INT:
      value.integer = *(int *)ste->variableAddress;
      break;
    case TYPE_FLOAT:
      value.real = *(float *)ste->variableAddress;
      break;
    case TYPE_POINTER:
    case TYPE_ARRAY:
      value.pointer = *(void **)ste->variableAddress;
      value.type = type;
      break;
    default:
      throw "Type error";
    }
    break;
  }
  case '+':
  {
    std::cout << "+" << std::endl;
    Value lvalue = this->evaluate(tree->children[0]);
    if (functionCall == true) return Value();
    Value rvalue = this->evaluate(tree->children[1]);
    if (functionCall == true) return Value();
    if (lvalue.type->typ == TYPE_INT && rvalue.type->typ == TYPE_INT)
    {
      value.integer = lvalue.integer + rvalue.integer;
      value.type = new TypeObject(TYPE_INT);
    }
    else if (lvalue.type->typ == TYPE_FLOAT || rvalue.type->typ == TYPE_FLOAT)
    {
      float firstTerm = lvalue.type->typ == TYPE_INT ? (float)lvalue.integer : lvalue.real;
      float secondTerm = rvalue.type->typ == TYPE_INT ? (float)rvalue.integer : rvalue.real;
      value.real = firstTerm + secondTerm;
      value.type = new TypeObject(TYPE_FLOAT);
    }
    else if (lvalue.type->typ == TYPE_POINTER && rvalue.type->typ == TYPE_POINTER)
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
    std::cout << "-" << std::endl;
    Value lvalue = this->evaluate(tree->children[0]);
    if (functionCall == true) return Value();
    Value rvalue = this->evaluate(tree->children[1]);
    if (functionCall == true) return Value();
    if (lvalue.type->typ == TYPE_INT && rvalue.type->typ == TYPE_INT)
    {
      value.integer = lvalue.integer - rvalue.integer;
      value.type = new TypeObject(TYPE_INT);
    }
    else if (lvalue.type->typ == TYPE_FLOAT || rvalue.type->typ == TYPE_FLOAT)
    {
      float firstTerm = lvalue.type->typ == TYPE_INT ? (float)lvalue.integer : lvalue.real;
      float secondTerm = rvalue.type->typ == TYPE_INT ? (float)rvalue.integer : rvalue.real;
      value.real = firstTerm - secondTerm;
      value.type = new TypeObject(TYPE_FLOAT);
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
    if (tree->children.size() == 2)
    {
      std::cout << "*(times)" << std::endl;
      Value lvalue = this->evaluate(tree->children[0]);
      if (functionCall == true) return Value();
      Value rvalue = this->evaluate(tree->children[1]);
      if (functionCall == true) return Value();
      if (lvalue.type->typ == TYPE_INT && rvalue.type->typ == TYPE_INT)
      {
        value.integer = lvalue.integer * rvalue.integer;
        value.type = new TypeObject(TYPE_INT);
      }
      else if (lvalue.type->typ == TYPE_FLOAT || rvalue.type->typ == TYPE_FLOAT)
      {
        float firstTerm = lvalue.type->typ == TYPE_INT ? (float)lvalue.integer : lvalue.real;
        float secondTerm = rvalue.type->typ == TYPE_INT ? (float)rvalue.integer : rvalue.real;
        value.real = firstTerm * secondTerm;
        value.type = new TypeObject(TYPE_FLOAT);
      }
      else
      {
        throw "type error";
      }
    }
    else if (tree->children.size() == 1)
    {
      std::cout << "*(pointer)" << std::endl;
      Value rvalue = this->evaluate(tree->children[0]);
      if (functionCall == true) return Value();
      if (rvalue.type->typ != TYPE_POINTER)
      {
        throw "Type error";
      }
      value.type = rvalue.type->baseType;
      value.line = rvalue.line;
      value.ste = rvalue.ste;
      value.address = rvalue.pointer;
      switch (value.type->typ)
      {
      case TYPE_INT:
        value.integer = *(int *)rvalue.pointer;
        break;
      case TYPE_FLOAT:
        value.real = *(float *)rvalue.pointer;
        break;
      case TYPE_POINTER:
      case TYPE_ARRAY:
        value.pointer = *(void **)rvalue.pointer;
        break;
      default:
        throw "Type error";
      }
    }
    else
    {
      throw "Type error";
    }
    break;
  }
  case '/':
  {
    std::cout << "/" << std::endl;
    Value lvalue = this->evaluate(tree->children[0]);
    if (functionCall == true) return Value();
    Value rvalue = this->evaluate(tree->children[1]);
    if (functionCall == true) return Value();
    if (lvalue.type->typ == TYPE_INT && rvalue.type->typ == TYPE_INT)
    {
      value.integer = lvalue.integer / rvalue.integer;
      value.type = new TypeObject(TYPE_INT);
    }
    else if (lvalue.type->typ == TYPE_FLOAT || rvalue.type->typ == TYPE_FLOAT)
    {
      float firstTerm = lvalue.type->typ == TYPE_INT ? (float)lvalue.integer : lvalue.real;
      float secondTerm = rvalue.type->typ == TYPE_INT ? (float)rvalue.integer : rvalue.real;
      value.real = firstTerm / secondTerm;
      value.type = new TypeObject(TYPE_FLOAT);
    }
    else
    {
      throw "type error";
    }
    break;
  }
  case INC:
  {
    std::cout << "++" << std::endl;
    Value rvalue = this->evaluate(tree->children[0]);
    if (functionCall == true) return Value();
    value.type = rvalue.type;
    if (rvalue.type->typ == TYPE_INT)
    {
      value.integer = rvalue.integer;
      rvalue.integer++;
    }
    else if (rvalue.type->typ == TYPE_FLOAT)
    {
      value.real = rvalue.real;
      rvalue.real++;
    }
    else if (rvalue.type->typ == TYPE_POINTER)
    {
      value.pointer = rvalue.pointer;
      switch (rvalue.type->baseType->typ)
      {
      case TYPE_INT:
        rvalue.pointer = (int *)rvalue.pointer + 1;
        break;
      case TYPE_FLOAT:
        rvalue.pointer = (float *)rvalue.pointer + 1;
        break;
      case TYPE_POINTER:
      case TYPE_ARRAY:
        rvalue.pointer = (void **)rvalue.pointer + 1;
        break;
      default:
        throw "Type error";
      }
    }
    else
    {
      throw "Type error";
    }
    switch (rvalue.type->typ)
    {
    case TYPE_INT:
    {
      int *addr = (int *)rvalue.address;
      *addr = rvalue.integer;
      rvalue.ste->history.addEntry(rvalue.line, rvalue.integer);
      rvalue.ste->setAssigned(true);
      break;
    }
    case TYPE_FLOAT:
    {
      float *addr = (float *)rvalue.address;
      *addr = rvalue.real;
      rvalue.ste->history.addEntry(rvalue.line, rvalue.real);
      rvalue.ste->setAssigned(true);
      break;
    }
    case TYPE_POINTER:
    case TYPE_ARRAY:
    {
      void **addr = (void **)rvalue.address;
      *addr = rvalue.pointer;
      rvalue.ste->history.addEntry(rvalue.line, rvalue.pointer);
      rvalue.ste->setAssigned(true);
      break;
    }
    }
    break;
  }
  case DEC:
  {
    std::cout << "--" << std::endl;
    Value rvalue = this->evaluate(tree->children[0]);
    if (functionCall == true) return Value();
    value.type = rvalue.type;
    if (rvalue.type->typ == TYPE_INT)
    {
      value.integer = rvalue.integer;
      rvalue.integer--;
    }
    else if (rvalue.type->typ == TYPE_FLOAT)
    {
      value.real = rvalue.real;
      rvalue.real--;
    }
    else if (rvalue.type->typ == TYPE_POINTER)
    {
      value.pointer = rvalue.pointer;
      switch (rvalue.type->baseType->typ)
      {
      case TYPE_INT:
        rvalue.pointer = (int *)rvalue.pointer - 1;
        break;
      case TYPE_FLOAT:
        rvalue.pointer = (float *)rvalue.pointer - 1;
        break;
      case TYPE_POINTER:
      case TYPE_ARRAY:
        rvalue.pointer = (void **)rvalue.pointer - 1;
        break;
      default:
        throw "Type error";
      }
    }
    else
    {
      throw "Type error";
    }
    switch (rvalue.type->typ)
    {
    case TYPE_INT:
    {
      int *addr = (int *)rvalue.address;
      *addr = rvalue.integer;
      rvalue.ste->history.addEntry(rvalue.line, rvalue.integer);
      rvalue.ste->setAssigned(true);
      break;
    }
    case TYPE_FLOAT:
    {
      float *addr = (float *)rvalue.address;
      *addr = rvalue.real;
      rvalue.ste->history.addEntry(rvalue.line, rvalue.real);
      rvalue.ste->setAssigned(true);
      break;
    }
    case TYPE_POINTER:
    case TYPE_ARRAY:
    {
      void **addr = (void **)rvalue.address;
      *addr = rvalue.pointer;
      rvalue.ste->history.addEntry(rvalue.line, rvalue.pointer);
      rvalue.ste->setAssigned(true);
      break;
    }
    }
    break;
  }
  case '=':
  {
    std::cout << "=" << std::endl;
    Value lvalue = this->evaluate(tree->children[0]);
    if (functionCall == true) return Value();
    Value rvalue = this->evaluate(tree->children[1]);
    if (functionCall == true) return Value();
    // if (!isSameType(lvalue.type, rvalue.type))
    // {
    //   throw "Type error";
    // }
    switch (lvalue.type->typ)
    {
    case TYPE_INT:
    {
      if (rvalue.type->typ != TYPE_FLOAT && rvalue.type->typ != TYPE_INT)
        throw "Type error";
      int *addr = (int *)lvalue.address;
      *addr = rvalue.type->typ == TYPE_FLOAT ? (int)rvalue.real : rvalue.integer;
      // *addr = rvalue.integer;
      lvalue.ste->history.addEntry(lvalue.line, *addr);
      lvalue.ste->setAssigned(true);
      break;
    }
    case TYPE_FLOAT:
    {
      if (rvalue.type->typ != TYPE_FLOAT && rvalue.type->typ != TYPE_INT)
        throw "Type error";
      float *addr = (float *)lvalue.address;
      *addr = rvalue.type->typ == TYPE_FLOAT ? rvalue.real : (float)rvalue.integer;
      lvalue.ste->history.addEntry(lvalue.line, *addr);
      lvalue.ste->setAssigned(true);
      break;
    }
    case TYPE_POINTER:
    case TYPE_ARRAY:
    {
      if (rvalue.type->typ != TYPE_POINTER && rvalue.type->typ != TYPE_ARRAY)
        throw "Type error";
      void **addr = (void **)lvalue.address;
      *addr = rvalue.pointer;
      lvalue.ste->history.addEntry(lvalue.line, *addr);
      lvalue.ste->setAssigned(true);
      break;
    }
    default:
    {
      std::cout << "lvalue type: " << lvalue.type->typ << std::endl;
      throw "Type error";
    }
    }
    break;
  }
  default:
  {
    if (tree->wordData == "subscript")
    {
      std::cout << "[]" << std::endl;
      Value lvalue = this->evaluate(tree->children[0]);
      if (functionCall == true) return Value();
      Value rvalue = this->evaluate(tree->children[1]);
      if (functionCall == true) return Value();
      std::cout << "lvalue type : " << lvalue.type->typ << std::endl;
      std::cout << "lvalue basetype : " << lvalue.type->baseType->typ << std::endl;
      if (rvalue.type->typ != TYPE_INT)
        throw "Type error";
      // if (lvalue.type->typ != TYPE_ARRAY)
      //   throw "Type error";
      value.type = lvalue.type->baseType;
      value.line = lvalue.line;
      value.ste = lvalue.ste;
      switch (value.type->typ)
      {
      case TYPE_INT:
        value.integer = *((int *)lvalue.address + rvalue.integer);
        value.address = ((int *)lvalue.address + rvalue.integer);
        break;
      case TYPE_FLOAT:
        value.real = *((float *)lvalue.address + rvalue.integer);
        value.address = ((float *)lvalue.address + rvalue.integer);
        ;
        break;
      case TYPE_POINTER:
      case TYPE_ARRAY:
        value.pointer = *((void **)lvalue.address + rvalue.integer);
        value.address = ((void **)lvalue.address + rvalue.integer);
        break;
      default:
        throw "Type error";
      }
    }
    else if (tree->wordData == "call") {
      // set return value
      if (this->returned) {
        std::cout << "already called the function" << std::endl;
        tree->value = this->returnValue;
        tree->evaluated = true;
        this->returned = false;
        return tree->value;
      }
      auto funcTree = tree->children[0];
      auto argsTree = tree->children[1];
      std::cout << "function call : " << funcTree->wordData << std::endl;
      auto funcIndex = this->symbolTable.lookup(funcTree->wordData);
      if (funcIndex < 0)
      {
        std::cout << "function not found" << std::endl;
        throw "";
      }
      // put current node into call stack
      this->callStack.addEntry(std::pair<ParseTree*, int>(this->currentNode, this->symbolTable.currentLevel()));

      auto functionEntry = this->symbolTable.get(funcIndex);
      auto funcParameterTypes = functionEntry->getType()->parameterTypes;
      auto function = (ParseTree*)(functionEntry->variableAddress);

      // evaluate arguments
      if (argsTree->children.size() != funcParameterTypes.size()) {
        std::cout << "function parameter number mismatch" <<std::endl;
      }
      std::vector<Value> argVals = std::vector<Value>();
      for (int i = 0; i < argsTree->children.size(); i++)
      {
        Value val = this->evaluate(argsTree->children[i]);
        if (!isSameType(funcParameterTypes[i], val.type))
        {
          if (funcParameterTypes[i]->typ == TYPE_FLOAT && val.type->typ == TYPE_INT)
          {
            val.type->typ = TYPE_FLOAT;
            val.real = (float)val.integer;
          }
          else if (funcParameterTypes[i]->typ == TYPE_POINTER && val.type->typ == TYPE_ARRAY)
          {
            val.type->typ = TYPE_POINTER;
          }
          else 
          {
            std::cout << "function parameter type does not match" << std::endl;

          }
        }
        argVals.push_back(val);
      }
      std::cout << "function call : " << funcTree->wordData << " : parameters evaluated." << std::endl;

      // put argument into symbolTable
      this->symbolTable.newProcedure();
      auto pr = function;
      auto params = pr->children[2];
      for (int i = 0; i < argVals.size();i++) {
        auto ptr = params->children[i]->children[1];
        while (ptr->tag != ID) {
          ptr = ptr->children[0];
        }
        std::string parameterID = ptr->wordData;
        auto varType = argVals[i].type;
        void *mem;
        if (varType->typ == TYPE_ARRAY)
        {
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
        this->symbolTable.addNewSymbol(parameterID, *(argVals[i].type), mem);
        int index = this->symbolTable.lookup(parameterID);
        this->symbolTable.set(index, argVals[i], pr->lineNumber);
      }
      std::cout << "function call : " << funcTree->wordData << " : " << argVals.size() << " parameters allocated." << std::endl;


      this->functionCall = true;
      this->currentNode = (function->children[3]);
      std::cout << "function call : " << funcTree->wordData<< ", jump to " << this->currentNode << std::endl;
      return Value();
      // procedure call end
    }
    else
    {
      throw "Type error";
    }
  }
  }
  tree->evaluated = true;
  return value;
}

static SymbolTableEntry *getSymbolTableEntry(SymbolTable *symbolTable, std::string name)
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