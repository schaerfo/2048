# 2048
This project is aimed at crating a lightweight command-line implementation of the 2048 game (play2048.co) in the C language.
The ultimate goal is to run the program on the TI-89 graphical calculator using TIGCC (tigcc.ticalc.org).

## Building
Building 2048 is pretty straightforward, only CMake, make and a compiler toolchain are required
```
cmake
make
```
This should produce the `2048` executable.

## Internal representation of the grid
The data type used to represent the grid is essentially a `unsigned int **`.
For a n×n grid, we have a n*n-sized array of `unsigned int`s with pointers to the first elements of each row.
To give an example, for a 3×3 grid, this boils down to the following:
 ```
       grid
        ↓
       ┌──┬──┬──┐
       │  │  │  │
       └──┴──┴──┘
        ╷  ╷  ╷   
  ┌─────┘  │  └─────┐
  ↓        ↓        ↓
 ┌──┬──┬──┬──┬──┬──┬──┬──┬──┐
 │  │  │  │  │  │  │  │  │  │
 └──┴──┴──┴──┴──┴──┴──┴──┴──┘
 ```

## Binary logarithms as values
Note that, in contrast to most other implementations, here the binary logarithms of the values are used. That means:
 * The lowest value is 1.
 * When merging 2 tiles with equal values, the value of the resulting is the value of the previous tiles incremented instead of the added values.
 * A value of 0 means empty tile.
 
