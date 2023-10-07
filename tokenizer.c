#include "shell.h"

/**
 * **strtow - Breaks a String into individual words.
 * Duplicates delim are ignore
 * @str: String INput
 * @d: String delimeter
 * Return: Ptr to Array of Strings, or NULL if otherwise
 */
char **strtow(char *str, char *d)
{
	int x, y, a, b, nwords = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			nwords++;
	if (nwords == 0)
		return (NULL);
	st = malloc((1 + nwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (x = 0, y = 0; y < nwords; y++)
	{
		while (is_delim(str[x], d))
			x++;
		a = 0;
		while (!is_delim(str[x + a], d) && str[x + a])
			a++;
		st[y] = malloc((a + 1) * sizeof(char));
		if (!st[y])
		{
			for (a = 0; a < y; a++)
				free(st[a]);
			free(st);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			st[y][b] = str[x++];
		st[y][b] = 0;
	}
	st[y] = NULL;
	return (st);
}

/**
 * **strtow2 - breaks a stirng into group of chars
 * @str: String Input
 * @d: String delim
 * Return: Ptr to Array of Strings or NULL if failed
 */
char **strtow2(char *str, char d)
{
	int x, y, a, b, nwords = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
			(str[x] != d && !str[x + 1]) || str[x + 1] == d)
			nwords++;
	if (nwords == 0)
		return (NULL);
	st = malloc((1 + nwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (x = 0, y = 0; y < nwords; y++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		a = 0;
		while (str[x + a] != d && str[x + a] && str[x + a] != d)
			a++;
		st[y] = malloc((a + 1) * sizeof(char));
		if (!st[y])
		{
			for (a = 0; a < y; a++)
				free(st[a]);
			free(st);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			st[y][b] = str[x++];
		st[y][b] = 0;
	}
	st[y] = NULL;
	return (st);
}
