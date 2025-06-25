#ifndef COMPUTER_MOVE_H
#define COMPUTER_MOVE_H


constexpr int SIZE = 3;  // Make SIZE a compile-time constant
extern char board[3][3];
extern bool isMove;

void computerMove(bool& isMove);
int evaluate(char b[3][3]);
bool isMovesLeft(char b[3][3]);
int minimax(char b[3][3], int depth, bool isMax);

#endif // COMPUTER_MOVE_H
