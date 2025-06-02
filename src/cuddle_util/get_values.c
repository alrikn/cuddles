/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** get_values
*/

#include "dataframe.h"
#include "my.h"
#include <string.h>

static void *get_element(element_t *current, column_type_t type)
{
    size_t array_sizes[STRING] = {sizeof(bool), sizeof(int),
        sizeof(unsigned int), sizeof(float)};
    void *current_value = malloc(array_sizes[type]);

    memcpy(current_value, current, array_sizes[type]);
    return current_value;
}

/*
 **this initializes the array and gives what type it is
*/
static void **type_finder(dataframe_t *frame, int index, column_type_t *type)
{
    void **array = malloc(sizeof(void *) * (frame->nb_rows + 1));

    *type = frame->head->type[index];
    return array;
}

/*
 **fills the array with the specific.
 **the inside is only malloced if its a string
 **i consider that i don't have to null terminate the array
 TODO: figure this out
*/
static void **array_filler(int index, const dataframe_t *frame,
    void **array, column_type_t type)
{
    row_t *current = frame->head;
    int tracker = 0;

    while (current) {
        if (type == STRING)
            array[tracker] = (void *)strdup(current->row_data[index].s);
        else
            array[tracker] = get_element(&current->row_data[index], type);
        tracker++;
        current = current->next;
    }
    array[tracker] = NULL;
    return array;
}

void **df_get_values(dataframe_t *dataframe, const char *column)
{
    void **array = NULL;
    int index = index_finder(dataframe, column);
    column_type_t type = UNDEFINED;

    if (index < 0 || dataframe->nb_rows == 0)
        return NULL;
    array = type_finder(dataframe, index, &type);
    array = array_filler(index, dataframe, array, type);
    return array;
}
