#include <string>
#include <vector>

enum Type {
  FUNCTION = 0,
  VOID,
  INT,
  FLOAT,
  ARRAY,
  POINTER
};

class TypeObject {
public:
  Type typ;

  // only valid when array or pointer
  TypeObject* baseType;
  // only valid when array
  std::vector<int> arraySize;
  // only valid when function
  std::vector<TypeObject*> parameterTypes;
  TypeObject* returnType;

public:
  TypeObject(Type t);
  ~TypeObject();
  static bool isSameType(TypeObject *a, TypeObject *b);
  static TypeObject* buildType(Type t);
  static TypeObject* buildPointer(TypeObject* baseType);
  static TypeObject* buildArray(TypeObject* baseType, std::vector<int>& arraySize);
  static TypeObject* buildFunction(std::vector<TypeObject*> &parameterTypes, TypeObject* returnType);
  //Type stringToType(std::string);
};