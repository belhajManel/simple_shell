#include "shell.h"

/**
 * Unsets an alias.
 * @info: Pointer to the info_t structure.
 * @str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *equal_sign, character;
    int ret;

    equal_sign = findCharacter(str, '=');
    if (!equal_sign)
        return 1;
    character = *equal_sign;
    *equal_sign = '\0';
    ret = delete_node_at_index(&(info->alias),
                            get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *equal_sign = character;
    return ret;
}

/**
 * Sets an alias.
 * @info: Pointer to the info_t structure.
 * @str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *equal_sign;

    equal_sign = findCharacter(str, '=');
    if (!equal_sign)
        return 1;
    if (!*++equal_sign)
        return unset_alias(info, str);

    unset_alias(info, str);
    return add_node_end(&(info->alias), str, 0) == NULL;
}

/**
 * Displays the command history list, with line numbers.
 * @info: Pointer to the info_t structure.
 * Return: Always 0.
 */
int displayHistory(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * Prints an alias string.
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *equal_sign = NULL, *alias_string = NULL;

    if (node)
    {
        equal_sign = findCharacter(node->str, '=');
        for (alias_string = node->str; alias_string <= equal_sign; alias_string++)
            _putchar(*alias_string);
        _putchar('\'');
        _puts(equal_sign + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}



/**
 * Implements the alias built-in command.
 * @info: Pointer to the info_t structure.
 * Return: Always 0.
 */
int handleAlias(info_t *info)
{
    int i = 0;
    char *equal_sign = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        equal_sign = findCharacter(info->argv[i], '=');
        if (equal_sign)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return 0;
}

