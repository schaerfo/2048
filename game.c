#include "game.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void initialize_rng() {
    srand((unsigned int)time(NULL));
}

void add_number(grid_t ** g, grid_size_t s) {
    /* Find out which spots in g are free, store their adresses */
    grid_size_t free_spot_count = 0;
    grid_t ** free_spots = calloc(s*s, sizeof(grid_t *));
    grid_t ** next_free = free_spots;
    for (grid_t * it=*g; it<&(g[0][s*s]); ++it){
        if (!(*it)) {
            ++free_spot_count;
            *next_free = it;
            ++next_free;
        }
    }

    if (free_spot_count){
        grid_size_t pos = (grid_size_t) rand() % free_spot_count;
        bool use4 = rand() % 4;
        free_spots[pos][0] = use4 ? 1 : 2;
    }
    free(free_spots);
}
