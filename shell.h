#ifndef SHELL_H
#define SHELL_H

/*-------------Libraries------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* Converting a number */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Use to read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

extern char **environ;

/*----------Funtion Prototypes for atoi.c-----*/
int interactive_mode(info_t *info);
int is_delimiter(char c, char *delimiter);
int is_alphabet(int c);
int my_atoi(char *str);

/**
 * struct liststr - the singly linked list.
 * @num: number field.
 * @str: string.
 * @next: points to the next node.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function.
 *@arg: string generated from getline containing arguements.
 *@argv: array of strings generated from arg.
 *@path: string path for the current command.
 *@argc: argument count.
 *@line_count: error count.
 *@err_num: error code for exit..
 *@linecount_flag: if on count this line of input.
 *@fname: program filename.
 *@env: linked list local copy of environ.
 *@environ: custom modified copy of environ.
 *@history: the history node.
 *@alias: alias node.
 *@env_changed:if environ was changed.
 *@status: status of the last executed command.
 *@cmd_buf: address of pointer to cmd_buf, on if chaining.
 *@cmd_buf_type: ||, &&, ;.
 *@readfd: file descriptor from which to read line input.
 *@histcount: history line number count.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - for builtin string and associated function.
 *@type: the builtin command flag.
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

#endif
