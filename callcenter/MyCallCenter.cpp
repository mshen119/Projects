#include "MyCallCenter.h"
#include <iostream>


CallCenter* CallCenter::create(std::vector<Employee> employees) {
  return new MyCallCenter(employees);
}

MyCallCenter::MyCallCenter(std::vector<Employee> employees){
  //sort all employees with skill. Useless near front, most valued near back. No need for maps ;]
  sort(employees.begin(), employees.end(), [] (Employee a, Employee b){
    return a.skill < b.skill;
  });
  _employees =  std::vector<CallEmployee>(employees.size());
  e_size = _employees.size();
  
  for(int emp_i = 0; emp_i<e_size; emp_i++){
    _employees[emp_i] = employees[emp_i];
    _employees[emp_i].call_id = -1;
  }
 
}

// MyCallCenter Member Functions
std::vector<int> MyCallCenter::calls(int minute, const std::vector<int>& call_ids){
  _minute = minute;
  //int employee_id;
  //int stub = 0;
  //work on any calls
  //std::queue<int> actionQ;
  std::vector<int> actions(_employees.size(), 0);
  //recieves all incoming new calls and their ids
  for(auto id: call_ids){
    callList.emplace(id);
  }

  //iterate from back to front because most usefull are sorted near back
  for(int emp_id = e_size-1; emp_id>=0; emp_id--){
      CallEmployee* employee = &_employees[emp_id];
      if(employee->call == nullptr&&(employee->call_id != -1)){//there is a learned call that is not assigned to an Employee
        if(all_pool[employee->call_id] != nullptr){ //check if that call exists and has been learned
          employee->call = all_pool[employee->call_id];
          if(all_pool[employee->call_id]->difficulty>employee->skill){
            bool found = false;//need a skilled employee
            for(int j = emp_id; j<e_size;j++){
              //_employees[j].call_id == -1 means that the employee is not working on a call
              if(_employees[j].call_id == -1 && _employees[j].skill>=employee->call->difficulty){//find an employee that is available and skilled enough
                _employees[j].call_id = employee->call_id;
                employee->call_id = -1;
                employee->call = nullptr;
                found = true;
                break;
              }
            }
            if(!found){
              employee->call_id = -1; //no skilled employees are found
            }
          }
        }
      }
        
  }

//picks up incoming calls and assign them to an employee to answer
  for(int emp_i = 0; emp_i<e_size;emp_i++){
    if(_employees[emp_i].call_id ==  -1 && _employees[emp_i].call == nullptr){
      if(!(callList.empty())){
        _employees[emp_i].call_id = callList.front();
        all_pool.insert(std::pair<int,Call*>(callList.front(), nullptr));
        callList.pop();
      }
    }
  }
  

  if(!(hold_pool.empty())){//sorts the hold pool
     sort(hold_pool.begin(), hold_pool.end(), [] (Call* a, Call* b){
      double ia =r_importance(a), ib = r_importance(b);
      if(ia == ib){
        return a->importance > b->importance;
      }else{
        return ia < ib;
      }
    });
  }

  for(int emp_id = 0; emp_id<e_size; emp_id++){//assign to free employees
    if(_employees[emp_id].call_id== -1 && _employees[emp_id].call == nullptr){
      if(!(hold_pool.empty())){
        for(auto it = hold_pool.begin(); it != hold_pool.end(); it++){
          if(_employees[emp_id].skill >= (*it)->difficulty){//checks that they are skilled enough
            _employees[emp_id].call_id = (*it)->id;
            hold_pool.erase(it);
            break;
          }
        }
      }
    }
  }
  
if(callList.size()>269){
    //handles transfer and reassigning calls
    if(!(hold_pool.empty())){//there are calls on hold
      for(int emp_id = 0; emp_id<e_size; emp_id++){
        if(_employees[emp_id].call_id!=-1 && _employees[emp_id].call){
          int time = 0;
          for(size_t j = 0; j<hold_pool.size(); j++){
            if(time_saved(_employees[emp_id].call, hold_pool[j], minute) > time && _employees[emp_id].skill >= hold_pool[j]->difficulty){
              time = time_saved(_employees[emp_id].call, hold_pool[j], minute);
            }
          }
          if(time > 0){
            _employees[emp_id].call_id = -1;
          }
        }
      }
    }

    

    int time_remain = 540 - minute;
    for(auto call : hold_pool){//end of the day
      if((call->work_required - call->work_performed) + 2 >= time_remain){
        CallEmployee* most_time_saved = 0;
        int time = - time_remain;
        for(auto employee : _employees){
          if(employee.call){
            if(time_saved(employee.call, call, minute) > time){
              time = time_saved(employee.call, call, minute);
              most_time_saved = &employee;
            }
          }
        }

        if(most_time_saved)
          most_time_saved->call_id= call->id;
      }
    }
}

minute++;
minute--;
//updates actions with the calls we want and handles all of the push into hold pool and answering
for(int i = 0; i < e_size; i++){

    CallEmployee* employee = &_employees[i];
    if(employee->call_id != -1){
      if(employee->call != nullptr){
        //checks if the callid is assigned to the right employee
        if(employee->call->id == employee->call_id){
          //checks if need to complete call or work on call
          if(employee->call->work_performed == employee->call->work_required){
            employee->call_id = -1;
            employee->call = 0;
            actions[employee->id] = -1;
          }else{
            employee->call->work_performed++;
            actions[employee->id] = employee->call_id;
          }
        //push in hold pool
        }else {
          hold_pool.push_back(employee->call);
          actions[employee->id] = employee->call_id;
          employee->call = 0;
        }
      }else{
        //answering the call
        employee->call = all_pool[employee->call_id];
        actions[employee->id] = employee->call_id;
      }

    }else{
      if(employee->call != nullptr)
        hold_pool.push_back(employee->call);
      actions[employee->id] = 0;
      employee->call = 0;
    }
  }


  /*
  for(auto& employee :_employees){
    std::cout<<employee.id<<" "<<employee.name<<" "<<employee.call_id<<" "<<employee.call<<std::endl;
  }
  
  for(int i = 0; i< e_size; i++){
    std::cout<<"action: "<<i<<":"<<actions[i]<<std::endl;
  }
  */
 int count = 0;
  for(auto& e: _employees){
    if(e.call_id == -1 || e.call_id == 0){
      count++;
    }
  }/*
  std::cout<<count<<std::endl;
  std::cout<<hold_pool.size()<<std::endl;
  */
  int totalTime = 0;
  for(auto& call : hold_pool){
    totalTime+=call->work_required-call->work_performed;
  }
  for(auto& e: _employees){
    if(e.call!=nullptr)
      totalTime+=e.call->work_required - e.call->work_performed;
  }

  //std::cout<<"Total Time: "<<totalTime<<std::endl;
  
  return actions;
}

void MyCallCenter::learn(int , const std::vector<Call>& calls){
  //new calls
  for(auto call : calls)
    all_pool[call.id] = new Call(call);
}


int MyCallCenter::time_saved(const Call* curr, const Call* other, int minute){
  int time = (curr->work_required - curr->work_performed) * (minute-other->recieved)
            - minute-curr->recieved * (other->work_required - other->work_performed)
            - 2 * (curr->importance);
  return time;
}


double MyCallCenter::r_importance(const Call* call){
  return (call->work_required-call->work_performed)/double(_minute-call->recieved);
}


MyCallCenter::~MyCallCenter(){
  
  for(auto& call : all_pool){
    delete call.second;
  }
  all_pool.clear();
  
}