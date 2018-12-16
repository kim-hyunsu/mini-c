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
ParseTree *root;

extern YYSTYPE yylval;
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
  int i = yyparse();
  // std::cout << "yyparse result : " << i << std::endl;

  // std::cout << root->children.size() << std::endl;
  // root->printParseTree(0);
  // running
  Runtime *run = new Runtime(root);

  run->findProcedures();
  run->findMain();

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
      if (argNum == 1)
      {
        arglist.push_back("1");
        argNum++;
      }
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
      {
        cout << "End of Program" << endl;
        return 0;
      }
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

static bool invalidArgNum(int argc, int validNum)
{
  if (argc != validNum)
  {
    cout << "Prompt: Invalid Number Of Argument." << endl;
    return true;
  }
  return false;
}

int yylex()
{
  if (parser->cursor == parser->tokens.size())
  {
    return -1;
  }
  auto t = parser->tokens[parser->cursor];
  yylval = new ParseTree();
  yylval->lineNumber = t.second.lineNumber;
  yylval->tag = t.second.tag;
  if (tokenType(t.second.tag) == -1)
  {
  }
  else if (tokenType(t.second.tag) == NUM)
  {
    yylval->numData = *(int *)t.first;
  }
  else if (tokenType(t.second.tag) == REAL)
  {
    yylval->realData = *(double *)t.first;
  }
  else if (tokenType(t.second.tag) == 0)
  {
    yylval->wordData = *(std::string *)t.first;
  }
  else if (tokenType(t.second.tag) == 1)
  {
  }
  parser->cursor++;
  return t.second.tag;
}