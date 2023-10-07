#include "shell.h"

/**
 * is_cmd - Checks whether a File is an Exec Cmd
 * @info: Struct Info
 * @path: File Path
 * Return: 1 if it is, or else 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat s;

	(void)info;
	if (!path || stat(path, &s))
		return (0);
	if (s.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Copy Chars
 * @pathstr: String Path
 * @start: Beginnning Index
 * @stop: Ending Index
 * Return: Ptr to New Buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int x = 0, m = 0;

	for (m = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buffer[m++] = pathstr[x];
	buffer[m] = 0;
	return (buffer);
}

/**
 * find_path - Identify this CMD in PATH String
 * @info: Struct Info
 * @pathstr: String Path
 * @cmd: CMD to search
 * Return: If found, return full path of CMD or else NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int x = 0, curr_index = 0;
	char *paths;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			paths = dup_chars(pathstr, curr_index, x);
			if (!*paths)
				_strcat(paths, cmd);
			else
			{
				_strcat(paths, "/");
				_strcat(paths, cmd);
			}
			if (is_cmd(info, paths))
				return (paths);
			if (!pathstr[x])
				break;
			curr_index = x;
		}
		x++;
	}
	return (NULL);
}
