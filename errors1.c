#include "shell.h"

/**
 * _erratoi - Change a Str to a Number
 * @s: Conv Str
 * Return: If no nums found in str return 0, -1 when
 * error occurs or the Converted Num
 */
int _erratoi(char *s)
{
	unsigned long int res = 0;
	int x = 0;

	if (*s == '+')
		s++; /* TODO: why does this result to 255 return frm main */
	for (x = 0; s[x] != '\0'; x++)
	{
		if (s[x] >= '0' && s[x] <= '9')
		{
			res *= 10;
			res += (s[x] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - Print Error Message
 * @info: Param & Struct Info is return
 * @estr: Str having a  specific type of error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(estr);
}

/**
 * print_d - Prints a dec (int) num (Base 10)
 * @fd: File Descriptor to be written to
 * @input: Input var
 * Return: Num of Chars Printed
 */
int print_d(int input, int fd)
{
	int x, counts = 0;
	int (*__putchar)(char) = _putchar;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counts++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + curr / x);
			counts++;
		}
		curr %= x;
	}
	__putchar('0' + curr);
	counts++;
	return (counts);
}

/**
 * convert_number - Converter Func, an ITOA CLONE
 * @num: Integer
 * @base: Base Number
 * @flags: Arg Flag
 * Return: Str
 */
char *convert_number(long int num, int base, int flags)
{
	unsigned long int n = num;
	char *pt, sign = 0;
	static char *arr, buf[50];

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buf[49];
	*pt = '\0';
	do {
		*--pt = arr[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--pt = sign;
	return (pt);
}

/**
 * remove_comments - Func that changes first instance of '#' with '\0'
 * @buf: Addr of Str to change
 */
void remove_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
