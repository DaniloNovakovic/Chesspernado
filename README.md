# Chessparnado

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![No Maintenance Intended](http://unmaintained.tech/badge.svg)](http://unmaintained.tech/)

**Chesspernado** is an original game made by Danilo Novakovic inspired by Chess, Tetris and Plants vs Zombies.
The game is Player vs AI, played on a 12x8 board. Players goal is to protect the first row as long as possible
from the attacking enemy pieces. Player starts with 3 knights and 2 bishops, and is able to upgrade and buy
more from the shop as the game progresses.

> More on rules of the chessperando, figure movement, and notation in the program can be found in Documentation.pdf
aswell as, in any time, inside of programm by typing command `/help` or by selection option 2. from the main menu.

## Table of Contents

- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Setup](#setup)
- [Personal Logs](#personal-logs)
- [Support](#support)
- [License](#license)

## Getting started

### Prerequisites

This game uses **C** programming language standard libraries (*ANSII C Standard*)
(No external library is needed, you only need `gcc` compiler and UNIX Terminal (*ex. Linux or WSL for Windows*))

### Setup

Use these steps to compile and start console application.

#### Linux

- Open terminal
- Navigate to the project repository
- Enter `make`.
- After you compile it you can run it by typing `./chesspernado`

#### Windows

- Install [WSL (Windows Subsystem for Linux)](https://docs.microsoft.com/en-us/windows/wsl/install-win10)
- Navigate to the project repository in WSL terminal
- Enter `make` (*Compiles the program*)
- Start program by running `./chesspernado`

> In case you run into problems related to missing packages try using `sudo apt-get install build-essential` command (it should install `gcc` and `make` alongside [other usefull tools](https://packages.ubuntu.com/xenial/build-essential))

## Personal logs

### 9/May/2019

This project is an example of how NOT to write code. It is full of code smells and poorly named variables, with methods that do too many things.

Additionally it is not covered by tests making even refactoring pretty hard.

However, it holds significant historical value to myself since it taught me alot.

At the time of writing this project i was just starting out and this was biggest challange i posed to myself at that time. A new challange today would be to refactor this into more readable code without breaking its functionality.

---

## Support

Reach out to me at one of the following places!

- Website at <a href="https://danilonovakovic.github.io/index.html" target="_blank">`danilonovakovic.github.io`</a>
- Linkedin at <a href="https://www.linkedin.com/in/danilo-novakovi%C4%87-821934167/" target="_blank">`DaniloNovakovic`</a>

---

## License

- **[GPLv3 License](https://www.gnu.org/licenses/gpl-3.0)**
- Copyright 2017 © [DaniloNovakovic](https://github.com/DaniloNovakovic)
