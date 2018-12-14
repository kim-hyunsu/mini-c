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

void SymbolTable::set(int index, Value value)
{
  SymbolTableEntry ste = this->table[index];
  if (ste.getType().typ != value.type)
    throw "Type error";
  switch (value.type)
  {
  case TYPE_INT:
  {
    int *addr = (int *)ste.variableAddress;
    *addr = value.integer;
    break;
  }
  case TYPE_FLOAT:
  {
    float *addr = (float *)ste.variableAddress;
    *addr = value.real;
    break;
  }
  case TYPE_POINTER:
  {
    void **addr = (void **)ste.variableAddress;
    *addr = value.pointer;
    break;
  }
  }
}
void SymbolTable::setArrayEntry(int index, int arrayIndex, Value value)
{
  SymbolTableEntry ste = this->table[index];
  TypeObject type = ste.getType();
  if (type.typ != TYPE_ARRAY)
    throw "Type error";
  if (type.baseType->typ != value.type)
    throw "Type error";
  switch (value.type)
  {
  case TYPE_INT:
  {
    int *addr = (int *)ste.variableAddress;
    addr[arrayIndex] = value.integer;
    break;
  }
  case TYPE_FLOAT:
  {
    float *addr = (float *)ste.variableAddress;
    addr[arrayIndex] = value.real;
    break;
  }
  case TYPE_POINTER:
  {
    void **addr = (void **)ste.variableAddress;
    addr[arrayIndex] = value.pointer;
    break;
  }
  }
}