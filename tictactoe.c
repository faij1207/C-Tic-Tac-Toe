#include <stdio.h>
#include <stdbool.h>

#define PLAYER 'X'
#define AI 'O'

char board[3][3];

// Function prototypes
void initializeBoard();
void printBoard();
bool isMovesLeft();
int evaluate();
int minimax(bool isAI);
void playerMove();
void aiMove();
bool checkWin(char player);
void playGame(int mode);

int main() {
    int mode;
    printf("Tic-Tac-Toe Game\n");
    printf("Select Mode:\n1. Two-Player Mode\n2. Single-Player Mode\n");
    printf("Enter your choice: ");
    scanf("%d", &mode);

    if (mode == 1 || mode == 2) {
        playGame(mode);
    } else {
        printf("Invalid mode selected. Exiting...\n");
    }

    return 0;
}

void initializeBoard() {
    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '0' + count++;
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n-----------\n");
    }
    printf("\n");
}

bool isMovesLeft() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != PLAYER && board[i][j] != AI)
                return true;
        }
    }
    return false;
}

int evaluate() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == AI) return +10;
            if (board[i][0] == PLAYER) return -10;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == AI) return +10;
            if (board[0][i] == PLAYER) return -10;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        if (board[0][0] == PLAYER) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        if (board[0][2] == PLAYER) return -10;
    }

    return 0;
}

int minimax(bool isAI) {
    int score = evaluate();

    if (score == 10) return score;
    if (score == -10) return score;
    if (!isMovesLeft()) return 0;

    if (isAI) {
        int best = -1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != PLAYER && board[i][j] != AI) {
                    char temp = board[i][j];
                    board[i][j] = AI;
                    best = (best > minimax(false)) ? best : minimax(false);
                    board[i][j] = temp;
                }
            }
        }
        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != PLAYER && board[i][j] != AI) {
                    char temp = board[i][j];
                    board[i][j] = PLAYER;
                    best = (best < minimax(true)) ? best : minimax(true);
                    board[i][j] = temp;
                }
            }
        }
        return best;
    }
}

void playerMove() {
    int choice;
    printf("Enter your move (1-9): ");
    scanf("%d", &choice);

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] != PLAYER && board[row][col] != AI) {
        board[row][col] = PLAYER;
    } else {
        printf("Invalid move! Try again.\n");
        playerMove();
    }
}

void aiMove() {
    int bestVal = -1000;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != PLAYER && board[i][j] != AI) {
                char temp = board[i][j];
                board[i][j] = AI;
                int moveVal = minimax(false);
                board[i][j] = temp;

                if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[bestRow][bestCol] = AI;
}

bool checkWin(char player) {
    return evaluate() == (player == AI ? 10 : -10);
}

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
