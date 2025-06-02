/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** sorting
*/

#include "dataframe.h"
#include "my.h"

/*
 ** if sort_func crashes not my responsability
*/
static bool figure_out(bool (*sort_func)(void *value1, void *value2),
    const int i, row_t *nod1, row_t *nod2)
{
    if (nod1->type[i] == BOOL)
        return sort_func(&nod1->row_data[i].b, &nod2->prev->row_data[i].b);
    if (nod1->type[i] == INT)
        return sort_func(&nod1->row_data[i].i, &nod2->prev->row_data[i].i);
    if (nod1->type[i] == UINT)
        return sort_func(&nod1->row_data[i].ui, &nod2->prev->row_data[i].ui);
    if (nod1->type[i] == FLOAT)
        return sort_func(&nod1->row_data[i].f, &nod2->prev->row_data[i].f);
    if (nod1->type[i] == STRING)
        return sort_func(&nod1->row_data[i].s, &nod2->prev->row_data[i].s);
    return true;
}

static row_t *merge(row_t *first, row_t *second,
    bool (*sort_func)(void *value1, void *value2), const int index)
{
    if (!first)
        return second;
    if (!second)
        return first;
    if (!figure_out(sort_func, index, first, second)) {
        first->next = merge(first->next, second, sort_func, index);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    } else {
        second->next = merge(first, second->next, sort_func, index);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

static row_t *merge_handle(row_t *head1, row_t *head2,
    bool (*sort_func)(void *value1, void *value2), const int index)
{
    row_t *last_row_t;
    row_t *final_head;

    if (!head1)
        return head2;
    if (!head2)
        return head1;
    if (!figure_out(sort_func, index, head1->prev, head2->prev))
        last_row_t = head2->prev;
    else
        last_row_t = head1->prev;
    head1->prev->next = NULL;
    head2->prev->next = NULL;
    final_head = merge(head1, head2, sort_func, index);
    final_head->prev = last_row_t;
    last_row_t->next = final_head;
    return final_head;
}

static row_t **array_updater(int *i, row_t *head, row_t **temp_array)
{
    row_t *new_list;
    row_t *current = head;
    row_t *temp;

    do {
        new_list = NULL;
        temp = current;
        current = current->next;
        link_to_list(&new_list, temp);
        temp_array[*i] = new_list;
        (*i)++;
    } while (current != head);
    return temp_array;
}

/*
 ** i return an array which array[0] = head
 ** array is malloced so you have to free
*/
row_t **split_to_array(row_t *head, dataframe_t *frame,
    bool (*sort_func)(void *value1, void *value2), const int index)
{
    row_t **array = malloc(frame->nb_rows * sizeof(row_t *));
    int index_count = 0;

    if (head == NULL)
        return array;
    array = array_updater(&index_count, head, array);
    while (index_count > 1) {
        array[0] = merge_handle(array[0], array[1], sort_func, index);
        for (int i = 1; i < index_count - 1; i++)
            array[i] = array[i + 1];
        (index_count)--;
    }
    return array;
}

/*
 **handles circularisation and decircularisation
*/
dataframe_t *sort_it(dataframe_t *new_frame, dataframe_t *old_frame,
    int const index, bool (*sort_func)(void *value1, void *value2))
{
    row_t **array = NULL;

    new_frame = frame_dup(old_frame);
    new_frame->head->prev = new_frame->tail;
    new_frame->tail->next = new_frame->head;
    array = split_to_array(new_frame->head, new_frame, sort_func, index);
    new_frame->head = array[0];
    free(array);
    new_frame->tail = new_frame->head->prev;
    new_frame->head->prev->next = NULL;
    new_frame->head->prev = NULL;
    return new_frame;
}

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2))
{
    int index = index_finder(dataframe, column);
    dataframe_t *new_frame = NULL;

    if (!column || !dataframe || index < 0 || dataframe->nb_rows <= 0) {
        return NULL;
    }
    return sort_it(new_frame, dataframe, index, sort_func);
}
