# Chessparnado 

[![No Maintenance Intended](http://unmaintained.tech/badge.svg)](http://unmaintained.tech/)

**Chesspernado** is an original game made by Danilo Novakovic inspired by Chess, Tetris and Plants vs Zombies.
The game is Player vs AI, played on a 12x8 board. Players goal is to protect the first row as long as possible
from the attacking enemy pieces. Player starts with 3 knights and 2 bishops, and is able to upgrade and buy
more from the shop as the game progresses.

> More on rules of the chessperando, figure movement, and notation in the program can be found in Documentation.pdf
aswell as, in any time, inside of programm by typing command `/help` or by selection option 2. from the main menu.

## Requirements

This game uses C programming language standard libraries (ANSII C Standard)
(No additional library is needed, you only need terminal and some kind of compiler like GCC)

## Compiling

Linux: Open terminal, navigate to directory containing the source files and execute the following command:
`make`.

After you compile it you can run it by typing `./chesspernado`

> For more detailed information, see documentation file.

## Update 9/May/2019 (Personal log):

This project is an example of how NOT to write code. It is full of code smells and poorly named variables, with methods that do too many things.

Additionally it is not covered by tests making even refactoring pretty hard.

However, it holds significant historical value to myself since it taught me alot.

At the time of writing this project i was just starting out and this was biggest challange i posed to myself at that time. A new challange today would be to refactor this into more readable code without breaking its functionality.
