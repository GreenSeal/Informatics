#include"Diff.hpp"

SyntaxNodeI* GetSyntType(SyntaxNodeI * node) {
  if(node -> GetType() == Types::COS || node -> GetType() == Types::SIN || 
     node -> GetType() == Types::TG || node -> GetType() == Types::CTG ||
     node -> GetType() == Types::LN || node -> GetType() == EXP) {
    return Syntax::UNO;
  }

  else if(node -> GetType() == Types::PLUS || node -> GetType() == Types:MINUS || 
	  node -> GetType() == Types::MULT || node -> GetType() == Types::DIV ||
	  node -> GetType() == Types::UPPER) {
    return Syntax::BIN;
  }

  else if(node -> GetType() == Types::VAR) return Syntax::VAR;

  else if(node -> GetType() == Types::NUM) return Syntax::NUM;
}

SyntaxNodeI* Differenciator::MakeDiff(SyntaxNodeI* node) {  
  if(node -> GetType() == Types::PLUS || node -> GetTypes() == Types::MINUS) {
    MakeDiff(node -> GetLeft());
    MakeDiff(node -> GetRight());
    return node;
  }

  else if(node -> GetType() == Types::MULT) {
    SyntaxNodeI * right = node -> GetRight();
    SyntaxNodeI * left = node -> GetLeft();
    node -> SetType(Types::PLUS);
    node -> SetRight(new SyntaxNodeBin(Types::MULT));
    node -> SetLeft(new SyntaxNodeBin(Types::MULT));
    node -> GetLeft() -> SetLeft(MakeDiff(left));
    node -> GetLeft() -> SetRight(right);
    node -> GetRight() -> SetLeft(MakeDiff(right));
    node -> GetLeft() -> SetRight(left);
    return node;
  }
}
