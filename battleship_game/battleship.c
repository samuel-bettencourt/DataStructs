#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
void initialize_boards(char user_board[10][10] , char hidden_board[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            user_board[i][j] = '~';
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            hidden_board[i][j] = 'X';
        }
    }
}

void display_board(char board_array[10][10]) {
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < 10; i++) {
        printf("%d " , i);
        for (int j = 0; j < 10; j++) {
            printf("%c " , board_array[i][j]);
        }
        printf("\n");
    }
}
int check_placement_vertical(char hidden_board[10][10], int starting_row, int starting_column, int size) {
    if (starting_row > 10 - size || starting_row + size > 10) {
        return 0;
    } else {
        for (int i = starting_row; i < starting_row + size; i++) {
            if (hidden_board[i][starting_column] != 'X') {
                return 0;
            } else {
            }
        }
    }
    return 1;
}

int check_placement_horizontal(char hidden_board[10][10], int starting_row, int starting_column, int size) {
    if (starting_column > 10 - size || starting_column + size > 10) {
        return 0;
    } else {
        for (int i = starting_column; i < starting_column + size; i++) {
            if (hidden_board[starting_row][i] != 'X') {
                return 0;
            }
        }
    }
    return 1;
}

void place_ship_vertical(char hidden_board[10][10], int size, char letter) {
    int result;
    int starting_row;
    int starting_column;
    do {
        starting_row = (rand()%(9-0+1))+0;
        starting_column = (rand()%(9-0+1))+0;
        result = check_placement_vertical(hidden_board, starting_row, starting_column, size);
    } while (result != 1);
    for (int i = starting_row; i < starting_row + size; i++) {
        hidden_board[i][starting_column] = letter;
    }
}

void place_ship_horizontal(char hidden_board[10][10], int size, char letter) {
    int result;
    int starting_row;
    int starting_column;
    do {
        starting_row = (rand()%(9-0+1))+0;
        starting_column = (rand()%(9-0+1))+0;
        result = check_placement_horizontal(hidden_board, starting_row, starting_column, size);
    } while (result != 1);
    for (int i = starting_column; i < starting_column + size; i++) {
        hidden_board[starting_row][i] = letter;
    }
}

void place_ship(char hidden_board[10][10]) {
    int ship;
    int size;
    for (int i = 0; i < 20; i++) {
        char letter = 'A' + i;
        if (letter == 'C') {
            size = 5;
        } else if (letter == 'B') {
            size = 4;
        } else if (letter == 'D') {
            size = 3;
        } else if (letter == 'S') {
            size = 3;
        } else if (letter == 'P') {
            size = 2;
        } else {
            size = 0;
        }
        ship = (rand()%(1-0+1))+0;
        if (ship == 1 && size != 0) {
            place_ship_vertical(hidden_board, size, letter);
        } else if (ship != 1 && size != 0) {
            place_ship_horizontal(hidden_board, size, letter);
        } else {
        }
    }
}

int is_guess_valid(char user_board[10][10], int row, int column) {
    if (row < 0 || row > 9) {
        printf("You entered an invalid row.\n");
        return 0;
    } else if (column < 0 || column > 9) {
        printf("You entered an invalid column.\n");
        return 0;
    } else if (user_board[row][column] != '~') {
        printf("You have already guessed that position.\n");
        return 0;
    } else {
        return 1;
    }
}

char make_guess(char hidden_board[10][10], char user_board[10][10]) {
    int row;
    int column;
    int valid;
    do {
        printf("Enter a row: ");
        scanf("%d" , &row);
        printf("Enter a column: ");
        scanf("%d" , &column);
        valid = is_guess_valid(user_board, row, column);
    } while (valid != 1);
    user_board[row][column] = hidden_board[row][column];
    return user_board[row][column];
}
int main() {
    srand(time(NULL));
    char user_board[10][10];
    char hidden_board[10][10];
    int counter = 0;
    initialize_boards(user_board, hidden_board);
    place_ship(hidden_board);
    char guess_result;
    int carrier_health = 5;
    int battleship_health = 4;
    int destroyer_health = 3;
    int submarine_health = 3;
    int patrolboat_health = 2;
    while(carrier_health != 0 || battleship_health != 0 || destroyer_health != 0 || submarine_health != 0 || patrolboat_health != 0) {
        display_board(user_board);
        guess_result = make_guess(hidden_board, user_board);
        counter ++ ;
        if (guess_result == 'C') {
            carrier_health -- ;
            if (carrier_health == 0) {
                printf("You sunk my Carrier!\n");
            } else {
                printf("You hit my Carrier.\n");
            }
        } else if (guess_result == 'B') {
            battleship_health -- ;
            if (battleship_health == 0) {
                printf("You sunk my Battleship!\n");
            } else {
                printf("You hit my Battleship.\n");
            }
        } else if (guess_result == 'D') {
            destroyer_health -- ;
            if (destroyer_health == 0) {
                printf("You sunk my Destroyer!\n");
            } else {
                printf("You hit my Destroyer.\n");
            }
        } else if (guess_result == 'S') {
            submarine_health -- ;
            if (submarine_health == 0) {
                printf("You sunk my Submarine!\n");
            } else {
                printf("You hit my Submarine.\n");
            }
        } else if (guess_result == 'P') {
            patrolboat_health -- ;
            if (patrolboat_health == 0) {
                printf("You sunk my Patrol Boat!\n");
            } else {
                printf("You hit my Patrol Boat.\n");
            }
        } else {
            printf("You missed.\n");
        }
        printf("Guess number %d\n" , counter);
    }
    display_board(user_board);
    printf("Wow you sunk all my ships!\nIt took you %d guesses to win.\nCongratulations you won!\n" , counter);
}