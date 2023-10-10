#include "shell.h"

/**
 * _myenv - Displays da Curr Env
 * @info: Struct having Potential Arg
 * Return: 0 (always)
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Gets Val of an Env Var
 * @name: Name Environment Variable
 * @info: Struct having Potential Args
 * Return: value of env var
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *nd = info->env;
	char *pt;

	while (nd)
	{
		pt = starts_with(nd->str, name);
		if (pt && *pt)
			return (pt);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Init a New Env Var or Change an Existing One
 * @info: Struct having Potential Arg
 * Return: zero always
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Delete an Env Var
 * @info: Struct having a Potential Args
 * Return: 0
 */
int _myunsetenv(info_t *info)
{
	int x = 0;

	if (info->argc == 1)
	{
		_eputs("Too few Arguments.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		_unsetenv(info, info->argv[x]);
	return (0);
}

/**
 * populate_env_list - Populates Env Linked List
 * @info: Struct having Potential Args
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *nd = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_node_end(&nd, environ[x], 0);
	info->env = nd;
	return (0);
}
