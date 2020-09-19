#include "MyStack.h"


// TODO: Implement MyStack member functions here.
MyStack::MyStack(){
   mtop = nullptr;
   mcount = 0;
}
void MyStack::clear(){
    if(mtop==NULL){
        return;
    }
    Node* temp;
    while(mtop!=nullptr){
        temp = mtop;
        mtop = mtop->next;
        delete temp;
    }
    mtop = nullptr;
    mcount = 0;
    

}
int MyStack::count(){
    return mcount;
}
bool MyStack::is_empty() const{
    return mtop == NULL;

}
void MyStack::push(double item){
    Node* temp = new Node;
    temp->data = item;
    temp->next = mtop;
    mtop = temp;
    mcount++;

}
double MyStack::pop(){
    if(is_empty()){
        throw std::underflow_error("invalid");
    }else{
        double value = mtop->data;
        Node* temp = mtop;
        mtop = temp->next;
        delete temp;
        mcount--;
        return value; 
    }

}
double MyStack::top() const{
    if(is_empty()){
        throw std::underflow_error("invalid");
    }
    return mtop->data;

}
MyStack::~MyStack(){
    if(mtop){
        Node* traverse = mtop;
        Node* temp;
        while(traverse!=nullptr){
            temp = traverse;
            traverse = traverse->next;
            delete temp; 
        
        
    }
        mtop= nullptr;

    }
    
    
    
}
