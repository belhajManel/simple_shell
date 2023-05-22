#include "shell.h"

/**
 * Calculates the length of a string.
 * @str: The string to calculate the length of.
 *
 * Return: The length of the string.
 */
size_t stringLength(const char *str)
{
    size_t length = 0;

    if (str == NULL)
        return 0;

    while (str[length] != '\0')
        length++;

    return length;
}

/**
 * Performs lexicographic comparison of two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: Negative if str1 < str2, positive if str1 > str2, zero if str1 == str2.
 */
int stringCompare(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

/**
 * Checks if needle starts with haystack.
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Return: Address of the next character of haystack or NULL if not found.
 */
char *startsWith(const char *haystack, const char *needle)
{
    while (*needle)
    {
        if (*haystack != *needle)
            return NULL;
        haystack++;
        needle++;
    }

    return (char *)haystack;
}

/**
 * Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *stringConcat(char *dest, const char *src)
{
    char *temp = dest;

    while (*dest)
        dest++;

    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';

    return temp;
}
