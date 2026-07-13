#ifndef ROUND_H
#define ROUND_H

#include "constants.h"

class Round {

public:
  int shell[MAX_SHELLS];
  int total;
  int current;

  Round();

  void load();
  void print_rounds();
  int get_shot();
  bool has_shells();
};

#endif
