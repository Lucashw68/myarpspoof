/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** log.c
*/

#include <stdio.h>
#include "core.h"

void print_log(char *message, int type)
{
    switch (type) {
        case INFO:
        printf("\033[33m[INFO] %s \033[0m\n", message);
        break;
        case ERROR:
        printf("\033[31m[ERROR] %s \033[0m\n", message);
        break;
        default:
        printf("%s\n", message);
        break;
    }
    printf("\033[0m");
}
