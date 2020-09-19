#ifndef OPERATOR_H
#define OPERATOR_H
#include "AST.h"
#include <sstream>
class Operator: public AST {
  AST* mlhs;
  AST* mrhs;
  std::string op;
public:
  // Constructor
  // Destructor?
  Operator(const std::string& token, AST* lhs, AST* rhs);
  ~Operator();

  // Required helper functions.
  int arity()         const;
  int associativity() const;
  int precedence()    const;
  //bool needsParenthesis();

  // Required member functions.
  std::string infix()   const;
  std::string postfix() const;
  std::string prefix()  const;
};

#endif
