#include <stdio.h>
#include <stdbool.h>

#define PLAYER 'X'   // Symbol for the player
#define AI 'O'       // Symbol for the AI

char board[3][3];    // 3x3 board for the game

// Function prototypes
void initializeBoard();          // Initialize the game board with numbers 1-9
void printBoard();               // Display the current state of the board
bool isMovesLeft();              // Check if there are any moves left
int evaluate();                  // Evaluate the board for win/draw conditions
int minimax(bool isAI);          // AI's decision-making using the Minimax algorithm
void playerMove();               // Handle the player's move
void aiMove();                   // Handle the AI's move
bool checkWin(char player);      // Check if the given player has won
void playGame(int mode);         // Main game loop

int main() {
    int mode;
    printf("Tic-Tac-Toe Game\n");
    printf("Select Mode:\n1. Two-Player Mode\n2. Single-Player Mode\n");
    printf("Enter your choice: ");
    scanf("%d", &mode);

    if (mode == 1 || mode == 2) {
        playGame(mode); // Start the game based on the chosen mode
    } else {
        printf("Invalid mode selected. Exiting...\n");
    }

    return 0;
}

// Initialize the game board with numbers 1-9
void initializeBoard() {
    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '0' + count++;
        }
    }
}

// Display the current state of the board
void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|"); // Print vertical separators
        }
        if (i < 2) printf("\n-----------\n"); // Print horizontal separators
    }
    printf("\n");
}

// Check if there are any moves left on the board
bool isMovesLeft() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != PLAYER && board[i][j] != AI) {
                return true; // Return true if an empty cell is found
            }
        }
    }
    return false; // No moves left
}

// Evaluate the board and return the score based on the game state
int evaluate() {
    // Check rows and columns for win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == AI) return +10;   // AI wins
            if (board[i][0] == PLAYER) return -10; // Player wins
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == AI) return +10;   // AI wins
            if (board[0][i] == PLAYER) return -10; // Player wins
        }
    }

    // Check diagonals for win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        if (board[0][0] == PLAYER) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        if (board[0][2] == PLAYER) return -10;
    }

    return 0; // Return 0 for a draw
}

// Minimax algorithm to calculate the best move for AI or Player
int minimax(bool isAI) {
    int score = evaluate();

    // If AI wins or Player wins, return the score
    if (score == 10) return score;
    if (score == -10) return score;
    if (!isMovesLeft()) return 0; // Return 0 for a draw

    if (isAI) {
        int best = -1000;

        // Loop through all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != PLAYER && board[i][j] != AI) {
                    char temp = board[i][j]; // Save the current cell
                    board[i][j] = AI;       // Make the AI move
                    best = (best > minimax(false)) ? best : minimax(false); // Maximize score
                    board[i][j] = temp;     // Undo the move
                }
            }
        }
        return best;
    } else {
        int best = 1000;

        // Loop through all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != PLAYER && board[i][j] != AI) {
                    char temp = board[i][j]; // Save the current cell
                    board[i][j] = PLAYER;   // Make the player's move
                    best = (best < minimax(true)) ? best : minimax(true); // Minimize score
                    board[i][j] = temp;     // Undo the move
                }
            }
        }
        return best;
    }
}

// Handle the player's move
void playerMove() {
    int choice;
    printf("Enter your move (1-9): ");
    scanf("%d", &choice);

    int row = (choice - 1) / 3; // Calculate row from the choice
    int col = (choice - 1) % 3; // Calculate column from the choice

    if (board[row][col] != PLAYER && board[row][col] != AI) {
        board[row][col] = PLAYER; // Place the player's symbol
    } else {
        printf("Invalid move! Try again.\n");
        playerMove(); // Retry the move
    }
}

// Handle the AI's move
void aiMove() {
    int bestVal = -1000;
    int bestRow = -1, bestCol = -1;

    // Evaluate all possible moves
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != PLAYER && board[i][j] != AI) {
                char temp = board[i][j];
                board[i][j] = AI;           // AI makes a move
                int moveVal = minimax(false); // Evaluate move
                board[i][j] = temp;         // Undo move

                if (moveVal > bestVal) {    // Update best move
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[bestRow][bestCol] = AI; // Make the best move
}

// Check if the given player has won
bool checkWin(char player) {
    return evaluate() == (player == AI ? 10 : -10);
}

// Main game loop
void playGame(int mode) {
    initializeBoard();
    printBoard();

    while (true) {
        playerMove();
        printBoard();

        if (checkWin(PLAYER)) {
            printf("Player Wins!\n");
            break;
        }

        if (!isMovesLeft()) {
            printf("It's a Draw!\n");
            break;
        }

        if (mode == 2) {
            printf("AI's turn...\n");
            aiMove();
        } else {
            printf("Player 2's turn...\n");
            playerMove();
        }
        printBoard();

        if (checkWin(AI)) {
            printf("AI Wins!\n");
            break;
        }

        if (!isMovesLeft()) {
            printf("It's a Draw!\n");
            break;
        }
    }
}
