/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "my_navy.h"

extern users_t users;

void zero(int signum)
{
    users.signal = 0;
}

void one(int signum)
{
    users.signal = 1;
}

int wait_signal(void)
{
    int value = -1;

    while (users.signal == -1);
    value = users.signal;
    users.signal = -1;
    return value;
}

void get_pid_from_sig(int signum, siginfo_t *info, void *context)
{
    my_printf("enemy connected\n");
    users.pid_enemy = info->si_pid;
}
