# ChessAI

## Project Overview

This project is a Chess AI simulation developed in C++. The simulation supports standard chess rules, including advanced moves like castling and en passant. The AI uses a minimax algorithm with alpha-beta pruning to evaluate and decide on the best move. The project is structured to allow for easy expansion, enabling you to improve the AI, add more game rules, or enhance the user interface.

## Features

- **Full Chess Rules**: Supports all standard chess rules, including castling, en passant, and pawn promotion.
- **AI Opponent**: Implements a basic AI that uses the minimax algorithm with alpha-beta pruning to determine the best moves.

- **Move Validation**: Ensures that all moves made by players and the AI are legal.

- **Board Evaluation**: Provides a simple evaluation function to assess board positions, aiding the AI in decision-making.

- **Extendable Codebase**: The project is organized to allow easy extensions and improvements, such as implementing more sophisticated AI or enhancing the user interface.

## Key Components

- **`include/`**: Contains all header files defining classes, methods, and data structures used across the project.
- **`src/`**: Contains all implementation files for the classes and methods defined in the header files.

- **`Makefile`**: Automates the compilation process, ensuring all dependencies are handled correctly.

## Getting Started

### Prerequisites

- **C++ Compiler**: Ensure you have a C++ compiler installed. GCC or Clang is recommended.
- **Make**: The Make utility is required to build the project using the provided Makefile.

### Building the Project

To build the project, navigate to the project directory in your terminal and run:

```bash
make
```

This will compile all the source files and generate an executable named `chess`.

### Running the Game

Once built, you can start the game by running the following command:

```bash
./chess
```

You can then play against the AI by entering your moves in standard algebraic notation (e.g., `e2e4`).

### Example Game

```bash
White's turn. Enter move (e.g., e2e4): e2e4
...
```

The game will continue until checkmate or stalemate.
