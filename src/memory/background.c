/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** background
*/

#include "my.h"

sfSprite *sprite_texture_add(char *filepath, core_t *fm)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(filepath, NULL);

    if (!texture) {
        return NULL;
    }
    sfSprite_setTexture(sprite, texture, sfTrue);
    return sprite;
}

sfSprite *create_background(char *filepath, core_t *fm)
{
    sfSprite *background = sprite_texture_add(filepath, fm);
    sfVector2u window_size = sfRenderWindow_getSize(fm->window);
    sfVector2u texr_s = sfTexture_getSize(sfSprite_getTexture(background));
    sfVector2f scale = {
        (float)window_size.x / texr_s.x,
        (float)window_size.y / texr_s.y
    };

    sfSprite_setScale(background, scale);
    return background;
}
