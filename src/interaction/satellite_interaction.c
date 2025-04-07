/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** visible_handler
*/

#include "my.h"
#include <SFML/System/Vector2.h>
#include <math.h>
#include <stdbool.h>

bool plane_touches_tower(core_t *fm, air_t *air, tow_t *tower)
{
    sfVector2f size = {20, 20};
    sfVector2f corners[4] = {
        {air->position.x - size.x / 2, air->position.y - size.y / 2},
        {air->position.x + size.x / 2, air->position.y - size.y / 2},
        {air->position.x - size.x / 2, air->position.y + size.y / 2},
        {air->position.x + size.x / 2, air->position.y + size.y / 2}
    };
    float dx;
    float dy;
    float distance;

    for (int i = 0; i < 4; i++) {
        dx = corners[i].x - tower->position.x;
        dy = corners[i].y - tower->position.y;
        distance = sqrt(dx * dx + dy * dy);
        if (distance <= tower->radius)
            return true;
    }
    return false;
}

void handle_interaction(core_t *fm, air_t *air, tow_t *tow, bool *collided)
{
    if (!air || !tow)
        return;
    if (air->visible_exempt)
        return;
    if (plane_touches_tower(fm, air, tow)) {
        *collided = true;
    }
}

void tower_plane_interaction(core_t *fm)
{
    bool collided = false;
    air_t *current = fm->head;
    tow_t *current_tow;

    if (!fm->head || !fm->head_tow)
        return;
    do {
        collided = false;
        current_tow = fm->head_tow;
        do {
            handle_interaction(fm, current, current_tow, &collided);
            current_tow = current_tow->next;
        } while (current_tow != fm->head_tow);
        if (collided)
            current->collision_exempt = true;
        else
            current->collision_exempt = false;
        current = current->next;
    } while (current != fm->head);
}
