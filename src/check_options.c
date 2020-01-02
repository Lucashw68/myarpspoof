/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** check_options.c
*/

#include <string.h>
#include <stdio.h>
#include "core.h"
#include "options.h"

int valid_options(int ac, char *str)
{
    if (!str || !str[0])
        return (0);
    for (unsigned int i = 0; options[i]; i++) {
        if ((strcmp(str, options[i]) == 0)
        && ((unsigned int)ac == options_arg[i])) {
            return (i + 1);
        }
    }
    return (0);
}
