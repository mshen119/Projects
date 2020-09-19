#ifndef MYGENEPOOL_H
#define MYGENEPOOL_H

#include "GenePool.h"
#include "MyPerson.h"
#include <map>

class MyGenePool: public GenePool {
  // Member Variables
  std::map<std::string,MyPerson*> mMap;

public:
  // Constructor
  // Destructor
  MyGenePool(std::istream& stream);
  ~MyGenePool();

  // Required Function
  MyPerson* find(const std::string& name) const;

  // Other Member Functions
};

#endif
