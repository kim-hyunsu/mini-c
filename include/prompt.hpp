#include <string>
#include <vector>
#include "TypeObject.hpp"

class NameInfo
{
public:
  TypeObject type;
  std::string name;
};

std::vector<std::string> parsePrompt(std::string command);
NameInfo parseVariable(std::string variableName);