#include "SymbolTable.hpp"

SymbolTable::SymbolTable()
  : level(0)
{}

int SymbolTable::currentLevel() {
  return this->level;
}

int SymbolTable::lookup(std::string name) {
  // search from the bottom of the table
  for (std::vector<SymbolTableEntry>::reverse_iterator it = this->table.rbegin(); it != this->table.rend(); it++) {
    if ((*it).checkName(name))
    {
      int index = this->table.size() - 1 - std::distance(it, this->table.rbegin());
      return index;
    }
  }
}

void SymbolTable::addNewSymbol(std::string name, TypeObject vType, void *address) {
  SymbolTableEntry entry = SymbolTableEntry(name, vType, this->currentLevel(), address);
  this->table.push_back(entry);
}

void SymbolTable::newLevel() {
  this->level += 1;
}

