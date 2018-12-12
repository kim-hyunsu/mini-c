#include <string>
#include <vector>

#include "SymbolTableEntry.hpp"

class SymbolTable {
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
  void deleteLevel();
  void newProcedure();
  void deleteProcedure();
  
};