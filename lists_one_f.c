#include "shell.h"

/**
 * list_len - Calc linked list length
 * @h: First Node Ptr
 * Return: List Size
 */
size_t list_len(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - Arr of list->str strings
 * @head: Ptr to the beginning node
 * Return: String Arr
 */
char **list_to_strings(list_t *head)
{
	list_t *nd = head;
	size_t y, x = list_len(head);
	char **strs;
	char *str;

	if (!head || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; nd; nd = nd->next, x++)
	{
		str = malloc(_strlen(nd->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, nd->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}

/**
 * print_list - Displays List_t Linked List elements
 * @h: ptr to First Node
 * Return: List Size
 */
size_t print_list(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - Node Strings that Commences with Prefix
 * @prefix: Matching String
 * @c: Next Char after matched prefix
 * @node: Ptr to Head List
 * Return: If unmatched, NULL or the matched node
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *q = NULL;

	while (node)
	{
		q = starts_with(node->str, prefix);
		if (q && ((*q == c) || (c == -1)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Obtains Node Position
 * @node: Node Ptr
 * @head: List Head Ptr
 * Return: Node Posit or -1 if no index
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
