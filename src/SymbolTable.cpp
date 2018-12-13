#include "SymbolTable.hpp"

SymbolTable::SymbolTable()
    : level(0), procedure(0)
{
}

int SymbolTable::currentLevel()
{
  return this->level;
}

// return index by name; -2 if invisible, -1 if not found
int SymbolTable::lookup(std::string name)
{
  // search from the bottom of the table
  for (int i = this->table.size() - 1; i >= 0; i--)
  {
    if (this->table[i].checkName(name))
    {
      if (this->table[i].getProcedure() == this->procedure)
      {
        return i;
      }
      else
      {
        return -2;
      }
    }
  }
  return -1;
}

void SymbolTable::addNewSymbol(std::string name, TypeObject vType, void *address)
{
  SymbolTableEntry entry = SymbolTableEntry(name, vType, this->level, this->procedure, address);
  this->table.push_back(entry);
}

void SymbolTable::newLevel()
{
  this->level += 1;
}

void SymbolTable::newProcedure()
{
  this->procedure += 1;
}

void SymbolTable::deleteLevel()
{
  int currentLevel = this->level;
  int currentProcedure = this->procedure;

  for (std::vector<SymbolTableEntry>::reverse_iterator it = this->table.rbegin(); it != this->table.rend(); it++)
  {
    int entryLevel = (*it).getLevel();
    int entryProcedure = (*it).getProcedure();

    if (entryLevel == currentLevel && entryProcedure == currentProcedure)
    {
      this->table.erase(it.base());
    }
    else
    {
      break;
    }
  }
  this->level -= 1;
}

void SymbolTable::deleteProcedure()
{
  int currentLevel = this->level;
  int currentProcedure = this->procedure;

  for (std::vector<SymbolTableEntry>::reverse_iterator it = this->table.rbegin(); it != this->table.rend(); it++)
  {
    int entryLevel = (*it).getLevel();
    int entryProcedure = (*it).getProcedure();

    if (entryProcedure == currentProcedure)
    {
      this->table.erase(it.base());
    }
    else
    {
      break;
    }
  }
  this->procedure -= 1;
  // need to set this->level after cleaning up the call stack
}

SymbolTableEntry SymbolTable::get(int index)
{
  return this->table[index];
}
