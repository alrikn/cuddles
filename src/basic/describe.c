/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** describe
*/

#include "dataframe.h"
#include "my.h"
#include <math.h>
#include <stdio.h>


void check_valid_type(dataframe_t *dataframe)
{
    col_t *column = dataframe->column;
    int nb_col = 1;

    while (column) {
        if (column->type == INT)
            make_value_array_int(dataframe, nb_col, column->name);
        if (column->type == UINT)
            make_value_array_unsigned(dataframe, nb_col, column->name);
        if (column->type == FLOAT)
            make_value_array_float(dataframe, nb_col, column->name);
        column = column->next;
        nb_col++;
    }
}

void df_describe(dataframe_t *dataframe)
{
    check_valid_type(dataframe);
    return;
}
