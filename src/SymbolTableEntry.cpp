#include "SymbolTableEntry.hpp"
#include <sstream>

static std::string toString(TypeObject type, void *addr);

SymbolTableEntry::SymbolTableEntry(std::string name, TypeObject vType, int lv, int proc, void *address)
    : name(name), variableType(vType), level(lv), procedure(proc), variableAddress(address)
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
  TypeObject type = this->variableType;
  void *addr = this->variableAddress;
  return toString(type, addr);
}

std::vector<std::string> SymbolTableEntry::getHistory(std::string name)
{
  return this->history.getHistory(name);
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
    ss << addr;
    value = ss.str();
    break;
  case TYPE_ARRAY:
    ss << "{";
    for (int i = 0; i < type.arraySize.size(); i++)
    {
      ss << "{";
      for (int j = 0; j < type.arraySize[i]; j++)
      {
        if (type.baseType->typ == TYPE_POINTER)
        {
          ss << toString(*type.baseType, (char *)addr + 8 * i);
        }
        else
        {
          ss << toString(*type.baseType, (char *)addr + 4 * i);
        }
        ss << ", ";
      }
      ss << "}";
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