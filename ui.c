#include "ui.h"

#include <stdio.h>

void show_grid(grid_t ** grid, grid_size_t size) {
    printf("┌");
    for (grid_size_t i=0; i<size-1; ++i)
        printf("───┬");
    printf("───┐");
    for (grid_t **i = grid; i<&(grid[size]); ++i) {
        printf("\n│");
        for (grid_t *j=*i; j<&((*i)[size]); ++j) {
            if (*j == 0)
                printf("   │");
            else
                printf("%3d│", *j);
        }
        if (i != &(grid[size-1])) {
            printf("\n├");
            for (grid_size_t j=0; j<size-1; ++j)
                printf("───┼");
            printf("───┤");
        }
    }
    printf("\n└");
    for (grid_size_t i=0; i<size-1; ++i)
        printf("───┴");
    printf("───┘\n");
}
