/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** aggregation
*/

#include "my.h"

dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate, void *(*agg_func)(void **values, int nb_values))
{
    return dataframe;
}
