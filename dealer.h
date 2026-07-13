#ifndef DEALER_H
#define DEALER_H

#include "player.h"
#include "round.h"

class Dealer : public Player {

public:
  Dealer();

  void take_turn(Round &round, Player &player, bool &is_player_turn);
};

#endif
