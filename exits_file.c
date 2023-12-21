#include "shell.h"

/**
 * *_strncpy - Duplicate a Str
 * @dest: Destination Str to be Copied
 * @src: Source Str
 * @n: Amt of Chars to be Copied
 * Return: Conc Str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int x, y;
	char *st = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (st);
}

/**
 * *_strncat - Concat Two Strs
 * @dest: 1st Str
 * @src: Sec Str
 * @n: Amt of Bytes to be Maximally Used
 * Return: Concat Str
 */
char *_strncat(char *dest, char  *src, int n)
{
	int x, y;
	char *st = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
		dest[x] = '\0';
	return (st);
}

/**
 * *_strchr - Loc a Char in a Str
 * @s: Parsed Str
 * @c: Char to Search for
 * Return: Ptr to the Memory Area (s)
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
