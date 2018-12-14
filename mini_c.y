%{
#include "Tag.hpp"
#include "Lexer.hpp"
#include "parser.hpp"
#include "ParseTree.hpp"

extern ParseTree* root;

void yyerror(std::string s);
int yylex();
%}


%token GREATER LESS T F ADD SUB MUL DIV MOD MINUS ASSIGN
%token POINTER ARRAY ADDR INC DEC BASIC IF ELSE FOR TEMP
%token INDEX NUM REAL ID COMMA FUNC
%token INT FLOAT VOID
%token CONTINUE BREAK RETURN
%token NONTERMINAL

%start start_symbol
%%

start_symbol
  : procedures
    {root = $1;}
  ;

procedures
  : procedures procedure
    {$1->addChild($2);$$=$1;}
  | 
    {auto pt=new ParseTree(); pt->tag=NONTERMINAL; pt->wordData="procedures"; $$=pt;}
  ;

procedure
  : return_type_declarator ID '(' parameters ')' block
    {auto pt=new ParseTree($1, $2, $4, $6); pt->tag=NONTERMINAL; pt->wordData="procedure"; $$=pt;}
  | ID '(' parameters ')' block
    {}
  ;

type
  : INT 
    {$$ = $1;}
  | FLOAT
    {$$ = $1;}
  | VOID
    {$$ = $1;}
  ;

return_type_declarator
  : return_type_declarator '*'
    {$1->addChild($2);$$=$1;}
  | type
    {$$ = $1;}
  ;

parameters
  : parameters_list   
    {$$ = $1;}  
  | VOID      
    {$$ = $1;}        
  |
    {$$ = new ParseTree();}
  ;

parameters_list
  : parameters_list ',' parameter 
    {$1->addChild($3); $$ = $1;}   
  | parameter
    {auto pt=new ParseTree(); pt->tag=NONTERMINAL; pt->wordData="parameters_list"; $$=pt;}
  ;

parameter
  : ID_type_declaration
    {$$ = $1;}
  ;

ID_type_declaration
  : type ID
    {auto pt=new ParseTree($1, $2); pt->tag=NONTERMINAL; pt->wordData="IDtypeDeclaration"; $$=pt;}     
  | type ID array_declaration 
    {auto pt=new ParseTree($1, $2, $3); pt->tag=NONTERMINAL; pt->wordData="IDtypeDeclaration"; $$=pt;}     
           
  ;

array_declaration
  : '[' ']'
    {$$ = new ParseTree();}      
  | '[' NUM ']'
    {$$ = new ParseTree($2);}
  ;

block
  : '{' statements '}'
    {$$ = $2;}
  ;

statements 
  : statements statement
    {$1->addChild($2); $$ = $1;}
  |
    {auto pt=new ParseTree(); pt->tag=NONTERMINAL; pt->wordData="statements"; $$=pt;}
  ;

statement
  : expression ';'
    {$$ = $1;}
  | assignment ';'
    {$$ = $1;}
  | declaration ';'
    {$$ = $1;}
  | block
    {$$ = $1;}
  ;

declaration 
  : ID_type_declaration
    {$$ = $1;}
  | ID_type_declaration '=' expression
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  ;

assignment
  : expression '=' expression
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  ;

expression
  : arithmetic_expr
    {$$ = $1;}
  ; 

arithmetic_expr
  : add_expr
    {$$ = $1;}
  ;

add_expr
  : mult_expr
    {$$ = $1;}
  | add_expr '+' mult_expr
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  | add_expr '-' mult_expr
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  ;

mult_expr
  : unary_expr
    {$$ = $1;}
  | mult_expr '*' unary_expr
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  | mult_expr '/' unary_expr
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  | mult_expr '%' unary_expr
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  ;

unary_expr
  : single_expr
    {$$ = $1;}
  | single_expr DEC
    {$2->addChild($1); $$=$2;}
  | single_expr INC
    {$2->addChild($1); $$=$2;}
  | single_expr '[' expression ']'
    {auto pt = new ParseTree($1,$3); pt->tag=NONTERMINAL; pt->wordData="subscript"; $$=pt;}
  ;

single_expr
  : ID
    {$$ = $1;}
  | NUM
    {$$ = $1;}
  | REAL
    {$$ = $1;}
  | '(' expression ')'
    {$$ = $2;}
  ;

%%

extern char yytext[];

void yyerror(std::string s)
{
  std::cout << s << std::endl;
}