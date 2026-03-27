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

/*
//this is a circular linked list btw.


for some reason:

==239388== Invalid read of size 8
==239388==    at 0x49859E9: sfSprite_getTexture (in /usr/lib/x86_64-linux-gnu/libcsfml-graphics.so.2.6.0)
==239388==    by 0x10D774: destroy_everything (memory_handling.c:22)
==239388==    by 0x10AC20: main (main.c:99)
==239388==  Address 0x189685e0 is 288 bytes inside a block of size 368 free'd
==239388==    at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==239388==    by 0x10D7A7: destroy_everything (memory_handling.c:26)
==239388==    by 0x10AC20: main (main.c:99)


*/
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
        sfSprite_destroy(current->sprite);
        current = current->next;
    } while (current != head_ref);
    sfText_destroy(fm->text);
    texture_sp = (sfTexture *)sfSprite_getTexture(fm->background.back_sp);
    sfTexture_destroy(texture_sp);
    sfSprite_destroy(fm->background.back_sp);
}
