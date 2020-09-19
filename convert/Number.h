#ifndef NUMBER_H
#define NUMBER_H
#include "AST.h"
#include <sstream>
class Number: public AST {
  // Member Variables
  double mValue;
public:
  // Constructor
  Number(const std::string& token);
  // Destructor?

  // Required helper functions.
  int arity()         const;
  int associativity() const;
  int precedence()    const;

  // Required member functions.
  std::string infix()   const;
  std::string postfix() const;
  std::string prefix()  const;
  std::string to_string() const;
};

#endif
