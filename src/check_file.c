/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "my_navy.h"

static int coding_style(int *len)
{
    for (int i = 0; i < 4; i++) {
        if (len[i] == 0) {
            my_putstr_error("file must contains lengths"
            " : 2, 3, 4, 5. (Only)\n");
            return FAILURE;
        }
    }
    return CONTINUE;
}

static int check_len(char *str, int n)
{
    char c = n + '1';

    if (my_strlen(str) != 7) {
        my_putstr_error("bad info -> \"");
        my_putstr_error(str);
        my_putstr_error("\" at line : ");
        write(2, &c, 1);
        my_putstr_error("\n");
        return FAILURE;
    }
    return CONTINUE;
}

int check_ships_length(char **arr)
{
    int len[5] = {0, 0, 0, 0};

    for (int j = 0; arr[j]; j++) {
        if (check_len(arr[j], j) == FAILURE)
            return FAILURE;
        if (arr[j][0] == '2')
            len[0] = 2;
        if (arr[j][0] == '3')
            len[1] = 3;
        if (arr[j][0] == '4')
            len[2] = 4;
        if (arr[j][0] == '5')
            len[3] = 5;
    }
    if (coding_style(len) == FAILURE)
        return FAILURE;
    return CONTINUE;
}

int check_arr(char **arr)
{
    int i = 0;

    for (; arr[i]; i++);
    if (i != 4) {
        my_putstr_error("file must contains 4 ships only.\n");
        return FAILURE;
    }
    if (check_ships_length(arr) == FAILURE)
        return FAILURE;
    return CONTINUE;
}

int check_file(int ac, char **av, nodes_t **ships)
{
    int fd;
    char buffer[33];
    char **arr;

    if (ac > 3 || ac == 1) {
        my_putstr_error("maximum 3 arguments\n");
        return FAILURE;
    }
    fd = open(av[ac - 1], O_RDONLY);
    if (fd == -1) {
        my_putstr_error("Can't open map\n");
        return FAILURE;
    }
    if (read(fd, buffer, 33) != 32)
        return FAILURE;
    buffer[32] = '\0';
    arr = my_str_to_word_array(buffer);
    if (check_arr(arr) == FAILURE || check_info(arr, ships) == FAILURE)
        return FAILURE;
    return CONTINUE;
}
