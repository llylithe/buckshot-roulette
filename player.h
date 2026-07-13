#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"
#include <string>

using std::string;

class Player {

public:
  string name;
  int charges;
  int items[NUM_ITEMS];

  Player(string n);

  void take_damage();
  void reset();
  bool is_alive();
};

#endif
