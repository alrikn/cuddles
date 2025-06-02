/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** float_handler
*/

#include "my.h"
#include <math.h>

static double print_min_max_int(float *data, int array_len,
    double *min, double *max)
{
    double sum = 0.0;

    *min = data[0];
    *max = data[0];
    for (int i = 0; i < array_len; i++) {
        sum += (double)data[i];
        if (data[i] < *min)
            *min = data[i];
        if (data[i] > *max)
            *max = data[i];
    }
    printf("Count: %d\n", array_len);
    return sum;
}

static int print_values_int(float *data, int array_len)
{
    double min = 0.0;
    double max = 0.0;
    double sum = print_min_max_int(data, array_len, &min, &max);
    double mean = 0.0;
    double std_dev = 0.0;

    mean = sum / array_len;
    for (int i = 0; i < array_len; i++) {
        std_dev += (double)pow(data[i] - mean, 2);
    }
    std_dev = sqrt(std_dev / array_len);
    printf("Mean: %.2f\n", mean);
    printf("Std: %.2f\n", std_dev);
    printf("Min: %.2f\n", min);
    printf("Max: %.2f\n", max);
    return 0;
}

void make_value_array_float(dataframe_t *frame, int nb_col, const char *name)
{
    float *array = malloc(sizeof(float) * frame->nb_rows);
    int tracker = 0;
    void *value = NULL;

    printf("Column: %s\n", name);
    while (tracker < frame->nb_rows) {
        value = df_get_value(frame, tracker, name);
        if (!value) {
            array[tracker] = 0.0;
        } else {
            array[tracker] = *(float *)value;
        }
        tracker++;
    }
    print_values_int(array, frame->nb_rows);
    free(array);
}
