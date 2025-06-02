/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** write_csv
*/

#include "dataframe.h"
#include "my.h"
#include <stdio.h>
#include <threads.h>

static void write_element(element_t current, column_type_t type, FILE *new_csv)
{
    char *bool_str[2] = {"false", "true"};

    switch (type) {
        case BOOL:
            fprintf(new_csv, "%s", bool_str[current.b]);
            break;
        case INT:
            fprintf(new_csv, "%d", current.i);
            break;
        case UINT:
            fprintf(new_csv, "%d", current.ui);
            break;
        case FLOAT:
            fprintf(new_csv, "%#4.2f", current.f);
            break;
        case STRING:
            fprintf(new_csv, "%s", current.s);
        case UNDEFINED:
            break;
    }
}

static void write_row(dataframe_t *dataframe, FILE *new_csv,
    row_t *current_row, bool last_line)
{
    for (int i = 0; i < dataframe->nb_columns; i++) {
        write_element(current_row->row_data[i], current_row->type[i], new_csv);
        if (i + 1 < dataframe->nb_columns)
            fprintf(new_csv, "%s", dataframe->separator);
        else
            fprintf(new_csv, "\n");
    }
}

static void write_headers(dataframe_t *dataframe, FILE *new_csv)
{
    col_t *current_col = dataframe->column;

    for (int i = 0; i < dataframe->nb_columns; i++) {
        fprintf(new_csv, "%s", current_col->name);
        if (i + 1 < dataframe->nb_columns)
            fprintf(new_csv, "%s", dataframe->separator);
        else
            fprintf(new_csv, "\n");
        current_col = current_col->next;
    }
}

int df_write_csv(dataframe_t *dataframe, const char *filename)
{
    FILE *new_csv = NULL;
    row_t *current_row = NULL;

    if (!dataframe || !filename)
        return 84;
    new_csv = fopen(filename, "w");
    if (!new_csv)
        return 84;
    current_row = dataframe->head;
    write_headers(dataframe, new_csv);
    for (int i = 0; i < dataframe->nb_rows; i++) {
        write_row(dataframe, new_csv, current_row, i + 1 < dataframe->nb_rows);
        current_row = current_row->next;
    }
    fclose(new_csv);
    return 0;
}
