#ifndef GAME_H
#define GAME_H

#include "dealer.h"
#include "player.h"
#include <string>

using std::string;

string sign_waiver();
void print_menu();
void take_player_turn(Round &round, Player &player, Dealer &dealer,
                      bool &is_player_turn);
void play_game(Player &player, Dealer &dealer);

#endif
