#include "SymbolTableEntry.hpp"

SymbolTableEntry::SymbolTableEntry(std::string name, TypeObject vType, int lv, void *address)
    : name(name), variableType(vType), level(lv), variableAddress(address)
{
}

int SymbolTableEntry::getLevel() {
  return this->level;
}

int SymbolTableEntry::getProcedure() {
  return this->procedure;
}

bool SymbolTableEntry::checkName(std::string str) {
  return this->name == str;
}