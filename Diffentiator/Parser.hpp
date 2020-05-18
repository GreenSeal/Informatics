#pragma once

#include "Lexer.hpp"
#include "SyntaxTree.hpp"

class Parser {
public:
  Lexer lexer;
  SyntaxNodeI * tree;
  int idx = 0;

  SyntaxNodeI * Expr();
  SyntaxNodeI * Mult();
  SyntaxNodeI * Term();

public:
  void Parsing();
  void Lexing() {
    lexer.Tokenisation();
  }
};
