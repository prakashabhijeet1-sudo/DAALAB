#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};

void printBoard() {
    printf("\n");
    printf(" %c | %c | %c\n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n\n", board[6], board[7], board[8]);
}

char checkWinner() {
    int win[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

    for(int i = 0; i < 8; i++) {
        int a = win[i][0];
        int b = win[i][1];
        int c = win[i][2];

        if(board[a] != ' ' &&
           board[a] == board[b] &&
           board[b] == board[c])
            return board[a];
    }

    return ' ';
}

int boardFull() {
    for(int i = 0; i < 9; i++) {
        if(board[i] == ' ')
            return 0;
    }
    return 1;
}

void computerMove() {
    int pos;

    do {
        pos = rand() % 9;
    } while(board[pos] != ' ');

    board[pos] = 'O';

    printf("Computer chooses cell %d\n", pos + 1);
}

int main() {

    srand(time(NULL));

    int mode;

    printf("===== TIC TAC TOE =====\n");
    printf("1. Human vs Computer\n");
    printf("2. Human vs Human\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    char currentPlayer = 'X';

    while(1) {

        printBoard();

        if(mode == 1 && currentPlayer == 'O') {

            computerMove();

        } else {

            int move;

            printf("Player %c, enter cell (1-9): ", currentPlayer);
            scanf("%d", &move);

            move--;

            if(move < 0 || move > 8 || board[move] != ' ') {
                printf("Invalid move! Try again.\n");
                continue;
            }

            board[move] = currentPlayer;
        }

        char winner = checkWinner();

        if(winner != ' ') {
            printBoard();

            if(mode == 1 && winner == 'O')
                printf("Computer Wins!\n");
            else
                printf("Player %c Wins!\n", winner);

            break;
        }

        if(boardFull()) {
            printBoard();
            printf("It's a Draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}