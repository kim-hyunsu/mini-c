#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "prompt.hpp"
#include "Lexer.hpp"
#include "SymbolTable.hpp"
#include "CallStack.hpp"

using namespace std;

static bool next(int lines);
static string print(string var);
static vector<string> trace(string var);
static bool invalidArgNum(int argc, int validNum);
/*
int main(void)
{
  vector<string> argv;
  while (true)
  {
    string command;
    cout << ">> ";
    getline(cin, command);
    argv = parsePrompt(command);
    int argc = argv.size();
    if (argv[0].compare("next") == 0)
    {
      if (invalidArgNum(argc, 2) && invalidArgNum(argc, 1))
        continue;
      if (argc == 1)
        argv[1] = "1";
      int lines = 0;
      try
      {
        lines = stoi(argv[1]);
      }
      catch (invalid_argument &e)
      {
        cout << "Incorrect command usage : try 'next [lines]'" << endl;
        continue;
      }
      bool done = next(lines);
      if (done)
        cout << "End of Program" << endl;
    }
    else if (argv[0].compare("print") == 0)
    {
      if (invalidArgNum(argc, 2))
        continue;
      string result = print(argv[1]);
      cout << result << endl;
    }
    else if (argv[0].compare("trace") == 0)
    {
      if (invalidArgNum(argc, 2))
        continue;
      vector<string> results = trace(argv[1]);
      for (auto result : results)
      {
        cout << result << endl;
      }
    }
    else if (argv[0].compare("exit") == 0 || argv[0] == "quit")
    {
      break;
    }
    else
    {
      cout << "Prompt: Command Not Found." << endl;
    }
  }
  return 0;
}

static bool next(int lines)
{
  bool end = false;
  // TODO
  return end;
}

static string print(string var)
{
  string value;
  // TODO
  return value;
}

static vector<string> trace(string var)
{
  vector<string> history;
  // TODO
  return history;
}

static bool invalidArgNum(int argc, int validNum)
{
  if (argc != validNum)
  {
    cout << "Prompt: Invalid Number Of Argument." << endl;
    return true;
  }
  return false;
}
*/

// scanner test
int main(void) {
  Lexer lexer = Lexer();
  SymbolTable symbolTable = SymbolTable();
  CallStack callStack = CallStack();
  std::ifstream fs;
  fs.open("./test.txt", std::ios_base::openmode::_S_in);
  lexer.input.swap(fs);
  for (int i = 0; i < 1000; i++) {
    Token t = lexer.scan();
    if (t.tag == -1) {
      break;
    }
    if (t.tag < 256) {
      std::cout << "|" << t.tag << ":" << (char)t.tag << " ";
    }
    else if (tokenType(t.tag) == NUM) {
      std::cout << "|" << t.tag << ":" << lexer.numData << " ";
    } 
    else if (tokenType(t.tag) == REAL) {
      std::cout << "|" << t.tag << ":" << lexer.realData << " ";
    } 
    else if (tokenType(t.tag) == 0) {
      std::cout << "|" << t.tag << ":" << lexer.wordData << " ";
    }
    else if (tokenType(t.tag) == 1) {
      std::cout << "|" << t.tag << " ";
    }
  }
}