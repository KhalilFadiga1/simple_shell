#include "shell.h"

/**
 * _strcpy - Duplicates a String
 * @dest: Destination buffer
 * @src: Source buffer
 * Return: Ptr to dest
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - Copies a String
 * @str: String to Copy
 * Return: Ptr to Copied String
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *res;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	for (len++; len--;)
		res[len] = *--str;
	return (res);
}

/**
 * _puts - Prints an Input String
 * @str: String to be Printed
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - Writes the Char c to STDOUT
 * @c: The Char to Print
 * Return: 1 if it worked
 * On Error, -1 is return, and errno is set appropriate
 */
int _putchar(char c)
{
	static char buffer[WRITE_BUF_SIZE];
	static int x;

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buffer, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buffer[x++] = c;
	return (1);
}
