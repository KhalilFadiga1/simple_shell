#include "shell.h"

/**
 * _myhistory - Prints Hist list, 1 CMD by line, with line numbers
 * at the beginning, commencing at 0
 * @info: Struct having potent args which is used in maintaining cosnt
 * funct prottype
 * Return: zero always
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Initiates Alias to Chars
 * @info: Struct Param
 * @str: Alias String
 * Return: one if error or zero if it worked
 */
int unset_alias(info_t *info, char *str)
{
	char *q, m;
	int res;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	m = *q;
	*q = 0;
	res = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = m;
	return (res);
}

/**
 * set_alias - Sets Alias To String
 * @info: Struct Param
 * @str: String Alias
 * Return: zero if error or 1 if it worked
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Displays an Alias String
 * @node: An Alias Node
 * Return: 0 if successful, 1 if it fail
 */
int print_alias(list_t *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (b = node->str; b <= q; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics Alias Builtin (Main Alias)
 * @info: Struct having Potential Arg used in maintaining cosnt func prottype
 * Return: 0 if successful
 */
int _myalias(info_t *info)
{
	int x = 0;
	char *q = NULL;
	list_t *nd = NULL;

	if (info->argc == 1)
	{
		nd = info->alias;
		while (nd)
		{
			print_alias(nd);
			nd = nd->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		q = _strchr(info->argv[x], '=');
		if (q)
			set_alias(info, info->argv[x]);
		else
			print_alias(node_starts_with(info->alias, info->argv[x], '='));
	}
	return (0);
}
