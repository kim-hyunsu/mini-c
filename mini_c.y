%token GREATER LESS T F ADD SUB MUL DIV MOD MINUS ASSIGN
%token POINTER ARRAY ADDR INC DEC BASIC IF ELSE FOR TEMP
%token INDEX NUM REAL ID COMMA FUNC
%token INT FLOAT VOID
%token CONTINUE BREAK RETURN

%start start_symbol
%%

start_symbol
  : procedure start_symbol  { std::cout << "multiple procedure" << std::endl;}
  | procedure               { std::cout << "1 procedure" << std::endl;}
  ;

procedure
  : return_type_declarator ID '(' parameters ')' '{' statements '}'   { std::cout << "end of procedure : " << std::endl;}
  | ID '(' parameters ')' '{' statements '}'          
  ;

type
  : INT     { std::cout << "int" << std::endl;}
  | FLOAT   { std::cout << "float" << std::endl;}
  ;

return_type_declarator
  : return_type_declarator '*'
  | type
  ;

parameters
  : parameters_list
  | VOID
  |
  ;

parameters_list
  : parameter ',' parameters_list { std::cout << "params : more than 2" << std::endl;}
  | parameter { std::cout << "1 parameter" << std::endl;}
  ;

parameter
  : ID_type_declaration { std::cout << "a parameter" << std::endl;}
  ;

ID_type_declaration
  : type ID
  | type ID array_declaration
  ;

array_declaration
  : '[' ']'
  | '[' NUM ']'
  ;

statements 
  : statement statements
  |
  ;

statement
  : expression ';'
  ;

expression
  : 
  ;

%%
#include "Tag.hpp"
#include "Lexer.hpp"
#include "parser.hpp"

extern char yytext[];

void yyerror(std::string s)
{
  std::cout << s << std::endl;
}