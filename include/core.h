/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** core.h
*/

#ifndef CORE_H_
 #define CORE_H_

#include <stdbool.h>
#include <stdint.h>
#include "arp.h"

#define IFACE_PATH "/sys/class/net/"
#define IFACE_FILE "/address"
#define MAC_LEN 18

#define VERBOSE 0

enum {
    NORMAL,
    ERROR,
    INFO
};

typedef struct core_s
{
    unsigned char options;
    char *mac_addr;
    char *ip_src;
    char *ip_dst;
    char *interface;

    char *iface_mac;
    char *path;
    int frame_length;
    int bytes;
    int opcode;
    int sd;

    uint8_t *src_mac;
    uint8_t *dst_mac;
    uint8_t *ether_frame;

    struct addrinfo hints;
    struct addrinfo *res;

    struct sockaddr_in *ipv4;
    struct sockaddr_ll device;
    struct ifreq ifr;
    arp_hdr_t arphdr;

    int (*fct_ptr[4])(struct core_s *core);
} core_t;

/* CORE */
void initialize_core(core_t *core, char **av);
int print(core_t *core);
int arp(void);

/* PACKET */
void fill_hints(core_t *core);
void fill_device(core_t *core);
void fill_arp(core_t *core, int arpop);
int get_interface_index(core_t *core);
int initialize_packet(core_t *core);
int send_packet(core_t *core);
int receive(core_t *core);

/* INTERFACE */
int exist_interface(char *iface);
int get_interface_mac(core_t *core, char *iface);

/* START */
int start_spoof(core_t *core);
int print_spoof(core_t *core);
int print_broadcast(core_t *core);

/* PRINT */
void print_hexa_array(uint8_t *array, char sep, int len, bool end);

/* ERROR */
int valid_args(core_t *core, int ac, char **av);
int valid_options(int ac, char *str);

/* UTILS */
void free_core(core_t *core);
int is_number(char *str);
int hexa_str_to_decimal(char *str);
uint8_t *str_to_mac_address(char *iface_mac);

/* LOGS */
void print_log(char *message, int type);

#endif /* CORE_H_ */
