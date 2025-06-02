/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** frame_dup
*/

#include "dataframe.h"
#include "my.h"
#include <string.h>

/*
 **duplicates entire lsit, not only specific
 ** tail is not necessary can be NULL, it will return pointer to last of list
*/
row_t *row_dup(row_t *old_head, int nb_col, row_t **tail)
{
    row_t *new_head;
    row_t *old_cur;
    row_t *new_cur;

    new_head = spec_mem_handle(old_head, old_head->type, nb_col);
    new_head->type = type_dup(old_head->type, nb_col);
    new_head->prev = NULL;
    old_cur = old_head->next;
    new_cur = new_head;
    while (old_cur) {
        new_cur->next = spec_mem_handle(old_cur, old_cur->type, nb_col);
        new_cur->next->type = new_head->type;
        new_cur->next->prev = new_cur;
        new_cur = new_cur->next;
        old_cur = old_cur->next;
    }
    new_cur->next = NULL;
    *tail = new_cur;
    return new_head;
}

/*
 **duplicates entire node, not only specific
*/
col_t *col_dup(col_t *old_col)
{
    col_t *new_head = malloc(sizeof(col_t));
    col_t *old_cur = NULL;
    col_t *new_cur = NULL;

    new_head->name = strdup(old_col->name);
    new_head->type = old_col->type;
    old_cur = old_col->next;
    new_cur = new_head;
    while (old_cur) {
        new_cur->next = malloc(sizeof(col_t));
        new_cur->next->name = strdup(old_cur->name);
        new_cur->next->type = old_cur->type;
        new_cur->next->next = NULL;
        new_cur = new_cur->next;
        old_cur = old_cur->next;
    }
    new_cur->next = NULL;
    return new_head;
}

/*
 ** this the entire frame
 ** if the input is null segfaults
*/
dataframe_t *frame_dup(dataframe_t *frame)
{
    dataframe_t *new = malloc(sizeof(dataframe_t));

    new->separator = strdup(frame->separator);
    new->nb_columns = frame->nb_columns;
    new->nb_rows = frame->nb_rows;
    new->head = row_dup(frame->head, frame->nb_columns, &new->tail);
    new->column = col_dup(frame->column);
    return new;
}
