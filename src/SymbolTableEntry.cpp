#include "SymbolTableEntry.hpp"
#include <sstream>
#include <iostream>

static std::string toString(TypeObject type, void *addr);

SymbolTableEntry::SymbolTableEntry(std::string name, TypeObject vType, int lv, int proc, void *address)
    : name(name), variableType(vType), level(lv), procedure(proc), variableAddress(address), assigned(false)
{
}

int SymbolTableEntry::getLevel()
{
  return this->level;
}

int SymbolTableEntry::getProcedure()
{
  return this->procedure;
}

bool SymbolTableEntry::checkName(std::string str)
{
  return this->name == str;
}

std::string SymbolTableEntry::getValue()
{
  if (this->assigned == false)
  {
    return "N/A";
  }
  else
  {
    TypeObject type = this->variableType;
    void *addr = this->variableAddress;
    return toString(type, addr);
  }
}

TypeObject *SymbolTableEntry::getType()
{
  return &this->variableType;
}

std::vector<std::string> SymbolTableEntry::getHistory(std::string name)
{
  return this->history.getHistory(name);
}

void SymbolTableEntry::setAssigned(bool v)
{
  this->assigned = v;
}

static std::string toString(TypeObject type, void *addr)
{
  std::string value;
  std::stringstream ss;

  switch (type.typ)
  {
  case TYPE_INT:
    value = std::to_string(*(int *)addr);
    break;
  case TYPE_FLOAT:
    value = std::to_string(*(float *)addr);
    break;
  case TYPE_POINTER:
    ss << *(void **)addr;
    value = ss.str();
    break;
  case TYPE_ARRAY:
    ss << "{";
    for (int j = 0; j < type.arraySize[0]; j++)
    {
      switch (type.baseType->typ)
      {
      case TYPE_INT:
      case TYPE_FLOAT:
        ss << toString(*type.baseType, ((int *)addr + j));
        break;
      case TYPE_POINTER:
      case TYPE_ARRAY:
        ss << toString(*type.baseType, ((void **)addr + j));
        break;
      }
      if (j != type.arraySize[0] - 1)
        ss << ", ";
    }
    ss << "}";
    value = ss.str();
    break;
  default:
    value = "Invalid typing of the variable name";
  }
  return value;
}