/*
** EPITECH PROJECT, 2023
** MY_NAVY
** File description:
** MY_NAVY
*/


#ifndef MY_NAVY_H
    #define MY_NAVY_H
    #include "mylist.h"
    #include <signal.h>


typedef enum state {
    CONTINUE,
    SUCCESS,
    FAILURE,
    USER1,
    USER2,
}state_enum;

char **my_str_to_word_array2(char const *str);

typedef struct {
    char *str;
    int range_lines;
    int range_cols;
} info_ship_t;

typedef struct user {
    int my_pid;
    int pid_enemy;
    int win;
    char **map;
    char **map_enemy;
    int my_turn;
    int print_map;
    int col;
    int line;
    int send_it;
    int signal;
} users_t;

//Maps
char **create_map(nodes_t **ships, int empty);
void print_map(char **map, int my);
int check_line(char *attack);
int wait_signal(void);

//Sig handling
void one(int signum);
void zero(int signum);
void send_attack(char *attack);
void wait_result(char *attack);
void check_attack(void);
void check_win(void);

//User1
void get_pid_from_sig(int signum, siginfo_t *info, void *context);
int do_usr1(struct sigaction *sa, char **map, nodes_t **ships);

//User2
int do_usr2(struct sigaction *sa, char **map, nodes_t **ships, char **av);

int main_game(nodes_t **ships, int ac, char **av);
int check_info(char **arr, nodes_t **ships);
int check_file(int ac, char **av, nodes_t **info_ship);
int my_navy(int ac, char **av);
void charToBinary(char c);

#endif //MY_NAVY_H
