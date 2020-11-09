#include "MyChunkyList.h"

#include <iostream>

// TODO: Member Function Implementation
MyChunkyList::MyChunkyList(int chunksize){
    start = nullptr;
    end = nullptr;
    counter = 0;
    size = chunksize;
    
}
int MyChunkyList::count() const{
   /* MyChunkyNode* h = start;
    int counter = 0;
    while(h !=NULL){
        h = h->after;
       counter+=h->numberOfItems;
    }*/
    return counter; 

}
MyChunkyNode* MyChunkyList::head() const{
    return start;
}
MyChunkyNode* MyChunkyList::tail() const{
    return end; 
}
void MyChunkyList::insert(int index, const std::string& item){
     if(index <0 || index>counter){
        throw std::out_of_range("invalid index");
    }
    else if(index == 0 && counter == 0){
           MyChunkyNode* newStart = new MyChunkyNode(nullptr, nullptr,size);
           start = newStart;
           end = newStart;
           newStart->items()[0] = item;
           newStart->increment();
           counter++;
           
       }
    else if(index == 0 && start->count() == size ){
        
            MyChunkyNode* newStart = new MyChunkyNode(start, nullptr, size);
            newStart->items()[0]= item;
            newStart->increment();
            start->setprev(newStart);
            start = newStart;
            counter++;
            

    } 
    else if(index==counter){
        if(end->count()==size){
            MyChunkyNode* newEnd = new MyChunkyNode(nullptr,end, size);
            newEnd->items()[0] = item;
            newEnd->increment();
            end->setnext(newEnd);
            end = newEnd;
            counter++;
           

        }else{
            end->items()[end->count()] = item;
            end->increment();
            counter++;
        }
    } 
           
    
    else{
        MyChunkyNode* n = start;
        MyChunkyNode* track;
        int tracker = 0;
        while(n!=nullptr){//gets to the node with the desired index
            /*if(n->next() == nullptr){
                track = n;
                tracker+=n->count();
            }*/
            tracker+=n->count();
            if(tracker > index){
                track = n;
                break;
            }
            n = n->next();
        }
        if(track->count()< size){
            int priorAmount = 0;
            if(track->prev()==nullptr){
                priorAmount = 0;

            }else{
                priorAmount = tracker - track->count();

            }
            
            int currentIndex = index- priorAmount;
            if(track->items()[currentIndex]== ""){
                track->items()[currentIndex] = item;
                track->increment();
                counter++;
               

            }
            else{
                for(int i = track->count()-1; i>=currentIndex;i--){
                    track->items()[i+1] = track->items()[i]; 

                }
                track->items()[currentIndex] = item;
                track->increment();
                counter++;
               
            }


        }
        else{
            if((track->count()+1)%2 == 0){
                MyChunkyNode* split = new MyChunkyNode(track->next(),track, size);
                std::string temp = track->items()[size-1];
                int priorAmount = 0;
                if(track->prev()==nullptr){
                    priorAmount = 0;

                }else{
                    priorAmount = tracker - track->count();

                }
                int currentIndex = index- priorAmount;
                
                for(int i = track->count()-2; i>=currentIndex;i--){
                    track->items()[i+1] = track->items()[i]; 

                }
                track->items()[currentIndex] = item;
                
                /*for(int k = size-1; k>=size/2;k--){
                    split->items()[size-1-k] = track->items()[k];
                    track->items()[k] = "";
                    
                     

                }*/
                int g =0;
                for(int i = (track->count()+1)/2; i<size;i++){
                    //for(int g = 0; g<(track->count()+1)/2;g++){
                        split->items()[g] = track->items()[i];
                        track->items()[i] = "";
                        g++;
                    //}
                }
                for(int i = 0;i<size;i++){
                    if(split->items()[i] == ""){
                        split->items()[i] = temp;
                        break;
                    }
                }
                /*int tempI = size-1-currentIndex+index;
                split->items()[tempI] = temp;*/

                counter++;
                if(track->next()!=nullptr){
                    track->next()->setprev(split);

                }else{
                    end = split;
                }
                
                track->setnext(split);
                
                split->countItems();
                track->countItems();
           }
            else{
                MyChunkyNode* splitOdd = new MyChunkyNode(track->next(),track, size);
                //std::cout<<"hello"<<std::endl;
                std::string temp = track->items()[size-1];
                int priorAmount = 0;
                if(track->prev()==nullptr){
                    priorAmount = 0;

                }else{
                    priorAmount = tracker - track->count();

                }
                int currentIndex = index- priorAmount;
                //std::cout<<currentIndex<<std::endl;
                 //std::cout<<track->count()<<std::endl;
                for(int i = track->count()-2; i>=currentIndex;i--){//shift
                    track->items()[i+1] = track->items()[i]; 

                }
                track->items()[currentIndex] = item;
                 //std::cout<<track->items()[4]<<std::endl;
                //std::cout<<((track->count()+1)/2)+1<<std::endl;
                int k =0;
                for(int i = ((track->count()+1)/2)+1;i<size;i++){
                    //for(int k = 0; k<size;k++){
                        splitOdd->items()[k] = track->items()[i];
                        track->items()[i] = "";
                        k++;
                    //}
                }
                 for(int i = 0;i<size;i++){
                    if(splitOdd->items()[i] == ""){
                        splitOdd->items()[i] = temp;
                        break;
                    }
                }
                counter++;
                if(track->next()!=nullptr){
                    track->next()->setprev(splitOdd);

                }else{
                    end = splitOdd;
                }
                
                track->setnext(splitOdd);
                
                splitOdd->countItems();
                track->countItems();
            }
        }
            
                
        }
}

  
std::string& MyChunkyList::lookup(int index){
     if(index <0 || index>=count()){
        throw std::out_of_range("invalid index");
    }
    MyChunkyNode* h = start;
     
    MyChunkyNode* track;
    int tracker = 0;
    while(h!=nullptr){
            
        tracker+=h->count();
        if(tracker > index){
            track = h;
            break;
        }
        h = h->next();
    }
    int priorAmount = 0;
    if(track->prev()==nullptr){
        priorAmount = 0;

    }else{
        priorAmount = tracker - track->count();

    }
    int currentindex = index - priorAmount;

    return h->items()[currentindex]; 

}
void MyChunkyList::remove(int index){
     if(index <0 || index>=count()){
        throw std::out_of_range("invalid index");
    }
    else if(start == nullptr){
        return;
    }
    else{//remove from the middle
        //std::cout<<"hello"<<std::endl;
        //std::cout<<"hello"<<std::endl;
        MyChunkyNode* track = start;
         //std::cout<<track<<std::endl;
        int tracker = 0;
        while(track!=nullptr){
            tracker+=track->count();
            if(tracker > index){
                break;
            }
            track = track->next();
        }
         //std::cout<<track<<std::endl;
        int priorAmount = 0;
        if(track->prev()!=nullptr){
            priorAmount = tracker - track->count();

         }
          //std::cout<<priorAmount<<std::endl;
        int currentindex = index - priorAmount;
        //std::cout<<currentindex<<std::endl;
        //std::cout<<track->count()<<std::endl;
        track->items()[currentindex] = "";
        track->decrement();
        counter--;

        //std::cout<<track->count()<<std::endl;
        if(track->count()==0){//empty
             //std::cout<<track<<std::endl;
            //std::cout<<start<<std::endl;
            //std::cout<<end<<std::endl;
            if(track==start&&track == end){
                delete track;
                start = nullptr;
                end = nullptr;
                return;
            }
            else if(track == start){
                track->next()->setprev(nullptr);
                MyChunkyNode* temp = track;
                //track = track->next();
                start = track->next();
                delete temp;
                return;
            }
            else if(track == end){
                MyChunkyNode* temp = track;
                track->prev()->setnext(nullptr);
                //track = track->prev();
                end = track->prev();
                delete temp;
                return;
            }else{
                track->next()->setprev(track->prev());
                track->prev()->setnext(track->next());
                delete track;
                return;

            }
            
        }
        //std::cout<<currentindex<<std::endl;
        //std::cout<<size-1<<std::endl;
        if(currentindex<size-1 && track->items()[currentindex+1] != ""){//shift left
            //std::cout<<"why"<<std::endl;
            for(int i = currentindex; i< track->count();i++){
                track->items()[i] = track->items()[i+1];
                track->items()[i+1] = ""; 
            }
        }
        //std::cout<<"hello1"<<std::endl;
    
        if(track == start){
            if(track->next() != nullptr){
                if((track->count()+track->next()->count())<=(size/2)){//merge head and adjacent
                    if(track->next()->next() == nullptr){//if only two nodes including head
                        MyChunkyNode* newNode = new MyChunkyNode(nullptr, nullptr,size);
                        for(int i = 0; i<size;i++){
                            if(track->items()[i]!=""){
                                newNode->items()[i] = track->items()[i];
                            }
                        }
                        newNode->countItems();
                        int j = 0;
                        for(int i = newNode->count(); i<size; i++){
                        
                            if(track->next()->items()[j]!=""){
                                newNode->items()[i] = track->next()->items()[j];
                                j++;
                            }
                        }
                        delete track->next();
                        delete track;
                        start = newNode;
                        end = newNode;
                        newNode->countItems();
                        return;    

                    }else{
                        MyChunkyNode* newNode = new MyChunkyNode(track->next()->next(),nullptr,size);
                        for(int i = 0; i<size;i++){
                            if(track->items()[i]!=""){
                                newNode->items()[i] = track->items()[i];
                            }
                        }
                        newNode->countItems();
                        int j = 0;
                        for(int i = newNode->count(); i<size; i++){
                        
                            if(track->next()->items()[j]!=""){
                                newNode->items()[i] = track->next()->items()[j];
                                j++;
                            }
                        }
                        track->next()->next()->setprev(newNode);
                        delete track->next();
                        delete track;
                        start = newNode;
                        newNode->countItems();
                        return;
                    }
                }
            }
        }
        if(track == end){
            if(track->prev()!=nullptr){
                if((track->prev()->count()+track->count())<=(size/2)){
                    if(track->prev()->prev() == nullptr){
                        MyChunkyNode* newNode = new MyChunkyNode(nullptr,nullptr,size);
                        for(int i = 0; i<size;i++){
                            if(track->prev()->items()[i]!=""){
                            newNode->items()[i] = track->prev()->items()[i];
                            }
                        }
                        newNode->countItems();
                        int j = 0;
                        for(int i = newNode->count(); i<size; i++){
                            if(track->items()[j]!=""){
                                newNode->items()[i] = track->items()[j];
                                j++;
                            }
                        }
                        delete track->prev();
                        delete track;
                        start = newNode;
                        end = newNode;
                        newNode->countItems();
                        return;

                    }else{
                        MyChunkyNode* newNode = new MyChunkyNode(nullptr,track->prev()->prev(),size);
                        for(int i = 0; i<size;i++){
                            if(track->prev()->items()[i]!=""){
                                newNode->items()[i] = track->prev()->items()[i];
                            }
                        }
                        newNode->countItems();
                        int j = 0;
                        for(int i = newNode->count(); i<size; i++){
                            if(track->items()[j]!=""){
                                newNode->items()[i] = track->items()[j];
                                j++;
                            }                                            
                        }
                        track->prev()->prev()->setnext(newNode);
                        delete track->prev();
                        delete track;
                        end = newNode;
                        newNode->countItems();
                        return;
                    }

                }
            }

         }
          if(track->prev()!=nullptr&&((track->count()+track->prev()->count())<=(size/2))){
            MyChunkyNode* newNode = new MyChunkyNode(track->next(),track->prev()->prev(),size);
            for(int i = 0; i< size; i++){
                if(track->prev()->items()[i] != ""){
                    newNode->items()[i] = track->prev()->items()[i];
                }
            }
            newNode->countItems();
            int j = 0;
            for(int i = newNode->count();i<size;i++){
                if(track->items()[j]!=""){
                    newNode->items()[i] = track->items()[j];
                    j++;
                }
            }
            if(track->next()!=nullptr){
                track->next()->setprev(newNode);
            }else{
                end = newNode;
            }
            if(track->prev()->prev()!=nullptr){
                track->prev()->prev()->setnext(newNode);
            }else{
                start = newNode;
            }
            delete track->prev();
            delete track;
            newNode->countItems();
            return;

        }
        if(track->next()!=nullptr&&((track->count()+track->next()->count())<=(size/2))){
            MyChunkyNode* newNode = new MyChunkyNode(track->next()->next(),track->prev(),size);
            for(int i = 0; i< size; i++){
                if(track->items()[i] != ""){
                        newNode->items()[i] = track->items()[i];
                }
            }
            newNode->countItems();
            int j = 0;
            for(int i = newNode->count();i<size;i++){
                if(track->next()->items()[j]!=""){
                    newNode->items()[i] = track->next()->items()[j];
                    j++;
                }
            }
            if(track->next()->next()!= nullptr){
                track->next()->next()->setprev(newNode);
            }else{
                end = newNode;
            }
            if(track->prev()!=nullptr){
                track->prev()->setnext(newNode);

            }else{
                start = newNode;
            }
            delete track->next();
            delete track;
            newNode->countItems();
            return;

        }
       
    }
}
std::string MyChunkyList::listToString(){
    std::string str = "";
    MyChunkyNode* next;
    for(MyChunkyNode* node = start; node!=nullptr; node = next){
        str+=node->nodeToString();
        next = node->next();
    }
    return str;
}
MyChunkyList::~MyChunkyList() {
    MyChunkyNode* traverse = start;
    MyChunkyNode* temp;
    while(traverse!=nullptr){
        temp = traverse;
        traverse = traverse->next();
        delete temp; 
        
        
    }
    start = nullptr;
    end = nullptr;

}
