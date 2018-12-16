#include "ParseTree.hpp"
#include "Tag.hpp"

void ParseTree::printParseTree(int l)
{
  for (int i = 0; i < l; i++)
  {
    std::cout << " ";
  }

  std::cout << this->lineNumber << " ";
  if (tokenType(this->tag) == -1)
  {
    std::cout << "|" << this->tag << ":" << (char)this->tag << " ";
  }
  else if (tokenType(this->tag) == NUM)
  {
    std::cout << "|" << this->tag << ":" << this->numData << " ";
  }
  else if (tokenType(this->tag) == REAL)
  {
    std::cout << "|" << this->tag << ":" << this->realData << " ";
  }
  else if (tokenType(this->tag) == 0)
  {
    std::cout << "|" << this->tag << ":" << this->wordData << " ";
  }
  else if (tokenType(this->tag) == 2)
  {
    std::cout << "|" << this->tag << ":" << this->wordData << " ";
  }
  else if (tokenType(this->tag) == 1)
  {
  }
  std::cout << std::endl;

  for (int k = 0; k < this->children.size(); k++)
  {
    this->children[k]->printParseTree(l + 1);
  }
}


void ParseTree::clearTempValue(ParseTree * tree) {
  tree->evaluated = false;
  for (int i = 0; i < tree->children.size(); i++) {
    clearTempValue(tree->children[i]);
  }
}