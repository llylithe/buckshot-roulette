#include "dealer.h"
#include "display.h"
#include "splashkit.h"
#include "utilities.h"

Dealer::Dealer() : Player("Dealer") {}

void Dealer::take_turn(Round &round, Player &player, bool &is_player_turn) {

  write_line("\nDealer's turn\n");

  int blanks = 0;
  int remaining = round.total - round.current;

  for (int i = round.current; i < round.total; i++) {

    if (round.shell[i] == 0)
      blanks++;
  }

  double pr_blank = (double)blanks / remaining;

  if (pr_blank > 0.7) {

    write_line("\nDealer chooses to withstand.");

    int shot = round.get_shot();

    if (shot == 0) {

      write_line("\nBlank.");
      write_line(player.name + ": " + charge_icons(player.charges) +
                 "   Dealer: " + charge_icons(charges));
    } else {
      write_line("\nLive round.");

      take_damage();

      write_line("\nThe Dealer takes a hit.");
      write_line(player.name + ": " + charge_icons(player.charges) +
                 "   Dealer: " + charge_icons(charges));

      is_player_turn = true;
    }

  } else {
    write_line("\nDealer shoots");

    int shot = round.get_shot();

    if (shot == 0) {

      write_line("\nBlank.");
      write_line(player.name + ": " + charge_icons(player.charges) +
                 "   Dealer: " + charge_icons(charges));

      is_player_turn = true;
    } else {
      write_line("\nLive round.");

      player.take_damage();

      write_line("\n" + player.name + " takes a hit.");
      write_line(player.name + ": " + charge_icons(player.charges) +
                 "   Dealer: " + charge_icons(charges));

      is_player_turn = true;
    }
  }

  read_string("\nPress ENTER to continue...");
  clear_screen();
};
