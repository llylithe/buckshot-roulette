#include "player.h"
#include "splashkit.h"

Player::Player(string n) {
  name = n;
  charges = MAX_CHARGES;

  for (int i = 0; i < NUM_ITEMS; i++) {
    items[i] = 0;
  }
}

void Player::take_damage() { charges--; }

void Player::reset() { charges = MAX_CHARGES; }

bool Player::is_alive() { return charges > 0; }
