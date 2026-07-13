#include "item.h"
#include "display.h"
#include "splashkit.h"
#include "utilities.h"

string item_name(item i) {

  switch (i) {

  case adrenaline:
    return "Adrenaline";

  case beer:
    return "Beer";

  case burner_phone:
    return "Burner Phone";

  case cigarette:
    return "Cigarette";

  case expired_medicine:
    return "Expired Medicine";

  case saw:
    return "Hand Saw";

  case handcuffs:
    return "Handcuffs";

  case inverter:
    return "Inverter";

  case magnifying_glass:
    return "Magnifying Glass";

  default:
    return "Unknown Item";
  }
}

string ordinal(int n) {

  switch (n) {
  case 1:
    return "FIRST";
  case 2:
    return "SECOND";
  case 3:
    return "THIRD";
  case 4:
    return "FOURTH";
  case 5:
    return "FIFTH";
  case 6:
    return "SIXTH";
  case 7:
    return "SEVENTH";
  case 8:
    return "EIGHTH";
  default:
    return "UNKNOWN";
  }
}

int total_items_held(Player &p) {
  int total = 0;
  for (int i = 0; i < NUM_ITEMS; i++) {
    total += p.items[i];
  }

  return total;
}

void get_items(Player &p, int count) {

  int held = total_items_held(p);
  int to_give;

  if (held == 7) {
    to_give = 1;
  } else if (held > 7) {
    to_give = 0;
  } else {
    to_give = count;
  }

  for (int i = 0; i < to_give; i++) {

    int item_index = rnd(0, NUM_ITEMS - 1);
    p.items[item_index]++;
  }
}

int build_item_menu(Player &p, item available_items[]) {

  int count = 0;

  for (int i = 0; i < NUM_ITEMS; i++) {

    if (p.items[i] > 0) {

      count++;
      write_line(to_string(count) + ". " + item_name((item)i) + " (x" +
                 to_string(p.items[i]) + ")");
      available_items[count - 1] = item(i);
    }
  }

  write_line(to_string(count + 1) + ". No item");

  return count;
}

bool confirm_item_use(string description) {

  write_line(description);
  string confirm = read_string("Confirm use (y/n): ");
  return confirm == "y" || confirm == "Y";
}

void use_item(item chosen, Player &user, Player &opponent, Round &round) {

  switch (chosen) {

  case adrenaline:
    write_line("\n" + user.name +
               " used adrenaline (feature currently unavailable)");
    break;

  case beer:
    write_line("\n" + user.name + " used beer.");
    break;

  case burner_phone:

    if (confirm_item_use(
            "A mysterious voice gives you insight from the future.")) {

      user.items[chosen]--;

      write_line("\n" + user.name + " used burner phone.");

      int remaining = round.total - round.current;

      if (remaining < 2) {
        write_line("How unforunate...");

      } else {
        int random_index = rnd(round.current, round.total - 1);
        int position = random_index - round.current + 1;

        write_line("\n" + ordinal(position) + " SHELL ...");

        if (round.shell[random_index] == 1) {
          write_line("\n... LIVE ROUND.");
        } else {
          write_line("\n... BLANK.");
        }
      }
    }
    break;

  case cigarette:

    if (confirm_item_use("Takes the edge off. Regain 1 charge.")) {

      user.items[chosen]--;

      write_line("\n" + user.name + " used cigarette.");

      if (user.charges < MAX_CHARGES) {
        user.charges++;
        write_line(user.name + " heals 1 charge.");
      } else {
        write_line(user.name + " is already at full health.");
      }

      write_line(user.name + ": " + charge_icons(user.charges));
    }
    break;

  case expired_medicine:

    if (confirm_item_use("50% chance to regain two charges."
                         "If not, lose one charge.")) {

      user.items[chosen]--;

      write_line("\n" + user.name + " used expired medicine.");

      if (rnd(0, 1) == 1) {

        user.charges += 2;

        if (user.charges > MAX_CHARGES) {
          user.charges = MAX_CHARGES;
        }

        write_line("\n" + user.name + " regains 2 charges.");

      } else {

        user.take_damage();
        write_line("\n" + user.name + " loses 1 charge.");
      }
    }
    break;

  case handcuffs:

    if (confirm_item_use(opponent.name + " skips the next turn.")) {

      user.items[chosen]--;

      write_line("\n" + user.name + " used handcuffs.");
    }
    break;

  case inverter:

    if (confirm_item_use(
            "Swaps the polarity of the current shell in the chamber.")) {

      user.items[chosen]--;

      write_line("\n" + user.name + " used inverter.");

      round.shell[round.current] = 1 - round.shell[round.current];
    }
    break;

  case magnifying_glass:

    if (confirm_item_use("Check the current round in the chamber.")) {

      user.items[chosen]--;

      write_line("\n" + user.name + " used magnifying glass.");
      write_line("");

      if (round.shell[round.current] == 1) {
        write_line("LIVE ROUND.");

      } else {
        write_line("BLANK.");
      }
    }
    break;

  case saw:

    if (confirm_item_use("Shotgun deals 2 damage.")) {

      user.items[chosen]--;

      write_line("\n" + user.name + " used saw.");
    }
    break;
  }
}
