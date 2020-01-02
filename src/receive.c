/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** receive.c
*/

#include "core.h"

void print_hexa_array_inline(uint8_t *array, char sep, int len, bool end)
{
    int i = 0;

    if (end == true)
        len--;
    for (i = 0; i != len; i++) {
        if (i == (len))
            printf("%02x", array[i]);
        else
            printf("%02x%c", array[i], sep);
    }
    if (end == true)
        printf("%02x", array[i]);
}

static void set_target_mac(core_t *core, struct ethhdr *eth)
{
    for (int i = 0; i != 6 ; i++)
        core->dst_mac[i] = eth->h_source[i];
    printf("Found victim’s MAC address: '");
    print_hexa_array_inline(core->dst_mac, ':', 6, 1);
    printf("'\n");
}

int receive(core_t *core)
{
    struct ethhdr *eth;
    unsigned char *buffer;
    struct sockaddr saddr;
    int saddr_len = sizeof(saddr);
    int sock_r;

    sock_r = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock_r < 0) {
        print_log("Error in socket, Are you root ??", ERROR);
        return (84);
    }
    buffer = (unsigned char *) malloc(65536);
    memset(buffer, 0, 65536);
    if (recvfrom(sock_r, buffer, 65536, 0, &saddr, (socklen_t *)&saddr_len) < 0)
        return (84);
    eth = (struct ethhdr *)(buffer);
    set_target_mac(core, eth);
    free(buffer);
    return (0);
}
