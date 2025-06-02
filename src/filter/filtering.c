/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** filtering
*/

#include "dataframe.h"
#include "my.h"
#include <string.h>

bool is_correct(row_t *node, int index, bool (*filter_func)(void *value))
{
    column_type_t type = node->type[index];

    if (type == STRING)
        return filter_func(node->row_data[index].s);
    if (type == BOOL)
        return filter_func(&node->row_data[index].b);
    if (type == INT)
        return filter_func(&node->row_data[index].i);
    if (type == UINT)
        return filter_func(&node->row_data[index].ui);
    if (type == FLOAT)
        return filter_func(&node->row_data[index].f);
    return true;
}

/*
 **type is only malloced once and attached to the head
*/
static void copy_stuff(dataframe_t *new_frame, int row_nb,
    row_t **new, row_t *old)
{
    if (row_nb == 1) {
        *new = spec_mem_handle(old, old->type, new_frame->nb_columns);
        (*new)->type = type_dup(old->type, new_frame->nb_columns);
        (*new)->next = NULL;
        (*new)->prev = NULL;
        new_frame->head = *new;
    } else {
        (*new)->next = spec_mem_handle(old, old->type, new_frame->nb_columns);
        (*new)->next->prev = *new;
        (*new)->next->type = new_frame->head->type;
        *new = (*new)->next;
        (*new)->next = NULL;
    }
}

/*
 **if filter func is true then i duplicate the node in new_frame
 **new head IS NOT MALOCED
 **i also need to count how many rows
 **at the end i update the tail
*/
static void copy_valid(dataframe_t *new_frame, row_t *old_head,
    bool (*filter_func)(void *value), int index)
{
    row_t *new_cur = new_frame->head;
    row_t *old_cur = old_head;
    int row_nb = 0;

    while (old_cur) {
        if (is_correct(old_cur, index, filter_func)) {
            row_nb++;
            copy_stuff(new_frame, row_nb, &new_cur, old_cur);
        }
        old_cur = old_cur->next;
    }
    new_frame->nb_rows = row_nb;
    new_frame->tail = new_cur;
}

dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value))
{
    dataframe_t *new_frame = NULL;
    int index = index_finder(dataframe, column);

    if (index < 0 || !dataframe || !column)
        return NULL;
    new_frame = malloc(sizeof(dataframe_t));
    new_frame->separator = strdup(dataframe->separator);
    new_frame->column = col_dup(dataframe->column);
    new_frame->nb_columns = dataframe->nb_columns;
    copy_valid(new_frame, dataframe->head, filter_func, index);
    return new_frame;
}
