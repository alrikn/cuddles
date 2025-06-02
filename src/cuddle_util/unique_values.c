/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** unique_values
*/

#include "dataframe.h"
#include "my.h"
#include <string.h>

static void *void_dup(void *to_dup, column_type_t type)
{
    void *duped_val;
    size_t array_sizes[STRING] = {sizeof(bool), sizeof(int),
        sizeof(unsigned int), sizeof(float)};

    if (type == STRING)
        return strdup(to_dup);
    duped_val = malloc(array_sizes[type]);
    memcpy(duped_val, to_dup, array_sizes[type]);
    return duped_val;
}

static int value_compare(void *first, void *second, column_type_t type)
{
    if (type == STRING)
        return !(strcmp((char *)first, (char *)second));
    if (type == BOOL)
        return *((bool *)first) == *((bool *)second);
    if (type == INT)
        return (*((int *)first) == *((int *)second));
    if (type == UINT)
        return (*((unsigned int *)first) == *((unsigned int *)second));
    if (type == FLOAT)
        return (*((float *)first) == *((float *)second));
    return 1;
}

static int find_instances(void **array, void *element, column_type_t type)
{
    int count = 0;
    int index = 0;

    while (array[index] && count < 1) {
        count += value_compare(element, array[index], type);
        index++;
    }
    return count;
}

/*
 **this makes the given array unique
*/
static void **differentiate_array(dataframe_t *frame, void **array,
    column_type_t type)
{
    void **unique_array = malloc(sizeof(void *) * (frame->nb_rows + 1));
    int index = 0;

    for (int i = 0; i < frame->nb_rows + 1; i++)
        unique_array[i] = NULL;
    for (int i = 0; array[i]; i++) {
        if (find_instances(unique_array, array[i], type) < 1) {
            unique_array[index] = void_dup(array[i], type);
            index++;
        }
    }
    unique_array[index] = NULL;
    return unique_array;
}

static void *get_element(element_t *current, column_type_t type)
{
    size_t array_sizes[STRING] = {sizeof(bool), sizeof(int),
        sizeof(unsigned int), sizeof(float)};
    void *current_value = malloc(array_sizes[type]);

    memcpy(current_value, current, array_sizes[type]);
    return current_value;
}

/*
 **this ALSO initializes the array and gives what type it is but for unique
*/
static void **type_finder(dataframe_t *frame, int index, column_type_t *type)
{
    void **array = malloc(sizeof(void *) * (frame->nb_rows + 1));

    *type = frame->head->type[index];
    return array;
}

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

void **df_get_unique_values(dataframe_t *dataframe, const char *column)
{
    void **array = NULL;
    void **unique_array = NULL;
    int index = index_finder(dataframe, column);
    int tracker = 0;
    column_type_t type = UNDEFINED;

    if (index < 0 || dataframe->nb_rows == 0)
        return NULL;
    array = type_finder(dataframe, index, &type);
    array = array_filler(index, dataframe, array, type);
    unique_array = differentiate_array(dataframe, array, type);
    while (array[tracker]) {
        free(array[tracker]);
        tracker++;
    }
    free(array);
    return (void **)unique_array;
}
