#ifndef ITEM_H
#define ITEM_H

#include "constants.h"
#include "player.h"
#include "round.h"
#include <string>

using std::string;

enum item {
  adrenaline,
  beer,
  burner_phone,
  cigarette,
  expired_medicine,
  saw,
  handcuffs,
  inverter,
  magnifying_glass
};

string item_name(item i);
int total_items_held(Player &p);
void get_items(Player &p, int count);
int build_item_menu(Player &p, item available_items[]);
bool confirm_item_use(string description);
void use_item(item chosen, Player &user, Player &opponent, Round &round);

#endif
