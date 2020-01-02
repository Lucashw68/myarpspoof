/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** free.c
*/

#include "core.h"

void free_core(core_t *core)
{
    free(core->ip_src);
    free(core->ip_dst);
    free(core->interface);
    if (core->options != 0) {
        if (core->options == 2)
            free(core->mac_addr);
        free(core->src_mac);
        free(core->dst_mac);
        free(core->ether_frame);
        free(core->iface_mac);
        free(core->path);
    }
}
