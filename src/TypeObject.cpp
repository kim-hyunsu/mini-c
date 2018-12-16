#include "TypeObject.hpp"
#include <iostream>

TypeObject::TypeObject(Type t)
    : typ(t){};

TypeObject *TypeObject::buildType(Type t)
{
  TypeObject *obj = new TypeObject(t);
  return obj;
}

TypeObject::~TypeObject()
{
}

bool isSameType(TypeObject *a, TypeObject *b)
{
  if (a->typ == b->typ)
  {
    switch (a->typ)
    {
    case TYPE_INT:
    case TYPE_FLOAT:
      return true;
      break;
    case TYPE_POINTER:
      return isSameType(a->baseType, b->baseType);
      break;
    case TYPE_ARRAY:
      return isSameType(a->baseType, b->baseType) && (a->arraySize == b->arraySize);
      break;
    case TYPE_FUNCTION:
    {
      bool same = false;
      if (isSameType(a->returnType, b->returnType) && a->parameterTypes.size() == b->parameterTypes.size())
      {
        int i;
        for (i = 0; i < a->parameterTypes.size(); i++)
        {
          if (isSameType(a->parameterTypes[i], b->parameterTypes[i]) == false)
            break;
        }
        if (i == a->parameterTypes.size())
          same = true;
      }
      return same;
    }
    }
  }
  return false;
}

TypeObject *TypeObject::buildPointer(TypeObject *baseType)
{
  TypeObject *obj = new TypeObject(TYPE_POINTER);
  obj->baseType = baseType;
  return obj;
}

TypeObject *TypeObject::buildArray(TypeObject *baseType, std::vector<int> &arraySize)
{
  TypeObject *obj = new TypeObject(TYPE_ARRAY);
  obj->baseType = baseType;
  obj->arraySize = arraySize;
  return obj;
}

TypeObject *TypeObject::buildFunction(std::vector<TypeObject *> &parameterTypes, TypeObject *returnType)
{
  TypeObject *obj = new TypeObject(TYPE_FUNCTION);
  obj->parameterTypes = parameterTypes;
  obj->returnType = returnType;
}

std::string TypeObject::printType()
{
  switch (this->typ)
  {
  case TYPE_VOID:
    return "void";
  case TYPE_INT:
    return "int";
  case TYPE_FLOAT:
    return "float";
  case TYPE_POINTER:
    return "pointer to " + baseType->printType();
  case TYPE_ARRAY:
    return std::to_string(arraySize[0]) + " array of " + baseType->printType();
  case TYPE_FUNCTION:
    std::string ret = "function : ";
    for (int i = 0; i < this->parameterTypes.size(); i++)
    {
      ret += parameterTypes[i]->printType();
      ret += ", ";
    }
    ret += "-> ";
    ret += returnType->printType();
    return ret;
  }
}