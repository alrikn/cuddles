/*
** EPITECH PROJECT, 2025
** bsminishell1
** File description:
** main
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dataframe.h"
#include "my.h"

void *apply_func(void *value) {
    char *new_value = malloc(sizeof(int));
    *new_value = *(int *)value * 2;
    return new_value;
}

int main ( void ) {
    dataframe_t *dataframe = df_read_csv ( "test.csv" , NULL ) ;

    df_write_csv (dataframe , "applied.csv");
    df_info(dataframe);
    df_free(dataframe);
    return 0;
}
