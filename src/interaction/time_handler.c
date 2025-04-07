/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** time_handler
*/

#include "my.h"
#include <SFML/System/Vector2.h>

bool update_animate(core_t *fm)
{
    sfTime elapsed_time = sfClock_getElapsedTime(fm->time.refresh_clock);
    long long frame = sfTime_asMilliseconds(elapsed_time);

    if (frame >= 17) {
        sfClock_destroy(fm->time.refresh_clock);
        fm->time.refresh_clock = sfClock_create();
        return true;
    } else {
        return false;
    }
}

void handle_delay(core_t *fm)
{
    air_t *current = fm->head;
    air_t *next_node;
    sfTime elapsed_time = sfClock_getElapsedTime(fm->time.global_clock);
    long long frame = sfTime_asSeconds(elapsed_time);

    if (fm->head == NULL)
        return;
    do {
        next_node = current->next;
        if (frame < current->delay) {
            current->visible_exempt = true;
            current->collision_exempt = true;
        } else {
            current->visible_exempt = false;
        }
        current = fm->head ? next_node : NULL;
    } while (current && current != fm->head);
}

static int counter(core_t *fm)
{
    long int num = 0;
    air_t *current = fm->head;

    do {
        num++;
        current = current->next;
    } while (current != fm->head);
    return num;
}

static air_t **mini_init(core_t *fm, bucket_t *buc, long int n)
{
    air_t **pla;

    buc->top_left = (sfVector2f){0.0, 0.0};
    buc->dimensions = (sfVector2f){1920, 1080};
    pla = malloc((n + 1) * sizeof(air_t *));
    if (!pla || !buc) {
        fm->status.game_crash = true;
        return NULL;
    }
    return pla;
}

static void division_handler(core_t *fm)
{
    bucket_t *bucket = malloc(sizeof(*bucket));
    air_t *current = fm->head;
    long int num = counter(fm);
    air_t **planes;

    planes = mini_init(fm, bucket, num);
    if (!planes || !bucket)
        return;
    current = fm->head;
    for (long int i = 0; i < num; i++) {
        planes[i] = current;
        current = current->next;
    }
    fm->tower_num = 0;
    planes[num] = NULL;
    division(fm, planes, bucket);
}

int tick_operations(core_t *fm)
{
    const air_t *head_ref = fm->head;

    if (head_ref == NULL) {
        fm->status.game_over = true;
        return 0;
    }
    tower_plane_interaction(fm);
    division_handler(fm);
    return 0;
}

bool tick_refresh(core_t *fm)
{
    sfTime elapsed_time = sfClock_getElapsedTime(fm->time.tick_clock);
    long long frame = sfTime_asMilliseconds(elapsed_time);

    if (frame >= 60) {
        sfClock_destroy(fm->time.tick_clock);
        fm->time.tick_clock = sfClock_create();
        tick_operations(fm);
        return true;
    } else {
        return false;
    }
}
