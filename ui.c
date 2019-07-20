#include "ui.h"

#include <stdio.h>

#ifdef __linux__
  #include <termios.h>
  #include <unistd.h>
#elif defined(_WIN32)
  #include <conio.h>
#elif defined(__m68k__)
  #include <kbd.h>
#endif

#ifdef __linux__
static struct termios term_orig;
#endif

void prepare_terminal() {
#ifdef __linux__
    tcgetattr(STDIN_FILENO, &term_orig);
    struct termios term_mod = term_orig;
    /* We are not waiting for the enter key in getchar() and we
       do not want the input to appear in the terminal */
    term_mod.c_lflag &= ~ (ICANON/*|ECHO*/);
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
        for (grid_t *j=*i; j<&(i[0][size]); ++j) {
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
        printf("Input ('h' for help): ");
#ifdef __linux__
        int inp = getchar();
#elif defined(_WIN32)
        int inp = getch();
#elif defined(__m68k__)
        short inp = ngetchx();
#endif
        switch (inp) {
            case 'h':
            case 'H': printf("\n"); return HELP;
            case 'i':
            case 'I': printf("\n"); return INFO;
            case 'w':
            case 'W': printf("\n"); return MOVE_UP;
            case 's':
            case 'S': printf("\n"); return MOVE_DOWN;
            case 'a':
            case 'A': printf("\n"); return MOVE_LEFT;
            case 'd':
            case 'D': printf("\n"); return MOVE_RIGHT;
            case 'q':
            case 'Q': printf("\n"); return QUIT;
            default: printf("\nInvalid input, try again\n");
        }
    }
}

void show_help() {
    printf("h: Show help\n"
           "i: Show info\n"
           "q: Quit\n"
           "w: Move grid up\n"
           "s: Move grid down\n"
           "a: Move grid left\n"
           "d: Move grid right\n");
}

void show_info() {
    printf("C implementation of 2048\n"
           "Inspired by: github.com/gabrielecirulli/2048\n"
           "Website: github.com/schaerfo/2048\n"
           "Contributors (in alphabetical order):\n"
           " * Christian Schärf <c.schaerf@t-online.de>\n");
}
