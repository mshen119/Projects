#ifndef MYCHUNKYLIST_H
#define MYCHUNKYLIST_H

#include "ChunkyList.h"
#include "ChunkyNode.h"
#include "MyChunkyNode.h"
#include <stdexcept>

class MyChunkyList: public ChunkyList {
  MyChunkyNode* start;
  MyChunkyNode* end;
  int counter;
  int size;
public:
  // TODO: Member Function Declarations
  // Returns the number of items (not Nodes) in the list.
  virtual int count() const;
  
  MyChunkyList(int chunksize);

  // Returns a pointer to the first Node in the list, or nullptr.
  virtual MyChunkyNode* head() const;

  // Returns a pointer to the last Node in the list, or nullptr.
  virtual MyChunkyNode* tail() const;

  // Inserts an item at index.
  // Throws std::out_of_range if index is negative or > count().
  virtual void insert(int index, const std::string& item);

  // Returns a reference to the item at index.
  // Throws std::out_of_range if there is no such item.
  virtual std::string& lookup(int index);
  std::string listToString();

  // Removes the item at index.
  // Throws std::out_of_range if there is no such item.
  virtual void remove(int index);
  virtual ~MyChunkyList();

  // Don't forget!
};

#endif
