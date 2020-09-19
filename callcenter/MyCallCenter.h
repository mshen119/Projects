#ifndef MYCALLCENTER_H
#define MYCALLCENTER_H

#include "CallCenter.h"
#include <queue>
#include <set>
#include <algorithm>
#include <map>
#include <list>
#include "Objects.h"
#include <cmath>
struct CallEmployee: public Employee{
  int call_id;

  //So that we can do CallEmployee = Employee();
  void operator= (const Employee& employee){
    this->id = employee.id;
    this->name = employee.name;
    this->skill = employee.skill;
    this->call = employee.call;
  }
};

int _minute;
class MyCallCenter: public CallCenter {
std::vector<CallEmployee> _employees;
int e_size;
std::map<int, Call*> all_pool;
std::queue<int> callList;
std::vector<Call*> hold_pool;

  
public:
  // Constructor
  MyCallCenter(std::vector<Employee> employees);
  ~MyCallCenter();

  // Required Member Functions
  std::vector<int> calls(int minute, const std::vector<int>& call_ids);
  void learn(int minute, const std::vector<Call>& calls);

  // Other Member Functions
  
  static double r_importance(const Call* call);
  static int time_saved(const Call* curr, const Call* other, int minute);
};

#endif
/*
for(auto& employee : _employees){
    skillMap[employee.skill] = std::vector<int>();
  }
  for(auto& employee : _employees){
    skillMap.find(employee.skill)->second.push_back(employee.id);
  }

  for(auto skill_employee : skillMap){
    for(auto emp_id : skill_employee.second){
  */