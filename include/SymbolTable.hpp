#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <vector>

#include "SymbolTableEntry.hpp"
#include "Value.hpp"

class SymbolTable
{
private:
  int level;
  int procedure;
  std::vector<SymbolTableEntry> table;

public:
  SymbolTable();
  int currentLevel();
  int lookup(std::string name);
  void addNewSymbol(std::string name, TypeObject vType, void *address);
  void newLevel();
  bool deleteLevel();
  void newProcedure();
  void deleteProcedure(int lvl);
  SymbolTableEntry *get(int index);
  void set(int index, Value value, int line);
  void setArrayEntry(int index, int arrayIndex, Value value, int line);
};

#endif