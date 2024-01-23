/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "my_navy.h"

extern users_t users;

int receive_and_send(char *attack)
{
    if (!users.my_turn) {
        my_printf("waiting for enemy's attack...\n");
        check_attack();
        check_win();
        users.my_turn = 1;
    } else {
        check_line(attack);
        send_attack(attack);
        my_printf("%c%c: ", attack[0], attack[1]);
        wait_result(attack);
        users.my_turn = 0;
        check_win();
    }
    return 0;
}

int print_usr(void)
{
    char attack[4] = {1};

    signal(SIGUSR1, zero);
    signal(SIGUSR2, one);
    while (users.win == -1) {
        if (users.print_map) {
            print_map(users.map, 1);
            print_map(users.map_enemy, 0);
        }
        receive_and_send(attack);
        users.col = 0;
        users.line = 0;
        users.print_map = !users.print_map;
    }
    return users.win;
}

int do_usr1(struct sigaction *sa, char **map, nodes_t **ships)
{
    sa->sa_flags = SA_SIGINFO;
    sa->sa_sigaction = &get_pid_from_sig;
    sigaction(SIGUSR1, sa, NULL);
    my_printf("my_pid: %d\n", getpid());
    my_printf("waiting for enemy connection...\n");
    pause();
    return print_usr();
}

int do_usr2(struct sigaction *sa, char **map, nodes_t **ships, char **av)
{
    users.pid_enemy = my_getnbr(av[1]);
    users.my_pid = getpid();
    my_printf("my_pid: %d\n", getpid());
    if (kill(my_getnbr(av[1]), SIGUSR1) == 0)
        my_printf("successfully connected\n");
    else
        return 84;
    return print_usr();
}
