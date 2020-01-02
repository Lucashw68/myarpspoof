/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** convert.c
*/

#include "core.h"

int hexa_str_to_decimal(char *str)
{
    int len = strlen(str);
    int base = 1;
    int value = 0;

    for (int i = (len - 1); i >= 0; i--) {
        if (str[i] >= '0' && str[i] <= '9') {
            value += (str[i] - 48) * base;
            base = base * 16;
        } else if (str[i] >= 'a' && str[i] <= 'f') {
            value += (str[i] - 87) * base;
            base = base * 16;
        }
    }
    return (value);
}
