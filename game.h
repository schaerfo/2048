#include "globals.h"

#include <stdbool.h>

void initialize_rng();

void add_number(grid_t ** g, grid_size_t s);

bool move_grid(user_action direction, grid_t ** g, grid_size_t s);