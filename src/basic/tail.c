/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** tail
*/

#include "dataframe.h"
#include "my.h"

static void tail_initializer(row_t **old_tail, row_t **new_tail,
    row_t **old_cur, row_t **new_cur)
{
    (*new_tail)->next = NULL;
    *old_cur = (*old_tail)->prev;
    *new_cur = *new_tail;
}

/*
 **duplicates entire node, not only specific
 **tail is not necessary can be NULL, it will return pointer to last of list
 **duplicates only to upto
*/
row_t *row_dup_tail(row_t *old_tail, int nb_col, row_t **head, int upto)
{
    row_t *new_tail = NULL;
    row_t *old_cur = NULL;
    row_t *new_cur = NULL;
    int index = 1;

    new_tail = spec_mem_handle(old_tail, old_tail->type, nb_col);
    new_tail->type = type_dup(old_tail->type, nb_col);
    tail_initializer(&old_tail, &new_tail, &old_cur, &new_cur);
    while (old_cur && index < upto) {
        new_cur->prev = spec_mem_handle(old_cur, old_cur->type, nb_col);
        new_cur->prev->type = new_tail->type;
        new_cur->prev->next = new_cur;
        new_cur = new_cur->prev;
        old_cur = old_cur->prev;
        index++;
    }
    new_cur->prev = NULL;
    *head = new_cur;
    return new_tail;
}

/*
 ** copies last (in the order that it was previously)
*/
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *new = NULL;

    if (!dataframe || nb_rows < 0)
        return NULL;
    new = malloc(sizeof(dataframe_t));
    new->separator = strdup(dataframe->separator);
    new->nb_columns = dataframe->nb_columns;
    new->head = NULL;
    new->tail = NULL;
    if (nb_rows > dataframe->nb_rows)
        nb_rows = dataframe->nb_rows;
    new->nb_rows = nb_rows;
    if (nb_rows > 0)
        new->tail = row_dup_tail(dataframe->tail,
    dataframe->nb_columns, &new->head, nb_rows);
    new->column = col_dup(dataframe->column);
    return new;
    return dataframe;
}
