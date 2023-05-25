#include "shell.h"

/**
 * convertStringToInt - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 on success, 1 on error
 *       -1 on error
 */
int convertStringToInt(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

/**
 * printError - prints error messages
 * @info: the parameter & return info struct
 * @estr: the error message
 * Return: 0 on success, 1 on error
 *        -1 on error
 */
void printError(info_t *info, char *errorMsg)
{
    _eputs(info->fname);
    _eputs(": ");
    printDecimal(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(errorMsg);
}

/**
 * printDecimal - prints a decimal
 * @input: the input
 * @fd: file descriptor
 *
 * Return: number of characters printed
 */
int printDecimal(int input, int fd)
{
    int (*putCharFunc)(char) = printCharacter;
    int i, count = 0;
    unsigned int absoluteValue, current;

    if (fd == STDERR_FILENO)
        putCharFunc = _eputchar;
    if (input < 0)
    {
        absoluteValue = -input;
        putCharFunc('-');
        count++;
    }
    else
        absoluteValue = input;
    current = absoluteValue;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absoluteValue / i)
        {
            putCharFunc('0' + current / i);
            count++;
        }
        current %= i;
    }
    putCharFunc('0' + current);
    count++;

    return (count);
}

/**
 * convertNumber - converts a number to a string
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */

char* convertNumber(long int num, int base, int flags)
{
    static char *charArray;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    charArray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = charArray[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return (ptr);
}

/**
 * removeComments -  '\0' instead of '#' if '#' is found
 * @buf: buffer to remove comments from
 *
 * Return: Always 0;
 */
void removeComments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
}
