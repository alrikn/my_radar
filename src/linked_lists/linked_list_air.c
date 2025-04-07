/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** linked_list
*/

#include "my.h"
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>

static sfRectangleShape *square(sfVector2f pos)
{
    sfRectangleShape *square = sfRectangleShape_create();
    sfVector2f size = {20, 20};

    if (!square)
        return NULL;
    sfRectangleShape_setSize(square, (sfVector2f){20, 20});
    sfRectangleShape_setOrigin(square,
    (sfVector2f){size.x / 2.0f, size.y / 2.0f});
    sfRectangleShape_setFillColor(square, sfTransparent);
    sfRectangleShape_setPosition(square, pos);
    sfRectangleShape_setOutlineColor(square, sfWhite);
    sfRectangleShape_setOutlineThickness(square, 3.1);
    return square;
}

static air_t *details(core_t *fm)
{
    air_t *new = malloc(sizeof(air_t));

    if (!new)
        return NULL;
    new->num = fm->air_num;
    new->delay = fm->temp_air.delay;
    new->position.y = fm->temp_air.position.y;
    new->position.x = fm->temp_air.position.x;
    new->final_x_pos = fm->temp_air.final_x_pos;
    new->final_y_pos = fm->temp_air.final_y_pos;
    new->speed = fm->temp_air.speed;
    return new;
}

static air_t *create_node(core_t *fm)
{
    air_t *new = details(fm);
    sfTexture *text = sfTexture_createFromFile("./assets/air_new.png", NULL);
    sfVector2u siz = sfTexture_getSize(text);
    sfVector2f scale = {1, 1};

    if (!new)
        return NULL;
    new->sprite = sfSprite_create();
    sfSprite_setTexture(new->sprite, text, sfTrue);
    sfSprite_setScale(new->sprite, scale);
    sfSprite_setOrigin(new->sprite, (sfVector2f){siz.x / 2.0f, siz.y / 2.0f});
    new->square = square(new->position);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

void link_to_list(air_t **head, air_t *node)
{
    air_t *last;

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

void add_to_list_air(air_t **head, core_t *fm)
{
    air_t *new = create_node(fm);
    air_t *last;

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

static void free_helper(air_t *chosen_one)
{
    sfTexture *texture = (sfTexture *)sfSprite_getTexture(chosen_one->sprite);

    sfSprite_destroy(chosen_one->sprite);
    if (texture) {
        sfTexture_destroy(texture);
    }
    free(chosen_one);
    my_cooler_putstr("deleted a plane node\n");
}

static int exceptions(air_t **head, long int num, air_t *current)
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

static int search_del(air_t *temp, air_t **head, long int n, air_t **to_del)
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

int delete_node_air(air_t **head, long int num)
{
    air_t *current = *head;
    air_t *to_delete = NULL;
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
    to_delete = NULL;
    return 0;
}

void free_list(air_t *head)
{
    const air_t *head_ref = head;
    air_t *temp = head;
    air_t *to_free;

    if (!head)
        return;
    while (temp->next != head_ref) {
        to_free = temp;
        sfSprite_destroy(to_free->sprite);
        temp = temp->next;
        free(to_free);
    }
    free_helper(temp);
}
/*
int main(void)
{
    air_t *head = NULL;

    add_to_list_air(&head, 5, 'E', ("test5"));
    add_to_list_air(&head, 1, 'A', ("test1"));
    add_to_list_air(&head, 2, 'B', ("test2"));
    add_to_list_air(&head, 4, 'D', ("test4"));
    add_to_list_air(&head, 3, 'C', ("test3"));
    delete_node_air(&head, 2);
    print_list(head);
    return 0;
}
*/
