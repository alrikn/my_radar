/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** rev_str
*/

void my_charswap(char *a, char *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}

char *my_revstr(char *str)
{
    char *str_end = str;
    char *str_start = str;

    while (str_end[1] != '\0') {
        str_end++;
    }
    for (; str_start < str_end; str_start++) {
        my_charswap(str_start, str_end);
        str_end--;
    }
    return str;
}
