#include "shell.h"

/**
 * clearShellInfo - clears setShellInfo struct fields
 * @shell_info: struct address
 */
void clearShellInfo(info_t *shell_info)
{
	shell_info->arg = NULL;
	shell_info->argv = NULL;
	shell_info->path = NULL;
	shell_info->argc = 0;
}

/**
 * setShellInfo - sets setShellInfo struct fields
 * @shell_info: struct address
 * @av: argument vector
 */
void setShellInfo(info_t *shell_info, char **av)
{
	int i = 0;

	shell_info->fname = av[0];
	if (shell_info->arg)
	{
		shell_info->argv = strtow(shell_info->arg, " \t");
		if (!shell_info->argv)
		{

			shell_info->argv = malloc(sizeof(char *) * 2);
			if (shell_info->argv)
			{
				shell_info->argv[0] = stringDuplicate(shell_info->arg);
				shell_info->argv[1] = NULL;
			}
		}
		for (i = 0; shell_info->argv && shell_info->argv[i]; i++)
			;
		shell_info->argc = i;

		replaceAlias(shell_info);
		replaceVars(shell_info);
	}
}

/**
 * freeShellInfo - frees setShellInfo struct fields
 * @shell_info: struct address
 * @all: flag to free all fields
 */
void freeShellInfo(info_t *shell_info, int all)
{
	ffree(shell_info->argv);
	shell_info->argv = NULL;
	shell_info->path = NULL;
	if (all)
	{
		if (!shell_info->cmd_buf)
			free(shell_info->arg);
		if (shell_info->env)
			freeList(&(shell_info->env));
		if (shell_info->history)
			freeList(&(shell_info->history));
		if (shell_info->alias)
			freeList(&(shell_info->alias));
		ffree(shell_info->environ);
			shell_info->environ = NULL;
		bfree((void **)shell_info->cmd_buf);
		if (shell_info->readfd > 2)
			close(shell_info->readfd);
		printCharacter(BUF_FLUSH);
	}
}
