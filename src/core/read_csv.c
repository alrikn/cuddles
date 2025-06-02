/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** read_csv
*/

#include "dataframe.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const element_fn_t element_getter_fn_map[UNDEFINED] = {
    [BOOL] = get_b_element,
    [INT] = get_i_element,
    [UINT] = get_ui_element,
    [FLOAT] = get_f_element,
    [STRING] = get_s_element,
};

static col_t *append_col(col_t *root, col_t *new_col)
{
    col_t *current = root;

    if (root == NULL)
        return new_col;
    while (current->next)
        current = current->next;
    current->next = new_col;
    return root;
}

static col_t *make_col(char *separator, char *col_title,
    int col_num, FILE *csv)
{
    col_t *current = malloc(sizeof(col_t));

    current->name = strdup(col_title);
    current->type = get_column_type(csv, col_num, separator);
    current->next = NULL;
    return current;
}

static col_t *df_create_cols(FILE *csv_file, char *separator)
{
    col_t *root = NULL;
    char *line = 0;
    char *cpy = NULL;
    char *token;
    size_t n;

    getline(&line, &n, csv_file);
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = 0;
    cpy = line;
    token = strsep(&cpy, separator);
    for (int i = 1; token; i++) {
        root = append_col(root, make_col(separator, token, i, csv_file));
        token = strsep(&cpy, separator);
    }
    free(line);
    return root;
}

static int col_count(col_t *root)
{
    int count = 0;

    while (root) {
        root = root->next;
        count++;
    }
    return count;
}

static void add_row(dataframe_t *frame, char *line, column_type_t *types,
    char *separator)
{
    row_t *new_row = malloc(sizeof(row_t));

    new_row->row_data = malloc(sizeof(element_t) * frame->nb_columns);
    new_row->type = types;
    new_row->next = NULL;
    for (int i = 0; i < frame->nb_columns; i++)
        new_row->row_data[i] = element_getter_fn_map[types[i]](strsep(&line,
            separator));
    frame->nb_rows++;
    if (!frame->head) {
        frame->head = new_row;
        frame->tail = new_row;
        new_row->prev = NULL;
        return;
    }
    frame->tail->next = new_row;
    new_row->prev = frame->tail;
    frame->tail = new_row;
}

static column_type_t *make_types_array(dataframe_t *frame)
{
    col_t *current = frame->column;
    column_type_t *type_array = malloc(sizeof(column_type_t)
        * frame->nb_columns);

    for (int i = 0; i < frame->nb_columns; i++) {
        type_array[i] = current->type;
        current = current->next;
    }
    return type_array;
}

void make_rows(FILE *csv_file, dataframe_t *frame)
{
    column_type_t *types = make_types_array(frame);
    char *line = 0;
    char *cpy = NULL;
    size_t n;

    frame->head = NULL;
    frame->tail = NULL;
    fseek(csv_file, 0, SEEK_SET);
    getline(&line, &n, csv_file);
    while (getline(&line, &n, csv_file) != -1) {
        if (line[0] == '\n')
            break;
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = 0;
        cpy = line;
        add_row(frame, cpy, types, frame->separator);
    }
    free(line);
    return;
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    dataframe_t *new_frame = malloc(sizeof(dataframe_t));
    FILE *csv_file = fopen(filename, "r");
    char *new_separator;

    if (!csv_file) {
        free(new_frame);
        return NULL;
    }
    if (!separator)
        new_separator = strdup(",");
    else
        new_separator = strdup(separator);
    new_frame->separator = new_separator;
    new_frame->column = df_create_cols(csv_file, new_separator);
    new_frame->nb_columns = col_count(new_frame->column);
    new_frame->nb_rows = 0;
    make_rows(csv_file, new_frame);
    fclose(csv_file);
    return new_frame;
}
