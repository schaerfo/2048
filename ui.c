#include "ui.h"

#include <stdio.h>

#ifdef __linux__
  #include <termios.h>
  #include <unistd.h>
#elif _WIN32
  #include <conio.h>
#endif

#ifdef __linux__
struct termios term_orig;
#endif

void prepare_terminal() {
#ifdef __linux__
    tcgetattr(STDIN_FILENO, &term_orig);
    struct termios term_mod = term_orig;
    /* We are not waiting for the enter key in getchar() and we
       do not want the input to appear in the terminal */
    term_mod.c_lflag &= ~ (ICANON|ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term_mod);
#endif /* Nothing to do on Windows */
}

void finalize_terminal() {
#ifdef __linux__
    tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
#endif /* Nothing to do on Windows */
}


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

user_action get_user_action() {
    for(;;) {
        printf("Input: ");
#ifdef __linux__
        int inp = getchar();
#elif _WIN32
        int inp = getch();
#endif
        switch (inp) {
            case 'h':
            case 'H': return HELP;
            case 'i':
            case 'I': return INFO;
            case 'w':
            case 'W': return MOVE_UP;
            case 's':
            case 'S': return MOVE_DOWN;
            case 'a':
            case 'A': return MOVE_LEFT;
            case 'd':
            case 'D': return MOVE_RIGHT;
        }
        printf("Invalid input, try again\n");
    }
    
}
