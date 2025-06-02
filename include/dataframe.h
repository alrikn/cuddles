/*
** EPITECH PROJECT, 2024
** cuddle
** File description:
** AAAHHHH
*/


#ifndef INCLUDED_DATA_H
    #define INCLUDED_DATA_H
    #define DEFAULT_SEPARATOR ","
    #include <stdbool.h>
    #include <stdio.h>

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED // only used internally before the type is determined
} column_type_t;

typedef union element_u {
    bool b;
    unsigned int ui;
    int i;
    float f;
    char *s;
} element_t;

/*
 ** element_t *type is malloced and if there is a str inside the str is malloc
 ** non circular
 ** type is an array that tells us what is inside the union array
*/

typedef struct row_s {
    struct row_s *prev;
    struct row_s *next;
    column_type_t *type;
    element_t *row_data;
} row_t;

typedef struct col_s {
    struct col_s *next;
    char *name;
    column_type_t type;
} col_t;

typedef struct dataframe_s {
    int nb_rows;
    int nb_columns;
    char *separator;
    col_t *column;
    row_t *head;
    row_t *tail;
} dataframe_t;

typedef struct dataframe_shape_s {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

/* core */

dataframe_t *df_read_csv(const char *filename,
    const char *separator); //done (tested)
int df_write_csv(dataframe_t *dataframe, const char *filename); //done (tested)

/* basic */

dataframe_shape_t df_shape(dataframe_t *dataframe); //done (tested)
void df_info(dataframe_t *dataframe); //done (tested)
dataframe_t *df_head(dataframe_t *dataframe, int nb_rows); // done (tested)
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows); //done (tested)
void df_describe(dataframe_t *dataframe); //done (untested)

/* filter */

dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value)); //done (tested)

/* sort */

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2)); //done (tested)

/* transform */

dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value)); //done (tested)
dataframe_t *df_to_type(dataframe_t *dataframe, const char *column,
    column_type_t downcast);

/* aggregate */

dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate,
    void *(*agg_func)(void **values, int nb_values));

/* cuddle util */

void *df_get_value(dataframe_t *dataframe,
    int row, const char *column); // done (untested)
void **df_get_values(dataframe_t *dataframe, const char *column);
    //done (tested)
void **df_get_unique_values(dataframe_t *dataframe,
    const char *column);
void df_free(dataframe_t *dataframe); //done (tested)


#endif
