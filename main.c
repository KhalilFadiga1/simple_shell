#include "shell.h"

/**
 * main - Entrance
 * @ac: Argument Counter
 * @av: Argument Vector
 * Return: 0 if worked or else 0
 */
int main(int ac, char **av)
{
	int fdr = 2;
	info_t info[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdr)
		: "r" (fdr));
	if (ac == 2)
	{
		fdr = open(av[1], O_RDONLY);
		if (fdr == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fdr;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
