#include "round.h"
#include "splashkit-arrays.h"
#include "splashkit.h"
#include "utilities.h"

Round::Round() {

  total = 0;
  current = 0;
}

void Round::load() { // loads the array for shell order.

  int lives = rnd(1, 4);
  int blanks = rnd(1, 4);

  total = lives + blanks;
  current = 0;

  for (int i = 0; i < lives; i++) {

    shell[i] = 1;
  }

  for (int i = lives; i < total; i++) {

    shell[i] = 0;
  }

  for (int i = total - 1; i > 0; i--) {

    int j = rnd(0, i);
    int temp = shell[i];
    shell[i] = shell[j];
    shell[j] = temp;
  }
}

void Round::print_rounds() { // prints the player number of lives and blanks.

  int lives = 0;
  int blanks = 0;

  for (int i = current; i < total; i++) {

    if (shell[i] == 1)
      lives++;

    else
      blanks++;
  }

  write_line("");

  if (lives == 1)
    write_line(to_string(lives) + " LIVE ROUND.");
  else
    write_line(to_string(lives) + " LIVE ROUNDS.");

  if (blanks == 1)
    write_line(to_string(blanks) + " BLANK.");
  else
    write_line(to_string(blanks) + " BLANKS.");
}

int Round::get_shot() { // gets the current shot (blank or live)

  int shot = shell[current];
  current++;

  return shot;
}

bool Round::has_shells() { return current < total; }
