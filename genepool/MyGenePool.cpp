#include "MyGenePool.h"
#include "MyPerson.h"
#include "vector"
#include "sstream"

// This is here to avoid having yet another object file:
GenePool* GenePool::create(std::istream& stream) {
  return new MyGenePool(stream);
}


// MyGenePool Member Functions
MyGenePool::MyGenePool(std::istream& stream){
  std::string line;
  std::vector<std::string> vec;
  std::string name;
    std::string gender;
    std::string mother;
    std::string father;
 
  while(std::getline(stream,line)){
    
    if(line.empty() || line[line.find_first_not_of("\t")] =='#'){
      continue;
    }
    std::istringstream iss(line);
    /*while(getline(iss,line,'\t')){
      vec.push_back(line);
    }
    
    std::string name = vec[0];
    std::string gender = vec[1];
    std::string mother = vec[2];
    std::string father = vec[3];*/
    std::getline(iss,name,'\t');
    std::getline(iss,gender,'\t');
    std::getline(iss,mother,'\t');
    std::getline(iss,father,'\t');
    Gender gend;
    MyPerson* m;
    MyPerson* d;
    if(gender == "male"){
      gend = Gender::MALE;
    }else{
      gend = Gender::FEMALE;
    }
 
    if(mother == "???"){
      m = nullptr;
    }else{
      m = mMap.find(mother)->second;
    }
    if(father == "???"){
      d = nullptr;
    }else{
      d=mMap.find(father)->second;
    }
    MyPerson* person = new MyPerson(name,gend,m,d);
    mMap.insert(std::pair<std::string, MyPerson*>(name,person));
    
    
  }
   for(std::map<std::string,MyPerson*>::iterator it=mMap.begin(); it!=mMap.end(); ++it){
     MyPerson* p = it->second;
    if(p->mother()!=nullptr){
      p->mother()->insertChild(p);
    } 
    if(p->father() != nullptr){
      p->father()->insertChild(p); 
   }

    
    
  }
  
 

 

}

MyPerson* MyGenePool::find(const std::string& name) const{
  MyPerson* person = mMap.find(name)->second;
  return person; 

}
MyGenePool::~MyGenePool(){
  std::map<std::string,MyPerson*>::iterator it=mMap.begin();
  while(it!=mMap.end()){
    delete it->second;
    mMap.erase(it++);
  }

}