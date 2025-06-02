/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** head
*/

#include "dataframe.h"
#include "my.h"
#include <string.h>

static void head_initializer(row_t **old_head, row_t **new_head,
    row_t **old_cur, row_t **new_cur)
{
    (*new_head)->prev = NULL;
    *old_cur = (*old_head)->next;
    *new_cur = *new_head;
}

/*
 **duplicates entire node, not only specific
 **tail is not necessary can be NULL, it will return pointer to last of list
 **duplicates only to upto
*/
row_t *row_dup_head(row_t *old_head, int nb_col, row_t **tail, int upto)
{
    row_t *new_head = NULL;
    row_t *old_cur = NULL;
    row_t *new_cur = NULL;
    int index = 1;

    new_head = spec_mem_handle(old_head, old_head->type, nb_col);
    new_head->type = type_dup(old_head->type, nb_col);
    head_initializer(&old_head, &new_head, &old_cur, &new_cur);
    while (old_cur && index < upto) {
        new_cur->next = spec_mem_handle(old_cur, old_cur->type, nb_col);
        new_cur->next->type = new_head->type;
        new_cur->next->prev = new_cur;
        new_cur = new_cur->next;
        old_cur = old_cur->next;
        index++;
    }
    new_cur->next = NULL;
    *tail = new_cur;
    return new_head;
}

/*
 **just takes the first few rows in a new dataframe
 **0 is valid just gonna mean thatyou gonna have no rows
 **if nb_row > dataframe->nb rows then we take max rows
*/
dataframe_t *df_head(dataframe_t *dataframe, int nb_rows)
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
        new->head = row_dup_head(dataframe->head,
    dataframe->nb_columns, &new->tail, nb_rows);
    new->column = col_dup(dataframe->column);
    return new;
}
