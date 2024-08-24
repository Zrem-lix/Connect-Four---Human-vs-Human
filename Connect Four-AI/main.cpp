#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Enumeration for players and AI
enum Player { NONE, RED, YELLOW, AI };
const int ROWS = 6;  // Number of rows in the board
const int COLS = 7;  // Number of columns in the board

class ConnectFour {
private:
    vector<vector<Player> > board;  // 2D vector representing the game board
    Player currentPlayer;          // Tracks the current player (RED, YELLOW, or AI)
    int redWins;                   // Counter for red player's wins
    int yellowWins;                // Counter for yellow player's wins
    int aiWins;                    // Counter for AI wins

public:
    // Constructor initializes the board and sets the first player to RED
    ConnectFour() : board(ROWS, vector<Player>(COLS, NONE)), currentPlayer(RED), redWins(0), yellowWins(0), aiWins(0) {
        srand(time(0));  // Seed random number generator
    }

    // Resets the board to its initial state
    void resetBoard() {
        board = vector<vector<Player> >(ROWS, vector<Player>(COLS, NONE));
        currentPlayer = RED;
    }

    // Resets the win counters for all players
    void resetScores() {
        redWins = 0;
        yellowWins = 0;
        aiWins = 0;
    }

    // Checks if the board is completely full
    bool isBoardFull() {
        for (int col = 0; col < COLS; ++col) {
            if (board[0][col] == NONE) {
                return false;  // There is at least one empty space
            }
        }
        return true;  // No empty spaces found, board is full
    }

    // Places a piece in the specified column and checks for win or draw
    bool dropPiece(int col) {
        if (col < 0 || col >= COLS) {
            cout << "Invalid column. Choose between 0 and " << COLS - 1 << ".\n";
            return false;
        }

        // Drop piece into the lowest available row in the column
        for (int row = ROWS - 1; row >= 0; --row) {
            if (board[row][col] == NONE) {
                board[row][col] = currentPlayer;
                if (checkWin(row, col)) {
                    // Update win counters and announce winner
                    if (currentPlayer == RED) {
                        redWins++;
                        cout << "Red wins!\n";
                    } else if (currentPlayer == YELLOW) {
                        yellowWins++;
                        cout << "Yellow wins!\n";
                    } else if (currentPlayer == AI) {
                        aiWins++;
                        cout << "AI wins!\n";
                    }
                    resetBoard();  // Reset board for a new game
                } else if (isBoardFull()) {
                    cout << "It's a draw!\n";
                    resetBoard();  // Reset board for a new game
                } else {
                    // Switch players
                    currentPlayer = (currentPlayer == RED) ? YELLOW : RED;
                }
                return true;
            }
        }

        cout << "Column is full. Choose another column.\n";
        return false;
    }

    // Checks if there is a win condition in any direction
    bool checkWin(int row, int col) {
        return checkDirection(row, col, 1, 0) ||   // Check horizontal
               checkDirection(row, col, 0, 1) ||   // Check vertical
               checkDirection(row, col, 1, 1) ||   // Check diagonal 
               checkDirection(row, col, 1, -1);    // Check diagonal 
    }

    // Checks for a win condition in a specific direction
    bool checkDirection(int row, int col, int dRow, int dCol) {
        Player player = board[row][col];  // Player whose piece is placed
        int count = 1;  // Initial count for the current piece

        // Check in the positive direction
        for (int i = 1; i < 4; ++i) {
            int r = row + i * dRow;
            int c = col + i * dCol;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
                count++;
            } else {
                break;
            }
        }

        // Check in the negative direction
        for (int i = 1; i < 4; ++i) {
            int r = row - i * dRow;
            int c = col - i * dCol;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
                count++;
            } else {
                break;
            }
        }

        return count >= 4;  // Return true if four or more pieces are connected
    }

    // Prints the current state of the board
    void printBoard() {
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                char piece = '.';
                if (board[row][col] == RED) {
                    piece = 'R';
                } else if (board[row][col] == YELLOW) {
                    piece = 'Y';
                } else if (board[row][col] == AI) {
                    piece = 'A';
                }
                cout << piece << " ";
            }
            cout << "\n";
        }
    }

    // Prints the current scores
    void printScores() {
        cout << "Red Wins: " << redWins << " | Yellow Wins: " << yellowWins << " | AI Wins: " << aiWins << "\n";
    }

    // Gets the current player
    Player getCurrentPlayer() {
        return currentPlayer;
    }

    // Sets the current player
    void setCurrentPlayer(Player player) {
        currentPlayer = player;
    }

    // Generates a valid column for the AI's move
    int getAiMove() {
        int col;
        do {
            col = rand() % COLS;  // Random column selection
        } while (!isValidMove(col));  // Ensure the column is not full
        return col;
    }

    // Checks if a move is valid (i.e., the column is not full)
    bool isValidMove(int col) {
        return board[0][col] == NONE;
    }
};

int main() {
    ConnectFour game;  // Create a new game instance
    int col;           // Column where the player will drop their piece
    bool playAgainstAI = true;  // Flag to indicate if the player is playing against the AI

    while (true) {
        game.printBoard();    // Print the current board state
        game.printScores();   // Print the current scores

        if (game.getCurrentPlayer() == AI) {
            col = game.getAiMove();  // AI chooses a column
            cout << "AI chooses column: " << col << "\n";
        } else {
            cout << "Player " << (game.getCurrentPlayer() == RED ? "Red" : "Yellow") << ", choose a column (0-6): ";
            cin >> col;  // Player chooses a column
        }

        game.dropPiece(col);  // Drop the piece and update the game state

        // Switch players if playing against AI
        if (playAgainstAI && game.getCurrentPlayer() == YELLOW) {
            game.setCurrentPlayer(AI);
        } else if (playAgainstAI && game.getCurrentPlayer() == AI) {
            game.setCurrentPlayer(RED);
        }
    }

    return 0;  // Exit the program
}
