/*
** EPITECH PROJECT, 2024
** Cuddle
** File description:
** main.c
*/

#include <stdio.h>
#include <string.h>
#include "dataframe.h"
#include "my.h"

int main(void)
{
    column_type_t type = get_column_type("test.csv", 1, strdup(","));

    printf("Column type: %d\n", type);
    return 0;
}
