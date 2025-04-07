/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** main
*/

#include "./include/my.h"
#include <SFML/Window/Event.h>
#include <stdbool.h>

static int explanation(void)
{
    my_cooler_putstr("[MY_RADAR]\n\t-h shows this help message\n");
    my_cooler_putstr("Air traffic simulation panel\n");
    my_cooler_putstr("USAGE: \n\t");
    my_cooler_putstr("./my_radar [OPTIONS] path_to_script\n\t");
    my_cooler_putstr("path_to_script\tThe path to the script file\n OPTION\n");
    my_cooler_putstr("\t-h\tprint the usage and quit\nUSER INTERACTIONS\n");
    my_cooler_putstr("\t'L' key\tenable/disable hitboxes and areas.\n");
    my_cooler_putstr("\t'S' key\tenable/disable sprites.\n");
    return 0;
}

static void key_pressed(core_t *fm, sfEvent *event)
{
    if (event->key.code == sfKeyL) {
        if (fm->status.disable_hitboxes == false)
            fm->status.disable_hitboxes = true;
        else
            fm->status.disable_hitboxes = false;
    }
    if (event->key.code == sfKeyS) {
        if (fm->status.invisible_sprites == false)
            fm->status.invisible_sprites = true;
        else
            fm->status.invisible_sprites = false;
    }
}

int manage_events(core_t *fm, sfEvent *event)
{
    if (fm->status.game_over == true) {
        return 1;
    }
    while (sfRenderWindow_pollEvent(fm->window, event)) {
        if (event->type == sfEvtClosed) {
            fm->status.game_over = true;
            return 1;
        }
        if (event->key.type == sfEvtKeyPressed) {
            key_pressed(fm, event);
        }
    }
    return 0;
}

int game_loop(core_t *fm, sfEvent *event, int animation_framerate)
{
    if (update_animate(fm)) {
        sfRenderWindow_clear(fm->window, sfBlack);
        sfRenderWindow_drawSprite(fm->window, fm->background.back_sp,
        NULL);
        game_handler(event, fm);
        sfRenderWindow_display(fm->window);
    }
    return 0;
}

int running(core_t *fm, sfEvent *event, int animation_framerate)
{
    int return_result = 0;

    sfRenderWindow_setFramerateLimit(fm->window, 60);
    while (sfRenderWindow_isOpen(fm->window)) {
        game_loop(fm, event, animation_framerate);
        if (manage_events(fm, event) == 1)
            return 0;
    }
    return return_result;
}

int main(int argc, char **av)
{
    core_t fm = {0};
    sfEvent event = {0};
    int is_working = 0;

    if (argc != 2)
        return 84;
    if (av[1][0] == '-' && av[1][1] == 'h' && my_strlen(av[1]) == 2)
        return explanation();
    initializer(&fm, av[1]);
    if (is_working == 84 || fm.status.game_over == true) {
        my_error_putstr("smth went wrong\n");
        return 84;
    }
    running(&fm, &event, 5);
    destroy_everything(&fm);
    if (fm.status.game_crash == true) {
        my_error_putstr("smth went wrong\n");
        return 84;
    }
    return 0;
}
