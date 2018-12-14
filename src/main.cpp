#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "prompt.hpp"
#include "Lexer.hpp"
#include "SymbolTable.hpp"
#include "CallStack.hpp"
#include "parser.hpp"

using namespace std;

static bool next(int lines);
static string print(string var);
static vector<string> trace(string var);
static bool invalidArgNum(int argc, int validNum);

Parser *parser;
ParseTree *root;

extern YYSTYPE yylval;
int yyparse(void);

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

int main(void) {
  parser = new Parser("./test2.txt");
  SymbolTable symbolTable = SymbolTable();
  CallStack callStack = CallStack();

  parser->tokenize();

  int i = yyparse();
  std::cout << "yyparse result : " << i << std::endl;

  std::cout << root->children.size() << std::endl;
  root->printParseTree(0);
}

int yylex() {
  if (parser->cursor == parser->tokens.size()) {
    return -1;
  }

  auto t = parser->tokens[parser->cursor];
  yylval = new ParseTree();
  yylval->tag = t.second.tag;
  if (tokenType(t.second.tag) == -1) {
  }
  else if (tokenType(t.second.tag) == NUM) {
    yylval->numData = *(int*)t.first;
  } 
  else if (tokenType(t.second.tag) == REAL) {
    yylval->realData = *(double*)t.first;
  } 
  else if (tokenType(t.second.tag) == 0) {
    yylval->wordData = *(std::string*)t.first;
  }
  else if (tokenType(t.second.tag) == 1) {
  }
  parser->cursor++;
  return t.second.tag;
}