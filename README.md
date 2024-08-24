# Connect Four-AI

Connect Four is a straightforward implementation of the classic board game where a human player competes against an artificial intelligence (AI). The goal is to connect four of your pieces in a row—either horizontally, vertically, or diagonally—on a 6-row by 7-column board.

## Features

- **Play Against AI**: Engage in a game against a AI that makes random moves.
- **Score Tracking**: Keeps track of wins for both the player and the AI.
- **Console Interface**: The game board and scores are displayed in the console, updating in real-time.
- **Move Validation**: Ensures that moves are made in valid columns and handles invalid or full columns appropriately.

## Game Rules

1. **Objective**: Connect four of your colored pieces in a line (horizontally, vertically, or diagonally) to win the game.
2. **Game Flow**:
   - **Player vs. AI**: The player (Red) and the AI (Yellow) take turns to drop their pieces into columns.
   - **AI Moves**: The AI selects a column at random from the available options.
   - **Win Check**: After each move, the game checks if there is a winner or if the board is full (resulting in a draw).
   - **Reset**: The board resets after a win or draw, and the game continues.

## How to Play

1. **Start the Game**:
   - Compile and run the program. The game board and current scores will be displayed in the console.
   
2. **Making a Move**:
   - When it's your turn, enter the column number (0-6) where you want to drop your piece.
   - The AI will automatically choose a column during its turn.

3. **Turn Management**:
   - The player (Red) and AI (Yellow) alternate turns. The game will automatically switch turns after each move.

4. **Winning and Drawing**:
   - The game will announce when a player or AI wins, or if the game ends in a draw (when the board is full).
   - After a win or draw, the board is reset for a new game, and the scores are updated.

## Running Instructions

1. **Compile**: Use a C++ compiler to compile the source code. For example, with `g++`:
   ```bash
   g++ -o connect_four connect_four.cpp
