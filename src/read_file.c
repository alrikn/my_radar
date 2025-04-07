/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** read_file
*/


#include "my.h"
#include <stdio.h>

static void airplane_check(core_t *fm, int field_count, char *token)
{
    switch (field_count) {
        case 1:
            fm->temp_air.position.x = my_strtodouble(token);
            break;
        case 2:
            fm->temp_air.position.y = my_strtodouble(token);
            break;
        case 3:
            fm->temp_air.final_x_pos = my_strtodouble(token);
            break;
        case 4:
            fm->temp_air.final_y_pos = my_strtodouble(token);
            break;
        case 5:
            fm->temp_air.speed = my_strtodouble(token);
            break;
        case 6:
            fm->temp_air.delay = my_strtodouble(token);
            break;
    }
}

static int airplane_maker(core_t *fm, char *line)
{
    int field_count = 0;
    char *token;

    token = my_strtok(line, " ");
    while (token != NULL) {
        field_count++;
        token = my_strtok(NULL, " ");
        airplane_check(fm, field_count, token);
    }
    if (field_count != 7) {
        my_error_putstr("Invalid air arguments\n");
        fm->status.game_crash = true;
        return 84;
    }
    fm->air_num++;
    fm->temp_air.num = fm->air_num;
    add_to_list_air(&fm->head, fm);
    my_cooler_putstr("Just added an airplane\n");
    return 0;
}

static void tower_check(core_t *fm, int field_count, char *token)
{
    switch (field_count) {
        case 1:
            fm->temp_tow.position.x = my_strtodouble(token);
            break;
        case 2:
            fm->temp_tow.position.y = my_strtodouble(token);
            break;
        case 3:
            fm->temp_tow.radius = my_strtodouble(token);
            break;
    }
}

static int tower_maker(core_t *fm, char *line)
{
    int field_count = 0;
    char *token;

    token = my_strtok(line, " ");
    while (token != NULL) {
        field_count++;
        token = my_strtok(NULL, " ");
        tower_check(fm, field_count, token);
    }
    if (field_count != 4) {
        my_error_putstr("Invalid tower arguments\n");
        fm->status.game_crash = true;
        return 84;
    }
    fm->tower_num++;
    fm->temp_tow.num = fm->tower_num;
    add_to_list_tower(&fm->head_tow, fm);
    my_cooler_putstr("Just added a tower\n");
    return 0;
}

int types(char type, core_t *fm, char *line)
{
    if (type == 'A')
        airplane_maker(fm, line);
    if (type == 'T')
        tower_maker(fm, line);
    return 0;
}

static int loop(FILE *file, char *line, core_t *fm)
{
    size_t line_len = 0;
    char type;
    ssize_t bytes_read;

    bytes_read = getline(&line, &line_len, file);
    while (bytes_read != -1) {
        if (line[0] == '#' || line[0] == '\n')
            continue;
        type = line[0];
        if (type != 'A' && type != 'T') {
            my_error_putstr("Invalid line: ");
            my_error_putstr(line);
            free(line);
            fclose(file);
            return 84;
        }
        types(type, fm, line);
        bytes_read = getline(&line, &line_len, file);
    }
    return 0;
}

int parse_script(const char *filename, core_t *fm)
{
    FILE *file = fopen(filename, "r");
    char *line = NULL;

    if (file == NULL) {
        my_error_putstr("Could not open file\n");
        return 84;
    }
    if (loop(file, line, fm) == 84)
        return 84;
    if (line)
        free(line);
    fclose(file);
    return 0;
}
