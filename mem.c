#include "mem.h"

#include "stdlib.h"

grid_t ** init_grid(int size) {
    grid_t * grid_start = (grid_t*) malloc(size * size * sizeof (grid_t));
    grid_t ** ret = (grid_t**) malloc(size * sizeof(grid_t*));
    for (int i=0; i<size*size; ++i)
        grid_start[i] = 0;

    for (int i=0; i<size; ++i)
        ret[i] = &(grid_start[i*size]);
    return ret;
}

void free_grid(grid_t ** grid){
    free(grid[0]);
    free(grid);
}
