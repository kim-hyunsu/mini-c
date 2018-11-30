#include "TypeObject.hpp"

TypeObject::TypeObject(Type t)
  : typ(t)
{};

TypeObject* TypeObject::buildType(Type t) {
  TypeObject* obj = new TypeObject(t);
  return obj;
}

TypeObject::~TypeObject() {

}

bool isSameType(TypeObject *a, TypeObject *b) {
  if (a->typ == b->typ) {
    switch (a->typ) {
      case Type::INT:
      case Type::FLOAT:
        return true;
        break;
      case Type::POINTER:
        return isSameType(a->baseType, b->baseType);
        break;
      case Type::ARRAY:
        return isSameType(a->baseType, b->baseType) && (a->arraySize == b->arraySize);
        break;
      case Type::FUNCTION:
        return isSameType(a->baseType, b->baseType) && (a->parameterTypes == b->parameterTypes) 
                && isSameType(a->returnType, b->returnType);
    }
  }
}

TypeObject* TypeObject::buildPointer(TypeObject* baseType) {
  TypeObject* obj = new TypeObject(Type::POINTER);
  obj->baseType = baseType;
  return obj;
}

TypeObject* TypeObject::buildArray(TypeObject* baseType, std::vector<int>& arraySize) {
  TypeObject* obj = new TypeObject(Type::ARRAY);
  obj->baseType = baseType;
  obj->arraySize = arraySize;
  return obj;
}

TypeObject* TypeObject::buildFunction(std::vector<TypeObject*> &parameterTypes, TypeObject* returnType) {
  TypeObject *obj = new TypeObject(Type::FUNCTION);
  obj->parameterTypes = parameterTypes;
  obj->returnType = returnType;
}

