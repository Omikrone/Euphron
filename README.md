# Euphron - A Chess Engine


## Introduction

Euphron is a chess engine developed in C++ that aims to provide a strong and efficient playing experience. It is designed to be compatible with my [Chessgame](https://github.com/Omikrone/Chessgame) project, allowing users to play against the engine or use it for analysis. It uses the [Chessboard](https://github.com/Omikrone/Chessboard) library for handling the chessboard and game logic.

- Current version : 0.0.0

## Features

- Implements the UCI (Universal Chess Interface) protocol for easy integration with chess GUIs.
- Implements an API Wrapper for communication with the Chessgame project.
- Generation of random legal moves.

## Installation

### Docker

To install Euphron and integrate it with the Chessgame project, please refer to the [Chessgame README](https://github.com/Omikrone/Chessgame).

### Manual Installation

If you prefer to install Euphron separately, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/Omikrone/Euphron.git
    cd Euphron
    ```

2. Build the project using CMake:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Run the engine:
    ```bash
    ./Euphron
    ```