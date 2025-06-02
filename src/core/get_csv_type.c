/*
** EPITECH PROJECT, 2024
** Cuddle
** File description:
** get_csv_type.c
*/

#include "dataframe.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void strlower(char *data)
{
    for (int i = 0; i < strlen(data); i++) {
        if (isalpha(data[i]))
            data[i] = tolower(data[i]);
    }
}

static column_type_t determine_number(char *data, column_type_t prev_type)
{
    if (prev_type == UINT && (data[0] == '-'))
        return INT;
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == '.')
            return FLOAT;
    }
    if (prev_type == UNDEFINED && data[0] == '-')
        return INT;
    if (prev_type == UNDEFINED)
        return UINT;
    return prev_type;
}

static int is_string(char *data)
{
    for (int i = 0; i < strlen(data); i++) {
        if (!isdigit(data[i]) && data[i] != '.' && data[i] != '-')
            return 1;
    }
    if (data[0] == '.')
        return 1;
    for (int i = 1; i < strlen(data); i++) {
        if (data[i] == '.' && (!isdigit(data[i - 1]) || !isdigit(data[i + 1])))
            return 1;
        if (data[i] == '-')
            return STRING;
    }
    return 0;
}

column_type_t get_type(char *data, column_type_t prev_type)
{
    strlower(data);
    if (*data == 0 || prev_type == STRING)
        return prev_type;
    if ((prev_type == UNDEFINED || prev_type == BOOL) &&
        (!strcmp(data, "true") || !strcmp(data, "false")))
        return BOOL;
    if (is_string(data))
        return STRING;
    if (prev_type == BOOL)
        return STRING;
    return determine_number(data, prev_type);
}

column_type_t get_column_type(FILE *csv_file, int column,
    const char *separator)
{
    column_type_t type = UNDEFINED;
    char *line = 0;
    char *cpy = NULL;
    size_t n;
    char *token;

    fseek(csv_file, 0, SEEK_SET);
    getline(&line, &n, csv_file);
    while (getline(&line, &n, csv_file) != -1 && line[0] != '\n') {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = 0;
        cpy = line;
        for (int i = 0; i < column; i++) {
            token = strsep(&cpy, separator);
        }
        type = get_type(token, type);
    }
    free(line);
    return type;
}
