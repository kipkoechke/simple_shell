#ifndef SHELL_H
#define SHELL_H

/*-------------Libraries------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/*----------Funtion Prototypes for atoi.c-----*/
int interactive_mode(info_t *info);
int is_delimiter(char c, char *delimiter);
int is_alphabet(int c);
int my_atoi(char *str);

#endif
