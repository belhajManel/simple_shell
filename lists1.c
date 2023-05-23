#include "shell.h"

/**
 * Determines the length of the linked list.
 * @h: Pointer to the first node.
 * Return: Size of the list.
 */
size_t listLen(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }
    return i;
}

/**
 * Returns an array of strings of the list->str.
 * @head: Pointer to the first node.
 * Return: Array of strings.
 */
char **listToStrings(list_t *head)
{
    list_t *node = head;
    size_t i = listLen(head), j;
    char **strs;
    char *str;

    if (!head || !i)
        return NULL;
    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return NULL;
    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(stringLength(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return NULL;
        }

        str = stringCopy(str, node->str);
        strs[i] = str;
    }
    strs[i] = NULL;
    return strs;
}

/**
 * Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 * Return: Size of the list.
 */
size_t printList(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        printString(convertNumber(h->num, 10, 0));
        printCharacter(':');
        printCharacter(' ');
        printString(h->str ? h->str : "(nil)");
        printString("\n");
        h = h->next;
        i++;
    }
    return i;
}

/**
 * Returns the node whose string starts with prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after prefix to match.
 * Return: Match node or NULL.
 */
list_t *nodeStartsWith(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = startsWith(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return node;
        node = node->next;
    }
    return NULL;
}

/**
 * Gets the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 * Return: Index of the node or -1.
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
    size_t i = 0;

    while (head)
    {
        if (head == node)
            return i;
        head = head->next;
        i++;
    }
    return -1;
}
