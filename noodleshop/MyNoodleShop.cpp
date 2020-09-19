#include "MyNoodleShop.h"
#include <algorithm>
#include <utility>

// This is here to avoid creating yet another object file.
NoodleShop* NoodleShop::create(int npots, int rent, int customers, std::vector<Noodle> noodles) {
  return new MyNoodleShop(npots, rent, customers, noodles);
}


MyNoodleShop::MyNoodleShop(int npots, int mrent, int mcustomers, std::vector<Noodle> mnoodles){

  for(const auto& noodle: mnoodles) {
    NoodleInfo info;
    info.noodleName      = noodle.name;
    info.cook_time       = noodle.cook_time;
    info.batch_size      = noodle.batch_size;
    info.ingredient_cost = noodle.ingredient_cost;
    info.serving_price   = noodle.serving_price;
    info.break_even_serves = noodle.batch_size - std::round(static_cast<double>(noodle.ingredient_cost)/static_cast<double>(noodle.serving_price));
  
    noods[noodle.name] = info;
    _supply[noodle.name] = 0;
  }

  orderCount = 0;
  serve_time = 0;
  
  for(int i = 0; i<npots; i++){
    PotInfo pot;
    pot.pot_id = i;
    pot.noodle = "";
    pot.ready_at = 0;
    pot.servings = 0;
    pot.stale_at = 0;
    mPots.push_back(pot);
  }
  
  num_pots = npots;
  _rent = mrent;
  _customers = mcustomers;
  _noodles = mnoodles;

}

// MyNoodleShop Member Functions
std::vector<Order> MyNoodleShop::orders(int minute, std::vector<Order> orderlist){
  std::vector<Order> wanted;
  
  for(const auto& order: orderlist) {
    auto itr = noods.find(order.noodle);

    OrderInfo info;
    info.id     = order.id;
    info.noodle = order.noodle;
    info.minute = minute;

    NoodleInfo& noodle = itr->second;
    noodle.orders.push(info);
    wanted.push_back(order);
  }
  return wanted;
}

Action* MyNoodleShop::action(int minute){
  for(auto& noodle : _supply){
    noodle.second = 0;
  }
  //Updates Supply for every noodle
  for(auto& pot : mPots){
    std::map<std::string, NoodleInfo>::iterator noodle = noods.find(pot.noodle);
    if(noodle != noods.end()){
      auto itr = _supply.find(pot.noodle);
      itr->second += pot.servings;
    }
  }

  Action* action = nullptr;
  int caseNum = -1;
  int pid = 0; 
  std::queue<int> pidQ;
  std::string noodle = "";
  std::queue<std::string> noodQ;

  bool valid = true;
  for(auto& _noodle : noods){
    int demand  = _noodle.second.orders.size();
    int supply = _supply.find(_noodle.first)->second;
    if(supply<demand){
      caseNum = 0;
      noodle = _noodle.first;
      noodQ.push(_noodle.first);
      break;
    }
    else if(supply>=demand && valid){
      for(const auto& _pot : mPots){
         if(needsServe(_pot, minute)){
          pidQ.push(_pot.pot_id);
          caseNum = 1;
        }
      }
      valid = false;
    }
  }//for noodles loop

  if(caseNum == 0 || !noodQ.empty()){
    //look for empty pot
    pid = emptyPotid();
    
    if(pid != -1){
      PotInfo& pot = mPots[pid];
      action = new CookAction(pid, noodle);
      pot.noodle   = noodQ.front();
      pot.ready_at = minute + noods.find(noodQ.front())->second.cook_time;
      pot.stale_at = minute + noods.find(noodQ.front())->second.cook_time + 30;
      pot.servings = noods.find(noodQ.front())->second.batch_size;
      noodQ.pop();
      return action;
    }
    else{
      auto nood = noods.find(noodQ.front());
      if(nood==noods.end())
        return new NoAction();
      else if(nood->second.orders.size()==0)
        return new NoAction();
      if(nood->second.orders.front().minute 
      + nood->second.cook_time + 1 > minute + 10){
        for(auto& _pot : mPots){
          if((_pot.servings == 0 && _pot.noodle != "") || (minute >= _pot.stale_at && _pot.stale_at!=0)){
            pid = _pot.pot_id;
            action = new CleanAction(pid);
            _pot.noodle = "";
            _pot.ready_at = 760;
            _pot.stale_at = 760;
            _pot.servings = 0;
            return action;
          }
          else{
            pid = mostUselessPotid();
            PotInfo& pot = mPots[pid];
            action = new CleanAction(pid);
            pot.noodle = "";
            pot.ready_at = 760;
            pot.stale_at = 760;
            pot.servings = 0;
            return action;
          }
        }
      }
    }
    caseNum = 1;
  }
  if(caseNum == 1 || minute%10==0){
    std::vector<Serve> serve;
    while(pidQ.size()!=0){
      PotInfo& pot = mPots[pidQ.front()];

      auto itr = noods.find(pot.noodle);
      NoodleInfo& noodle = itr->second; 

      //keeps track of ready orders to be served.
      int numServed = 0;

      while(noodle.orders.size() != 0 || numServed == noodle.batch_size){
        
        //look at the orders in queue for that specific noodle.
        Serve ready;
        if(noodle.orders.size()==0)
          break;
        OrderInfo& front = noodle.orders.front();
        ready.order_id = front.id;
        ready.pot_id = pidQ.front();

        //take the order out of ticket line and the order queue.
        noodle.orders.pop();

        //add the order to be served, update servings in the pot left.
        serve.push_back(ready);
        pot.servings -= 1;
        numServed++;
      }
      pidQ.pop();
    }
    if(serve.size()!=0){
      action = new ServeAction(serve);
      return action;
    }
      
  }
  
  for(auto& _pot : mPots){
    if(needsClean(_pot, minute)){
      pid = _pot.pot_id;
      action = new CleanAction(pid);
      _pot.noodle = "";
      _pot.ready_at = 0;
      _pot.stale_at = 0;
      _pot.servings = 0;
      return action;
    }
  } 

  if(action == nullptr){
    action = new NoAction();
  }
  
  return action;

}

bool MyNoodleShop::emptyPot(PotInfo pot){
  if(pot.noodle == "")
    return true;
  return false;
}

bool MyNoodleShop::needsClean(PotInfo pot, int minute){
    if((pot.servings == 0 && pot.noodle != "") || (minute >= pot.stale_at && pot.stale_at!=0))
      return true;
    /*
    else if(pot.servings <= noods.find(pot.noodle)->second.break_even_serves && pot.servings!=0)
      return true;
*/
    
    return false;
}

int MyNoodleShop::emptyPotid(){
  for(auto& pot: mPots){
    if(pot.noodle == "")
      return pot.pot_id;
  }
  return -1;
}

bool MyNoodleShop::needsServe(PotInfo pot, int minute){
  //we have an order for that noodle
  bool needServe = false;

  //searches for the noodle in our menu
  auto itr = noods.find(pot.noodle);

  //if the pot is empty, then nothing to be served.
  //if the pot serving is not equal to the noodle we are looking at, we dont want to serve.
  if(itr == noods.end()){
    return false;
  }

  NoodleInfo noodle = itr->second;
  if(noodle.orders.size()!=0)
    needServe = true;
  if(minute >= pot.ready_at && minute < pot.stale_at && needServe){
    return true;
  } 
  return false;
}

int MyNoodleShop::mostUselessPotid(){
  int pid = 0;
  for(auto& pot : mPots){
    if(pot.servings < mPots.at(pid).servings)
      pid = pot.pot_id;
  }
  return pid;
}

MyNoodleShop::~MyNoodleShop(){
}