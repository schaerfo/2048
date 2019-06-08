#ifndef MEM_H
#define MEM_H

#include "globals.h"

grid_t ** init_grid(grid_size_t size);

void free_grid(grid_t ** grid);

#endif
