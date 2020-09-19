#include "MyScheduler.h"

Scheduler* Scheduler::create(
  unsigned int                        deadline,
  std::map<std::string, unsigned int> cities,
  std::vector<std::string>            factories,
  std::vector<Route>                  routes
) {
  return new MyScheduler(deadline, cities, factories, routes);
}

MyScheduler::MyScheduler(
  unsigned int                        deadline, 
  std::map<std::string, unsigned int> cities, 
  std::vector<std::string>            factories, 
  std::vector<Route>                  routes
) {

  _deadline = deadline;
  _factories = factories;
  _routes = std::vector<RouteNode*>(routes.size());

  //goes through each city and initializes a new city object
  for(auto& pair : cities){
    City* city = new City;
    city->name = pair.first;
    city->population = pair.second;
    city->factory = false;
    city->dValue = 0;
    city->doses = 0;
    city->source = nullptr;
    _cities[pair.first] = city;
  }
  wDays = 0;
  wCosts = 0;
  //initialzes all the routes and it adds the routes to their member cities
  for(auto& rt : routes){
    //initalize all the routes
    RouteNode* route = new RouteNode;
    route->city1 = rt.city1;
    route->city2 = rt.city2;
    route->cost = rt.cost;
    route->days = rt.days;
    route->id = rt.id;
    route->load = rt.load;

    route->value = 0;
    route->src = nullptr;
    route->dest = nullptr;

    _routes[rt.id] = route;

    _cities[routes[rt.id].city1]->routeSet.insert(route);
    _cities[routes[rt.id].city1]->memberSet.insert(_cities[routes[rt.id].city2]);

    _cities[routes[rt.id].city2]->routeSet.insert(route);
    _cities[routes[rt.id].city2]->memberSet.insert(_cities[routes[rt.id].city1]);
    
    wDays+=route->days;
    wCosts+=((route->cost*1.0) / route->load*1.0);
  }

  //initalize the factory variable
  for(auto& factoryName : factories){
    _cities[factoryName]->factory = true;
    Node* n = new Node;
    n->city = _cities[factoryName];
    n->dValue = 0;
    n->source = nullptr;
    visited[_cities[factoryName]] = n;
    nodeTracker.push_back(n);
  }
}

// MyScheduler Member Functions
std::vector<Shipment> MyScheduler::schedule(){
  //int doses = 0;
  std::map<std::string, std::deque<std::pair<RouteNode, int>>> allPaths;
  
  std::vector<Node*> frontier;
  

  for(auto fac : _factories){
    for(auto& c : _cities[fac]->memberSet){
      if(!c->factory){
        Node* n = new Node;
        n->city = c;
        n->dValue = findDaysOfRoute(fac,c->name);
        n->cost = findCostOfRoute(fac, c->name, n->dValue);
        n->source = _cities[fac];
        frontier.push_back(n);
        nodeTracker.push_back(n);
      }
    }
  }
  
  while(visited.size()!=_cities.size()){
    std::sort(frontier.begin(), frontier.end(), [](const Node* lhs, const Node* rhs)
    {
      return lhs->cost < rhs->cost;
    } );
    
    Node* curr = frontier.front();
    while(visited.find(curr->city) != visited.end() && frontier.size()!=0){
      frontier.erase(frontier.begin());
      curr = frontier.front();
    }
    visited[curr->city] = curr;

    for(auto& d : curr->city->memberSet){
      if(visited.find(d)!=visited.end()){
        continue;
      }
      Node* n = new Node;
      n->city = d;
      n->dValue = findDaysOfRoute(curr->city->name, d->name) + curr->dValue;
      n->cost = findCostOfRoute(curr->city->name, d->name, n->dValue) + curr->cost;
      n->source = curr->city;
      frontier.push_back(n);
      nodeTracker.push_back(n);
    }
    frontier.erase(frontier.begin());
  }
  std::map<City*, std::vector<City*>> demandFrom;
  for(auto c : visited){
    c.first->source = c.second->source;
    c.first->dValue = c.second->dValue;
    if(!c.first->source){
      continue;
    }
    demandFrom[c.first->source].push_back(c.first);
  }
  
  for(auto f : _factories){
    update(_cities[f], demandFrom);
    //update(_cities[f], demandFrom, 0, nullptr);
  }
/*
  for(auto m : demandFrom){
    std::cout<<"Source: "<<m.first->name<<" = "<<m.first->doses<<std::endl;
    std::cout<<"Destinations: ";
    for(auto& r : m.second){
      std::cout<< r->name << " = " << r->doses<< "  ";
    }
    std::cout<<"\n";
    std::cout<<"\n";
  }
  */
  std::vector<Shipment> shipments;
  for(auto& m : demandFrom){
    for(auto& r : m.second){
      Shipment delivery;
      delivery.route_id = findRoute(m.first->name , r->name)->id;
      delivery.source = m.first->name;
      int day = m.first->dValue;
      delivery.day = day;
      delivery.doses = r->doses;
      shipments.push_back(delivery);
      /*
      std::cout<<"Day: "<<m.first->dValue<<std::endl;
      std::cout<<"Source: "<<m.first->name<<std::endl;
      std::cout<<"Doses: "<<m.first->doses<<std::endl;
      std::cout<<"city1: "<<_routes[delivery.route_id]->city1<<std::endl;
      std::cout<<"city2: "<<_routes[delivery.route_id]->city2<<std::endl;
      std::cout<<"\n";
      */
    }
  }
  return shipments;
}

int MyScheduler::update(City* source, std::map<City*, std::vector<City*>> demandFrom){
  if(demandFrom.find(source)!=demandFrom.end()){
    if(source->factory){
      for(auto& d : demandFrom[source])
        source->doses+=update(d, demandFrom);
    }
    else{
      for(auto& d : demandFrom[source])
        source->doses+=source->population + update(d, demandFrom);
    }
  }
  else
    source->doses = source->population;
  return source->doses;
}


/**
 * @return updates the day value for each city for when they should ship
 */ 
void MyScheduler::update(City* source, std::map<City*, std::vector<City*>> demandFrom, int days, City* parent){
  if(demandFrom.find(source)!=demandFrom.end()){
    if(source->factory){
      for(auto& d : demandFrom[source])
        update(d, demandFrom, 0, source);
    }
    else{
      source->dValue+=findDaysOfRoute(source->name, parent->name) + days;
      for(auto& d : demandFrom[source]){
        update(d, demandFrom, source->dValue, source);
      }
    }
  }
  else if(parent)
    source->dValue += findDaysOfRoute(source->name, parent->name) + days;
}



void MyScheduler::removeQueue(std::deque<RouteNode*>& q, RouteNode* r){
  for(auto it = q.cbegin(); it!=q.cend(); it++){
    if((*it)->id == r->id){
      q.erase(it);
      break;
    }
  }
}

RouteNode* MyScheduler::findRoute(std::string city1, std::string city2){
    for(size_t i = 0; i < _routes.size(); i++){
      if((_routes[i]->city1 == city1 || _routes[i]->city1 == city2)
      && (_routes[i]->city2 == city1 || _routes[i]->city2 == city2)){
        return _routes[i];
      }
    }
    return nullptr;
}

int MyScheduler::findDaysOfRoute(std::string city1, std::string city2){
    for(size_t i = 0; i < _routes.size(); i++){
      if((_routes[i]->city1 == city1 || _routes[i]->city1 == city2)
      && (_routes[i]->city2 == city1 || _routes[i]->city2 == city2)){
        return _routes[i]->days;
      }
    }
    return -1;
}

double MyScheduler::findCostOfRoute(std::string city1, std::string city2, double dValue){
    for(size_t i = 0; i < _routes.size(); i++){
      if((_routes[i]->city1 == city1 || _routes[i]->city1 == city2)
      && (_routes[i]->city2 == city1 || _routes[i]->city2 == city2)){
        double cost = (_routes[i]->cost*1.0) / (_routes[i]->load*1.0);
        double days = dValue;
        double weightedD = days/wDays;
        double weightedC = cost/wCosts;
        return 1.0/4.0*weightedD + 3.0/4.0*weightedC;
      }
    }
    return -1;
}



MyScheduler::~MyScheduler(){
  for(auto& r : _routes){
    delete r;
  }
  for(auto& c : _cities){
    delete c.second;
  }
  for(auto& n : nodeTracker){
    delete n;
  }
  nodeTracker.clear();
  _routes.clear();
  _cities.clear();
}