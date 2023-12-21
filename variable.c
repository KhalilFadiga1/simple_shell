#include "shell.h"

/**
 * is_chain - Verify if Curr Characetr in Buf is a Chain Delim
 * @info: Struct Param
 * @buf: Buf Character
 * @p: Addr of Curr Post in Buffer
 * Return: If it is, 1 is return and if not, 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';') /* Found at the end of the Cmd */
	{
		buf[i] = 0; /* change ; with NULL */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * check_chain - Verify whether to Continue with Chaining based on last result
 * @info: Struct Param
 * @buf: Buf Char
 * @p: An addr of Curr Post in buffer
 * @i: Beginning Point in Buf
 * @len: Buf length
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t m = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			m = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			m = len;
		}
	}
	*p = m;
}

/**
 * replace_alias - Change the Aliases in Tokenized String
 * @info: Struct Param
 * Return: If replace 1, or else 0
 */
int replace_alias(info_t *info)
{
	int x;
	list_t *nd;
	char *pt;

	for (x = 0; x < 10; x++)
	{
		nd = node_starts_with(info->alias, info->argv[0], '=');
		if (!nd)
			return (0);
		free(info->argv[0]);
		pt = _strchr(nd->str, '=');
		if (!pt)
			return (0);
		pt = _strdup(pt + 1);
		if (!pt)
			return (0);
		info->argv[0] = pt;
	}
	return (1);
}

/**
 * replace_vars - Change Vars in Tokenized String
 * @info: Struct
 * Return: If replace 1 and 0 if not
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *nd;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;
		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nd = node_starts_with(info->env, &info->argv[x][1], '=');
		if (nd)
		{
			replace_string(&(info->argv[x]),
				_strdup(_strchr(nd->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - Change a String
 * @old: Addr of Old String
 * @new: New String to be subtituted
 * Return: If replace 1, or else 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
