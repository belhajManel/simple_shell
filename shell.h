#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".history_simple_shell"
#define HIST_MAX	4096

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

extern char **environ;

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	
	int cmd_buf_type; 
	int readfd;
	int histcount;
	char **cmd_buf; 
	
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void printToStderr(char *);
int putCharToStderr(char);
int putCharToFd(char c, int fd);
int printToFd(char *str, int fd);

/* string.c */
size_t stringLength(const char *str);
int stringCompare(const char *str1, const char *str2);
char *startsWith(const char *, const char *);
char *stringConcat(char *dest, const char *src);

/* string1.c */
char *stringCopy(char *destination, const char *source);
char *stringDuplicate(const char *);
void printString(char *);
int printCharacter(char);

/* exits.c */
char *copyString(char *, char *, int);
char *concatStrings(char *, char *, int);
char *findCharacter(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfree(void **);

/* _atoi.c */
int determineInteractiveMode(info_t *);
int isDelimiter(char, char *);
int isAlphabetic(int);
int stringToInteger(char *);

/* errors1.c */
int convertStringToInt(char *);
void printError(info_t *, char *);
int printDecimal(int, int);
char* convertNumber(long int, int, int);
void removeComments(char *);

/* builtin.c */
int exitShell(info_t *);
int changeDirectory(info_t *);
int displayHelp(info_t *);
int safeAtoi(const char *str);
void print_error(info_t* info, const char*);

/* builtin1.c */
int displayHistory(info_t *);
int handleAlias(info_t *);

/* getline.c */
ssize_t getInput(info_t *);
int getLine(info_t *, char **, size_t *);
void handleSigint(int);

/* getinfo.c */
void clearShellInfo(info_t *shell_info);
void setShellInfo(info_t *, char **);
void freeShellInfo(info_t *, int);

/* environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetEnv(info_t *);
int _myunsetEnv(info_t *);
int populate_env_list(info_t *);

/* getenv.c */
char **getEnviron(info_t *);
int unsetEnv(info_t *, char *);
int setEnv(info_t *, char *, char *);

/* history.c */
char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);

/* lists.c */
list_t *addNode(list_t **, const char *, int);
list_t *addNode_end(list_t **, const char *, int);
size_t printListStr(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
void freeList(list_t **);

/* lists1.c */
size_t listLen(const list_t *);
char **listToStrings(list_t *);
size_t printList(const list_t *);
list_t *nodeStartsWith(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* vars.c */
int isChain(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVars(info_t *);
int replaceString(char **, char *);

#endif
