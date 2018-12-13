#include "SymbolTableEntry.hpp"

SymbolTableEntry::SymbolTableEntry(std::string name, TypeObject vType, int lv, int proc, void *address)
    : name(name), variableType(vType), level(lv), procedure(proc), variableAddress(address)
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