#include "CallStack.hpp"

void CallStack::addEntry(std::pair<ParseTree *, int> entry) {
  this->stack.push_back(entry);
}

std::pair<ParseTree *, int> CallStack::deleteEntry() {
  auto last = this->stack.back();
  this->stack.pop_back();
  return last;
}