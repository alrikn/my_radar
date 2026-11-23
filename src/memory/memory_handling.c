/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** memory_handling
*/

#include "my.h"
#include <CSFML/Graphics/Font.h>
#include <CSFML/Graphics/RenderWindow.h>
#include <CSFML/Graphics/Sprite.h>
#include <CSFML/Graphics/Text.h>
#include <CSFML/Graphics/Texture.h>
#include <CSFML/Graphics/Types.h>
#include <CSFML/System/Clock.h>

/*
** sfSprite and sfText don't own their texture / font, so grab the pointer
** first, destroy the owner, then destroy the resource.
*/
static void destroy_sprite_and_texture(sfSprite *sprite)
{
    sfTexture *texture;

    if (!sprite)
        return;
    texture = (sfTexture *)sfSprite_getTexture(sprite);
    sfSprite_destroy(sprite);
    if (texture)
        sfTexture_destroy(texture);
}

static void destroy_text_and_font(sfText *text)
{
    sfFont *font;

    if (!text)
        return;
    font = (sfFont *)sfText_getFont(text);
    sfText_destroy(text);
    if (font)
        sfFont_destroy(font);
}

static void destroy_clocks(lag_t *time)
{
    if (time->refresh_clock)
        sfClock_destroy(time->refresh_clock);
    if (time->global_clock)
        sfClock_destroy(time->global_clock);
    if (time->tick_clock)
        sfClock_destroy(time->tick_clock);
}

void destroy_everything(core_t *fm)
{
    free_list(fm->head);
    fm->head = NULL;
    free_list_tower(fm->head_tow);
    fm->head_tow = NULL;
    free_list_rectangle(fm->head_rec, fm);
    destroy_text_and_font(fm->text);
    fm->text = NULL;
    destroy_sprite_and_texture(fm->background.back_sp);
    fm->background.back_sp = NULL;
    destroy_clocks(&fm->time);
    if (fm->window)
        sfRenderWindow_destroy(fm->window);
    fm->window = NULL;
}
