#include <vector>
#include <string>

#include "HistoryTableEntry.hpp"

class HistoryTable
{
private:
  std::vector<HistoryTableEntry> table;

public:
  void addEntry(int line, int value);
  void addEntry(int line, float value);
  void addEntry(int line, void *value);
  void printHistory(std::string name);
  std::vector<std::string> getHistory(std::string name);
};