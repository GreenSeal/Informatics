#pragma once

class Differenciator{
  SyntaxNodeI* MakeDiff(SyntaxNodeI* node);
  Syntax::Types GetSyntType(SyntaxNodeI * node);
};
