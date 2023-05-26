#include "shell.h"

/**
 * Copies a string.
 * @destination: The destination buffer.
 * @source: The source string.
 *
 * Return: Pointer to the destination buffer.
 */
char *stringCopy(char *destination, const char *source)
{
	int i = 0;

	if (destination == source || source == NULL)
		return (destination);

	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}

	destination[i] = '\0';
	return (destination);
}

/**
 * Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *stringDuplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * Prints a string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void printString(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		printCharacter(str[i]);
		i++;
	}
}

/**
 * Writes a character to stdout.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int printCharacter(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buffer[i++] = c;

	return (1);
}
