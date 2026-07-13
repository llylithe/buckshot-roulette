#include "utilities.h"
#include "splashkit.h"

string read_string(string prompt) {
  write(prompt);
  return read_line();
}

int read_integer(string prompt) {
  string line = read_string(prompt);
  while (!is_integer(line)) {
    write_line("Please enter a whole number.");
    line = read_string(prompt);
  }
  return to_integer(line);
}

int read_integer(string prompt, int min, int max) {
  int value = read_integer(prompt);
  while (value < min || value > max) {
    write_line("Please enter a value between " + to_string(min) + " and " +
               to_string(max) + ".");
    value = read_integer(prompt);
  }
  return value;
}

double read_double(string prompt) {
  string line = read_string(prompt);
  while (!is_double(line)) {
    write_line("Please enter a number.");
    line = read_string(prompt);
  }
  return to_double(line);
}

bool read_boolean(string prompt) {
  string line = read_string(prompt);
  while (line != "y" && line != "n") {
    write_line("Please enter [y/n]");
    line = read_string(prompt);
  }
  return line == "y";
}
