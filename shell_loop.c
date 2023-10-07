#include "shell.h"

/**
 * hsh - Main Shell Loop
 * @info: Param & Return Struct Info
 * @av: Arg Vector
 * Return: 0 if it worked or 1 if it fails or Code Error
 */
int hsh(info_t *info, char **av)
{
	ssize_t q = 0;
	int builtin_rt = 0;

	while (q != -1 && builtin_rt != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		q = get_input(info);
		if (q != -1)
		{
			set_info(info, av);
			builtin_rt = find_builtin(info);
			if (builtin_rt == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_rt == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_rt);
}

/**
 * find_builtin - Search for a Builtin Cmd
 * @info: Param & Return Struct Info
 * Return: -1 if Builtin is not available,
 * -2 if Builtin Signals exits,
 *  0 if Builtin Execution worked,
 *  1 if Builtin is available but not executed
 */
int find_builtin(info_t *info)
{
	int x, built_in_rt = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			built_in_rt = builtintbl[x].func(info);
			break;
		}
	return (built_in_rt);
}

/**
 * find_cmd - Searches for a CMD in Path
 * @info: Param & Return Struct Info
 */
void find_cmd(info_t *info)
{
	int x, b;
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, b = 0; info->arg[x]; x++)
		if (!is_delim(info->arg[x], " \t\n"))
			b++;
	if (!b)
		return;
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an Execution Thread to Run Cmd
 * @info: Param & Return Struct Info
 */
void fork_cmd(info_t *info)
{
	pid_t chd_pid;

	chd_pid = fork();
	if (chd_pid == -1)
	{
		/* TODO: INSERT ERROR FUNC */
		perror("Error:");
		return;
	}
	if (chd_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: iNSERT ERROR FUNC */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
