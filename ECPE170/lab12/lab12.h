#ifndef LAB12_H
#define LAB12_H

//<function prototypes go here>
uint32_t random_in_range(uint32_t low, uint32_t high);
uint32_t get_random();
void print_board(bool init);
int win();
void place_on_board(char space, int col_choice);
int check_tie(int win);

#endif // LAB12_H

