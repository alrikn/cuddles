/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** dataframe_free
*/

#include "dataframe.h"
#include "my.h"

static void free_row_data(element_t *row_data, column_type_t *type, int nb_col)
{
    int index = 0;

    while (index < nb_col) {
        if (type[index] == STRING)
            free(row_data[index].s);
        index++;
    }
    free(row_data);
}

void free_row(row_t *head, int nb_col)
{
    row_t *current = head;
    row_t *temp = NULL;

    while (current) {
        temp = current;
        current = current->next;
        free_row_data(temp->row_data, temp->type, nb_col);
        free(temp);
    }
}

void free_col(col_t *head)
{
    col_t *current = head;
    col_t *temp;

    while (current) {
        temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }
}

void df_free(dataframe_t *dataframe)
{
    column_type_t *array = NULL;

    if (!dataframe || dataframe->nb_columns <= 0) {
        return;
    }
    if (dataframe->nb_rows > 0) {
        array = dataframe->head->type;
        free_row(dataframe->head, dataframe->nb_columns);
        free(array);
    }
    free_col(dataframe->column);
    free(dataframe->separator);
    free(dataframe);
    dataframe = NULL;
    return;
}
