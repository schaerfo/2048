#include <stdio.h>

#include "game.h"
#include "mem.h"
#include "ui.h"

void game_loop(grid_t ** g, grid_size_t s) {
    add_number(g, s);
    show_grid(g, s);
    for(;;) {
        user_action act = get_user_action();
        switch (act) {
            case HELP: show_help(); break;
            case INFO: show_info(); break;
            case QUIT: return;
            default:
                if (move_grid(act, g, s))
                    add_number(g, s);
                show_grid(g, s);
        }
    }
}

int main() {
    prepare_terminal();
    initialize_rng();
    grid_t ** g = init_grid(4);
    game_loop(g, 4);
    free_grid(g);
    finalize_terminal();
    return 0;
}
