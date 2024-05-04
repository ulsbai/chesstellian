# chesstellian
Chesstellian is a chess engine that I am working on making. It should eventually be able to play and analyze chess games at a reasonable strength. Now it is programmed to print all the possible sequences of moves following the start position, looking 2 moves ahead.

## Issues
I am testing the program it on my Raspberry Pi 4, 32-bit Raspberry Pi OS.
It should produce a list of all the moves from the starting position, looking 3 moves ahead.
It is only looking 2 moves ahead.
If anyone can solve this do a pull request.

## Usage
To test out this program, install it with a sequence of commands such as the following:\
`git clone https://github.com/ulsbai/chesstellian`\
`cd chesstellian/chesstellian`\
`make`

Now you can run it:\
`./chesstellian`

## Debugging
Currently the Makefile is configured to use debugging mode, so you can run the program in the debugger by:\
`gdb chesstellian`

In the debugger, type `run` to run the program.
