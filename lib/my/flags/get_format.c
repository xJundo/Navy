/*
** EPITECH PROJECT, 2023
** find the first format
** File description:
** find the first format
*/

#include "myformats.h"
#include "my.h"

static void check_operator(formating_t *formating)
{
    if (formating->next_chara == '+' || formating->next_chara == '-') {
        formating->nb_format += 2;
    } else {
        (formating->nb_format) += 1;
    }
}

void format_first(user_t *user, flags_t *flgs,
    formating_t *formating, int *copy)
{
    for (; user->str[*copy - 1] != flgs->str[flgs->index_flag]; (*copy)++) {
        find_first(user, copy, formating);
        if (formating->id_ft != -1) {
            check_operator(formating);
            break;
        }
    }
}

void format_width(user_t *user, flags_t *flgs,
    formating_t *formating, int *copy)
{
    for (; user->str[*copy - 1] != flgs->str[flgs->index_flag]; (*copy)++) {
        find_width(user, copy, formating);
        if (formating->id_wd != -1) {
            (formating->nb_format) += my_strlen(my_str_nbr(formating->id_wd));
            break;
        }
    }
}

void format_precision(user_t *user, flags_t *flgs,
    formating_t *formating, int *copy)
{
    for (; user->str[*copy - 1] != flgs->str[flgs->index_flag]; (*copy)++) {
        find_precision(user, copy, formating);
        if (formating->id_prc != -1) {
            formating->nb_format += 1;
            break;
        }
    }
}

void format_numbers(user_t *user, flags_t *flgs,
    formating_t *formating, int *copy)
{
    for (; user->str[*copy - 1] != flgs->str[flgs->index_flag]; (*copy)++) {
        find_numbers(user, copy, formating);
        if (formating->id_nb != -1) {
            (formating->nb_format) += my_strlen(my_str_nbr(formating->id_nb));
            break;
        }
    }
}

void format_specifier(user_t *user, flags_t *flgs,
    formating_t *formating, int *copy)
{
    find_specifier(user, copy, formating);
    if (formating->id_sp == 1 || formating->id_sp == 3) {
        formating->nb_format += 2;
    } else if (formating->id_sp != - 1) {
        formating->nb_format += 1;
    }
}
