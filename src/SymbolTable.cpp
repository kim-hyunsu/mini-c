#include <iostream>

#include "SymbolTable.hpp"
#include <iostream>

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
      if (this->table[i].getProcedure() == this->procedure || this->table[i].getType()->typ == TYPE_FUNCTION)
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
  this->level = 0;
  this->procedure += 1;
}

bool SymbolTable::deleteLevel()
{

  int currentLevel = this->level;
  int currentProcedure = this->procedure;

  if (currentLevel == 1 && currentProcedure == 0) {
    // main is closing
    return true;
  }
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
  return false;
}

void SymbolTable::deleteProcedure(int lvl)
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
  this->level = lvl;
  this->procedure -= 1;
  // need to set this->level after cleaning up the call stack
}

SymbolTableEntry *SymbolTable::get(int index)
{
  return &this->table[index];
}

void SymbolTable::set(int index, Value value, int line)
{
  SymbolTableEntry *ste = &(this->table[index]);
  if (!isSameType(ste->getType(), value.type))
    throw "Type error";
  switch (value.type->typ)
  {
  case TYPE_INT:
  {
    int *addr = (int *)ste->variableAddress;
    *addr = value.integer;
    ste->history.addEntry(line, value.integer);
    ste->setAssigned(true);
    break;
  }
  case TYPE_FLOAT:
  {
    float *addr = (float *)ste->variableAddress;
    *addr = value.real;
    ste->history.addEntry(line, value.real);
    ste->setAssigned(true);
    break;
  }
  case TYPE_POINTER:
  {
    void **addr = (void **)ste->variableAddress;
    *addr = value.pointer;
    ste->history.addEntry(line, value.pointer);
    ste->setAssigned(true);
    break;
  }
  }
}

void SymbolTable::setArrayEntry(int index, int arrayIndex, Value value, int line)
{
  SymbolTableEntry *ste = &this->table[index];
  TypeObject *type = ste->getType();
  if (type->typ != TYPE_ARRAY)
    throw "Type error";
  if (!isSameType(type->baseType, value.type))
    throw "Type error";
  switch (value.type->typ)
  {
  case TYPE_INT:
  {
    int *addr = (int *)ste->variableAddress;
    addr[arrayIndex] = value.integer;
    break;
  }
  case TYPE_FLOAT:
  {
    float *addr = (float *)ste->variableAddress;
    addr[arrayIndex] = value.real;
    break;
  }
  case TYPE_POINTER:
  {
    void **addr = (void **)ste->variableAddress;
    addr[arrayIndex] = value.pointer;
    break;
  }
  }
}
