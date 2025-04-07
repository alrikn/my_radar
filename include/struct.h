/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** struct
*/

#ifndef INCLUDED_STRUCT_H
    #define INCLUDED_STRUCT_H
    #include <SFML/Audio/Types.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Sprite.h>
    #include <SFML/Graphics/CircleShape.h>
    #include <SFML/Graphics/RectangleShape.h>
    #include <SFML/System/Vector2.h>
    #include <SFML/Window/Event.h>
    #include <SFML/System/Vector2.h>
    #include <stdbool.h>
    #include <SFML/Audio/Music.h>

typedef struct tower {
    sfVector2f position;
    long int num;
    long double radius;
    sfSprite *sprite;
    sfCircleShape *circle;
    struct tower *next;
    struct tower *prev;
} tow_t;

typedef struct rectangle {
    sfVector2f top_left;
    long long int num;
    sfVector2f dimensions;
    sfRectangleShape *rectangle;
    struct rectangle *next;
    struct rectangle *prev;
} rect_t;

typedef struct temp_tower {
    sfVector2f position;
    long int num;
    long double radius;
    sfSprite *sprite;
} temp_tow_t;

typedef struct airplane {
    bool collision_exempt;
    bool visible_exempt;
    sfVector2f position;
    double distance;
    long int num;
    long int delay;
    long int final_x_pos;
    long int final_y_pos;
    long int speed;
    sfRectangleShape *square;
    sfSprite *sprite;
    struct airplane *next;
    struct airplane *prev;
} air_t;


typedef struct temp_airplane {
    bool exempt;
    sfVector2f position;
    long int num;
    long int delay;
    long int final_x_pos;
    long int final_y_pos;
    long int speed;
    sfSprite *sprite;
} temp_air_t;

typedef struct status {
    bool game_over;
    bool game_crash;
    bool disable_hitboxes;
    bool invisible_sprites;
}status_t;

typedef struct lag {
    sfClock *refresh_clock;
    sfClock *global_clock;
    sfClock *tick_clock;
    int frame;
}lag_t;

typedef struct background {
    sfSprite *back_sp;
}back_t;

typedef struct bucket bucket_t;

typedef struct bucket {
    sfVector2f top_left;
    sfVector2f dimensions;
    bucket_t **children;
    air_t **planes;
    sfRectangleShape *rectangle;
} bucket_t;

typedef struct core {
    sfRenderWindow *window;
    sfVideoMode mode;
    lag_t time;
    status_t status;
    air_t *head;
    tow_t *head_tow;
    temp_air_t temp_air;
    temp_tow_t temp_tow;
    back_t background;
    rect_t *head_rec;
    sfText *text;
    long int air_num;
    long long int num_rec;
    unsigned long int tower_num;
}core_t;
#endif
