#include "MyPerson.h"
#include <iostream>
#include <stack>
// MyPerson Member Functions
MyPerson:: MyPerson(const std::string& name, Gender gender, MyPerson* mother, MyPerson* father){
    mName = name;
    mGender = gender;
    mMother = mother;
    mFather = father; 
    
    //mSon = new MyPerson(name, Gender::MALE,mMother,mFather);
    //mDaughter = new MyPerson(name,Gender::FEMALE,mMother,mFather);
}
const std::string& MyPerson::name() const{
    return mName;
}
Gender MyPerson::gender() const{
    return mGender;
}
MyPerson* MyPerson::mother(){
    return mMother;
}
MyPerson* MyPerson::father(){
    return mFather;
}
void MyPerson::insertChild(MyPerson*child){
    mChild.insert(child);
}
std::set<Person*> MyPerson::ancestors(PMod pmod){
    
    std::set<Person*> set1;
    for(auto m: parents(pmod)){
        set1.insert(m);
        std::set<Person*> maternal = m->ancestors();
        set1.insert(maternal.begin(),maternal.end());
    }
    return set1;

}
    
   


std::set<Person*> MyPerson::aunts(PMod pmod , SMod smod){
    std::set<Person*> set;
    if(pmod == PMod::MATERNAL){
        if(mother()!=nullptr){
            if(smod == SMod::FULL){
                set = mother()->sisters(PMod::ANY,SMod::FULL);
            }
            else if(smod == SMod::HALF){
                set = mother()->sisters(PMod::ANY,SMod::HALF);
            }
            else{
                set = mother()->sisters(PMod::ANY,SMod::ANY);
            }
        }
    }
    if(pmod == PMod::PATERNAL){
        if(father()!=nullptr){
            if(smod == SMod::FULL){
                set = father()->sisters(PMod::ANY,SMod::FULL);
            }
            else if(smod == SMod::HALF){
                set = father()->sisters(PMod::ANY,SMod::HALF);
            }
            else{
                set = father()->sisters(PMod::ANY,SMod::ANY);
            }
        }
    }
    if(pmod==PMod::ANY){
        if(father()!=nullptr&&mother()!=nullptr){
            if(smod==SMod::FULL){
                set = father()->sisters(PMod::ANY,SMod::FULL);
                std::set<Person*> MatBros = mother()->sisters(PMod::ANY,SMod::FULL);
                set.insert(MatBros.begin(),MatBros.end());
            }
            else if(smod==SMod::HALF){
                set = father()->sisters(PMod::ANY,SMod::HALF);
                std::set<Person*> MatBros = mother()->sisters(PMod::ANY,SMod::HALF);
                set.insert(MatBros.begin(),MatBros.end());
            }
            else{
                set = father()->sisters(PMod::ANY,SMod::ANY);
                std::set<Person*> MatBros = mother()->sisters(PMod::ANY,SMod::ANY);
                set.insert(MatBros.begin(),MatBros.end());
            }
        }
        if(father()==nullptr&&mother()!=nullptr){
            if(smod==SMod::FULL){
                set = mother()->sisters(PMod::ANY,SMod::FULL);
                
            }
            else if(smod==SMod::HALF){
                set = mother()->sisters(PMod::ANY,SMod::HALF);
               
            }
            else{
                set = mother()->sisters(PMod::ANY,SMod::ANY);
               
            }
        }
        if(father()!=nullptr&&mother()==nullptr){
            if(smod==SMod::FULL){
                set = father()->sisters(PMod::ANY,SMod::FULL);
                
            }
            else if(smod==SMod::HALF){
                set = father()->sisters(PMod::ANY,SMod::HALF);
               
            }
            else{
                set = father()->sisters(PMod::ANY,SMod::ANY);
               
            }
        }
    }

    
    return set;

}
std::set<Person*> MyPerson::brothers(PMod pmod , SMod smod){
    std::set<Person*> set;
    if(pmod == PMod::MATERNAL){
        if(mother()!=nullptr){
        std::set<Person*> maternal = mother()->children();
        for(Person* child: maternal){
            if(smod == SMod::FULL){
                if(child->father() == father()){
                    if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
                    
                }
            }
            else if(smod == SMod::HALF){
                if(child->father()!=father()){
                   if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
                }
            }
            else{
                if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
            }
            
        }
        }
        
    }
    if(pmod == PMod::PATERNAL){
         if(father()!=nullptr){
            std::set<Person*> paternal = father()->children();
        for(Person* child: paternal){
            if(smod == SMod::FULL){
                if(child->mother() == mother()){
                    if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
                }
            }
            else if(smod == SMod::HALF){
                if(child->mother()!=mother()){
                    if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
                }
            }
            else{
                if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
            }
            
        }
         }
        
    }
    if(pmod == PMod::ANY){
        if(mother()!=nullptr&&father()!=nullptr){
            std::set<Person*> maternal = mother()->children();
            std::set<Person*> paternal = father()->children();
            std::set<Person*> all;
            all.insert(maternal.begin(),maternal.end());
            all.insert(paternal.begin(),paternal.end());
            for(Person* child: all){
                if(smod==SMod::FULL){
                    if(child->mother() == mother()&&child->father()==father()){
                        if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
                    }
                }   
            else if(smod==SMod::HALF){
                 if((child->mother() == mother()&&child->father()!=father())||(child->mother() != mother()&&child->father()==father())){
                    if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
                }
            }
            else{
                if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
            }
            }
        }
        if(mother()==nullptr&&father()!=nullptr){
            
            std::set<Person*> paternal = father()->children();
            
            for(Person* child: paternal){
                if(smod==SMod::FULL){
                    if(child->father()==father()&&child->mother()==nullptr){
                        if(child->gender()==Gender::MALE){
                            set.insert(child);
                    }
                    }
                }
                else if(smod==SMod::HALF){
                    if(child->father()==father()&&child->mother()!=nullptr){
                        if(child->gender()==Gender::MALE){
                            set.insert(child);
                    }
                    
                    }
                }
                   
            else{
                if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
            }
            }
        }
         if(mother()!=nullptr&&father()==nullptr){
            
            std::set<Person*> maternal = mother()->children();
            
            for(Person* child: maternal){
                if(smod==SMod::FULL){
                    if(child->mother()==mother()&&child->father()==nullptr){
                        if(child->gender()==Gender::MALE){
                            set.insert(child);
                    }
                    }
                }
                else if(smod == SMod::HALF){
                    if(child->mother()==mother()&&child->father()!=nullptr){
                        if(child->gender()==Gender::MALE){
                            set.insert(child);
                    }
                    }
                }   
            else{
                if(child->gender()==Gender::MALE){
                        set.insert(child);
                    }
            }
            }
        }
        
    }
    set.erase(this);
    return set;

}
std::set<Person*> MyPerson::children(){
    std::set<Person*> set;
    set.insert(mChild.begin(),mChild.end());
    return set;

}
std::set<Person*> MyPerson::cousins(PMod pmod, SMod smod ){
    std::set<Person*> set;
    if(pmod == PMod::MATERNAL){
        if(mother()!=nullptr){
            if(smod == SMod::FULL){
                std::set<Person*> MotherSibs = mother()->siblings(PMod::ANY,SMod::FULL);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            else if(smod == SMod::HALF){
                std::set<Person*> MotherSibs = mother()->siblings(PMod::ANY,SMod::HALF);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            else{
                std::set<Person*> MotherSibs = mother()->siblings(PMod::ANY,SMod::ANY);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
        }
        
    }
    if(pmod == PMod::PATERNAL){
        if(father()!=nullptr){
            if(smod == SMod::FULL){
                std::set<Person*> MotherSibs = father()->siblings(PMod::ANY,SMod::FULL);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            else if(smod == SMod::HALF){
                std::set<Person*> MotherSibs = father()->siblings(PMod::ANY,SMod::HALF);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            else{
                std::set<Person*> MotherSibs = father()->siblings(PMod::ANY,SMod::ANY);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
        }

    }
    if(pmod == PMod::ANY){
        if(father()!=nullptr&&mother()!=nullptr){
            if(smod==SMod::FULL){
                std::set<Person*> MotherSibs = mother()->siblings(PMod::ANY,SMod::FULL);
                std::set<Person*> FatherSibs = father()->siblings(PMod::ANY,SMod::FULL);
                FatherSibs.insert(MotherSibs.begin(),MotherSibs.end());
                for(Person* sib:FatherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            else if(smod==SMod::HALF){
                std::set<Person*> MotherSibs = mother()->siblings(PMod::ANY,SMod::HALF);
                std::set<Person*> FatherSibs = father()->siblings(PMod::ANY,SMod::HALF);
                FatherSibs.insert(MotherSibs.begin(),MotherSibs.end());
                for(Person* sib:FatherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            else{
                std::set<Person*> MotherSibs = mother()->siblings(PMod::ANY,SMod::ANY);
                std::set<Person*> FatherSibs = father()->siblings(PMod::ANY,SMod::ANY);
                FatherSibs.insert(MotherSibs.begin(),MotherSibs.end());
                for(Person* sib:FatherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
        }
        if(father()==nullptr&&mother()!=nullptr){
            if(smod == SMod::FULL){
                std::set<Person*> MotherSibs = mother()->siblings(PMod::ANY,SMod::FULL);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            else if(smod == SMod::HALF){
                std::set<Person*> MotherSibs = mother()->siblings(PMod::ANY,SMod::HALF);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            else{
                std::set<Person*> MotherSibs = mother()->siblings(PMod::ANY,SMod::ANY);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            
        }
        if(father()!=nullptr&&mother()==nullptr){
            if(smod == SMod::FULL){
                std::set<Person*> MotherSibs = father()->siblings(PMod::ANY,SMod::FULL);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            else if(smod == SMod::HALF){
                std::set<Person*> MotherSibs = father()->siblings(PMod::ANY,SMod::HALF);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            else{
                std::set<Person*> MotherSibs = father()->siblings(PMod::ANY,SMod::ANY);
                for(Person* sib: MotherSibs){
                    for(Person* child: sib->children()){
                        set.insert(child);
                    }
                }
            }
            
        }
    }
    
    return set;

}
std::set<Person*> MyPerson::daughters(){
     std::set<Person*> set;
    for(std::set<MyPerson*>::iterator it=mChild.begin(); it!=mChild.end(); ++it){
        if((*it)->gender() == Gender::FEMALE){
            set.insert((*it));
        }

    }
    return set;

}
std::set<Person*> MyPerson::descendants(){
    
    if(children().empty()){
        std::set<Person*> set;
        return set;
    }
    else{
        std::set<Person*> set1;
      
        for(auto c: children()){
             set1.insert(c);
            std::set<Person*> set2 = c->descendants();
            set1.insert(set2.begin(),set2.end());
        }
        return set1;
    }
}
std::set<Person*> MyPerson::grandchildren(){
    std::set<Person*> set;
    
    if(!(children().empty())){
        std::set<Person*> p = this->children();
        for(std::set<Person*>::iterator it=p.begin(); it!=p.end(); ++it){
            if(!((*it)->children().empty())){
                for(auto second: (*it)->children()){
                    set.insert(second);
                }
            }
        }
    }
    return set;
}
std::set<Person*> MyPerson::granddaughters(){
    std::set<Person*> set;
    
    if(!(children().empty())){
        std::set<Person*> p = this->children();
        for(std::set<Person*>::iterator it=p.begin(); it!=p.end(); ++it){
            if(!((*it)->children().empty())){
                for(auto second: (*it)->children()){
                    if(second->gender() == Gender::FEMALE){
                         set.insert(second);
                    }
                   
                }
            }
        }
    }
    return set;
}
std::set<Person*> MyPerson::grandfathers(PMod pmod){
    std::set<Person*> set;
    //std::set<Person*>fPaternal = this->father()->parents(PMod::PATERNAL);
    //std::set<Person*>mPaternal = this->mother()->parents(PMod::PATERNAL);
    if(pmod == PMod::PATERNAL){
        if(mFather){
            set = this->father()->parents(PMod::PATERNAL);
        }
    }
    if(pmod == PMod::MATERNAL){
        if(mMother){
            set = this->mother()->parents(PMod::PATERNAL);
        }
    }
    if(pmod == PMod::ANY){
        if(mFather&&mMother){
            set = this->father()->parents(PMod::PATERNAL);
            std::set<Person*> set1 = this->mother()->parents(PMod::PATERNAL);
            set.insert(set1.begin(),set1.end());
        }
        if(mFather && !(mMother)){
            set = this->father()->parents(PMod::PATERNAL);
        }
        if(mMother && !(mFather)){
            set = this->mother()->parents(PMod::PATERNAL);
        }
    }
    return set;
}
std::set<Person*> MyPerson::grandmothers(PMod pmod){
    std::set<Person*> set;
    //std::set<Person*>fMaternal = this->father()->parents(PMod::MATERNAL);
    //std::set<Person*>mMaternal = this->mother()->parents(PMod::MATERNAL);
    if(pmod == PMod::PATERNAL){
        if(mFather){
            set = this->father()->parents(PMod::MATERNAL);
        }
    }
    if(pmod == PMod::MATERNAL){
        if(mMother){
            set = this->mother()->parents(PMod::MATERNAL);
        }
    }
    if(pmod == PMod::ANY){
        if(mFather&&mMother){
            set = this->father()->parents(PMod::MATERNAL);
            std::set<Person*> set1 = this->mother()->parents(PMod::MATERNAL);
            set.insert(set1.begin(),set1.end());
        }
        if(mFather && !(mMother)){
            set = this->father()->parents(PMod::MATERNAL);
        }
        if(mMother && !(mFather)){
            set = this->mother()->parents(PMod::MATERNAL);
        }
    }
    
    return set;
}
std::set<Person*> MyPerson::grandparents(PMod pmod){
    std::set<Person*> set;
    set = grandfathers(pmod);
    std::set<Person*> set1 = grandmothers(pmod);
    set.insert(set1.begin(),set1.end());
    
    return set;
}
std::set<Person*> MyPerson::grandsons(){
    std::set<Person*> set;
     if(!(children().empty())){
        std::set<Person*> p = this->children();
        for(std::set<Person*>::iterator it=p.begin(); it!=p.end(); ++it){
            if(!((*it)->children().empty())){
                for(auto second: (*it)->children()){
                    if(second->gender() == Gender::MALE){
                         set.insert(second);
                    }
                   
                }
            }
        }
    }
    return set;

}
std::set<Person*> MyPerson::nephews(PMod pmod , SMod smod ){
    std::set<Person*> set;
    if(pmod == PMod::MATERNAL){
        if(smod == SMod::FULL){
            std::set<Person*> FullCuz = siblings(PMod::MATERNAL,SMod::FULL);
            for(Person* cuz: FullCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::MALE){
                        set.insert(child);
                    }
                }
            }
        }
        else if(smod == SMod::HALF){
            std::set<Person*> HalfCuz = siblings(PMod::MATERNAL,SMod::HALF);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::MALE){
                        set.insert(child);
                    }
                }
            }
        }
        else{
            std::set<Person*> HalfCuz = siblings(PMod::MATERNAL,SMod::ANY);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::MALE){
                        set.insert(child);
                    }
                }
            }
        }
    }
    if(pmod == PMod::PATERNAL){
        if(smod == SMod::FULL){
            std::set<Person*> FullCuz = siblings(PMod::PATERNAL,SMod::FULL);
            for(Person* cuz: FullCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::MALE){
                        set.insert(child);
                    }
                }
            }
        }
        else if(smod == SMod::HALF){
            std::set<Person*> HalfCuz = siblings(PMod::PATERNAL,SMod::HALF);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::MALE){
                        set.insert(child);
                    }
                }
            }
        }
        else{
            std::set<Person*> HalfCuz = siblings(PMod::PATERNAL,SMod::ANY);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::MALE){
                        set.insert(child);
                    }
                }
            }
        }
    }
    if(pmod== PMod::ANY){
        if(smod == SMod::FULL){
            std::set<Person*> FullCuz = siblings(PMod::ANY,SMod::FULL);
            for(Person* cuz: FullCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::MALE){
                        set.insert(child);
                    }
                }
            }
        }
        else if(smod == SMod::HALF){
            std::set<Person*> HalfCuz = siblings(PMod::ANY,SMod::HALF);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::MALE){
                        set.insert(child);
                    }
                }
            }
        }
        else{
            std::set<Person*> HalfCuz = siblings(PMod::ANY,SMod::ANY);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::MALE){
                        set.insert(child);
                    }
                }
            }
        }
    }
    
    return set;
}
std::set<Person*> MyPerson::nieces(PMod pmod , SMod smod){
   std::set<Person*> set;
    if(pmod == PMod::MATERNAL){
        if(smod == SMod::FULL){
            std::set<Person*> FullCuz = siblings(PMod::MATERNAL,SMod::FULL);
            for(Person* cuz: FullCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
        }
        else if(smod == SMod::HALF){
            std::set<Person*> HalfCuz = siblings(PMod::MATERNAL,SMod::HALF);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
        }
        else{
            std::set<Person*> HalfCuz = siblings(PMod::MATERNAL,SMod::ANY);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
        }
    }
    if(pmod == PMod::PATERNAL){
        if(smod == SMod::FULL){
            std::set<Person*> FullCuz = siblings(PMod::PATERNAL,SMod::FULL);
            for(Person* cuz: FullCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
        }
        else if(smod == SMod::HALF){
            std::set<Person*> HalfCuz = siblings(PMod::PATERNAL,SMod::HALF);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
        }
        else{
            std::set<Person*> HalfCuz = siblings(PMod::PATERNAL,SMod::ANY);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
        }
    }
    if(pmod== PMod::ANY){
        if(smod == SMod::FULL){
            std::set<Person*> FullCuz = siblings(PMod::ANY,SMod::FULL);
            for(Person* cuz: FullCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
        }
        else if(smod == SMod::HALF){
            std::set<Person*> HalfCuz = siblings(PMod::ANY,SMod::HALF);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
        }
        else{
            std::set<Person*> HalfCuz = siblings(PMod::ANY,SMod::ANY);
            for(Person* cuz: HalfCuz){
                for(Person* child: cuz->children()){
                    if(child->gender() == Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
        }
    }
    
    return set;
}
std::set<Person*> MyPerson::parents(PMod pmod){
    std::set<Person*> set;
    if(pmod == PMod::PATERNAL){
        if(mFather){
            set.insert(mFather);
        }else{
            return set;
        }
    }
    else if(pmod==PMod::MATERNAL){
        if(mMother){
            set.insert(mMother);
        }else{
            return set;
        }
    }
    else if(pmod==PMod::ANY){
        if(mFather&&mMother){
            set.insert(mFather);
            set.insert(mMother);
        }
        if(mFather&&!(mMother)){
            set.insert(mFather);
        }
        if(mMother&&!(mFather)){
            set.insert(mMother);
        }
        
        
    }
  
    return set;
}
std::set<Person*> MyPerson::siblings(PMod pmod , SMod smod ){
     std::set<Person*> set;
    if(pmod == PMod::MATERNAL){
        if(mother()!=nullptr){
        std::set<Person*> maternal = mother()->children();
        for(Person* child: maternal){
            if(smod == SMod::FULL){
                if(child->father() == father()){
                    set.insert(child);
                }
            }
            else if(smod == SMod::HALF){
                if(child->father()!=father()){
                    set.insert(child);
                }
            }
            else{
                set.insert(child);
            }
            
        }
        }
        
    }
    if(pmod == PMod::PATERNAL){
         if(father()!=nullptr){
            std::set<Person*> paternal = father()->children();
        for(Person* child: paternal){
            if(smod == SMod::FULL){
                if(child->mother() == mother()){
                    set.insert(child);
                }
            }
            else if(smod == SMod::HALF){
                if(child->mother()!=mother()){
                    set.insert(child);
                }
            }
            else{
                set.insert(child);
            }
            
        }
         }
        
    }
    if(pmod == PMod::ANY){
        if(mother()!=nullptr&&father()!=nullptr){
            std::set<Person*> maternal = mother()->children();
            std::set<Person*> paternal = father()->children();
            std::set<Person*> all;
            all.insert(maternal.begin(),maternal.end());
            all.insert(paternal.begin(),paternal.end());
            for(Person* child: all){
                if(smod==SMod::FULL){
                    if(child->mother() == mother()&&child->father()==father()){
                        set.insert(child);
                    }
                }   
            else if(smod==SMod::HALF){
                 if((child->mother() == mother()&&child->father()!=father())||(child->mother() != mother()&&child->father()==father())){
                    set.insert(child);
                }
            }
            else{
                set.insert(child);
            }
            }
        }
        if(mother()==nullptr&&father()!=nullptr){
            
            std::set<Person*> paternal = father()->children();
            
            for(Person* child: paternal){
                if(smod==SMod::FULL){
                    if(child->father()==father()&&child->mother()==nullptr){
                        set.insert(child);
                    }
                }
                else if(smod==SMod::HALF){
                    if(child->father()==father()&&child->mother()!=nullptr){
                        set.insert(child);
                    
                    }
                }
                   
            else{
                set.insert(child);
            }
            }
        }
         if(mother()!=nullptr&&father()==nullptr){
            
            std::set<Person*> maternal = mother()->children();
            
            for(Person* child: maternal){
                if(smod==SMod::FULL){
                    if(child->mother()==mother()&&child->father()==nullptr){
                        set.insert(child);
                    }
                }
                else if(smod == SMod::HALF){
                    if(child->mother()==mother()&&child->father()!=nullptr){
                        set.insert(child);
                    }
                }   
            else{
                set.insert(child);
            }
            }
        }
        
    }
    set.erase(this);
    return set;
}
std::set<Person*> MyPerson::sisters(PMod pmod, SMod smod ){
   std::set<Person*> set;
    if(pmod == PMod::MATERNAL){
        if(mother()!=nullptr){
        std::set<Person*> maternal = mother()->children();
        for(Person* child: maternal){
            if(smod == SMod::FULL){
                if(child->father() == father()){
                    if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
                    
                }
            }
            else if(smod == SMod::HALF){
                if(child->father()!=father()){
                   if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
            else{
                if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
            }
            
        }
        }
        
    }
    if(pmod == PMod::PATERNAL){
         if(father()!=nullptr){
            std::set<Person*> paternal = father()->children();
        for(Person* child: paternal){
            if(smod == SMod::FULL){
                if(child->mother() == mother()){
                    if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
            else if(smod == SMod::HALF){
                if(child->mother()!=mother()){
                    if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
            else{
                if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
            }
            
        }
         }
        
    }
    if(pmod == PMod::ANY){
        if(mother()!=nullptr&&father()!=nullptr){
            std::set<Person*> maternal = mother()->children();
            std::set<Person*> paternal = father()->children();
            std::set<Person*> all;
            all.insert(maternal.begin(),maternal.end());
            all.insert(paternal.begin(),paternal.end());
            for(Person* child: all){
                if(smod==SMod::FULL){
                    if(child->mother() == mother()&&child->father()==father()){
                        if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
                    }
                }   
            else if(smod==SMod::HALF){
                 if((child->mother() == mother()&&child->father()!=father())||(child->mother() != mother()&&child->father()==father())){
                    if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
                }
            }
            else{
                if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
            }
            }
        }
        if(mother()==nullptr&&father()!=nullptr){
            
            std::set<Person*> paternal = father()->children();
            
            for(Person* child: paternal){
                if(smod==SMod::FULL){
                    if(child->father()==father()&&child->mother()==nullptr){
                        if(child->gender()==Gender::FEMALE){
                            set.insert(child);
                    }
                    }
                }
                else if(smod==SMod::HALF){
                    if(child->father()==father()&&child->mother()!=nullptr){
                        if(child->gender()==Gender::FEMALE){
                            set.insert(child);
                    }
                    
                    }
                }
                   
            else{
                if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
            }
            }
        }
         if(mother()!=nullptr&&father()==nullptr){
            
            std::set<Person*> maternal = mother()->children();
            
            for(Person* child: maternal){
                if(smod==SMod::FULL){
                    if(child->mother()==mother()&&child->father()==nullptr){
                        if(child->gender()==Gender::FEMALE){
                            set.insert(child);
                    }
                    }
                }
                else if(smod == SMod::HALF){
                    if(child->mother()==mother()&&child->father()!=nullptr){
                        if(child->gender()==Gender::FEMALE){
                            set.insert(child);
                    }
                    }
                }   
            else{
                if(child->gender()==Gender::FEMALE){
                        set.insert(child);
                    }
            }
            }
        }
        
    }
    set.erase(this);
    return set;
}
std::set<Person*> MyPerson::sons(){
    std::set<Person*> set;
    for(std::set<MyPerson*>::iterator it=mChild.begin(); it!=mChild.end(); ++it){
        if((*it)->gender() == Gender::MALE){
            set.insert((*it));
        }

    }
    return set;
}
std::set<Person*> MyPerson::uncles(PMod pmod , SMod smod ){
    std::set<Person*> set;
    if(pmod == PMod::MATERNAL){
        if(mother()!=nullptr){
            if(smod == SMod::FULL){
                set = mother()->brothers(PMod::ANY,SMod::FULL);
            }
            else if(smod == SMod::HALF){
                set = mother()->brothers(PMod::ANY,SMod::HALF);
            }
            else{
                set = mother()->brothers(PMod::ANY,SMod::ANY);
            }
        }
    }
    if(pmod == PMod::PATERNAL){
        if(father()!=nullptr){
            if(smod == SMod::FULL){
                set = father()->brothers(PMod::ANY,SMod::FULL);
            }
            else if(smod == SMod::HALF){
                set = father()->brothers(PMod::ANY,SMod::HALF);
            }
            else{
                set = father()->brothers(PMod::ANY,SMod::ANY);
            }
        }
    }
    if(pmod==PMod::ANY){
        if(father()!=nullptr&&mother()!=nullptr){
            if(smod==SMod::FULL){
                set = father()->brothers(PMod::ANY,SMod::FULL);
                std::set<Person*> MatBros = mother()->brothers(PMod::ANY,SMod::FULL);
                set.insert(MatBros.begin(),MatBros.end());
            }
            else if(smod==SMod::HALF){
                set = father()->brothers(PMod::ANY,SMod::HALF);
                std::set<Person*> MatBros = mother()->brothers(PMod::ANY,SMod::HALF);
                set.insert(MatBros.begin(),MatBros.end());
            }
            else{
                set = father()->brothers(PMod::ANY,SMod::ANY);
                std::set<Person*> MatBros = mother()->brothers(PMod::ANY,SMod::ANY);
                set.insert(MatBros.begin(),MatBros.end());
            }
        }
        if(father()==nullptr&&mother()!=nullptr){
            if(smod==SMod::FULL){
                set = mother()->brothers(PMod::ANY,SMod::FULL);
                
            }
            else if(smod==SMod::HALF){
                set = mother()->brothers(PMod::ANY,SMod::HALF);
               
            }
            else{
                set = mother()->brothers(PMod::ANY,SMod::ANY);
               
            }
        }
        if(father()!=nullptr&&mother()==nullptr){
            if(smod==SMod::FULL){
                set = father()->brothers(PMod::ANY,SMod::FULL);
                
            }
            else if(smod==SMod::HALF){
                set = father()->brothers(PMod::ANY,SMod::HALF);
               
            }
            else{
                set = father()->brothers(PMod::ANY,SMod::ANY);
               
            }
        }
    }

    
    return set;
}