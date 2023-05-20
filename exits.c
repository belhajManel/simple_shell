#include "shell.h"

/**
 * copyString - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string to be copied from
 * @n: the amount of bytes to be maximally used
 *
 * Return: a pointer to the memory area dest
 */
char *copyString(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * concatStrings - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 *
 * Return: the concatenated string
 */
char *concatStrings(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * findCharacter - finds a character in a string
 * @s: the string to be searched
 * @c: the character to be found
 *
 * Return: a pointer to the first occurrence of the character c in the string s
 */
char *findCharacter(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
