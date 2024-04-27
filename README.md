# chesstellian
Chesstellian is a chess engine that I am working on making. It should eventually be able to play and analyze chess games at a reasonable strength. Now it is programmed to print all the possible sequences of moves following the start position, looking 2 moves ahead. For some reason when I test it on my Raspberry Pi it is segment faulting. I think this is because the program is running out of memory.

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
