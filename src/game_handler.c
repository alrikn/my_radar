/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** game_handler
*/
#include "my.h"
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Time.h>
#include <stdbool.h>

static void handle_air_exceptions(core_t *fm, air_t *current)
{
    if (current->visible_exempt == false) {
        if (fm->status.invisible_sprites == false) {
            sfSprite_setPosition(current->sprite, current->position);
            sfRenderWindow_drawSprite(fm->window, current->sprite, NULL);
        }
        if (fm->status.disable_hitboxes == false) {
            sfRectangleShape_setPosition(current->square, current->position);
            sfRenderWindow_drawRectangleShape(fm->window,
            current->square, NULL);
        }
    }
}

void draw_air_sprites(core_t *fm)
{
    const air_t *head_ref = fm->head;
    air_t *current = fm->head;

    if (head_ref == NULL)
        return;
    do {
        handle_air_exceptions(fm, current);
        current = current->next;
    } while (current != head_ref);
}

void draw_rec_sprites(core_t *fm)
{
    const rect_t *head_ref = fm->head_rec;
    rect_t *current = fm->head_rec;

    if (head_ref == NULL)
        return;
    do {
        if (!current)
            return;
        sfRenderWindow_drawRectangleShape(fm->window,
        current->rectangle, NULL);
        current = current->next;
    } while (current != head_ref);
}

void draw_tower_sprites(core_t *fm)
{
    const tow_t *head_ref = fm->head_tow;
    tow_t *current = fm->head_tow;

    if (head_ref == NULL)
        return;
    do {
        if (fm->status.invisible_sprites == false)
            sfRenderWindow_drawSprite(fm->window, current->sprite, NULL);
        sfSprite_setPosition(current->sprite, current->position);
        if (fm->status.disable_hitboxes == false)
            sfRenderWindow_drawCircleShape(fm->window, current->circle, NULL);
        current = current->next;
    } while (current != head_ref);
}

static int score_str(core_t *fm)
{
    char *buffer = malloc(35);
    sfTime elapsed_time = sfClock_getElapsedTime(fm->time.global_clock);
    long long frame = sfTime_asSeconds(elapsed_time);

    if (!buffer) {
        my_error_putstr("did not allocate properly");
        return 84;
    }
    my_strcpy(buffer, "time : ");
    my_strcat(buffer, num_to_str(frame));
    sfText_setString(fm->text, buffer);
    sfRenderWindow_drawText(fm->window, fm->text, NULL);
    free(buffer);
    return 0;
}

int game_handler(sfEvent *event, core_t *fm)
{
    handle_delay(fm);
    position_updater(fm);
    draw_air_sprites(fm);
    draw_tower_sprites(fm);
    score_str(fm);
    tick_refresh(fm);
    return 0;
}
