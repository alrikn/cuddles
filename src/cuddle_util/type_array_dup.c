/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** remake_type_array
*/

#include "dataframe.h"
#include "my.h"

row_t *spec_mem_handle(row_t *old, column_type_t *types, int nb_col)
{
    row_t *new = malloc(sizeof(row_t));

    new->next = NULL;
    new->prev = NULL;
    new->row_data = malloc(sizeof(element_t) * nb_col);
    for (int i = 0; i < nb_col; i++) {
        if (old->type[i] == STRING)
            new->row_data[i].s = strdup(old->row_data[i].s);
        else
            new->row_data[i] = old->row_data[i];
    }
    return new;
}

column_type_t *type_dup(column_type_t *old, int nb_col)
{
    column_type_t *new = malloc(sizeof(column_type_t) * nb_col);
    int index = 0;

    while (index < nb_col) {
        new[index] = old[index];
        index++;
    }
    return new;
}
