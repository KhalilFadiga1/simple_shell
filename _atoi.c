#include "shell.h"

/**
 * interactive - Funct dat return True if Shell is Interactive Mode
 * @info: Addr of Struct
 * Return: If interactive mode return or else 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks If Char is a Delim
 * @c: Char to Verify
 * @delim: String Delim
 * Return: 1 for true and 0 for false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Verify for Alpha Char
 * @c: Input Char
 * Return: If c is Alpha, return 1 and 0 if not
 */
int _isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Change a String to a number
 * @s: String to convert
 * Return: Converted integer or 0 if otherwise
 */
int _atoi(char *s)
{
	int x, res, sgn = 1, flg = 0;
	unsigned int outcome = 0;

	for (x = 0; s[x] != '\0' && flg != 2; x++)
	{
		if (s[x] == '-')
			sgn *= -1;
		if (s[x] >= '0' && s[x] <= '9')
		{
			flg = 1;
			outcome *= 10;
			outcome += (s[x] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}
	if (sgn == -1)
		res = -outcome;
	else
		res = outcome;
	return (res);
}
