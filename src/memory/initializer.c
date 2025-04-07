/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** initializer
*/

#include "my.h"

void time_init(core_t *fm)
{
    fm->time.refresh_clock = sfClock_create();
    fm->time.global_clock = sfClock_create();
    fm->time.tick_clock = sfClock_create();
}

sfText *create_score_text(core_t *fm)
{
    sfText *text = sfText_create();
    sfVector2f position = {20, 20};
    sfFont *font = sfFont_createFromFile("assets/Xolonium-Regular.ttf");

    if (!font) {
        my_error_putstr("font failed to load\n");
        fm->status.game_crash = true;
    }
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 30);
    sfText_setFillColor(text, sfWhite);
    sfText_setString(text, "time = 0");
    sfText_setPosition(text, position);
    return text;
}

int initializer(core_t *fm, char *filename)
{
    sfVideoMode mode = {1920, 1080, 64};
    sfUint32 style = {sfClose | sfResize};

    fm->mode = mode;
    time_init(fm);
    fm->text = create_score_text(fm);
    fm->window = sfRenderWindow_create(mode, "simulator", style, 0);
    fm->background.back_sp = create_background("assets/background.png", fm);
    parse_script(filename, fm);
    return 0;
}
