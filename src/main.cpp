#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "prompt.hpp"
#include "Lexer.hpp"
#include "parser.hpp"
#include "Runtime.hpp"

using namespace std;

static bool invalidArgNum(int argc, int validNum);

Parser *parser;
extern int yylval;
int yyparse(void);

int main(int argc, char *argv[])
{
  string filename = argv[1];
  parser = new Parser(filename);
  // SymbolTable symbolTable = SymbolTable();
  // CallStack callStack = CallStack();
  // scanning
  parser->tokenize();
  // parsing
  yyparse();
  // running
  Runtime *run = new Runtime(parser);
  // prompt
  vector<string> arglist;
  while (true)
  {
    string command;
    cout << ">> ";
    getline(cin, command);
    arglist = parsePrompt(command);
    int argNum = arglist.size();
    if (arglist[0].compare("next") == 0)
    {
      if (invalidArgNum(argNum, 2) && invalidArgNum(argNum, 1))
        continue;
      if (argNum == 1)
        arglist[1] = "1";
      int lines = 0;
      try
      {
        lines = stoi(arglist[1]);
      }
      catch (invalid_argument &e)
      {
        cout << "Incorrect command usage : try 'next [lines]'" << endl;
        continue;
      }
      bool done = run->next(lines);
      if (done)
        cout << "End of Program" << endl;
    }
    else if (arglist[0].compare("print") == 0)
    {
      if (invalidArgNum(argNum, 2))
        continue;
      string result = run->print(arglist[1]);
      cout << result << endl;
    }
    else if (arglist[0].compare("trace") == 0)
    {
      if (invalidArgNum(argNum, 2))
        continue;
      vector<string> results = run->trace(arglist[1]);
      for (auto result : results)
      {
        cout << result << endl;
      }
    }
    else if (arglist[0].compare("exit") == 0 || arglist[0] == "quit")
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

int yylex()
{
  if (parser->cursor == parser->tokens.size())
  {
    return -1;
  }
  auto t = parser->tokens[parser->cursor];
  parser->cursor++;
  return t.second.tag;
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