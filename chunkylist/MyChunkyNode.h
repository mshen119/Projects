#ifndef MYCHUNKYNODE_H
#define MYCHUNKYNODE_H

#include "ChunkyNode.h"

class MyChunkyNode: public ChunkyNode {
  std::string* objects;
  int numberOfItems; 
  int mchunk;
  MyChunkyNode* after;
  MyChunkyNode* previous;
  
public:
  // TODO: Member Function Declarations
  // Returns the number of items stored in this Node.
  virtual int count() const;

  // Returns the items at this node as a C array.
  virtual std::string* items() const;

  // Returns a pointer to the Node before this one, or nullptr.
  virtual MyChunkyNode* prev() const;

  // Returns a pointer to the Node after this one, or nullptr.
  virtual MyChunkyNode* next() const;
  void increment();
  void decrement();
  void countItems();
  
  MyChunkyNode(MyChunkyNode* next, MyChunkyNode* prev, int chunksize);

  virtual void setnext(MyChunkyNode* next);
  virtual void setprev(MyChunkyNode* prev);
  std::string nodeToString();
  virtual ~MyChunkyNode();

  
};

#endif
