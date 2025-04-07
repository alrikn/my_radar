/*
** EPITECH PROJECT, 2024
** Header Pool Day 5
** File description:
** Header file for the tasks today
*/
#ifndef COMMON_H
    #include <unistd.h>
    #include <limits.h>
    #include <stdlib.h>
    #include "./struct.h"
    #include <stdlib.h>
    #include <stdbool.h>
    #include <fcntl.h>
    #define COMMON_H
    #define MAX_INT 2147483647
    #define MIN_INT –2147483648
    #define BUCKET_LIMIT 10
    #define COLLISION_THRESHOLD 20
    #define MAX_BUCKET_SIZE 4
    #define MAX_PARTITIONS 4
    #define UNUSED_ATTR __attribute__((unused))
void my_putchar(char);
int my_putstr(char const *);
int my_error_putstr(char const *str);
int my_strlen(char const *);
char *my_strcpy(char *, char const *);
char *my_strncpy(char *, char const *, int);
int my_strncmp(char const *, char const *, int);
int my_strcmp(char const *, char const *);
char *my_strstr(char *, char const *);
void my_charswap(char *, char *);
char *my_revstr(char *);
int my_strncmp(char const *, char const *, int);
int my_strcmp(char const *, char const *);
int my_str_isalpha(char const *);
int my_str_islower(char const *);
int my_str_isupper(char const *);
int my_str_isnum(char const *);
char *my_strcat(char *, char const *);
int my_compute_power_rec(int, int);
int my_find_prime_sup(int);
int my_getnbr(char const *);
int my_isneg(int);
int my_is_prime(int);
void do_recursive_int_extraction(int);
int my_put_nbr(int);
int my_showmem(char const *, int);
int my_showstr(char const *);
void my_sort_int_array(int *, int);
int check_to_capitalize_next(char *);
char *my_strcapitalize(char *);
int my_str_isprintable(char const *);
char *my_strlowcase(char *);
char *my_strncat(char *, char const *, int);
char *my_strupcase(char *);
void my_swap(int *, int *);
char *my_strtok(char *str, const char *delim);
double my_strtodouble(const char *ptr);
int my_cooler_putstr(char const *str);
char *my_strdup(char const *src);
char *num_to_str(int num);
sfSprite *create_background(char *filepath, core_t *fm);
void add_to_list_air(air_t **head, core_t *fm);
int parse_script(const char *filename, core_t *fm);
void position_updater(core_t *fm);
int game_handler(sfEvent *event, core_t *fm);
int delete_node_air(air_t **head, long int num);
int initializer(core_t *fm, char *filename);
void add_to_list_tower(tow_t **head, core_t *fm);
int delete_node_tower(tow_t **head, long int num);
bool update_animate(core_t *fm);
bool tick_refresh(core_t *fm);
void handle_delay(core_t *fm);
void reach_edges(air_t *airplane, core_t *fm);
void update_position(air_t *airplane);
void division(core_t *fm, air_t **planes, bucket_t *self);
void free_list_rectangle(rect_t *head, core_t *fm);
int delete_node_rec(rect_t **head, long int num);
void add_to_list_rec(rect_t **head, core_t *fm, bucket_t *buc);
void tower_plane_interaction(core_t *fm);
void free_list_tower(tow_t *head);
void destroy_everything(core_t *fm);
#endif /* COMMON_H */
