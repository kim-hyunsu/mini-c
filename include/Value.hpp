#ifndef VALUE_H
#define VALUE_H

#include "TypeObject.hpp"
class Value
{
public:
  bool boolean;
  int integer;
  float real;
  void *pointer;
  Type type;
};

#endif