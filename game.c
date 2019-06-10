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

bool move_fields(grid_t ** fields, grid_size_t s){
    grid_t ** it = fields;
    bool ret = false;
    while (it != &(fields[s-1])){
        // Field not occupied, but next field is:
        // move value from next field, then continue from beginning
        if (!(**it) && **(it+1)) {
            **it = **(it+1);
            **(it+1) = 0;
            it = fields;
            ret |= true;
        }

        // Field and next field have same value (but not 0!):
        // increment field and set next field to 0
        // also advance iterator
        else if (**it && (**it == **(it+1))){
            ++(**it);
            ++it;
            **it = 0;
            ret |= true;
        }

        // Else: do not do anything, just advance iterator
        else ++it;
    }
    return ret;
}

bool move_grid(user_action direction, grid_t **g, grid_size_t s) {
    grid_t ** fields_sequence = calloc(s, sizeof(grid_t*));
    bool ret = false;
    for (grid_size_t i=0; i<s; ++i) {
        for (grid_size_t j=0; j<s; ++j) {
            if (direction == MOVE_DOWN) {
                fields_sequence[j] = &(g[s-j-1][i]);
            }
            else if (direction == MOVE_UP) {
                fields_sequence[j] = &(g[j][i]);
            }
            else if (direction == MOVE_RIGHT) {
                fields_sequence[j] = &(g[i][s-j-1]);
            }
            else if (direction == MOVE_LEFT) {
                fields_sequence[j] = &(g[i][j]);
            }
        }
        ret |= move_fields(fields_sequence, s);
    }
    free (fields_sequence);
    return ret;
}