#include "shell.h"

/**
 * get_environ - String Arr Copy of Environ
 * @info: Struct having Potential Arg used in
 * maintaining const func prottype
 * Return: Zero always
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - Delete an Env Variable
 * @info: Struct having Potential Arg use in Maintaining
 * Const Func Prottype
 * @var: String Env Var Property
 * Return: 1 if successful, or else 0
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *nd = info->env;
	size_t x = 0;
	char *q;

	if (!nd || !var)
		return (0);
	while (nd)
	{
		q = starts_with(nd->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), x);
			x = 0;
			nd = info->env;
			continue;
		}
		nd = nd->next;
		x++;
	}
	return (info->env_changed);
}

/**
 * _setenv - init a new  env var or change an available 1
 * @info: Struct having Potential Arg
 * @var: String Environment Variable
 * @value: String Environment Value
 * Return: Zero always
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *q, *buff = NULL;
	list_t *nd;

	if (!var || !value)
		return (0);
	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	nd = info->env;
	while (nd)
	{
		q = starts_with(nd->str, var);
		if (q && *q == '=')
		{
			free(nd->str);
			nd->str = buff;
			info->env_changed = 1;
			return (0);
		}
		nd = nd->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
