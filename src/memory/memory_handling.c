/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** memory_handling
*/

#include "struct.h"
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
void destroy_everything(core_t *fm)
{
    const tow_t *head_ref = fm->head_tow;
    tow_t *current = fm->head_tow;
    sfTexture *texture_sp;

    if (head_ref == NULL)
        return;
    do {
        texture_sp = (sfTexture *)sfSprite_getTexture(current->sprite);
        if (texture_sp)
            sfTexture_destroy(texture_sp);
        current = current->next;
        sfSprite_destroy(current->sprite);
    } while (current != head_ref);
    sfText_destroy(fm->text);
    texture_sp = (sfTexture *)sfSprite_getTexture(fm->background.back_sp);
    sfTexture_destroy(texture_sp);
    sfSprite_destroy(fm->background.back_sp);
}
