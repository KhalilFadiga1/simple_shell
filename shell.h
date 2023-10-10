#ifndef _SHELL_H
#define _SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* READ & WRITE BUFFERS */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* CONVERSION OF NUMBER */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* CMD CHAINING */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* SYSTEM GETLINE */
#define USE_GETLINE 0
#define USE_STRTOK
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX  4096

extern char **environ;

/**
 * struct liststr - Singly Linked List
 * @num: Field nu
 * @str: Str
 * @next: Ptr to Next Node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains Pseudo-arguments to be pass to a function,
 * permitting homogeneous prototype for Ptr Struct func
 * @arg: Getline string having arguments
 * @argv: String Arrays
 * @path: String Path for curr cmd
 * @argc: Arg Counter
 * @line_count: Counting of error
 * @err_num: Error num for Exit func
 * @fname: Program Filename
 * @history: History node
 * @status: Return  Status of the Last Exec'd Cmd
 * @env: Linked List Local Copy of Environ
 * @readfd: Fd to read line input
 * @environ: Custom modified Copy of Environ from LL env
 * @env_changed: ON if environ ws Changed
 * @linecount_flag: Count this line of input if ON
 * @alias: Alias node
 * @cmd_buf: Ptr to cmd_buf, ON if chaining
 * @histcount: History Line Number Count
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
	char **cmd_buf; /* Ptr to Cmd; Chain Buffer, for Memory Mgt */
	int cmd_buf_type; /* CMD_TYPE ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - Contains Builtin String and rel func
 * @type: Builtin Cmd flag
 * @func: Function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* PARSER FILE */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);

/* SH_LOOP FILE */
int find_builtin(info_t *);
int hsh(info_t *, char **);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* TOKENIZER FILE */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* ERRORS FILE COMPONENTS */
int _putsfd(char *str, int fd);
int _eputchar(char);
int _putfd(char c, int fd);
void _eputs(char *);

/* EXITS FILE */
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

/* STRING FILE */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* REALLOC FILE */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* STRING1 FILE */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* ATOI FILE */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* LOOPHSH FILE */
int loophsh(char **);

/* MEMORY FILE */
int bfree(void **);

/* GETLINE FILE */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* BUILTIN FILE */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* ERRORS1 FILE */
int _erratoi(char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void print_error(info_t *, char *);
void remove_comments(char *);

/* BUILTIN1 FILE */
int _myhistory(info_t *);
int _myalias(info_t *);

/* ENVIRON FILE */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* GETINFO FILE */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* GETENV FILE */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* HISTORY FILE */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *inf, char  *buf, int linecount);
int renumber_history(info_t *info);

/* LISTS FILE */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* LISTS1 FILE */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* VARS FILE */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
