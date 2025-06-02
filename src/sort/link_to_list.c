/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** link_to_list
*/

#include "my.h"

void link_to_list(row_t **head, row_t *node)
{
    row_t *last;

    if (!node)
        return;
    if (*head == NULL) {
        *head = node;
        node->next = node;
        node->prev = node;
        return;
    }
    last = (*head)->prev;
    last->next = node;
    node->prev = last;
    node->next = *head;
    (*head)->prev = node;
}
