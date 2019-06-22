#ifndef MAIN_H
#define MAIN_H

#include "globals.h"

void game_loop(grid_t ** g, grid_size_t s);
void run_game();

#ifndef __m68k__
int main();
#endif

#endif
