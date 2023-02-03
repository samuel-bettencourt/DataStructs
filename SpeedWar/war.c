#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct node {
    int data;
    struct node *next;
} node;
typedef struct linked_stack {
    node *head;
} linked_stack;
void add_to_start_of_list(node **head_ptr, int data) {
    node *new_node = malloc(sizeof(node));
    new_node->data = data;
    new_node->next = *head_ptr;
    *head_ptr = new_node;
}
void remove_from_start_of_list(node **head_ptr) {
    if (*head_ptr == NULL) {
        printf("Nothing to remove\n");
    } else {
        node *remove_node = *head_ptr;
        *head_ptr = remove_node->next;
        remove_node->next = NULL;
        free(remove_node);
    }
}
void display_linked(node *head) {
    node *current = head;
    while (current != NULL) {
        printf("{ %d } -> " , current->data);
        current = current->next;
    }
    printf("X\n");
}
void linked_push(linked_stack *stack, int element) {    
    add_to_start_of_list(&(stack->head), element); 
}
int linked_peek(linked_stack stack, int *top_value) {    
    if (stack.head == NULL) {        
        return 0;    
    } else {        
        *top_value = stack.head->data;        
        return 1;    
    } 
}
int linked_pop(linked_stack *stack) {
    if (stack->head == NULL) {
        return 0;
    } else {
        remove_from_start_of_list(&(stack->head));
        return 1;
    }
}
void initialize_deck(int deck[]) {
    int card_val = 2;
    while (card_val <= 14) {
      for (int i = 0; i < 13; i++) {
        deck[(4 * i)] = card_val;
        deck[(4 * i) + 1] = card_val;
        deck[(4 * i) + 2] = card_val;
        deck[(4 * i) + 3] = card_val;
        card_val += 1;
      }
    }
}
void shuffle_deck(int deck[]) {
    for (int i = 0; i < 500; i++) {
        int card1 = rand()%(51-0+1);
        int card2 = rand()%(51-0+1);
        int temp = deck[card1];
        deck[card1] = deck[card2];
        deck[card2] = temp;
    }
}
void deal_deck(linked_stack *player1_stack, linked_stack *player2_stack, int deck[]) {
  for (int i = 0; i < 26; i++) {
    linked_push(player1_stack, deck[i]);
  }
  for (int i = 26; i < 52; i++) {
    linked_push(player2_stack, deck[i]);
  }
}
int get_card_pick(linked_stack *player_stack, linked_stack *player_discard_stack) {
    int options[3];
    int index = 0;
    int value;
    int pop_check;
    int peek_check;
    while (player_stack->head != NULL && index < 3) {
      peek_check = linked_peek(*player_stack, &value);
      if (peek_check != 0) {
          options[index] = value;
      }
      pop_check = linked_pop(player_stack);
      index++;
    }
    for (int i = 0; i < index; i++) {
        printf("%d) %d\n" , i, options[i]);
    }
    int choice;
    do {
        printf("Enter which index you want to pick: ");
        scanf("%d" , &choice);
    } while (choice >= index || choice < 0);
    printf("You chose %d\n" , options[choice]);
    for (int i = 0; i < 3; i++) {
        if (i != choice) {
            linked_push(player_discard_stack, options[i]);
        } else {
        }
    }
    return options[choice];
}
void reshuffle_stack(linked_stack *player_discard_stack, linked_stack *player_stack) {
    int value;
    int peek_check = 0;
    int pop_check = 0;
    while (player_discard_stack->head != NULL) {
        printf("reshuffling\n");
        peek_check = linked_peek(*player_discard_stack, &value);
        if (peek_check != 0) {
            linked_push(player_stack, value);
        }
        pop_check = linked_pop(player_discard_stack);
    }
    
}
void game(linked_stack *player1_stack, linked_stack *player2_stack, linked_stack *player1_discard_stack, linked_stack *player2_discard_stack, int *player1_points, int *player2_points) {
    int whos_turn = 1;
    int empty_check;
    int discard1_size = 0;
    int discard2_size = 0;
    while (player1_stack->head != NULL) {
        printf("Round Start\n");
        int player1_card;
        int player2_card;
        if (whos_turn % 2 != 0) {
            printf("player 1:\n");
            player1_card = get_card_pick(player1_stack , player1_discard_stack);
            printf("player 2:\n");
            player2_card = get_card_pick(player2_stack , player2_discard_stack);
        } else {
            printf("player 2\n");
            player2_card = get_card_pick(player2_stack , player2_discard_stack);
            printf("player 1\n");
            player1_card = get_card_pick(player1_stack , player1_discard_stack);
        }
        if (player1_card > player2_card) {
            *player1_points += 2;
        } else if (player2_card > player1_card) {
            *player2_points += 2;
        } else if (player1_card == player2_card) {
            *player1_points += 1;
            *player2_points += 1;
        } else{
        }
        whos_turn++;
        int dummy_val;
        empty_check = linked_peek(*player1_stack, &dummy_val);
        if (empty_check == 0) {
        }

    }  
}
int main() {
    srand(time(NULL));
    int deck[52];
    initialize_deck(deck);
    shuffle_deck(deck);
    linked_stack player1_stack;
    player1_stack.head = NULL;
    linked_stack player1_discard_stack;
    player1_discard_stack.head = NULL;
    int player1_points = 0;
    linked_stack player2_stack;
    player2_stack.head = NULL;
    linked_stack player2_discard_stack;
    player2_discard_stack.head = NULL;
    int player2_points = 0;
    deal_deck(&player1_stack, &player2_stack, deck);
    game(&player1_stack, &player2_stack, &player1_discard_stack, &player2_discard_stack, &player1_points, &player2_points);
    printf("Player 1 ended with %d points\n" , player1_points);
    printf("Player 2 ended with %d points\n" , player2_points);
    if (player1_points > player2_points) {
        printf("Player 1 is victorious\n");
    } else if (player2_points > player1_points) {
        printf("Player 2 is victorious\n");
    } else {
        printf("You both tied with %d points\n" , player1_points);
    }
}