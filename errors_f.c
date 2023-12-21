#include "shell.h"

/**
 * _eputs - Prints an Input Str
 * @str: Printed Str
 */
void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}

/**
 * _eputchar - Writes de char c to stderr
 * @c: Char to Print
 * Return: 1 if it worked
 * Return -1 if it fails, and  errno is set appropriately
 */
int _eputchar(char c)
{
	static char buff[WRITE_BUF_SIZE];
	static int x;

	if (x >= WRITE_BUF_SIZE || c == BUF_FLUSH)
	{
		write(2, buff, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buff[x++] = c;
	return (1);
}

/**
 * _putfd - Writes Char c to Given fd
 * @c: Char to Print
 * @fd: File Descriptor to be Written
 * Return: 1 if successful
 * -1 if it did not work successful and errno is set appropriately
 */
int _putfd(char c, int fd)
{
	static char buff[WRITE_BUF_SIZE];
	static int x;

	if (x >= WRITE_BUF_SIZE || c == BUF_FLUSH)
	{
		write(fd, buff, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buff[x++] = c;
	return (1);
}

/**
 * _putsfd - Prints Input Str
 * @str: Printed Str
 * @fd: File Descriptor to Write to
 * Return: Num of Characters put
 */
int _putsfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += _putfd(*str++, fd);
	}
	return (x);
}
