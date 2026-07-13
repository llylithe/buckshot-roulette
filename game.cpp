#include "game.h"
#include "display.h"
#include "item.h"
#include "splashkit.h"
#include "utilities.h"

string sign_waiver() {

  write_line(
      "This General Release (\"Release\") is made on 22 day of January, 2018 "
      "between ████████ at ████████████████████████████████ (\"Releasor\") and "
      "\n████████ at ████████████████████████ (\"Releasee\").");
  write_line(
      "\n1. Releasor and anyone claiming on Releasor's behalf releases and "
      "forever discharges Releasees and its affiliates, successors, officers, "
      "\nemployees, representatives, partners, agents and anyone claiming "
      "through them (collectively, the \"Released Parties\") in their "
      "\nindividual and/or corporate capacities from any and all claims, "
      "liabilities, obligations, promises, agreements, disputes, demands, "
      "\ndamages, causes of action of any nature and kind, known or unknown, "
      "which Releasor has or ever had or may in the future have against "
      "\nReleasees or any of the Released Parties arising out of or relating "
      "to: "
      "the termination of a contractual relationship between the Releasor and "
      "\nthe Releasee (\"Claims\").");
  write_line("\n2. In exchange for the release of Claims, Releasee will "
             "provide Releasor a payment in the amount of $10,000.00. In "
             "\nconsideration of such payment, Releasor agrees to accept the "
             "payment as full and complete settlement and satisfaction of any "
             "\npresent and prospective claims.");
  write_line("\n3. This Release shall not be in any way construed as an "
             "admission by the Releasee that it has acted wrongfully with "
             "\nrespect to Releasor or any other preson, that it admits "
             "liability or responsibility at any time for any purpose, or that "
             "\nReleasor has any rights whatsoever against the Releasee.");
  write_line(
      "\n4. This release shall be binding upon the parties and their "
      "respective heirs, administrators, personal representatives, executors, "
      "\nsuccessors and assigns. Releasor has the authority to release the "
      "Claims and has not assigned or transferred any Claims to any other "
      "\nparty. The provisions of this Release are severable. If any provision "
      "is held to be invalid or unenforceable, it shall not affect the "
      "\nvalidity or enforceability of any other provision. This Release "
      "constitutes the entire agreement between the parties and supersedes any "
      "\nand all prior oral or written agreements or understandings between "
      "the");

  return read_string("\nENTER NAME: ");
}

void print_menu() {
  write_line("BUCKSHOT ROULETTE\n");
  write_line("1. New Game");
  write_line("2. Help");
  write_line("3. Quit");
}

void take_player_turn(Round &round, Player &player, Dealer &dealer,
                      bool &is_player_turn) { // initiates one turn.

  bool shot_fired = false;

  while (!shot_fired) {

    write_line("\n" + player.name + "'s turn");
    write_line("\nChoose action: \n");
    write_line("1. Shoot Dealer");
    write_line("2. Withstand");
    write_line("3. Use item");

    int choice;
    choice = read_integer("\nOption: ", 1, 3);

    if (choice == 3) {

      item available_items[NUM_ITEMS];
      int num_options = build_item_menu(player, available_items);

      int item_choice = read_integer("\nOption: ", 1, num_options + 1);

      if (item_choice != num_options + 1) {
        item chosen = available_items[item_choice - 1];
        use_item(chosen, player, dealer, round);
        read_string("\nPress ENTER to continue...");
      }

      clear_screen();

    } else {

      int shot = round.get_shot();

      if (choice == 1) {
        if (shot == 1) {

          write_line("\nLive round.");

          dealer.take_damage();

          write_line("\nThe Dealer takes a hit.");
          write_line(player.name + ": " + charge_icons(player.charges) +
                     "   Dealer: " + charge_icons(dealer.charges));

        } else {
          write_line("\nBlank.");
          write_line(player.name + ": " + charge_icons(player.charges) +
                     "   Dealer: " + charge_icons(dealer.charges));
        }
        is_player_turn = false;

      } else {
        if (shot == 1) {

          write_line("\nLive round.");

          player.take_damage();

          write_line("\n" + player.name + " takes a hit.");
          write_line(player.name + ": " + charge_icons(player.charges) +
                     "   Dealer: " + charge_icons(dealer.charges));

          is_player_turn = false;

        } else {
          write_line("\nBlank.");
          write_line("Player's turn.");
          write_line(player.name + ": " + charge_icons(player.charges) +
                     "   Dealer: " + charge_icons(dealer.charges));
        }
      }
      read_string("\nPress ENTER to continue...");
      clear_screen();
      shot_fired = true;
    }
  }
}

void play_game(Player &player, Dealer &dealer) {

  read_string("\nPress Enter to start the game.");
  clear_screen();

  Round round;
  round.load();
  round.print_rounds();

  get_items(player, 2);
  get_items(dealer, 2);

  bool is_player_turn = rnd(0, 1) == 1;

  write_line("");

  if (is_player_turn) {
    write_line("The Player will start.");
  } else {
    write_line("The Dealer will take the first shot.");
  }

  read_string("\nPress ENTER to continue...");
  clear_screen();

  while (player.is_alive() && dealer.is_alive() && round.has_shells()) {
    if (is_player_turn) {
      take_player_turn(round, player, dealer, is_player_turn);
    } else {
      dealer.take_turn(round, player, is_player_turn);
    }
  }

  write_line("");

  if (!player.is_alive()) {
    write_line("You have died. Game over.");
  } else if (!dealer.is_alive()) {
    write_line("The Dealer has died. You win.");
  } else {
    write_line("Round over. Loading next round...");
  }
}
