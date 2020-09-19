#include "MyChunkyNode.h"

// TODO: Member Function Implementation
MyChunkyNode::MyChunkyNode(MyChunkyNode* next, MyChunkyNode* prev, int chunksize){
    objects = new std::string[chunksize];
    numberOfItems = 0;
    after = next;
    mchunk = chunksize;
    previous = prev;
    for(int i = 0; i<mchunk;i++){
        objects[i] = "";
        
    }
}
int MyChunkyNode::count() const{
    
    return numberOfItems; 
}
void MyChunkyNode::increment(){
   
    numberOfItems++;

}
void MyChunkyNode::decrement(){
    numberOfItems--;
}
void MyChunkyNode::countItems(){
    int temp = 0;
    for(int i = 0; i<mchunk;i++){
        if(objects[i]!=""){
            temp++;
            
        }
    numberOfItems = temp;
}
    
}
std::string* MyChunkyNode::items() const{
    
    return objects;

}
MyChunkyNode* MyChunkyNode::prev() const{
    return previous;
}

MyChunkyNode* MyChunkyNode::next() const{
    return after;
}
void MyChunkyNode::setnext(MyChunkyNode* next){
    after = next;
}
void MyChunkyNode::setprev(MyChunkyNode* prev){
    previous = prev;
}
std::string MyChunkyNode::nodeToString(){
    std::string str = "";
    str+="[";
        for(int i = 0; i<this->mchunk; i++){
            if((this->items()[i].empty()) || this->items()[i].compare("")==0)
                str+="_,";
            else
                str += this->items()[i]+ ",";
        }
    str+="]";
    return str;
}

MyChunkyNode::~MyChunkyNode() {
    delete[] objects;
}