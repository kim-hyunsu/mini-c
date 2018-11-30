#include <string>
#include <vector>
using namespace std;

vector<string> parsePrompt(string command)
{
  string delimiter = " ";
  size_t pos = 0;
  string token;
  vector<string> argv(0);
  while ((pos = command.find(delimiter)) != string::npos)
  {
    token = command.substr(0, pos);
    argv.push_back(token);
    command.erase(0, pos + delimiter.length());
  }
  argv.push_back(command);
  return argv;
}