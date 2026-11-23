/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** linked_list_rectangle
*/

#include "my.h"
#include "struct.h"
#include <CSFML/Graphics/RectangleShape.h>

/*
** NULL-terminated doubly linked list (not circular).
*/
static rect_t *create_node(core_t *fm, bucket_t *buc)
{
    rect_t *new = malloc(sizeof(rect_t));
    sfRectangleShape *rectangle = sfRectangleShape_create();

    if (!new || !rectangle || !buc) {
        free(new);
        if (rectangle)
            sfRectangleShape_destroy(rectangle);
        return NULL;
    }
    sfRectangleShape_setSize(rectangle, buc->dimensions);
    sfRectangleShape_setFillColor(rectangle, sfTransparent);
    sfRectangleShape_setPosition(rectangle, buc->top_left);
    sfRectangleShape_setOutlineColor(rectangle, sfRed);
    sfRectangleShape_setOutlineThickness(rectangle, 2.1);
    new->rectangle = rectangle;
    fm->num_rec++;
    new->num = fm->num_rec;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

void add_to_list_rec(rect_t **head, core_t *fm, bucket_t *buc)
{
    rect_t *new = create_node(fm, buc);
    rect_t *last = *head;

    if (!new)
        return;
    if (*head == NULL) {
        *head = new;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new;
    new->prev = last;
}

static void free_helper(rect_t *chosen_one)
{
    sfRectangleShape_destroy(chosen_one->rectangle);
    free(chosen_one);
}

int delete_node_rec(rect_t **head, long int num)
{
    rect_t *to_delete = *head;

    while (to_delete != NULL && to_delete->num != num)
        to_delete = to_delete->next;
    if (to_delete == NULL)
        return 84;
    if (to_delete->prev)
        to_delete->prev->next = to_delete->next;
    else
        *head = to_delete->next;
    if (to_delete->next)
        to_delete->next->prev = to_delete->prev;
    free_helper(to_delete);
    return 0;
}

void free_list_rectangle(rect_t *head, core_t *fm)
{
    rect_t *next_node;

    while (head != NULL) {
        next_node = head->next;
        free_helper(head);
        head = next_node;
    }
    fm->head_rec = NULL;
    fm->num_rec = 0;
}

void draw_rectangle_list(rect_t *head, sfRenderWindow *window)
{
    for (rect_t *current = head; current != NULL; current = current->next)
        sfRenderWindow_drawRectangleShape(window, current->rectangle, NULL);
}
