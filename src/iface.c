/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** iface.c
*/

#include <dirent.h>
#include "core.h"
#include "arp.h"

int exist_interface(char *iface)
{
   struct dirent *read;
   DIR *files;

   files = opendir("/sys/class/net/");
   while ((read = readdir(files))) {
      if (strcmp(read->d_name, iface) == 0) {
         closedir(files);
         return (1);
      }
   }
   closedir(files);
   return (0);
}

static char *get_path_interface(char *iface)
{
   unsigned int i = 0;
   char *path;
   int j = 0;

   if (!exist_interface(iface))
      return (NULL);
   path = malloc(sizeof(char) * (strlen(IFACE_PATH) + strlen(iface) +
      strlen(IFACE_FILE)) + 1);
   strcpy(path, IFACE_PATH);
   for (i = strlen(IFACE_PATH); i != strlen(IFACE_PATH) + strlen(iface); i++)
      path[i] = iface[j++];
   for (int k = 0; k != strlen(IFACE_FILE); k++)
      path[i++] = IFACE_FILE[k];
   path[i] = '\0';
   return (path);
}

int get_interface_mac(core_t *core, char *iface)
{
   char ch;
   FILE *fp;
   int i = 0;

   core->path = get_path_interface(iface);
   if (core->path == NULL) {
      print_log("The interface is invalid or doesn't exist", ERROR);
      return (0);
   }
   core->iface_mac = malloc(sizeof(char) * (MAC_LEN + 1));
   fp = fopen(core->path, "r");
   if (fp == NULL) {
      print_log("Error while opening the file.", ERROR);
      exit(84);
   }
   while ((ch = fgetc(fp)) != EOF)
      core->iface_mac[i++] = ch;
   core->iface_mac[i] = '\0';
   fclose(fp);
   return (1);
}
