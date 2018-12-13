#include "CallStack.hpp"

void CallStack::addEntry(void* ast, int level) {
  this->stack.push_back(std::pair<void*, int>(ast, level));
}

std::pair<void*, int> CallStack::deleteEntry() {
  auto last = this->stack.back();
  this->stack.pop_back();
  return last;
}