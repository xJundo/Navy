/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "my_navy.h"

users_t users = {0};

static int create_map_bis(info_ship_t *ship, int empty, char **map)
{
    for (int i = 0; i <= ship->range_lines; i++)
        map[(ship->str[3] - '0' - 1) + i]
        [(ship->str[2] - 'A') * 2] = ship->str[0];
    for (int i = 0; i <= ship->range_cols; i++)
        map[(ship->str[3] - '0' - 1)]
        [((ship->str[2] - 'A') * 2) + (i * 2)] = ship->str[0];
    return 0;
}

char **create_map(nodes_t **ships, int empty)
{
    char **map = malloc(sizeof(char *) * 9);
    info_ship_t *ship;

    for (int i = 0; i < 9; i++) {
        map[i] = malloc(sizeof(char) * 16);
        (map[i], 0, 16);
        my_strcat(map[i], ". . . . . . . .\0");
    }
    map[8] = NULL;
    if (empty)
        return map;
    for (nodes_t *tmp = *ships; tmp; tmp = tmp->next) {
        ship = tmp->data;
        create_map_bis(ship, empty, map);
    }
    return map;
}

void print_map(char **map, int my)
{
    if (my) {
        my_printf("my positions: \n");
        my_printf(" |A B C D E F G H\n-+---------------\n");
    } else {
        my_printf("enemy's positions: \n");
        my_printf(" |A B C D E F G H\n-+---------------\n");
    }
    for (int i = 0; map[i]; i++) {
        my_printf("%d|", i + 1);
        my_printf("%s\n", map[i]);
    }
}

int check_line(char *attack, size_t len)
{
    int failure = 0;

    if (my_strlen(attack) != 3 || (attack[0] < 'A' || attack[0] > 'H')
        || (attack[1] < '1' || attack[1] > '8'))
        failure = 1;
    while (failure) {
        my_printf("wrong position\nattack : ");
        free(attack);
        attack = NULL;
        len = 0;
        getline(&attack, &len, stdin);
        if (my_strlen(attack) != 3 || (attack[0] < 'A' || attack[0] > 'H')
            || (attack[1] < '1' || attack[1] > '8'))
            failure = 1;
        else
            failure = 0;
    }
    return CONTINUE;
}

static int init_users(char **map, nodes_t **ships)
{
    users.map = map;
    users.map_enemy = create_map(ships, 1);
    users.col = 0;
    users.line = 0;
    users.print_map = 1;
    users.win = -1;
    users.signal = -1;
}

int main_game(nodes_t **ships, int ac, char **av)
{
    char **map = create_map(ships, 0);
    struct sigaction sa;

    init_users(map, ships);
    if (ac == 2) {
        users.my_pid = getpid();
        users.my_turn = 1;
        users.print_map = 1;
        return do_usr1(&sa, map, ships);
    }
    if (ac == 3) {
        users.my_turn = 0;
        return do_usr2(&sa, map, ships, av);
    }
    return CONTINUE;
}
