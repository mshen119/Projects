#include "ChunkyList.h"
#include "MyChunkyList.h"

ChunkyList* ChunkyList::create(int chunksize) {
  return new MyChunkyList(chunksize);
}  




