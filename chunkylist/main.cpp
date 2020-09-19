#include <iostream>
#include "MyChunkyList.h"
#include "MyChunkyNode.h"
using namespace std;

/*std::string MyChunkyList::listToString(){
    std::string str = "";
    MyChunkyNode* next;
    for(MyChunkyNode* node = _head; node!=nullptr; node = next){
        str+=node->nodeToString();
        next = node->next();
    }
    return str;
}
.
.
.
std::string MyChunkyNode::nodeToString(){
    std::string str = "";
    str+="[";
        for(int i = 0; i<this->_size; i++){
            if((this->items()[i].empty()) || this->items()[i].compare("")==0)
                str+="_,";
            else
                str += this->items()[i]+ ",";
        }
    str+="]";
    return str;
}*/

int main(){
    MyChunkyList list(4);
    
    list.insert(0,"bob");
    cout<<list.listToString()<<endl;
    list.insert(1,"bad");
    cout<<list.listToString()<<endl;
    list.insert(2,"good");
    cout<<list.listToString()<<endl;
    list.insert(3,"dog");
    cout<<list.listToString()<<endl;
    list.insert(4,"cat");
    cout<<list.listToString()<<endl;
    list.insert(5,"yes");
    cout<<list.listToString()<<endl;
    list.insert(6,"where");
    cout<<list.listToString()<<endl;
    list.insert(7,"alice");
    cout<<list.listToString()<<endl;
    list.insert(8,"alice");
    cout<<list.listToString()<<endl;
     list.insert(9,"where");
    cout<<list.listToString()<<endl;
    list.insert(10,"alice");
    cout<<list.listToString()<<endl;
    list.insert(11,"alice");
    cout<<list.listToString()<<endl;
    /*list.remove(0);
    cout<<list.listToString()<<endl;*/
    list.remove(5);
    cout<<list.listToString()<<endl;
    list.remove(5);
    cout<<list.listToString()<<endl;
    list.remove(5);
    cout<<list.listToString()<<endl;
    list.remove(1);
    cout<<list.listToString()<<endl;
    list.remove(1);
    cout<<list.listToString()<<endl;
    list.remove(1);
    cout<<list.listToString()<<endl;
 
    
 
    /*list.insert(1,"hello");
    cout<<list.listToString()<<endl;
    list.insert(2,"where");
    cout<<list.listToString()<<endl;
    list.insert(3,"yellow");
    cout<<list.listToString()<<endl;
    list.insert(4,"goodbye");
    cout<<list.listToString()<<endl;
    list.insert(5,"there");
    cout<<list.listToString()<<endl;
    list.insert(3,"yes");
    cout<<list.listToString()<<endl;
   list.remove(5);
   cout<<list.listToString()<<endl;*/
    
    //list.remove(1);
    //cout<<list.listToString()<<endl;
    //list.remove(3);
    //cout<<list.listToString()<<endl;
    //cout<<list.count()<<endl;
    //cout<<list.head()->count()<<endl;
    //cout<<list.head()->next()->count()<<endl;
    /*list.remove(0);
    cout<<list.listToString()<<endl;
    list.remove(0);
    cout<<list.listToString()<<endl;
    list.remove(0);
    cout<<list.listToString()<<endl;*/
    /*list.insert(1,"why");
    cout<<list.listToString()<<endl;
    list.remove(1);
    cout<<list.listToString()<<endl;
    list.remove(1);
    cout<<list.listToString()<<endl;*/

 



     

    
   
}
