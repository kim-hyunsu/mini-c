#include <string>
#include <vector>

class CallStack {
private:
  // pair (pointer to AST, level of the scope)
  // should change to proper AST type later
  std::vector<std::pair<void*, int>> stack;

public:
  void addEntry(void* ast, int level);
  std::pair<void*, int> deleteEntry();
};