# 2048
This project is aimed at crating a lightweight command-line implementation of the 2048 game (play2048.co) in the C language.
The ultimate goal is to run the program on the TI-89 graphical calculator using TIGCC (tigcc.ticalc.org).

## Building
### For the TI-89
You can download the required tools from https://tigcc.ticalc.org. Under linux, the binaries of the latest beta (http://tigcc.ticalc.org/linux/tigcc_bin.tar.bz2) are used. The setup is as follows:
```
wget http://tigcc.ticalc.org/linux/tigcc_bin.tar.bz2 # Download the archive
mkdir tigcc; cd tigcc  # Create a director to unpack the archive and change to it
tar -xjf ../tigcc_bin.tar.gz  # You guess it
export TIGCC=$PWD # Set the TIGCC environment variable. This is required by the tigcc executable to locate other tools
cd /path/to/2048  # Change to the 2048 source directory
```
Then, in the source directory, the compiler can be invoked as:
```
$TIGCC/bin/tigcc -std=c99 -O2 run2048.c game.c main.c mem.c ui.c
```
Note that the output file will be named after the first source file on the command line. Thus, if the compiler is invoked as shown, the resulting TI-89 executable will be `run2048.89z`. This file can then be deployed to the calculator (or an emulator).

TIGCC also supports other calculators via the `USE_V200` and `USE_TI92PLUS` preprocessor macros. Thus, if you would like to compile for these, simply invoke the compiler with the appropriate `-D` flag. Notice, however, that they are not officially supported and the experience may be degraded, for example, due to the different screen resolution.

### Other platforms
Building 2048 is pretty straightforward, only CMake, make and a compiler toolchain are required.
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
 * A value of 0 corresponds to an empty tile.
 
