#ifndef MYSCHEDULER_H
#define MYSCHEDULER_H

#include "Scheduler.h"
#include <set>
#include <deque>
#include <iostream>
#include <algorithm>

struct City;

struct RouteNode : public Route{
  int value;
  City* src;
  City* dest;
};

struct City {
  std::string          name;
  bool                 factory;
  unsigned int         population;
  int                  dValue;
  int                  doses;
  City* source;
  std::set<RouteNode*> routeSet;
  std::set<City*>      memberSet;
};

struct Node{
  City* city;
  int dValue;
  double cost;
  City* source;
  bool nope;
};
class MyScheduler: public Scheduler {
  unsigned int _deadline; 
  std::map<std::string, City*> _cities;
  std::vector<std::string> _factories; 
  std::vector<RouteNode*> _routes;
  std::map<City*, Node*> visited;
  std::vector<Node*> nodeTracker;
  double wDays;
  double wCosts;

public:
  MyScheduler(
    unsigned int deadline, 
    std::map<std::string, unsigned int> cities, 
    std::vector<std::string> factories, 
    std::vector<Route> routes
    );

  ~MyScheduler();

  // Required Member Function
  std::vector<Shipment> schedule();

  void removeQueue(std::deque<RouteNode*>& q, RouteNode* r);

  //Recursive call that updates the doses for each city in a path
  int update(City* source, std::map<City*, std::vector<City*>> demandFrom);

  //Recursive call that updates the days for each city in a path
  void update(City* source, std::map<City*, std::vector<City*>> demandFrom, int days, City* parent);

  //Returns the pointer to the route that contains the cities
  RouteNode* findRoute(std::string city1, std::string city2);

  //Returns the days of the route that contains the cities
  int findDaysOfRoute(std::string city1, std::string city2);

  //returns the cost of the route that contains the cities
  double findCostOfRoute(std::string city1, std::string city2, double dValue);
};

#endif