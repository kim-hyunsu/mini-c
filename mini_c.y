%token GREATER LESS T F ADD SUB MUL DIV MOD MINUS ASSIGN
%token POINTER ARRAY ADDR INC DEC BASIC IF ELSE FOR TEMP
%token INDEX NUM REAL ID COMMA FUNC
%token INT FLOAT VOID
%token CONTINUE BREAK RETURN

%start start_symbol
%%

start_symbol
  : procedure start_symbol 
  | procedure
  ;

procedure
  : return_type_declarator ID '(' parameters ')' '{' statements '}'
  | ID '(' parameters ')' '{' statements '}'
  ;

type
  : INT
  | FLOAT
  ;

return_type_declarator
  : return_type_declarator '*'
  | type
  ;

parameters
  : parameter parameters
  | parameter
  | VOID
  |
  ;

parameter
  : ID_type_declaration
  ;

ID_type_declaration
  : type ID 
  | ID array_declaration
  ;

array_declaration
  : '[' ']'
  | '[' NUM ']'
  ;
  
statements 
  :
  ;

%%
#include "Tag.hpp"
#include "Lexer.hpp"
#include "parser.hpp"

extern char yytext[];

void yyerror(char *s)
{
  std::cout << s << std::endl;
}