/*
** EPITECH PROJECT, 2024
** Cuddle
** File description:
** get_element.c
*/

#include "dataframe.h"
#include "my.h"
#include <string.h>
#include <stdlib.h>

element_t get_b_element(char *token)
{
    element_t new_element;
    char *token_cpy = strdup(token);

    strlower(token_cpy);
    new_element.b = (!strcmp(token_cpy, "true")) ? true : false;
    free(token_cpy);
    return new_element;
}

element_t get_i_element(char *token)
{
    element_t new_element;

    new_element.i = atoi(token);
    return new_element;
}

element_t get_ui_element(char *token)
{
    element_t new_element;

    new_element.ui = atoi(token);
    return new_element;
}

element_t get_f_element(char *token)
{
    element_t new_element;

    new_element.f = atof(token);
    return new_element;
}

element_t get_s_element(char *token)
{
    element_t new_element;

    new_element.s = strdup(token);
    return new_element;
}
