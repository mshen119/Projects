#ifndef MYSTACK_H
#define MYSTACK_H

#include "Stack.h"
#include <stdexcept>
#include <iostream>
struct Node
{
  double data;
  Node* next;
};


class MyStack: public Stack {
  // TODO: Member Variables
  Node* mtop;
  int mcount;
public:
  // TODO: Constructor & Destructor

  // Required Stack functions.
  // See Stack.h for descriptions.
  MyStack();
  void   clear();
  bool   is_empty() const;
  void   push(double item);
  double pop();
  double top() const;
  int count();
  ~MyStack();

  // TODO: Add helper functions if necessary.
};

#endif
