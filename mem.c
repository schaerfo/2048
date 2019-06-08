#include "mem.h"

#include "stdlib.h"

grid_t ** init_grid(grid_size_t size) {
    grid_t * grid_start = (grid_t*) malloc(size * size * sizeof (grid_t));
    grid_t ** ret = (grid_t**) malloc(size * sizeof(grid_t*));
    for (grid_size_t i=0; i<size*size; ++i)
        grid_start[i] = 0;

    for (grid_size_t i=0; i<size; ++i)
        ret[i] = &(grid_start[i*size]);
    return ret;
}

void free_grid(grid_t ** grid){
    free(grid[0]);
    free(grid);
}
