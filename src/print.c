/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** print.c
*/

#include "core.h"

void print_hexa_array(uint8_t *array, char sep, int len, bool end)
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
        printf("%02x\n", array[i]);
}

int print(core_t *core)
{
    if (initialize_packet(core))
        return (84);
    print_hexa_array(core->ether_frame, ' ', 14, 0);
    printf("%02x ", 0);
    printf("%02x ", 1);
    printf("%02x ", core->arphdr.ptype);
    printf("%02x ", 0);
    printf("%02x ", core->arphdr.hlen);
    printf("%02x ", core->arphdr.plen);
    printf("%02x ", 0);
    if (core->opcode == ARPOP_REQUEST)
        printf("%02x ", ARPOP_REQUEST);
    else if (core->opcode == ARPOP_REPLY)
        printf("%02x ", ARPOP_REPLY);
    print_hexa_array(core->arphdr.sender_mac, ' ', 6, 0);
    print_hexa_array(core->arphdr.sender_ip, ' ', 4, 0);
    print_hexa_array(core->ether_frame, ' ', 6, 0);
    print_hexa_array(core->arphdr.target_ip, ' ', 4, 1);
    return (0);
}
