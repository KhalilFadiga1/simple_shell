#include "shell.h"

/**
 * input_buf - Buf Chained Cmd
 * @len: Addr of Length var
 * @info: Struct Param
 * @buf: Addr of Buf
 * Return: Read Bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t rd = 0;
	size_t len_pt = 0;

	if (!*len) /* Fill it if buffer is empty */
	{
		/* bfree((void **)info->cmd_buf) */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rd = getline(buf, &len_pt, stdin);
#else
		rd = _getline(info, buf, &len_pt);
#endif
		if (rd > 0)
		{
			if ((*buf)[rd - 1] == '\n')
			{
				(*buf)[rd - 1] = '\0'; /* delete Trailing new line */
				rd--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* If (_strchr(*buf, ';')) is it a Cmd Chain ? */
			{
				*len = rd;
				info->cmd_buf = buf;
			}
		}
	}
	return (rd);
}

/**
 * get_input - Obtain Line Minus The Newline
 * @info: Struct param
 * Return: Read Bytes
 */
ssize_t get_input(info_t *info)
{
	char **buf_p = &(info->arg), *q;
	ssize_t rd = 0;
	static size_t x, y, length;
	static char *buff; /* The ';' Cmd Chain Buf */

	_putchar(BUF_FLUSH);
	rd = input_buf(info, &buff, &length);
	if (rd == -1) /* End Of File */
		return (-1);
	if (length) /* Chain Buf is not empty (Cmds remains) */
	{
		y = x; /* Init New Iterator to Curr Buff Posit */
		q = buff + x; /* Get a return ptr */
		check_chain(info, buff, &y, x, length);
		while (y < length) /* Iterate to ; or End */
		{
			if (is_chain(info, buff, &y))
				break;
			y++;
		}
		x = y + 1; /* Incrase Past NULLED ';'' */
		if (x >= length) /* Gotten to End of Buf ? */
		{
			x = length = 0; /* Return Ptr to Curr Cmd Index */
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = q; /* Return Ptr to Curr Cmd Index */
		return (_strlen(q)); /* Return len of Curr Cmd */
	}
	*buf_p = buff; /* Else Not a Chain, Return buf frm _getline() */
	return (rd); /* Return Len of Buf frm getline func */
}

/**
 * read_buf - Reads a Buf
 * @i: Size
 * @buf: Buf
 * @info: Struct Param
 * Return: rd
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t rd = 0;

	if (*i)
		return (0);
	rd = read(info->readfd, buf, READ_BUF_SIZE);
	if (rd >= 0)
		*i = rd;
	return (rd);
}

/**
 * _getline - Gets Next Line of Input frm STDIN
 * @ptr: Addr of Ptr to Buf, Prealloc or NULL
 * @length: Size of Prealloc Ptr Buf If not NULL
 * @info: Struct Param
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t x, leng;
	size_t k;
	ssize_t rd = 0, str = 0;
	char *pt = NULL, *new_pt = NULL, *c;

	pt = *ptr;
	if (pt && length)
		str = *length;
	if (x == leng)
		x = leng = 0;
	rd = read_buf(info, buff, &leng);
	if ((rd == 0 && leng == 0) || rd == -1)
		return (-1);
	c = _strchr(buff + x, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : leng;
	new_pt = _realloc(pt, str, str ? str + k : k + 1);
	if (!new_pt) /* if malloc fails */
		return (pt ? free(pt), -1 : -1);
	if (str)
		_strncat(new_pt, buff + x, k - x);
	else
		_strncpy(new_pt, buff + x, k - x + 1);
	str += k - x;
	x = k;
	pt = new_pt;
	if (length)
		*length = str;
	*ptr = pt;
	return (str);
}

/**
 * sigintHandler - Block Ctrl-C
 * @sig_num: Signal Num
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
