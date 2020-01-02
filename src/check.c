/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** check.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "core.h"

static int valid_mac(char *str)
{
    (void)str;
    return (1);
}

static int valid_ip(char *str)
{
    char *tmp;
    char *token;
    unsigned int len = 0;

    if (!str || !str[0])
        return (0);
    tmp = strdup(str);
    token = strtok(tmp, ".");
    while (token != NULL) {
        len++;
        if (!is_number(token) && (strlen(token) >= 1 && strlen(token) <= 3)) {
            print_log("IP provided is not valid", ERROR);
            free(tmp);
            return (0);
        }
        token = strtok(NULL, ".");
    }
    free(tmp);
    return (len == 4 ? 1 : 0);
}

static int valid_iface(int ac, char *str)
{
    (void)ac;

    if (!exist_interface(str))
        return (0);
    return (1);
}

int valid_args(core_t *core, int ac, char **av)
{
    if (ac == 4 && (valid_ip(av[1]) && valid_ip(av[2])
        && valid_iface(ac, av[3])))
        core->options = 0;
    else if ((ac > 4 || ac <= 6) && (valid_ip(av[1]) && valid_ip(av[2])
        && valid_iface(ac, av[3]))) {
        core->options = valid_options(ac, av[4]);
        if (core->options == 0 || (core->options == 2 && !valid_mac(av[5]))) {
            print_log("Invalid option or invalid MAC adress", ERROR);
            return (0);
        }
    } else
        return (0);
    initialize_core(core, av);
    return (1);
}
