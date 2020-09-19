#ifndef MYNOODLESHOP_H
#define MYNOODLESHOP_H

#include "NoodleShop.h"
#include <map>
#include <queue>
#include <cmath>

  struct PotInfo {
    int pot_id;
    std::string noodle;
    int         ready_at;
    int         stale_at;
    int         servings;
    int         midpoint;
  };

  struct OrderInfo {
    int         id;
    std::string noodle;
    int         minute;
  };

  struct NoodleInfo {
    std::string noodleName;
    int cook_time;
    int batch_size;
    int ingredient_cost;
    int serving_price;
    int break_even_serves;

    std::queue<OrderInfo> orders;
  };

class MyNoodleShop: public NoodleShop {
  // Member Variables
  int orderCount;

  int serve_time;
  std::map<std::string, NoodleInfo> noods;
  std::vector<PotInfo> mPots;
  std::map<std::string, int> _supply;
  std::queue<std::string> noodQ;
  //std::map<NoodleInfo, int> demand;
  
  int num_pots;
  int _rent;
  int _customers;
  std::vector<Noodle> _noodles;

public:
  
  MyNoodleShop(int npots, int mrent, int mcustomers, std::vector<Noodle> mnoodles);
  ~MyNoodleShop();

  // Required Member Functions
  std::vector<Order> orders(int minute, std::vector<Order> orderlist);
  Action* action(int minute);

  // Other Member Functions
  Order takeOrder(std::vector<Order>& orderlist);

  void updateSupply();
  bool alreadyCooking(std::string noodle);
  bool needsCook();
  bool emptyPot(PotInfo pot);
  bool needsClean(PotInfo pot, int minute);
  bool needsServe(PotInfo pot, int minute,std::string noodleName);
  bool needsServe(PotInfo pot, int minute);
  //Action* recentOrder(int pid, PotInfo& pot, int minute);
  int emptyPotid();
  void updateTbCooked();
  int mostUselessPotid();
  
};

#endif
