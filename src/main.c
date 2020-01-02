/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** main.c
*/

#include <stdio.h>
#include <string.h>
#include "core.h"

static int print_usage(int return_code)
{
    printf("USAGE:\n\t./arpspoof [Source IP] [Target IP] [Interface] "
    "++ [--printBroadcast | --printSpoofing [MAC address] ]\n\n"
    "DESCRIPTION:\n\tSource IP:\tSource Ip adress\n\tTarget IP:\t"
    "Target Ip adress\n\tInterface:\tInterface to use\n");
    return (return_code);
}

void initialize_core(core_t *core, char **av)
{
    core->fct_ptr[0] = &start_spoof;
    core->fct_ptr[1] = &print_broadcast;
    core->fct_ptr[2] = &print_spoof;
    core->fct_ptr[3] = NULL;
    core->ip_src = strdup(av[1]);
    core->ip_dst = strdup(av[2]);
    core->interface = strdup(av[3]);
    if (core->options == 2)
        core->mac_addr = strdup(av[5]);
}

int main(int ac, char **av)
{
    core_t core;

    if ((ac < 4 || ac > 6) || !valid_args(&core, ac, av))
        return (print_usage(84));
    return (core.fct_ptr[core.options](&core));
}
