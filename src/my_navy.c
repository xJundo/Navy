/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "my_navy.h"

int help(int ac, char **av)
{
    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        my_printf("USAGE\n     ./navy [first_player_pid] navy_positions\n"
        "DESCRIPTION\n     first_player_pid: only for the 2nd player."
        "pid of the first player.\n     "
        "navy_positions: file representing"
        "the positions of the ships\n");
        return SUCCESS;
    }
    return 0;
}

int my_navy(int ac, char **av)
{
    nodes_t *ships = NULL;

    if (help(ac, av) == SUCCESS)
        return 0;
    if (check_file(ac, av, &ships) == FAILURE)
        return 84;
    if (main_game(&ships, ac, av) == USER1)
        return 0;
    else
        return 1;
    return 0;
}
