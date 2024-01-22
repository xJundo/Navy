/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "my_navy.h"

int checkletter(char **arr, int i, int last, int first)
{
    int check_letter = 0;

    if (arr[i][last] < arr[i][first])
        check_letter = ABS(arr[i][first] - arr[i][last]);
    else
        check_letter = ABS(arr[i][last] - arr[i][first]);
    return check_letter;
}

int fill_info_ship(nodes_t **ships, int range_lines, int range_cols, char *str)
{
    info_ship_t *info_ship = malloc(sizeof(info_ship_t));

    info_ship->str = str;
    info_ship->range_cols = range_cols;
    info_ship->range_lines = range_lines;
    push_f_doubly(ships, info_ship, UNKNOW);
}

int check_error(char **arr, int i, nodes_t **ships)
{
    int check_letter = 0;
    int check_digit = 0;

    if (arr[i][1] != ':' || arr[i][4] != ':') {
        my_putstr_error("bad separator\n");
        return FAILURE;
    }
    if (arr[i][2] < 'A' || arr[i][2] > 'H'
        || arr[i][5] < 'A' || arr[i][5] > 'H') {
        my_putstr_error("coord between 'A' and 'H'\n");
        return FAILURE;
    }
    check_letter = checkletter(arr, i, 5, 2);
    check_digit = checkletter(arr, i, 6, 3);
    if (check_letter + check_digit + 1 != arr[i][0] - '0') {
        my_putstr_error("length problem\n");
        return FAILURE;
    }
    fill_info_ship(ships, check_digit, check_letter, arr[i]);
    return CONTINUE;
}

int check_correct_coord(char **arr, nodes_t **ships)
{
    for (int i = 0; arr[i]; i++) {
        if (check_error(arr, i, ships) == FAILURE)
            return FAILURE;
    }
    return CONTINUE;
}

int check_info(char **arr, nodes_t **ships)
{
    if (check_correct_coord(arr, ships) == FAILURE)
        return FAILURE;
    return CONTINUE;
}
