/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** linked_list_tower
*/

#include "my.h"
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Color.h>
#include <SFML/System/Vector2.h>
#include "struct.h"
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>

static sfCircleShape *circles(double radius, sfVector2f pos)
{
    sfCircleShape *circle = sfCircleShape_create();

    if (!circle)
        return NULL;
    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setOrigin(circle, (sfVector2f){radius, radius});
    sfCircleShape_setFillColor(circle, sfTransparent);
    sfCircleShape_setPosition(circle, pos);
    sfCircleShape_setOutlineColor(circle, sfWhite);
    sfCircleShape_setOutlineThickness(circle, 3.1);
    return circle;
}

static tow_t *create_node(core_t *fm)
{
    tow_t *new = malloc(sizeof(tow_t));
    sfTexture *text = sfTexture_createFromFile("./assets/satellite.png", NULL);
    sfVector2u siz = sfTexture_getSize(text);
    sfVector2f scale = {1, 1};

    if (!new)
        return NULL;
    new->num = fm->air_num;
    new->position.y = fm->temp_tow.position.y;
    new->position.x = fm->temp_tow.position.x;
    new->radius = fm->temp_tow.radius;
    new->sprite = sfSprite_create();
    sfSprite_setTexture(new->sprite, text, sfTrue);
    sfSprite_setScale(new->sprite, scale);
    sfSprite_setOrigin(new->sprite, (sfVector2f){siz.x / 2.0f, siz.y / 2.0f});
    new->circle = circles(fm->temp_tow.radius, new->position);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

void add_to_list_tower(tow_t **head, core_t *fm)
{
    tow_t *new = create_node(fm);
    tow_t *last;

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

static void free_helper(tow_t *chosen_one)
{
    sfTexture *texture = (sfTexture *)sfSprite_getTexture(chosen_one->sprite);

    sfSprite_destroy(chosen_one->sprite);
    if (texture) {
        sfTexture_destroy(texture);
    }
    free(chosen_one);
    my_cooler_putstr("deleted a tower node\n");
}

static int exceptions(tow_t **head, long int num, tow_t *current)
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

static int search_del(tow_t *temp, tow_t **head, long int n, tow_t **to_del)
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

int delete_node_tower(tow_t **head, long int num)
{
    tow_t *current = *head;
    tow_t *to_delete = NULL;
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

void free_list_tower(tow_t *head)
{
    const tow_t *head_ref = head;
    tow_t *temp = head;
    tow_t *to_free;

    if (!head)
        return;
    while (temp->next != head_ref) {
        to_free = temp;
        temp = temp->next;
        free_helper(to_free);
    }
    free_helper(temp);
}
