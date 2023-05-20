#include "shell.h"

/**
 * printToStderr - prints an input string to stderr
 * @str:  the string to be printed
 *
 * Return: void
 */
void printToStderr(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putCharToStderr(str[i]);
		i++;
	}
}

/**
 * putCharToStderr -  vharacter c to stderr
 * @c: The character to print to stderr or flush the buffer
 *
 * Return: 1 if successful, -1 otherwise
 */
int putCharToStderr(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * putCharToFd - vharacter c to file descriptor fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: 1 if successful, -1 otherwise
 */
int putCharToFd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * printToFd - prints an input string to a file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: The number of characters printed
 */
int printToFd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += putCharToFd(*str++, fd);
	}
	return (i);
}
