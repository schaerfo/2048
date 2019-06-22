#ifdef __m68k__

#define SAVE_SCREEN
#define USE_TI89

// Must be included so TIGCC knows for which calculators to build
#include <default.h>

#include "main.h"

void _main() {
  run_game();
}

#endif
