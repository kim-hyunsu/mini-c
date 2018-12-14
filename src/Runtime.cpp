#include "Runtime.hpp"
#include <iostream>
#include <stdio.h>

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
        else {
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

bool Runtime::findMain() {
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
    this->currentNode = ((ParseTree*)(ste.variableAddress))->children[3];
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
  if (tag == NONTERMINAL && wordData == "statements") {
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
    if (this->currentNode->children.size() == 0) {
      std::cout << "No ID at declaration." << std::endl;
    }
    auto list = this->currentNode->children[0];
    if (list->children.size() == 0 ) {
      std::cout << " No ID at declaration." << std::endl;
    }
    
    for (int i = 0; i < list->children.size(); i++) {
      auto ch = list->children[i];
      TypeObject *varType = new TypeObject(tag==INT ? TYPE_INT : TYPE_FLOAT);
      if (ch->tag == '=') {
        // declaration + initialization
        auto lch = ch->children[0];
        auto rch = ch->children[1];

        // TODO: should call 'eval' then initialize variables
      }
      else {
        // no declaration
        auto ptr = ch;
        while (ptr->tag != ID) {
          ptr = ptr->children[0];
          TypeObject *newType = new TypeObject(TYPE_POINTER);
          newType->baseType = varType;
          varType = newType;
        }
        if (ptr->children.size() == 1) {
          // array
          auto chch = ptr->children[0];
          TypeObject *newType = new TypeObject(TYPE_ARRAY);
          if (chch->children.size() == 1 && chch->children[0]->tag == NUM) {
            newType->arraySize.push_back(chch->children[0]->numData);
          }
          newType->baseType = varType;
          varType = newType;
        }
        else {
          // a simple declaration
        }
        void *mem;
        if (varType->typ == TYPE_ARRAY) {
          // should allocate array
          int size = varType->arraySize[0];
          if (varType->baseType->typ == TYPE_INT) {
            mem = new int[size]();
          }
          else if (varType->baseType->typ == TYPE_FLOAT) {
            mem = new float[size]();
          }
          else if (varType->baseType->typ == TYPE_POINTER) {
            mem = new void*[size]();
          }
        }
        else if (varType->typ == TYPE_POINTER) {
          mem = new void*();
        }
        else if (varType->typ == TYPE_INT) {
          mem = new int();
        }
        else if (varType->typ == TYPE_FLOAT) {
          mem = new float();
        }
        this->symbolTable.addNewSymbol(ch->wordData, *varType, mem);
      }
    }
    
    auto nxt = nextStatement(this->currentNode);
    if (nxt == nullptr) {
      // TODO: should return
    }
    else {
      this->currentNode = nxt;
    }
  }

  // IF statement
  else if (tag == IF) {
    ParseTree *cond;
    ParseTree *then;
    ParseTree *els;

    cond = children[0];
    then = children[1];
    if (children.size() == 3) {
      els = children[2];
    }

    // TODO: evaluate expression then jump
    bool condVal = true; // = this->eval(cond);
    if (condVal != 0) {
      this->currentNode = then;
    }
    else if (children.size() == 3) {
      this->currentNode = els;
    }
    else {
      auto nxt = nextStatement(this->currentNode);
      if (nxt == nullptr) {
        // TODO: should return
      }
      else {
        this->currentNode = nxt;
      }
    }
  }
  else if (tag == FOR) {
    auto init = children[0];
    auto cond = children[1];
    auto after = children[2];
    auto stmt = children[3];
  }
  else if (tag == RETURN) {
    auto expr = children[0];
    // TODO: eval expression, return it
  }
  else if (tag == PRINTF) {
    auto arg = children[0];
    if (children.size() == 1) {
      printf(arg->wordData.c_str());
    }
    else if (children.size() == 2) {
      auto expr = children[1];
      // TODO: eval expression, print it
      printf(arg->wordData.c_str(), expr);
    }

    auto nxt = nextStatement(this->currentNode);
    if (nxt == nullptr) {
      // TODO: should return
    }
    else {
      this->currentNode = nxt;
    }
  }
  // accidentaly jumped into next procedure
  else if (tag == NONTERMINAL && wordData == "procedure") {
    // TODO : should return (in interpreter space) immediately
  }

  // statement is expression
  else {
    // reuslt = this->eval(currentNode);
  }
  
  if (wordData == "IDtypeDeclaration")
  {
    // TODO
  }

  return end;
}

ParseTree* Runtime::nextStatement(ParseTree *crnt) {
  auto parent = crnt->parent;
  auto sibling = crnt->nextSibling;

  if (sibling != nullptr) {
    return sibling;
  }
  else {
    auto pt = crnt;
    while (true) {
      if (pt->nextSibling == nullptr && pt->parent != nullptr 
            && !(pt->parent->tag == NONTERMINAL && pt->parent->wordData == "procedure")) {
        pt = pt->parent;
      }
    }
    if (pt->parent == nullptr) {
      return nullptr;
    }
    if (pt->nextSibling != nullptr) {
      return pt->nextSibling;
    }
    else if (pt->parent->tag == NONTERMINAL && pt->parent->wordData == "procedure") {
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