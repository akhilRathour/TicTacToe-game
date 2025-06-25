#include "computerMove.h"
#include <algorithm> // For std::max, std::min

// External board defined in main or elsewhere
extern char board[3][3];
extern bool isMove;
//extern const int SIZE;

// Evaluate the board for a win/loss
int evaluate(char b[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == 'x') return +10;
            if (b[row][0] == 'o') return -10;
        }
    }
    for (int col = 0; col < SIZE; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == 'x') return +10;
            if (b[0][col] == 'o') return -10;
        }
    }
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == 'x') return +10;
        if (b[0][0] == 'o') return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == 'x') return +10;
        if (b[0][2] == 'o') return -10;
    }

    return 0;
}

// Check if any moves are left
bool isMovesLeft(char b[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (b[i][j] == ' ') return true;
    return false;
}

// Minimax implementation
int minimax(char b[SIZE][SIZE], int depth, bool isMax) {
    int score = evaluate(b);

    if (score == 10 || score == -10)
        return score;

    if (!isMovesLeft(b))
        return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (b[i][j] == ' ') {
                    b[i][j] = 'x';
                    best = std::max(best, minimax(b, depth + 1, false));
                    b[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (b[i][j] == ' ') {
                    b[i][j] = 'o';
                    best = std::min(best, minimax(b, depth + 1, true));
                    b[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Find the best move and make it
void computerMove(bool& isMove) {
    int bestVal = -1000;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'x';
                int moveVal = minimax(board, 0, false);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    if (bestRow != -1 && bestCol != -1) {
        board[bestRow][bestCol] = 'x';
        isMove = true;
    }
}
