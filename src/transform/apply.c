/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** apply
*/

#include "dataframe.h"
#include "my.h"
#include <time.h>

/*
 **for finding position in array based of column name
 ** it goes through the columns and gets the index of the row_data array
*/
int index_finder(dataframe_t *frame, const char *column)
{
    int index = 0;
    col_t *current = NULL;

    if (!frame || !column || !frame->head)
        return -84;
    current = frame->column;
    while (current && strcmp(column, current->name) != 0) {
        index++;
        current = current->next;
    }
    if (!current)
        return -84;
    return index;
}

static row_t *apply_update(dataframe_t *frame, int index,
    void *(*apply_func)(void *value), row_t *cur)
{
    if (cur->type[index] == STRING)
        cur->row_data[index].s = apply_func(&cur->row_data[index].s);
    if (cur->type[index] == BOOL)
        cur->row_data[index].b = *(bool *)apply_func(&cur->row_data[index].b);
    if (cur->type[index] == INT)
        cur->row_data[index].i = *(int *)apply_func(&cur->row_data[index].i);
    if (cur->type[index] == UINT)
        cur->row_data[index].ui = *(unsigned int *)apply_func
        (&cur->row_data[index].ui);
    if (cur->type[index] == FLOAT)
        cur->row_data[index].f = *(float *)apply_func(&cur->row_data[index].f);
    return cur;
}

static dataframe_t *go_through(dataframe_t *frame, int index,
    void *(*apply_func)(void *value))
{
    row_t *current = frame->head;

    while (current) {
        current = apply_update(frame, index, apply_func, current);
        current = current->next;
    }
    return frame;
}

/*
 **just updates an entire row
*/
dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value))
{
    dataframe_t *new_frame = NULL;
    int index = index_finder(dataframe, column);

    if (!dataframe || index < 0 || !apply_func) {
        return NULL;
    }
    return NULL;
    new_frame = frame_dup(dataframe);
    new_frame = go_through(new_frame, index, apply_func);
    return new_frame;
}
