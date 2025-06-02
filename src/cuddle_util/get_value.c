/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** get_value
*/

#include "dataframe.h"
#include "my.h"
#include <stdio.h>
#include <string.h>

int static index_finder_stat(dataframe_t *frame, int row, const char *column)
{
    int index = 0;
    col_t *current = frame->column;

    if (!frame || row < 0 || row > frame->nb_rows - 1 || !column)
        return -84;
    while (current && strcmp(column, current->name) != 0) {
        index++;
        current = current->next;
    }
    if (!current)
        return -84;
    return index;
}

void *allocate_element(element_t *element, column_type_t type)
{
    size_t element_sizes[STRING] = {sizeof(bool), sizeof(int),
        sizeof(unsigned int), sizeof(float)};
    void *value;

    if (type == STRING)
        return strdup(element->s);
    value = malloc(element_sizes[type]);
    memcpy(value, element, element_sizes[type]);
    return value;
}

/*
 ** i just return the value without verify what it is cus i don't need to
*/
void *df_get_value(dataframe_t *dataframe, int row, const char *column)
{
    int index = index_finder_stat(dataframe, row, column);
    row_t *current = NULL;
    int tracker = 0;

    if (!column || index < 0)
        return NULL;
    current = dataframe->head;
    while (current && tracker < row) {
        tracker++;
        current = current->next;
    }
    if (!current)
        return NULL;
    return allocate_element(&current->row_data[index], current->type[index]);
}
