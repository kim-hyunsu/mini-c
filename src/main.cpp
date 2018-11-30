#include <string>
#include <iostream>
#include <vector>
#include "prompt.hpp"

using namespace std;

int main(void)
{
  char input[20];
  vector<string> argv;
  while (true)
  {
    cout << ">> ";
    cin.getline(input, 20);
    string command(input);
    argv = parsePrompt(command);
    if (argv[0].compare("next") == 0)
    {
      // next();
    }
    else if (argv[0].compare("print") == 0)
    {
      // print();
    }
    else if (argv[0].compare("trace") == 0)
    {
      // trace();
    }
    else if (argv[0].compare("exit") == 0)
    {
      break;
    }
    else
    {
      cout << "Command Not Found" << endl;
    }
  }
  return 0;
}