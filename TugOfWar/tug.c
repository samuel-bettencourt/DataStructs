#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct shop {
    int push;
    int jump;
} shop;
typedef struct doubly {
    char name;
    struct doubly *next;
    struct doubly *prev;
} doubly;
void get_shop(shop option_arr[]) {
    for (int i = 0; i < 5; i++) {
        option_arr[i].push = rand()%(3-1+1)+1;
        option_arr[i].jump = rand()%(3-1+1)+1;
    }
}
shop option_select(shop option_arr[]) {
    for (int i = 1; i <= 5; i++) {
        printf("%d)push: %d jump: %d\n" , i, option_arr[i-1].push, option_arr[i-1].jump);
    }
    int user_choice;
    do {
        printf("Enter the number of the card you want to pick: ");
        scanf("%d" , &user_choice);
    } while (user_choice <= 0 || user_choice > 5);
    return option_arr[user_choice-1];
}
void add_to_empty_list(doubly **head_ptr) {    
  doubly *new_node = malloc(sizeof(doubly));       
  new_node->next = NULL;    
  new_node->prev = NULL;    
  *head_ptr = new_node;
}
void add_to_end(doubly **head_ptr) {    
    if (*head_ptr == NULL) {        
        add_to_empty_list(head_ptr);    
    } else {        
        doubly *current = *head_ptr;        
        while (current->next != NULL) {        
            current = current->next;    
        }    
        doubly *new_node = malloc(sizeof(doubly));       
        current->next = new_node;    
        new_node->prev = current;    
        new_node->next = NULL;    
    }
}
void create_board(doubly **board_ptr) {
  int index = 1;
  while (index <= 11) {
    add_to_end(board_ptr);
    index++;
  } 
}
void initialize_board(doubly **board_ptr) {
    int index = 1;
    doubly *current = *board_ptr;
    while (index == 1) {
        current->name = '1';
        current = current->next;
        index++;
    }
    while (index > 1 && index <= 5) {
        current->name = 'N';
        current = current->next;
        index++;
    }
    while (index == 6) {
        current->name = 'G';
        current = current->next;
        index++;
    }
    while (index > 6 && index < 11) {
        current->name = 'N';
        current = current->next;
        index++;
    }
    while (index == 11) {
        current->name = '2';
        current = current->next;
        index++;
    }
}
void display_board(doubly *board) {
  doubly *current = board;
  while (current != NULL) {
    printf("> { %c } <" , current->name);
    current = current->next;
  }
  printf("\n");
}
void game(doubly **board_ptr) {
    doubly *player1 = *board_ptr;
    doubly *player2 = *board_ptr;
    doubly *goal = *board_ptr;
    while (goal->name != 'G') {
        goal = goal->next;
    }
    while (player1->name != '1') {
        player1 = player1->next;
    }
    while (player2->name != '2') {
        player2 = player2->next;
    }
    while (goal->name == 'G') {
        display_board(*board_ptr);
        printf("Player 1s turn to pick a card..\n");
        shop options1[5];
        get_shop(options1);
        shop player1_choice = option_select(options1);
        int move_player1_1 = player1_choice.jump;
        int move_player2_1 = player1_choice.push;
        player1->name = 'N';
        while (move_player1_1 >= 1 && player1 != goal) {
            player1 = player1->next;
            move_player1_1--;
        }
        player1->name = '1';
        player2->name = 'N';
        while (move_player2_1 >= 1 && player2->next != NULL) {
            player2 = player2->next;
            move_player2_1--;
        }
        player2->name = '2';
        display_board(*board_ptr);
        if (player1 == goal) {
            break;
        }
        printf("Player 2s turn to pick a card...\n");
        shop options2[5];
        get_shop(options2);
        shop player2_choice = option_select(options2);
        int move_player1_2 = player2_choice.push;
        int move_player2_2 = player2_choice.jump;
        player1->name = 'N';
        while (move_player1_2 >= 1 && player1->prev != NULL) {
            player1 = player1->prev;
            move_player1_2--;
        }
        player1->name = '1';
        player2->name = 'N';
        while (move_player2_2 >= 1 && player2 != goal) {
            player2 = player2->prev;
            move_player2_2--;
        }
        player2->name = '2';
    }
    if (player1 == goal) {
        printf("Player 1 reached the goal first\nYou win!!\n");
    } else {
        printf("Player 2 reached the goal first\nYou win!\n");
    }
}
int main() {
    srand(time(NULL));
    doubly *board = NULL;
    create_board(&board);
    initialize_board(&board);
    game(&board);
}