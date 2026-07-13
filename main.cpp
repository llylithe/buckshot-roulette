#include "dealer.h"
#include "display.h"
#include "game.h"
#include "item.h"
#include "player.h"
#include "splashkit.h"
#include "utilities.h"

int main() {

  clear_screen();

  write_line(
      "██████╗ ██╗   ██╗ ██████╗██╗  ██╗███████╗██╗  ██╗ ██████╗ ████████╗ \n"
      "██╔══██╗██║   ██║██╔════╝██║ ██╔╝██╔════╝██║  ██║██╔═══██╗╚══██╔══╝\n"
      "██████╔╝██║   ██║██║     █████╔╝ ███████╗███████║██║   ██║   ██║ \n"
      "██╔══██╗██║   ██║██║     ██╔═██╗ ╚════██║██╔══██║██║   ██║   ██║  \n"
      "██████╔╝╚██████╔╝╚██████╗██║  ██╗███████║██║  ██║╚██████╔╝   ██║ \n"
      "╚═════╝  ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝    ╚═╝ \n"
      "                                                                  \n"
      "██████╗  ██████╗ ██╗   ██╗██╗     ███████╗████████╗████████╗███████╗\n"
      "██╔══██╗██╔═══██╗██║   ██║██║     ██╔════╝╚══██╔══╝╚══██╔══╝██╔════╝\n"
      "██████╔╝██║   ██║██║   ██║██║     █████╗     ██║      ██║   █████╗ \n"
      "██╔══██╗██║   ██║██║   ██║██║     ██╔══╝     ██║      ██║   ██╔══╝ \n"
      "██║  ██║╚██████╔╝╚██████╔╝███████╗███████╗   ██║      ██║   ███████╗\n"
      "╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝      ╚═╝   ╚══════╝\n");

  read_string("");

  open_audio();
  load_music("buckshot", "buckshot.mp3");
  play_music("buckshot", -1);

  string player_name = sign_waiver();

  clear_screen();

  Player player(player_name);
  Dealer dealer;
  int choice;

  do {
    write_line("");
    print_menu();

    choice = read_integer("\nOption: ", 1, 3);

    switch (choice) {
    case 1:
      player.reset();
      dealer.reset();

      while (player.is_alive() && dealer.is_alive()) {
        play_game(player, dealer);
      }
      break;
    case 2:
      write_line("Help coming soon");
      break;
    case 3:
      write_line("Goodbye.");
      break;
    }
  } while (choice != 3);
}
