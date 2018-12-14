#ifndef PARSETREE_H
#define PARSETREE_H

#include <vector>
#include <string>
#include <iostream>

#include "Token.hpp"
#include "Tag.hpp"

class ParseTree
{
public:
  std::string name;
  int lineNumber;
  int tag;
  int numData;
  double realData;
  std::string wordData;
  ParseTree *parent;
  std::vector<ParseTree *> children;

  ParseTree(){};
  ParseTree(ParseTree *a) { this->addChild(a); }
  ParseTree(ParseTree *a, ParseTree *b)
  {
    this->addChild(a);
    this->addChild(b);
  }
  ParseTree(ParseTree *a, ParseTree *b, ParseTree *c)
  {
    this->addChild(a);
    this->addChild(b);
    this->addChild(c);
  }
  ParseTree(ParseTree *a, ParseTree *b, ParseTree *c, ParseTree *d)
  {
    this->addChild(a);
    this->addChild(b);
    this->addChild(c);
    this->addChild(d);
  }
  void addChild(ParseTree *childPtr)
  {
    this->children.push_back(childPtr);
    if (childPtr != nullptr)
      childPtr->parent = this;
  }
  void printParseTree(int l);
  bool getBoolean();
  int getInteger();
  double getReal();
};

#define YYSTYPE ParseTree *

#endif