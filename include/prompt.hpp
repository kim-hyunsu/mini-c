#include <string>
#include <vector>
#include "TypeObject.hpp"

using namespace std;

struct NameInfo
{
  TypeObject type;
  string name;
}

vector<string>
parsePrompt(string command);