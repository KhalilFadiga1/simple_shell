#include "shell.h"

/**
 * get_history_file - Obtains a History File
 * @info: Struct Param
 * Return: Alloc Str having History File
 */
char *get_history_file(info_t *info)
{
	char *dir, *buff;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - Make a File, or Adds to Available File
 * @info: Struct Param
 * Return: 1 if successful, -1 if otherwise
 */
int write_history(info_t *info)
{
	list_t *nd = NULL;
	char *flname = get_history_file(info);
	ssize_t fd;

	if (!flname)
		return (-1);
	fd = open(flname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(flname);
	if (fd == -1)
		return (-1);
	for (nd = info->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Read File History
 * @info: Struct Param
 * Return: Histcount if it worked, or else 0
 */
int read_history(info_t *info)
{
	char *buff = NULL, *flname = get_history_file(info);
	ssize_t rlen, fld, fsz = 0;
	struct stat str;
	int x, end = 0, linenum = 0;

	if (!flname)
		return (0);
	fld = open(flname, O_RDONLY);
	free(flname);
	if (fld == -1)
		return (0);
	if (!fstat(fld, &str))
		fsz = str.st_size;
	if (fsz < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsz + 1));
	if (!buff)
		return (0);
	rlen = read(fld, buff, fsz);
	buff[fsz] = 0;
	if (rlen <= 0)
		return (free(buff), 0);
	close(fld);
	for (x = 0; x < fsz; x++)
		if (buff[x] == '\n')
		{
			buff[x] = 0;
			build_history_list(info, buff + end, linenum++);
			end = x + 1;
		}
	if (end != x)
		build_history_list(info, buff + end, linenum++);
	free(buff);
	info->histcount = linenum;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Appends Entry to History Linked List
 * @buf: Buffer
 * @linecount: Histcount, History Linecount
 * @info: Struct having Potential Arg
 * Return: Zero always
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nd = NULL;

	if (info->history)
		nd = info->history;
	add_node_end(&nd, buf, linecount);
	if (!info->history)
		info->history = nd;
	return (0);
}

/**
 * renumber_history - Renums History Linked List
 * @info: struct having Potential Arg
 * Return: A novel Histcount
 */
int renumber_history(info_t *info)
{
	list_t *nd = info->history;
	int x = 0;

	while (nd)
	{
		nd->num = x++;
		nd = nd->next;
	}
	return (info->histcount = x);
}
