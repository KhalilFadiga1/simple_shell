#include "shell.h"

/**
 * *_memset - Fills a Memory Space with Constant Byte
 * @s: Ptr to Memory Space
 * @b: Bytes to be used to fill the ptr *s
 * @n: Number of Bytes to fill
 * Return: Ptr to the Memory Space (s)
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;
	return (s);
}

/**
 * ffree - Empties Chars of String
 * @pp: String of String
 */
void ffree(char **pp)
{
	char **m = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(m);
}

/**
 * _realloc - Reassign a Memory Block
 * @ptr: Ptr to Previous Mem Alloc'd Block
 * @old_size: Previous Block Byte Size
 * @new_size: New Block Byte Size
 * Return: Ptr to Realloc'd Memory Name
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	q = malloc(new_size);
	if (!q)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}
