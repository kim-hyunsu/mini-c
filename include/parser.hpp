#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "Lexer.hpp"
#include "TypeObject.hpp"

class Parser {
public:
  Lexer lexer;
  std::vector<std::pair<void*, Token>> tokens;
  int cursor;
  TypeObject *typeObject;
  std::string currentName;
  
public:
  Parser(std::string filename);
  void tokenize();
  bool parseAbstractType();
  bool parseDeclaration();
  bool firstPass();
};

#endif