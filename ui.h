#ifndef UI_H
#define UI_H

#include "globals.h"

void prepare_terminal();
void finalize_terminal();

void show_grid(grid_t ** grid, grid_size_t size);

user_action get_user_action();

void show_help();
void show_info();

#endif
