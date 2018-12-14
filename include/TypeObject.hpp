#ifndef TYPEOBJECT_H
#define TYPEOBJECT_H

#include <string>
#include <vector>

enum Type
{
  TYPE_FUNCTION = 0,
  TYPE_VOID,
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_ARRAY,
  TYPE_POINTER,
  TYPE_BOOL
};

class TypeObject
{
public:
  Type typ;

  // only valid when array or pointer
  TypeObject *baseType;
  // only valid when array
  std::vector<int> arraySize;
  // only valid when function
  std::vector<TypeObject *> parameterTypes;
  TypeObject *returnType;

public:
  TypeObject(Type t);
  ~TypeObject();
  static bool isSameType(TypeObject *a, TypeObject *b);
  static TypeObject *buildType(Type t);
  static TypeObject *buildPointer(TypeObject *baseType);
  static TypeObject *buildArray(TypeObject *baseType, std::vector<int> &arraySize);
  static TypeObject *buildFunction(std::vector<TypeObject *> &parameterTypes, TypeObject *returnType);
  //Type stringToType(std::string);
};

#endif