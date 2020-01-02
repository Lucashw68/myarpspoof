/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** utils.c
*/

#include <string.h>
#include <ctype.h>
#include "core.h"

int is_number(char *str)
{
    if (!str || !str[0])
        return (0);
    for (unsigned int i = 0; i != strlen(str); i++) {
        if (!isdigit(str[i]))
            return (0);
    }
    return (1);
}

char *str_to_lower(char *str)
{
    unsigned int i = 0;
    char *tmp = malloc(sizeof(char) * (strlen(str) + 1));

    for (i = 0; i != strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            tmp[i] = str[i] + 32;
        else
            tmp[i] = str[i];
    }
    tmp[i] = '\0';
    return (tmp);
}

uint8_t *str_to_mac_address(char *iface_mac)
{
    uint8_t *mac;
    char *ltoken;
    char *token;
    char *tmp;
    int i = 0;

    if (!iface_mac || !iface_mac[0])
        return (NULL);
    mac = (uint8_t *)malloc(sizeof(uint8_t) * 6);
    tmp = strdup(iface_mac);
    token = strtok(tmp, ":");
    while (token != NULL) {
        ltoken = str_to_lower(token);
        mac[i++] = hexa_str_to_decimal(ltoken);
        token = strtok(NULL, ":");
        free(ltoken);
    }
    free(tmp);
    return (mac);
}

char *allocate_strmem (unsigned int len)
{
    void *tmp;

    tmp = (char *)malloc(len * sizeof(char));
    if (tmp != NULL) {
        memset(tmp, 0, len * sizeof(char));
        return (tmp);
    } else {
        printf("allocation failed\n");
        exit(84);
    }
}

uint8_t *allocate_ustrmem(unsigned int len)
{
    void *tmp;

    tmp = (uint8_t *)malloc(len * sizeof(uint8_t));
    if (tmp != NULL) {
        memset (tmp, 0, len * sizeof(uint8_t));
        return (tmp);
    } else {
        printf("allocation failed\n");
        exit(84);
    }
}
