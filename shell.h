#ifndef SHELL_H
#define SHELL_H

/*-------------Libraries------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

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

/*--------Funtion Prototypes for builtin.c--------*/
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);

/*--------Funtion Prototypes for builtin1.c--------*/
int my_history(info_t *);
int my_alias(info_t *);

/* loophsh.c */
int loophsh(char **);

/*--------Funtion Prototypes for environ.c--------*/
char *_getenv(info_t *, const char *);
int my_env(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int display_env_list(info_t *info);

/*--------Funtion Prototypes for errors.c--------*/
void _inputs(char *);
int _inputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/*--------Funtion Prototypes for errors1.c--------*/
int _erroratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*--------Funtion Prototypes for exits.c--------*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/*--------Funtion Prototypes for getenv.c--------*/
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/*--------Funtion Prototypes for getinfo.c--------*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/*--------Funtion Prototypes for getline.c--------*/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigint_handler(int);

/*--------Funtion Prototypes for history.c--------*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/*--------Funtion Prototypes for lists.c--------*/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/*--------Funtion Prototypes for lists1.c--------*/
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/*--------Funtion Prototypes for memory.c--------*/
int bfree(void **);

/*--------Funtion Prototypes for parser.c--------*/
int is_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/*--------Funtion Prototypes for realloc.c--------*/
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/*--------Funtion Prototypes for shell_loop.c--------*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/*--------Funtion Prototypes for string.c--------*/
int my_strlen(char *);
int my_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/*--------Funtion Prototypes for string1.c--------*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/*--------Funtion Prototypes for tokenizer.c--------*/
char **strtow(char *, char *);
char **strtow2(char *, char);

/*--------Funtion Prototypes for vars.c--------*/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

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
