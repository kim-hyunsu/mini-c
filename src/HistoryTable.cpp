#include "HistoryTable.hpp"

#include <iostream>
#include <sstream>

void HistoryTable::addEntry(int line, int value)
{
  HistoryTableEntry entry = HistoryTableEntry();
  entry.type = VALUETYPE_INT;
  entry.lineNumber = line;
  entry.value.integer = value;
  this->table.push_back(entry);
}

void HistoryTable::addEntry(int line, float value)
{
  HistoryTableEntry entry = HistoryTableEntry();
  entry.type = VALUETYPE_FLOAT;
  entry.lineNumber = line;
  entry.value.floating = value;
  this->table.push_back(entry);
}

void HistoryTable::addEntry(int line, void *value)
{
  HistoryTableEntry entry = HistoryTableEntry();
  entry.type = VALUETYPE_POINTER;
  entry.lineNumber = line;
  entry.value.pointer = value;
  this->table.push_back(entry);
}

void HistoryTable::printHistory(std::string name)
{
  for (std::vector<HistoryTableEntry>::iterator it = this->table.begin(); it != this->table.end(); it++)
  {
    //std::cout << name << " = " << (*it).value << " at line " << (*it).lineNumber << std::endl;
  }
}

std::vector<std::string> HistoryTable::getHistory(std::string name)
{
  std::vector<std::string> list;
  for (std::vector<HistoryTableEntry>::iterator it = this->table.begin(); it != this->table.end(); it++)
  {
    std::stringstream ss;
    ss << name << " = ";
    switch ((*it).type)
    {
    case VALUETYPE_INT:
      ss << (*it).value.integer;
      break;
    case VALUETYPE_FLOAT:
      ss << (*it).value.floating;
      break;
    case VALUETYPE_POINTER:
      ss << (*it).value.pointer;
      break;
    }
    ss << " at line ";
    ss << (*it).lineNumber;
    list.push_back(ss.str());
  }
  return list;
}
