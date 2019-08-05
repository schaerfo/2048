#include "ui.h"

#include <stdio.h>

#ifdef __linux__
  #include <termios.h>
  #include <unistd.h>
#elif defined(_WIN32)
  #include <conio.h>
#elif defined(__m68k__)
  #include <kbd.h>
  #include <graph.h>
#endif

#ifdef __linux__
static struct termios term_orig;
#elif defined(__m68k__)
static const short grid_x_start = 40;
static const short grid_x_delta = 16;

static const short grid_y_start = 28;
static const short grid_y_delta = 11;
#endif

void prepare_terminal() {
#ifdef __linux__
    tcgetattr(STDIN_FILENO, &term_orig);
    struct termios term_mod = term_orig;
    /* We are not waiting for the enter key in getchar() and we
       do not want the input to appear in the terminal */
    term_mod.c_lflag &= ~ (ICANON/*|ECHO*/);
    tcsetattr(STDIN_FILENO, TCSANOW, &term_mod);
#elif defined(__m68k__)
    ClrScr();

    // At the moment, we can draw 4x4 grids only
    const short grid_y_end = grid_y_start + 4* grid_y_delta;
    const short grid_x_end = grid_x_start + 4* grid_x_delta;
    for (short i = grid_y_start; i <= grid_y_end; i += grid_y_delta){
        DrawLine(grid_x_start, i, grid_x_end, i, A_NORMAL);
    }

    for (short i = grid_x_start; i <= grid_x_end; i += grid_x_delta){
        DrawLine(i, grid_y_start, i, grid_y_end, A_NORMAL);
    }
#endif /* Nothing to do on Windows */
}

void finalize_terminal() {
#ifdef __linux__
    tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
#endif /* Nothing to do on Windows */
}

void show_grid(grid_t ** grid, grid_size_t size) {
#ifndef __m68k__
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
#else
    // Draw a new, empty grid
    prepare_terminal();
    for (grid_size_t i = 0; i < size; ++i){
        for (grid_size_t j = 0; j < size; ++j){
            grid_t x = grid[i][j];
            if (x){
                if (x/10){
                    DrawChar(grid_x_start + j * grid_x_delta + 2, grid_y_start + i * grid_y_delta + 2, x/10 + '0', A_NORMAL);
                }
                DrawChar(grid_x_start + j * grid_x_delta + 9, grid_y_start + i * grid_y_delta + 2, x%10 + '0', A_NORMAL);
            }
        }
    }
#endif
}

user_action get_user_action() {
    for(;;) {
#ifndef __m68k__
        printf("Input ('h' for help): ");
#endif
#ifdef __linux__
        int inp = getchar();
#elif defined(_WIN32)
        int inp = getch();
#elif defined(__m68k__)
        short inp = ngetchx();
#endif
        user_action res;
        switch (inp) {
            case 'h':
            case 'H':
                res = HELP; break;
            case 'i':
            case 'I':
                res = INFO;  break;
#ifdef __m68k__
            case 337:
#else
            case 'w':
            case 'W':
#endif
                res = MOVE_UP; break;
#ifdef __m68k__
            case 340:
#else
            case 's':
            case 'S':
#endif
                res = MOVE_DOWN; break;
#ifdef __m68k__
            case 338:
#else
            case 'a':
            case 'A':
#endif
                res = MOVE_LEFT; break;
#ifdef __m68k__
            case 344:
#else
            case 'd':
            case 'D':
#endif
                res = MOVE_RIGHT; break;
#ifdef __m68k__
            case 264:
#else
            case 'q':
            case 'Q':
#endif
                res = QUIT; break;
            default: res = INVALID;
        }
#ifdef __m68k__
        if (res != INVALID) {
#else
        printf ("\n");
        if (res == INVALID) {
            printf ("Invalid input, try again\n");
        }
        else {
#endif
            return res;
        }
    }
}

void show_help() {
#ifndef __m68k__
    printf("h: Show help\n"
           "i: Show info\n"
           "q: Quit\n"
           "w: Move grid up\n"
           "s: Move grid down\n"
           "a: Move grid left\n"
           "d: Move grid right\n");
#endif
}

void show_info() {
#ifndef __m68k__
    printf("C implementation of 2048\n"
           "Inspired by: https://github.com/gabrielecirulli/2048\n"
           "Website: https://github.com/schaerfo/2048\n"
           "Contributors (in alphabetical order):\n"
           " * Christian Schärf <c.schaerf@t-online.de>\n");
#endif
}
