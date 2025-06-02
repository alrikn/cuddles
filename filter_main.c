/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** filter_main
*/

#include "dataframe.h"
#include "my.h"

void *apply_func(void *value)
{
    int *new_value = malloc(sizeof (int));
    *new_value = *( int *) value * 2;
return new_value ;
}

int main(void)
{
    dataframe_t *dataframe = df_read_csv("test.csv" , NULL ) ;
    dataframe_t *applied = df_apply(dataframe, "age", apply_func);

    df_info(applied);
    df_write_csv(applied, "applied.csv");
    df_free(applied);
    df_free(dataframe);
    return 0;
}
