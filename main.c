#include <stdio.h>

#include "mem.h"
#include "ui.h"

int main() {
    grid_t ** g = init_grid(6);
    g[3][2] = 3;
    g[1][4] = 1;
    g[1][0] = 7;
    show_grid(g, 6);
    free_grid(g);
    return 0;
}
