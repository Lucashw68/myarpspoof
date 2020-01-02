/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** fill.c
*/

#include "core.h"

int get_interface_index(core_t *core)
{
    if ((core->device.sll_ifindex = if_nametoindex(core->interface)) == 0) {
        perror("if_nametoindex() failed to obtain interface index ");
        return (84);
    }
    return (0);
}

void fill_hints(core_t *core)
{
    core->hints.ai_family = AF_INET;
    core->hints.ai_socktype = SOCK_STREAM;
    core->hints.ai_flags = core->hints.ai_flags | AI_CANONNAME;
}

void fill_device(core_t *core)
{
    core->device.sll_family = AF_PACKET;
    memcpy(core->device.sll_addr, core->src_mac, 6 * sizeof(uint8_t));
    core->device.sll_halen = 6;
}

void fill_arp(core_t *core, int arpop)
{
    core->arphdr.htype = htons(1);
    core->arphdr.ptype = htons(ETH_P_IP);
    core->arphdr.hlen = 6;
    core->arphdr.plen = 4;
    if (arpop == ARPOP_REQUEST)
        core->arphdr.opcode = htons(ARPOP_REQUEST);
    else if (arpop == ARPOP_REPLY)
        core->arphdr.opcode = htons(ARPOP_REPLY);
    memcpy(core->arphdr.sender_mac, core->src_mac, 6 * sizeof(uint8_t));
    memset(core->arphdr.target_mac, 0, 6 * sizeof(uint8_t));
    memcpy(core->ether_frame, core->dst_mac, 6 * sizeof(uint8_t));
    memcpy(core->ether_frame + 6, core->src_mac, 6 * sizeof(uint8_t));
    core->ether_frame[12] = ETH_P_ARP / 256;
    core->ether_frame[13] = ETH_P_ARP % 256;
}
