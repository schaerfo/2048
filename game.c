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