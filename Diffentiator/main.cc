#include <iostream>
#include <cstdio>
#include <string>

#include "Vector.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main() {
  Parser * parser = new Parser;
  parser -> Lexing();
  parser -> Parsing();
}
