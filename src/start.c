/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** start.c
*/

#include <stdio.h>
#include "core.h"

int start_spoof(core_t *core)
{
    int ret = 0;

    if (VERBOSE) {
        print_log("Start Spoofing", INFO);
        printf("Source ip: %s\n", core->ip_src);
        printf("Dest ip: %s\n", core->ip_dst);
        printf("Interface: %s\n", core->interface);
    }
    core->opcode = ARPOP_REQUEST;
    send_packet(core);
    free_core(core);
    return (ret);
}

int print_spoof(core_t *core)
{
    int ret = 0;

    if (VERBOSE) {
        print_log("Start Print Spoofing", INFO);
        printf("Source ip: %s\n", core->ip_src);
        printf("Source ip: %s\n", core->ip_dst);
        printf("Interface: %s\n", core->interface);
        printf("Mac Addr: %s\n", core->mac_addr);
    }
    core->opcode = ARPOP_REPLY;
    ret = print(core);
    free_core(core);
    return (ret);
}

int print_broadcast(core_t *core)
{
    int ret = 0;

    if (VERBOSE) {
        print_log("Start Print Broadcast", INFO);
        printf("Source ip: %s\n", core->ip_src);
        printf("Source ip: %s\n", core->ip_dst);
        printf("Interface: %s\n", core->interface);
    }
    core->opcode = ARPOP_REQUEST;
    ret = print(core);
    free_core(core);
    return (ret);
}
