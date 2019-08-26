# Chessparnado

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![No Maintenance Intended](http://unmaintained.tech/badge.svg)](http://unmaintained.tech/)

**Chesspernado** is an original game made by Danilo Novakovic inspired by Chess, Tetris, and Plants vs Zombies.
The game is Player vs AI, played on a 12x8 board. The player's goal is to protect the first row as long as possible
from the attacking enemy pieces. A player starts with 3 knights and 2 bishops and can upgrade and buy
more from the shop as the game progresses.

> More on rules of the Chessperando, figure movement, and notation in the program can be found in Documentation.pdf
as well as, at any time, inside of the program by typing command `/help` or by selection option 2. from the main menu.

---

## Table of Contents

- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Setup](#setup)
- [Game rules](#game-rules)
  - [Goal of the game](#goal-of-the-game)
  - [Phases](#phases)
  - [Turns](#turns)
  - [Supported Commands](#supported-commands)
  - [Pieces and movement](#pieces-and-movement)
- [Personal Logs](#personal-logs)
- [Support](#support)
- [License](#license)

---

## Getting started

### Prerequisites

This game uses **C** programming language standard libraries (*ANSII C Standard*)
(No external library is needed, you only need `GCC` compiler and UNIX Terminal (*ex. Linux or WSL for Windows*))

### Setup

Use these steps to compile and start the console application.

#### Linux

- Open terminal
- Navigate to the project repository
- Enter `make`.
- After you compile it you can run it by typing `./chesspernado`

#### Windows

- Install [WSL (Windows Subsystem for Linux)](https://docs.microsoft.com/en-us/windows/wsl/install-win10)
- Navigate to the project repository in WSL terminal
- Enter `make` (*Compiles the program*)
- Start the program by running `./chesspernado`

> In case you run into problems related to missing packages try using `sudo apt-get install build-essential` command (it should install `GCC` and `make` alongside [other useful tools](https://packages.ubuntu.com/xenial/build-essential))

---

## Game rules

### Goal of the game

The goal of the game is to stop enemy pawns & bishops from reaching to 1st row of the board.

- If the board is *FULL* on AI's turn, then the game will end.
- If the player lost *ALL OF HIS PIECES* then the game will end.

At the end of the game player will be prompted to enter the name, after which the result will be printed out in the *scoreboard.txt*

> Score won't be recorded if the program has been closed with /exit command

### Phases

#### Initial setup

At the beginning of the game, the player decides initial locations for 3 knights and 2 bishops. He can place them on any column from 1st to 5th row of the board. During this phase player can use :

- `/end, /exit` - exit the game
- `/re` - resets the initialization setup
- `/random` - generates bishops and knights on random positions.

Upon completion, the player will be prompted to confirm the setup.

![Random Demo](docs/random.gif)

#### Waves

After [initial setup](#initial-setup), the game begins, and the first randomly generated wave starts. Each wave gets harder and harder as the game goes on.

### Turns

`PLAYER` - can move 1 piece during his turn (with exception of the shop).

`ENEMY_AI` - during 1 turn **every** piece with legal moves will be moved. If **no piece has any legal move** then *N* new pawns will be randomly generated anywhere from 7 to 12th row.

### Supported commands

`/back` - goes back to the main menu.

![Back Demo](docs/back.gif)

`/hint` - shows either available places where a certain piece can move or additional information depending on what has been selected.

![Hint Demo](docs/hint.gif)

`/exit`, `/end` - exits the program.

`/undo` - undo the previous move. 

> It can be used from start to finish of the **CURRENT** wave. **Once the wave completes "undo history" is deleted!**

`/help` - prints Chesspernado manual whenever you want during the game.

![Help Demo](docs/help.gif)

`/skip` - skips 1 move during the wave.

`/revive` - you can sacrifice *60* points to revive dead piece (you can set him anywhere from 1st to 5th row)

![Revive Demo](docs/revive.gif)

`/buy` - summons *STORE* window, from which you can buy certain pieces and features for *X* points.

![Shop](docs/store.PNG)

### Pieces and Movement

Notation of the moves is as follows:
**Piece**/*column*/*row*/column/row
(**what piece do you want to move**, *from where*, to where)

Examples: **B***f4*d6, **N***b8*c6

#### SUICIDE ROOK (R)

It is a special piece that lasts for **ONE MOVE ONLY**. He first waits for player /other pieces to make a move, and
then sprints forward [i+k][j] until he hits ANYTHING (either end of the board, enemy or the player). Once he collides with an object he will then explode, killing both himself and that object (either player or enemy). A user can buy this piece in the shop as many times as he likes as long as he has points for it, and he can place as many as the suicide rooks he likes. If there are multiple suicide rooks on the board the priority will have those in front.

![Suicide Rook Demo](docs/suicide-rook.gif)

#### HAPPY KING (K)

It is a special piece that lasts until destroyed. Happy King is so happy that he won't hurt a fly, meaning that **he cannot kill other enemy pieces**. He shares his love of life with the player, and **generates 1 point each turn**.
Happy king can't be moved. A User can buy this piece from the shop, and it is generated on random positions anywhere from 1st row to 5th, on any column.

#### BISHOP (B)

Can move any number of squares diagonally, but cannot leap over other pieces.

![Bishop](docs/tutorial-bishop.PNG)

#### AI_BISHOP (b)

He has rules of regular bishop but will only move in
the following manner. BISHOP AI always "wakes up on the left foot"
meaning that he will prioritize moving as far to the bottom-left as he
can above all. Only if he is unable to move to the left anymore
will he swap directions meaning he will move as far to the bottom right
as he can. AI_BISHOP will only eat an enemy piece if it is caught
in this LEFT-RIGHT pattern.

![AI Bishop Demo](docs/ai-bishop.gif)

> AI_BISHOP is worth 12 points

#### KNIGHT (N)

The knight moves to any of the closest squares that are not on the same rank, file, or diagonal, thus the move forms an "L"-shape: two squares vertically and one square horizontally, or two squares horizontally and one square vertically.
The knight is the only piece that can leap over other pieces.

![Knight](docs/tutorial-knight.PNG)

#### AI_PAWN (p)

The pawn can move forward to the unoccupied square immediately in front of it on the same file, or on its first move it can advance two squares along the same file, provided both squares are unoccupied; or the pawn can capture an opponent's piece on a square diagonally in front of it on an adjacent file, by moving to that square. The *AI_PAWN* will prioritize eating enemy pieces over going forward.

![AI Pawn Demo](docs/ai-pawn.gif)

> AI_PAWN is worth 6 points

---

## Personal logs

### 9/May/2019

This project is an example of how NOT to write code. It is full of code smells and poorly named variables, with methods that do too many things.

Additionally, it is not covered by tests making even refactoring pretty hard.

However, it holds significant historical value to me since it taught me a lot.

At the time of writing this project, I was just starting and this was the biggest challenge I posed to myself at that time. A new challenge today would be to refactor this into a more readable code without breaking its functionality.

---

## Support

Reach out to me at one of the following places!

- Website at <a href="https://danilonovakovic.github.io/index.html" target="_blank">`danilonovakovic.github.io`</a>
- Linkedin at <a href="https://www.linkedin.com/in/danilo-novakovi%C4%87-821934167/" target="_blank">`DaniloNovakovic`</a>

> Special thanks to alpha-testers: [Vladimir Ivkovic](https://github.com/vladimirivkovic), Vladimir Virijevic, [Vuk Isic](https://github.com/vukisic), Slavko Lukic and Aleksandar Ristic

---

## License

- **[GPLv3 License](https://www.gnu.org/licenses/gpl-3.0)**
- Copyright 2017 © [DaniloNovakovic](https://github.com/DaniloNovakovic)
