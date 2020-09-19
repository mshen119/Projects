#include "ChunkyList.h"
#include "MyChunkyList.h"

ChunkyList* ChunkyList::create(int chunksize) {
  // TODO: Create and return a ChunkyList.
  return new MyChunkyList(chunksize);
  
  /*MyChunkyNode* h = start;
  MyChunkyNode* temp = new MyChunkyNode;
  temp->next = NULL; 
  newList->head = NULL;
  for(int i = 0; i<chuncksize;i++){
    if(h == NULL){
      temp->prev = NULL;
      h = temp; 
    }else{
      while(h->after != NULL){
        h= h->after;
        h->after = temp;
        temp->prev = h; 
      }

    }

  }
  return */
}



