#include "parser.hpp"

Parser::Parser(std::string filename) : cursor(0) {
  std::ifstream fs;
  fs.open(filename, std::ios_base::openmode::_S_in);
  this->lexer.input.swap(fs);
}

void Parser::tokenize() {
  for (int i = 0; true; i++) {
    Token t = lexer.scan();
    if (t.tag == -1) {
      break;
    }
    else {
      if (tokenType(t.tag) == -1) {
        tokens.push_back(std::pair<void*, Token>(nullptr, t));
        std::cout << "|" << t.tag << ":" << (char)t.tag << " ";
      }
      else if (tokenType(t.tag) == NUM) {
        int* addr = new int(lexer.numData);
        tokens.push_back(std::pair<void*, Token>(addr, t));
        std::cout << "|" << t.tag << ":" << lexer.numData << " ";
      } 
      else if (tokenType(t.tag) == REAL) {
        double* addr = new double(lexer.numData);
        tokens.push_back(std::pair<void*, Token>(addr, t));
        std::cout << "|" << t.tag << ":" << lexer.realData << " ";
      } 
      else if (tokenType(t.tag) == 0) {
        std::string* addr = new std::string(lexer.wordData);
        tokens.push_back(std::pair<void*, Token>(addr, t));
        std::cout << "|" << t.tag << ":" << lexer.wordData << " ";
      }
      else if (tokenType(t.tag) == 1) {
        tokens.push_back(std::pair<void*, Token>(nullptr, t));
      }
    }
  }
  std::cout << std::endl;
}

// parse abstract type only; eg. float***
// no array or function pointer
bool Parser::parseAbstractType() {
  TypeObject* type;
  int parseState = 0;
  
  while (true) {
    auto t = tokens[cursor];
    int tag = t.second.tag;

    if (parseState == 0) {
      // basic type
      if (tag == INT || tag == FLOAT) {
        type = new TypeObject(tag == INT ? TYPE_INT : TYPE_FLOAT);
        parseState = 1;
        cursor += 1;
      }
      else {
        return false;
      }
    }
    else if (parseState == 1) {
      // pointer
      if (tag == '*') {
        TypeObject *newType = new TypeObject(TYPE_POINTER);
        newType->baseType = type;
        type = newType;
        cursor += 1;
      }
      // type declarator ends here
      else {
        return true;
      }
    }
  }
}

bool Parser::parseDeclaration() {
  TypeObject* type;
  int parseState = 0;
  int idIndex;
  int k;

  // find first id
  for (idIndex = cursor; idIndex < this->tokens.size(); idIndex++) {
    auto t = tokens[idIndex];
    int tag = t.second.tag;

    if (tag == ID) {
      break;
    }
  }
  if (idIndex == this->tokens.size()) {
    // no ID found till the end
    return false;
  }
  
  // from ID, look right for array 
  k = idIndex;
  while (true) {
    auto t = tokens[k];
    int tag = t.second.tag;
    
    if (parseState == 0) {
      if (tag == '[') {
        parseState = 1;
      }
      else {
        // stop seeing right
      }
    }
    else if (parseState == 1) {
      if (tag == NUM) {
        parseState = 2;
      }
      else if (tag == ']') {
        // stop seeing right; one dimensional array
      }
    }
    else if (parseState == 2) {
      if (tag == ']') {
        // stop seeing right
      }
      else {
        return false;
      }
    }


  }
}

// pass 1 : find procedures 
bool Parser::firstPass() {
  // functions : ret_type func_name(params ...) { func_body } 
  // global variables : var_type var_name = var_init_val; but assume no global variables

  this->cursor = 0;
  int parseState = 0;
  std::string procedureName;
  std::string variableName;
  TypeObject *returnType;
  std::vector<TypeObject*> parameterTypes;

  for (int i = 0; i < tokens.size(); i++) {
    auto token = tokens[i];
    int tag = token.second.tag;
    Token tok = token.second;
    
    if (parseState == 0) {
      bool success = this->parseAbstractType();
      if (success) {
        returnType = this->typeObject;
        parseState = 1;
      }
      else {
        // error
      }
    }
    else if (parseState == 1) {
      // has seen a type declarator
      if (tag == ID) {
        currentName = *((std::string*)token.first);
        std::cout << "Function or global variable name : " << currentName << std::endl;
        parseState = 2;
        cursor += 1;
      }
    }
    else if (parseState == 2) {
      if (tag == '(') {
        // parameter list start
        parseState = 3;
        cursor += 1;
      }
    }
    else if (parseState == 3) {
      if (tag == ')') {

      }
    }
  }
}