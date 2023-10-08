#include "shell.h"

/**
 * _myexit - Shell Exits Function
 * @info: Struct having Potential Arg which is used in
 * maintaining const funct prototype
 * Return: 0 if shell does not exit or Exits with a given exit code
 */
int _myexit(info_t *info)
{
	int extchek;

	if (info->argv[1]) /* when exit argu is available */
	{
		extchek = _erratoi(info->argv[1]);
		if (extchek == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - replaces the curr direc of the process
 * @info: Struct having potential args which is used in maintaining
 * cosnt funct prottype
 * Return: 0 (always)
 */
int _mycd(info_t *info)
{
	char *st, *dirt, buf[1024];
	int chdir_res;

	st = getcwd(buf, 1024);
	if (!st)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirt = _getenv(info, "HOME=");
		if (!dirt)
			chdir_res = /* TODO: what must it be */
				chdir((dirt = _getenv(info, "PWD=")) ? dirt : "/");
		else
			chdir_res = chdir(dirt);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(st);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_res = /* TODO: what must it be ? */
			chdir((dirt = _getenv(info, "OLDPWD=")) ? dirt : "/");
	}
	else
		chdir_res = chdir(info->argv[1]);
	if (chdir_res == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _myhelp - replaces da curr dir of da process
 * @info: Struct having potential arg which is used in maintaining const
 * func prottype
 * Return: 0 (always)
 */
int _myhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Func not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temporal attribut_unused workar */
	return (0);
}
