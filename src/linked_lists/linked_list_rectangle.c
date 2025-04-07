/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** linked_list_rectangle
*/

#include "./include/my.h"
#include "include/struct.h"
#include <SFML/Graphics/RectangleShape.h>

static rect_t *create_node(core_t *fm, bucket_t *buc)
{
    rect_t *new = malloc(sizeof(rect_t));
    sfRectangleShape *rectangle = sfRectangleShape_create();

    if (!rectangle || !buc)
        return NULL;
    sfRectangleShape_setSize(rectangle, buc->dimensions);
    sfRectangleShape_setFillColor(rectangle, sfTransparent);
    sfRectangleShape_setPosition(rectangle, buc->top_left);
    sfRectangleShape_setOutlineColor(rectangle, sfWhite);
    sfRectangleShape_setOutlineThickness(rectangle, 2.1);
    new->rectangle = rectangle;
    fm->num_rec++;
    new->num = fm->num_rec;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

static void link_to_list_rec(rect_t **head, rect_t *node)
{
    rect_t *last;

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

void add_to_list_rec(rect_t **head, core_t *fm, bucket_t *buc)
{
    rect_t *new = create_node(fm, buc);
    rect_t *last;

    if (!new)
        return;
    if (*head == NULL) {
        *head = new;
        new->next = new;
        new->prev = new;
        return;
    }
    last = (*head)->prev;
    last->next = new;
    new->prev = last;
    new->next = *head;
    (*head)->prev = new;
}

static void free_helper(rect_t *chosen_one)
{
    sfRectangleShape_destroy(chosen_one->rectangle);
    free(chosen_one);
    chosen_one = NULL;
}

static int exceptions(rect_t **head, long int num, rect_t *current)
{
    if (*head == NULL)
        return 84;
    if (current->next == *head) {
        if (current->num == num) {
            free_helper(current);
            *head = NULL;
            return 0;
        }
        return 84;
    }
    return 1;
}

static int search_del(rect_t *temp, rect_t **head, long int n, rect_t **to_del)
{
    do {
        if (temp->num == n) {
            *to_del = temp;
            break;
        }
        temp = temp->next;
    } while (temp != *head);
    return 0;
}

int delete_node_rec(rect_t **head, long int num)
{
    rect_t *current = *head;
    rect_t *to_delete = NULL;
    int return_value = 0;

    return_value = exceptions(head, num, current);
    if (return_value == 84)
        return 84;
    if (return_value == 0)
        return 0;
    search_del(current, head, num, &to_delete);
    if (to_delete == NULL)
        return 84;
    if (to_delete == *head)
        *head = to_delete->next;
    to_delete->prev->next = to_delete->next;
    to_delete->next->prev = to_delete->prev;
    free_helper(to_delete);
    return 0;
}

void free_list_rectangle(rect_t *head, core_t *fm)
{
    rect_t *temp = head;
    rect_t *next_node;

    if (!head)
        return;
    do {
        next_node = temp->next;
        delete_node_rec(&temp, temp->num);
        temp = next_node;
    } while (temp != head);
    fm->head_rec = NULL;
}

