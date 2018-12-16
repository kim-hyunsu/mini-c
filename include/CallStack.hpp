#include <string>
#include <vector>

#include "ParseTree.hpp"

class CallStack {
private:
  std::vector<std::pair<ParseTree *, int>> stack;

public:
  void addEntry(std::pair<ParseTree *, int> entry);
  std::pair<ParseTree *, int> deleteEntry();
};