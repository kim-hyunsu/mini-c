%{
#include "Tag.hpp"
#include "Lexer.hpp"
#include "parser.hpp"
#include "ParseTree.hpp"

extern ParseTree* root;

void yyerror(std::string s);
int yylex();
%}


%token GREATER LESS EQUAL NEQUAL T F ADD SUB MUL DIV MOD MINUS ASSIGN
%token POINTER ARRAY ADDR INC DEC BASIC IF ELSE FOR TEMP
%token INDEX NUM REAL ID COMMA FUNC
%token INT FLOAT VOID
%token CONTINUE BREAK RETURN
%token PRINTF PRINTFARG
%token NONTERMINAL

%start start_symbol
%define parse.error verbose
%%

start_symbol
  : procedures
    {root = $1; root->parent=nullptr; root->nextSibling=nullptr;}
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
    {auto pt=new ParseTree($1); pt->tag=NONTERMINAL; pt->wordData="parameters_list"; $$=pt;}
  ;

parameter
  : ID_type_declaration
    {$$ = $1;}
  ;

declaration 
  : type_declarator declaration_list
    {$1->addChild($2); $$=$1;}
  ;

declaration_list
  : declaration_list ',' single_declaration
    {$1->addChild($3); $$=$1;}
  | single_declaration
    {auto pt=new ParseTree($1); pt->tag=NONTERMINAL; pt->wordData="declaration_list"; $$=pt;}
  ;

single_declaration
  : pointer_declaration
    {$$ = $1;}
  | pointer_declaration '=' expression
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  ;

ID_type_declaration
  : type_declarator pointer_declaration
    {auto pt=new ParseTree($1, $2); pt->tag=NONTERMINAL; pt->wordData="IDtypeDeclaration"; $$=pt;}     
  ;

type_declarator
  : type
    {$$ = $1;}
  ;

pointer_declaration
  : '*' pointer_declaration
    {$1->addChild($2); $$=$1;}
  | ID_declaration
    {$$ = $1;}
  ;

ID_declaration
  : ID
    {$$ = $1;}
  | ID array_declaration
    {$1->addChild($2); $$=$1;}
  ;

array_declaration
  : '[' NUM ']'
    {auto pt=new ParseTree($2); pt->tag=NONTERMINAL; pt->wordData="fixed_array"; $$=pt;}      
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
  | declaration ';'
    {$$ = $1;}
  | block
    {$$ = $1;}
  | branch_statement
    {$$ = $1;}
  | loop_statement
    {$$ = $1;}
  | return_statement
    {$$ = $1;}
  | printf_statement
    {$$ = $1;}
  ;

expressions
  : expressions ',' expression
    {$1->addChild($3); $$ = $1;}
  | expression
    {auto pt=new ParseTree($1); pt->tag=NONTERMINAL; pt->wordData="expressions"; $$=pt;}

printf_statement
  : PRINTF '(' PRINTFARG ')' ';'
    {$1->addChild($3);}
  | PRINTF '(' PRINTFARG ',' expressions ')' ';'
    {$1->addChild($3); $1->addChild($5); $$=$1;}
  ;

return_statement
  : RETURN expression ';'
    {$1->addChild($2); $$=$1;}
  | RETURN ';'
    {$$=$1;}
  ;

assignment
  : equality_expr
    {$$ = $1;}
  | equality_expr '=' equality_expr
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  ;

expression
  : assignment
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

postfix_expr
  : single_expr
    {$$ = $1;}
  | postfix_expr DEC
    {$2->addChild($1); $$=$2;}
  | postfix_expr INC
    {$2->addChild($1); $$=$2;}
  | postfix_expr '[' expression ']'
    {auto pt = new ParseTree($1,$3); pt->tag=NONTERMINAL; pt->wordData="subscript"; $$=pt;}
  | postfix_expr '(' ')'
    {auto pt=new ParseTree($1); pt->tag=NONTERMINAL; pt->wordData="call"; $$=pt;}
  | postfix_expr '(' args_list ')'
    {auto pt=new ParseTree($1,$3); pt->tag=NONTERMINAL; pt->wordData="call"; $$=pt;}
  ;

args_list
  : args_list ',' assignment 
    {$1->addChild($3); $$=$1;}
  | assignment
    {auto pt=new ParseTree($1); pt->tag=NONTERMINAL; pt->wordData="args_list"; $$=pt;}
  ;

unary_expr
  : postfix_expr
    {$$ = $1;}
  | '*' unary_expr
    {$1->addChild($2); $$=$1;}
  | '&' unary_expr
    {$1->addChild($2); $$=$1;}
  | INC unary_expr
    {$1->addChild($2); $$=$1;}
  | DEC unary_expr
    {$1->addChild($2); $$=$1;}
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

branch_statement
  : IF '(' expression ')' statement
    {$1->addChild($3); $1->addChild($5); $$=$1;}
  | IF '(' expression ')' statement ELSE statement
    {$1->addChild($3); $1->addChild($5); $1->addChild($7); $$=$1;}
  ;

loop_statement
  : FOR '(' expression ';' expression ';' expression ')' statement
    {$1->addChild($3); $1->addChild($5); $1->addChild($7); $1->addChild($9); $$=$1;}
  ;

comparison_expr
  : arithmetic_expr
    {$$=$1;}
  | arithmetic_expr '<' arithmetic_expr
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  | arithmetic_expr '>' arithmetic_expr
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  ;

equality_expr
  : comparison_expr
    {$$=$1;}
  | comparison_expr EQUAL comparison_expr
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  | comparison_expr NEQUAL comparison_expr
    {$2->addChild($1); $2->addChild($3); $$=$2;}
  ;
%%

extern char yytext[];

void yyerror(std::string s)
{
  std::cout << s << std::endl;
}
