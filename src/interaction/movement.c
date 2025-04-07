/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** movement
*/

#include "my.h"
#include <math.h>
#include <stdbool.h>

void reach_edges(air_t *airplane, core_t *fm)
{
    if (airplane->position.x >= fm->mode.width) {
        my_cooler_putstr("reached edge right side\n");
        airplane->position.x = 0;
    }
    if (airplane->position.x < 0) {
        my_cooler_putstr("reached edge left side\n");
        airplane->position.x = fm->mode.width;
    }
    if (airplane->position.y >= fm->mode.height) {
        my_cooler_putstr("reached edge bottom side\n");
        airplane->position.y = 0;
    }
    if (airplane->position.y < 0) {
        my_cooler_putstr("reached edge top side\n");
        airplane->position.y = fm->mode.height;
    }
}

void update_position(air_t *airplane)
{
    int dx = airplane->final_x_pos - airplane->position.x;
    int dy = airplane->final_y_pos - airplane->position.y;
    double angle = atan2(dy, dx) * (180.0 / M_PI) + 90;
    double distance = sqrt(dx * dx + dy * dy);
    double unit_dx;
    double unit_dy;

    if (distance <= airplane->speed) {
        airplane->position.x = airplane->final_x_pos;
        airplane->position.y = airplane->final_y_pos;
        return;
    }
    unit_dx = dx / distance;
    unit_dy = dy / distance;
    airplane->position.x += (unit_dx * airplane->speed) / 55;
    airplane->position.y += (unit_dy * airplane->speed) / 55;
    sfSprite_setRotation(airplane->sprite, angle);
}

int reach_destination(core_t *fm, air_t *air)
{
    if (air->final_x_pos == air->position.x &&
    air->final_y_pos == air->position.y) {
        my_cooler_putstr("one airplane has reached its destination\n");
        delete_node_air(&fm->head, air->num);
        return 0;
    }
    return 1;
}

void destination_checker(core_t *fm, air_t *current, air_t *next_node)
{
    if (reach_destination(fm, current) == 0) {
            if (current == fm->head) {
                fm->head = next_node == current ? NULL : next_node;
            }
        }
}

void position_updater(core_t *fm)
{
    air_t *current = fm->head;
    air_t *next_node;

    if (fm->head == NULL)
        return;
    do {
        next_node = current->next;
        reach_edges(current, fm);
        if (current->visible_exempt == false)
            update_position(current);
        destination_checker(fm, current, next_node);
        current = fm->head ? next_node : NULL;
    } while (current && current != fm->head);
}
