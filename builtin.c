#include "shell.h"

/**
 * Exits the shell.
 * @info: Pointer to the info_t structure.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int exitShell(info_t *info)
{
    int exitCode;
    
    if (info->argv[1])
    {
        exitCode = safeAtoi(info->argv[1]);
        if (exitCode == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            printString(info->argv[1]);
            printCharacter('\n');
            return 1;
        }
        info->err_num = safeAtoi(info->argv[1]);
        return -2;
    }
    info->err_num = -1;
    return -2;
}

/**
 * Displays help information.
 * @info: Pointer to the info_t structure.
 * Return: Always 0.
 */
int displayHelp(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    printString("help call works. Function not yet implemented \n");
    if (0)
        printString(*arg_array); 
    return 0;
}

/**
 * Changes the current directory of the process.
 * @info: Pointer to the info_t structure.
 * Return: Always 0.
 */
int changeDirectory(info_t *info)
{
    char *cwd, *dir, buffer[1024];
    int chdir_ret;

    cwd = getCwd(buffer, 1024);
    if (!cwd)
        printString("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dir = getEnv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = getEnv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (stringCompare(info->argv[1], "-") == 0)
    {
        if (!getEnv(info, "OLDPWD="))
        {
            printString(cwd);
            printCharacter('\n');
            return 1;
        }
        printString(getEnv(info, "OLDPWD="));
        printCharacter('\n');
        chdir_ret = chdir((dir = getEnv(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        printString(info->argv[1]);
        printCharacter('\n');
    }
    else
    {
        setEnv(info, "OLDPWD", getEnv(info, "PWD="));
        setEnv(info, "PWD", getCwd(buffer, 1024));
    }
    return 0;
}


