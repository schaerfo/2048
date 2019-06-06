#include "ui.h"

#include <stdio.h>

void show_grid(grid_t ** grid, int size) {
    printf("┌");
    for (int i=0; i<size-1; ++i)
        printf("───┬");
    printf("───┐");
    for (int i=0; i<size; ++i) {
        printf("\n│");
        for (int j=0; j<size; ++j) {
            if (grid[i][j] == 0)
                printf("   │");
            else
                printf("%3d│", grid[i][j]);
        }
        if (i != size-1) {
            printf("\n├");
            for (int j=0; j<size-1; ++j)
                printf("───┼");
            printf("───┤");
        }
    }
    printf("\n└");
    for (int i=0; i<size-1; ++i)
        printf("───┴");
    printf("───┘\n");
}
