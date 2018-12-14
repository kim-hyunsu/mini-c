#include "prompt.hpp"

std::vector<std::string> parsePrompt(std::string command)
{
  std::string delimiter = " ";
  size_t pos = 0;
  std::string token;
  std::vector<std::string> argv;
  while ((pos = command.find(delimiter)) != std::string::npos)
  {
    token = command.substr(0, pos);
    argv.push_back(token);
    command.erase(0, pos + delimiter.length());
  }
  argv.push_back(command);
  return argv;
}

// NameInfo parseVariable(std::string variableName)
// {
//   NameInfo nameInfo = NameInfo();
//   nameInfo.type = TypeObject(TYPE_VOID);
//   nameInfo.name = variableName;
//   std::string asterRisk = "*";
//   std::string leftBracket = "[";
//   std::string rightBracket = "]";
//   // TODO
//   return nameInfo;
// }