#include "shell.h"

/**
 * Checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int isDelimiter(char c, char *delim)
{
	while (*delim) 
    {
        if (*delim++ == c)
			return (1);
    }
		
	return (0);
}

/**
 * Checks if the shell is running in interactive mode.
 * @info: Pointer to the info_t structure.
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int determineInteractiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * Converts a string to an integer.
 * @s: the string to be converted
 * Return: The converted number if successful, 0 otherwise.
 */

int stringToInteger(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 *  Checks if a character is alphabetic.
 *  @c: The character to input
 *  Return: 1 if the character is alphabetic, 0 otherwise.
 */

int isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
