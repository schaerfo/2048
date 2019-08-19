#include "game.h"

#include "ui.h"
#include "mem.h"

#include <stdlib.h>
#ifndef __m68k__
#include <time.h>
#endif

void initialize_rng() {
#ifdef __m68k__
    randomize();
#else
    srand((unsigned int)time(NULL));
#endif
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
        bool use4 = rand() % 9;
        free_spots[pos][0] = use4 ? 1 : 2;
    }
    free(free_spots);
}

bool move_fields(grid_t ** fields, grid_size_t s){
    // Previous field with a non-zero value
    grid_t ** prev_number = NULL;
    // Let's see whether we have a number in the first field
    if (**fields)
        prev_number = fields;

    // We start at the second field
    grid_t ** it = &(fields[1]);
    bool ret = false;
    while (it != &(fields[s])){
        if (prev_number){
            // We can merge the fields
            if (**it && (**prev_number == **it)){
                ++(**prev_number);
                **it = 0;
                ret = true;
            }

            // We can move the field
            else if (prev_number != it-1){
                **(prev_number+1) = **it;
                **it = 0;
                ++prev_number;
                ret = true;
            }

            // Nothing done -> reset prev_number if required
            else {
                if (**it){
                    prev_number = it;
                }
            }
        }
        // Don't have a field with a previous number -> move to the start if field is non-zero
        else {
            if (**it) {
                **fields = **it;
                **it = 0;
                prev_number = fields;
                ret = true;
            }
        }
        ++it;
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
