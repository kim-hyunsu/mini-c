#ifndef VALUE_H
#define VALUE_H

#include "TypeObject.hpp"
#include "SymbolTableEntry.hpp"


class Value
{
public:
  bool boolean;
  int integer;
  float real;
  void *pointer;
  // for assignment
  void *address;
  int line;
  SymbolTableEntry *ste;
  TypeObject *type;
};

#endif