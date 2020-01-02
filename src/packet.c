/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** packet.c
*/

#include "core.h"

static int check_ip(core_t *core)
{
    int status;

    if ((status = inet_pton(AF_INET, core->ip_src,
        &core->arphdr.sender_ip)) != 1) {
        fprintf(stderr, "inet_pton() failed for source IP address."
        "\nError message: %s", strerror(status));
        return (84);
    }
    return (0);
}

static int resolve_target(core_t *core)
{
    int status;

    if ((status = getaddrinfo(core->ip_dst, NULL,
        &(core)->hints, &(core)->res)) != 0) {
        fprintf(stderr, "getaddrinfo() failed: %s\n", gai_strerror(status));
        return (84);
    }
    core->ipv4 = (struct sockaddr_in *) core->res->ai_addr;
    memcpy(&(core)->arphdr.target_ip,
        &(core)->ipv4->sin_addr, 4 * sizeof (uint8_t));
    freeaddrinfo(core->res);
    return (0);
}

int initialize_packet(core_t *core)
{
    core->dst_mac = allocate_ustrmem(6);
    core->ether_frame = allocate_ustrmem(IP_MAXPACKET);
    core->frame_length = 6 + 6 + 2 + ARP_HDRLEN;
    get_interface_mac(core, core->interface);
    core->src_mac = str_to_mac_address(core->iface_mac);
    memset(&(core)->device, 0, sizeof(core->device));
    if (core->options == 2) {
        free(core->dst_mac);
        core->dst_mac = str_to_mac_address(core->mac_addr);
    } else
        memset(core->dst_mac, 0xff, 6 * sizeof (uint8_t));
    memset(&(core)->hints, 0, sizeof(struct addrinfo));
    fill_hints(core);
    if (get_interface_index(core) || check_ip(core) || resolve_target(core))
        return (84);
    fill_device(core);
    fill_arp(core, core->opcode);
    return (0);
}
