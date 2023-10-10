#include "shell.h"

/**
 * bfree - Frees a Ptr and Nulls da Addr
 * @ptr: Addr of Ptr to be freed
 * Return: 1 if successful, or else 0
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
