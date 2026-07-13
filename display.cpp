#include "display.h"
#include "splashkit.h"

string charge_icons(int charges) {
  string icons = "";
  for (int i = 0; i < charges; i++) {
    icons += "⚡︎";
  }
  return icons;
}

void clear_screen() { write_line("\033[2J\033[1;1H"); }
