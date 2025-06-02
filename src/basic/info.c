/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** info
*/

#include "dataframe.h"
#include <stdio.h>

static void handle_specific(column_type_t type)
{
    if (type == BOOL)
        printf("bool\n");
    if (type == INT)
        printf("int\n");
    if (type == UINT)
        printf("unsigned int\n");
    if (type == FLOAT)
        printf("float\n");
    if (type == STRING)
        printf("string\n");
    if (type == UNDEFINED)
        printf("undefined\n");
}

void df_info(dataframe_t *dataframe)
{
    col_t *current = NULL;

    if (!dataframe)
        return;
    printf("%d columns:\n", dataframe->nb_columns);
    current = dataframe->column;
    while (current) {
        printf("- %s: ", current->name);
        handle_specific(current->type);
        current = current->next;
    }
    return;
}
