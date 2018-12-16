#ifndef SYMBOLTABLEENTRY_H
#define SYMBOLTABLEENTRY_H

#include <string>

#include "TypeObject.hpp"
#include "HistoryTable.hpp"

class SymbolTableEntry
{
private:
  //int index;
  std::string name;
  TypeObject variableType;
  bool assigned;
  int level;
  int procedure;

public:
  HistoryTable history;
  void *variableAddress;

public:
  SymbolTableEntry(std::string name, TypeObject vType, int lv, int proc, void *address);
  int getLevel();
  int getProcedure();
  bool checkName(std::string str);
  std::string getValue();
  TypeObject *getType();
  std::vector<std::string> getHistory(std::string name);
  void setAssigned(bool v);
};

#endif