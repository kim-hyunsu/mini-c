#include "HistoryTable.hpp"

#include <iostream>

void HistoryTable::addEntry(int line, int value)
{
  HistoryTableEntry entry = HistoryTableEntry();
  entry.lineNumber = line;
  entry.value.integer = value;
}

void HistoryTable::addEntry(int line, float value)
{
  HistoryTableEntry entry = HistoryTableEntry();
  entry.lineNumber = line;
  entry.value.floating = value;
}

void HistoryTable::addEntry(int line, void *value)
{
  HistoryTableEntry entry = HistoryTableEntry();
  entry.lineNumber = line;
  entry.value.pointer = value;
}

void HistoryTable::printHistory(std::string name)
{
  for (std::vector<HistoryTableEntry>::iterator it = this->table.begin(); it != this->table.end(); it++)
  {
    // std::cout << name << " = " << (*it).value << " at line " << (*it).lineNumber << std::endl;
  }
}
