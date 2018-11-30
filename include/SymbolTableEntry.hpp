#include <string>

#include "TypeObject.hpp"
#include "HistoryTable.hpp"

class SymbolTableEntry {
private:
  //int index;
  std::string name;
  TypeObject variableType;
  int level;
  void *variableAddress;
  HistoryTable history;

public:
  SymbolTableEntry(std::string name, TypeObject vType, int lv, void *address);
  bool checkName(std::string str);
};