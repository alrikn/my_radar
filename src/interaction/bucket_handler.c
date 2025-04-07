/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** bucket_handler
*/

#include "my.h"
#include "struct.h"
#include <SFML/System/Vector2.h>
#include <math.h>
#include <stdbool.h>

static sfVector2f make_new_dimensions(bucket_t *self, core_t *fm)
{
    sfVector2f size;

    size.x = self->dimensions.x / 2;
    size.y = self->dimensions.y / 2;
    return size;
}

bool is_plane_in_rectangle(air_t *plane, bucket_t *bucket)
{
    sfVector2f top_left = bucket->top_left;
    sfVector2f bottom_right = {
        top_left.x + bucket->dimensions.x,
        top_left.y + bucket->dimensions.y
    };

    if (plane == NULL || plane->sprite == NULL) {
        return false;
    }
    if (plane->collision_exempt == true) {
        return false;
    }
    return (plane->position.x >= top_left.x &&
    plane->position.x <= bottom_right.x &&
    plane->position.y >= top_left.y &&
    plane->position.y <= bottom_right.y);
}

static sfVector2f make_new_top_left(core_t *fm, bucket_t *self, int num)
{
    sfVector2f new_top_left = self->top_left;

    if (num == 0) {
        return self->top_left;
    }
    if (num == 1) {
        new_top_left.x += self->dimensions.x / 2;
        return new_top_left;
    }
    if (num == 2) {
        new_top_left.y += self->dimensions.y / 2;
        return new_top_left;
    }
    new_top_left.y += self->dimensions.y / 2;
    new_top_left.x += self->dimensions.x / 2;
    return new_top_left;
}

static air_t **filter_planes(core_t *fm, air_t **planes, bucket_t *new_bucket)
{
    int count = 0;
    air_t **filtered_planes = NULL;

    for (int i = 0; planes[i] != NULL; i++) {
        if (is_plane_in_rectangle(planes[i], new_bucket))
            count++;
    }
    filtered_planes = malloc((count + 1) * sizeof(air_t *));
    if (!filtered_planes)
        return NULL;
    count = 0;
    for (int i = 0; planes[i] != NULL; i++) {
        if (is_plane_in_rectangle(planes[i], new_bucket)) {
            filtered_planes[count] = planes[i];
            count++;
        }
    }
    filtered_planes[count] = NULL;
    return filtered_planes;
}

void planes_collide(core_t *fm, air_t **planes, long int i, long int j)
{
    double dx = 0.0;
    double dy = 0.0;
    double distance = 0;

    if (!planes[i] || !planes[j] || !fm->head || (planes[i] == planes[j]))
        return;
    if (planes[i]->collision_exempt == false && !planes[j]->collision_exempt) {
        dx = planes[i]->position.x - planes[j]->position.x;
        dy = planes[i]->position.y - planes[j]->position.y;
        distance = sqrt(dx * dx + dy * dy);
        if (distance <= COLLISION_THRESHOLD) {
            delete_node_air(&fm->head, planes[i]->num);
            planes[i] = NULL;
            delete_node_air(&fm->head, planes[j]->num);
            planes[j] = NULL;
            my_cooler_putstr("2 planes just collided \n");
        }
    }
}

//int delete_node_air(air_t **head, long int num);
void check_collision(core_t *fm, air_t **planes, int num_planes)
{
    for (int i = 0; i < num_planes; i++) {
        if (!planes[i])
            continue;
        for (int j = 0; j < num_planes; j++) {
            planes_collide(fm, planes, i, j);
        }
    }
}

void remove_offending(core_t *fm, air_t **planes, bucket_t *self, int num)
{
    check_collision(fm, planes, num);
    free(planes);
    free(self);
}

//self->children[a] = new_bucket;
//add_to_list_rec(&fm->head_rec, fm, new_bucket);
void division(core_t *fm, air_t **planes, bucket_t *self)
{
    int num_planes = 0;
    bucket_t *new_bucket = NULL;
    air_t **filtered_planes = NULL;

    while (planes[num_planes] != NULL)
        num_planes++;
    if (num_planes <= BUCKET_LIMIT)
        return remove_offending(fm, planes, self, num_planes);
    for (int i = 0; i < MAX_BUCKET_SIZE; i++) {
        new_bucket = malloc(sizeof *new_bucket);
        new_bucket->dimensions = make_new_dimensions(self, fm);
        new_bucket->top_left = make_new_top_left(fm, self, i);
        filtered_planes = filter_planes(fm, planes, new_bucket);
        division(fm, filtered_planes, new_bucket);
    }
    free(self);
    free(planes);
}
