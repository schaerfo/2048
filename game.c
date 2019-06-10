#include "game.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void initialize_rng() {
    srand((unsigned int)time(NULL));
}

void add_number(grid_t ** g, grid_size_t s) {
    /* Find out which spots in g are free, store their indices */
    grid_size_t occupied_spot_count = 0;
    unsigned int* free_spot_map = calloc(s*s, sizeof(int*));

    for(unsigned int i=0; i<s*s; ++i){
        if ((*g)[i])
            ++occupied_spot_count;
        else
            free_spot_map[i-occupied_spot_count] = i;
    }
    unsigned int available_count = s*s - occupied_spot_count;
    if (available_count){
        unsigned int pos = (unsigned int) rand() % (available_count);
        bool use4 = rand() % 4;
        (*g)[free_spot_map[pos]] = use4 ? 1 : 2;
    }
    free(free_spot_map);
}
