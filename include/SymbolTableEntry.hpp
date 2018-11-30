#include <string>

#include "TypeObject.hpp"
#include "HistoryTable.hpp"

class SymbolTableEntry {
private:
  //int index;
  std::string name;
  TypeObject variableType;
  int level;
  int procedure;
  void *variableAddress;
  HistoryTable history;

public:
  SymbolTableEntry(std::string name, TypeObject vType, int lv, void *address);
  int getLevel();
  int getProcedure();
  bool checkName(std::string str);
};