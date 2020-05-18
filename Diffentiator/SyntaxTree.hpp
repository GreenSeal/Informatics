#pragma once

class SyntaxNodeI {
  Tokens::Types type;

  void MessageAndAbort() const{
    std::cout << "You mustn't use this function in this scope\n";
    std::abort();
  }

public:

  SyntaxNodeI(Tokens::Types type_) {
    type = type_;
  }

  Tokens::Types GetType() const{
    return type;
  }

  void SetType(Tokens::Types type_) {
    type = type_;
  }
  virtual SyntaxNodeI* GetRight() const{
    return NULL;
  }
  virtual SyntaxNodeI* GetLeft() const{
    return NULL;
  };

  virtual void SetLeft(SyntaxNodeI* left_){
    MessageAndAbort();
  }

  virtual void SetRight(SyntaxNodeI* right_){
    MessageAndAbort();
  }

  virtual int GetData() const {
    MessageAndAbort();
  }

  virtual void SetData(int data_) {
    MessageAndAbort();
  }
    
};

class SyntaxNodeUno : public SyntaxNodeI {
  SyntaxNodeI * left;

public:
  
  SyntaxNodeUno(Tokens::Types type_) : SyntaxNodeI(type_) {}


  SyntaxNodeI* GetLeft() const override{
    return left;
  }

  void SetLeft(SyntaxNodeI * left_) override {
    left = left_;
  }
};

class SyntaxNodeBin : public SyntaxNodeUno {
  
  SyntaxNodeI * right;

public:

  SyntaxNodeBin(Tokens::Types type_) : SyntaxNodeI(type_) {}

  SyntaxNodeI* GetRight() const override{
    return right;
  }

  void SetRight(SyntaxNodeI * right_) override{
    right = right_;
  }
};

class SyntaxNodeNum : public SyntaxNodeI{
  int data;

  SyntaxNodeNum(Tokens::Types type_) : SyntaxNodeI(type_) {}

  void SetData(int data_) override{
    data = data_;
  }

  int GetData() const override{
    return data;
  }
};

class SyntaxTree {
  SyntaxNodeI * root;
  SyntaxNodeI * cur1;
  SyntaxNodeI * cur2;
};