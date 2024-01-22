/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "my_navy.h"

extern users_t users;

void wait_result(char *attack)
{
    int a;

    kill(users.pid_enemy, SIGUSR1);
    a = wait_signal();
    if (users.map_enemy[attack[1] - '0' - 1][(attack[0] - 'A') * 2] == 'x') {
        my_printf("missed\n");
        return;
    }
    if (a == 1) {
        users.map_enemy[attack[1] - '0' - 1][(attack[0] - 'A') * 2] = 'x';
        my_printf("hit\n");
    } else {
        users.map_enemy[attack[1] - '0' - 1][(attack[0] - 'A') * 2] = 'o';
        my_printf("missed\n");
    }
}

static void check_bis(void)
{
    wait_signal();
    if (users.map[users.line - '0' - 1][(users.col - 'A') * 2] == 'x') {
        kill(users.pid_enemy, SIGUSR2);
        my_printf("%c%c: missed\n", users.col, users.line);
        return;
    }
    if (users.map[users.line - '0' - 1][(users.col - 'A') * 2] >= '2'
        && users.map[users.line - '0' - 1][(users.col - 'A') * 2] <= '5') {
        kill(users.pid_enemy, SIGUSR2);
        my_printf("%c%c: hit\n", users.col, users.line);
        users.map[users.line - '0' - 1][(users.col - 'A') * 2] = 'x';
    } else {
        kill(users.pid_enemy, SIGUSR1);
        my_printf("%c%c: missed\n", users.col, users.line);
        users.map[users.line - '0' - 1][(users.col - 'A') * 2] = 'o';
    }
}

void check_attack(void)
{
    int j = 7;

    users.col = 0;
    users.line = 0;
    for (int i = 0; i < 8; i ++) {
        users.col += wait_signal() * my_compute_power_rec(2, j);
        kill(users.pid_enemy, SIGUSR1);
        j--;
    }
    j = 7;
    for (int i = 0; i < 8; i ++) {
        users.line += wait_signal() * my_compute_power_rec(2, j);
        kill(users.pid_enemy, SIGUSR2);
        j--;
    }
    check_bis();
}

static void send_bis(char *attack, char bit)
{
    for (int i = 7; i >= 0; i--) {
        bit = (attack[1] >> i) & 1;
        if (bit == 1)
            kill(users.pid_enemy, SIGUSR2);
        else
            kill(users.pid_enemy, SIGUSR1);
        wait_signal();
    }
}

void send_attack(char *attack)
{
    char bit;

    for (int i = 7; i >= 0; i--) {
        bit = (attack[0] >> i) & 1;
        if (bit == 1)
            kill(users.pid_enemy, SIGUSR2);
        else
            kill(users.pid_enemy, SIGUSR1);
        wait_signal();
    }
    send_bis(attack, bit);
}

static void check_win_bis(int *enemy, int *me, int i)
{
    for (int j = 0; users.map[i][j] != '\0'; j++) {
        if (users.map[i][j] == 'x')
            (*enemy)++;
        if (users.map_enemy[i][j] == 'x')
            (*me)++;
    }
}

void check_win(void)
{
    int enemy = 0;
    int me = 0;

    for (int i = 0; users.map[i] != NULL; i++)
        check_win_bis(&enemy, &me, i);
    if (me == 14) {
        my_printf("I won\n");
        users.win = 0;
    }
    if (enemy == 14) {
        my_printf("Enemy won\n");
        users.win = 1;
    }
    return;
}
