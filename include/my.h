/*
** EPITECH PROJECT, 2024
** fake_my_hunter
** File description:
** my
*/

#ifndef INCLUDED_MY_H
    #define INCLUDED_MY_H
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <string.h>
    #include <string.h>
    #include <sys/types.h>
    #include <time.h>
    #include <sys/wait.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include "dataframe.h"

    #define PATH "/etc/passwd"
    #define MAX_PATH_LEN 64
    #define MAX_LOOP_INPUT 2048

char *num_to_str(int num);
int num_len(int nb);
char *my_revstr(char *str);
int my_cooler_putstr(char const *str);
char *my_strcat(char *dest, char const *str);
char *my_strcpy(char *dest, char const *src);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
char *my_move_to_char(const char *str, int c);
char *my_strncpy(char *dest, char const *src, int n);
int my_strlen(char const *str);
int my_str_to_int(const char *str);
int my_strcmp(const char *str1, const char *str2);
char *my_strdup(char const *src);
char *my_get_time(void);
double my_str_to_float(const char *str, char **endptr);
char *my_strtok(char *str, const char *delim);
char *my_int_to_str(long int num);
int ascci_to_sum(const char *str);
char **my_str_to_word_array(char const *str);
char *last_char(const char *str, char character);
long my_put_nbr(long nb);
int argc_counter(char **array);
int print_array(char **array);
void link_to_list(row_t **head, row_t *node);
dataframe_t *frame_dup(dataframe_t *frame);
col_t *col_dup(col_t *old_col);
row_t *row_dup(row_t *old_head, int nb_col, row_t **tail);
int index_finder(dataframe_t *frame, const char *column);
column_type_t *type_dup(column_type_t *old, int nb_col);
row_t *spec_mem_handle(row_t *old, column_type_t *types, int nb_col);
typedef element_t (*element_fn_t)(char *token);
element_t get_b_element(char *token);
element_t get_i_element(char *token);
element_t get_ui_element(char *token);
element_t get_f_element(char *token);
element_t get_s_element(char *token);
void df_free(dataframe_t *dataframe);
column_type_t get_column_type(FILE *csv_file, int column,
    const char *separator);
void strlower(char *data); /* by jose bc i need in the other file */
void make_value_array_int(dataframe_t *frame, int nb_col, const char *name);
void make_value_array_float(dataframe_t *frame, int nb_col, const char *name);
void make_value_array_unsigned(dataframe_t *frame,
    int nb_col, const char *nam);
#endif
