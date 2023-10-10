#include "shell.h"

/**
 * add_node - Appends Node to the beginning of the List
 * @head: Addr of Ptr to NOde Head
 * @str: Node String Field
 * @num: Node post used by History
 * Return: List Size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_hd;

	if (!head)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	_memset((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = num;
	if (str)
	{
		new_hd->str = _strdup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *head;
	*head = new_hd;
	return (new_hd);
}

/**
 * add_node_end - Appends Node to the end of the List
 * @head: Addr of Ptr to Node Head
 * @str: Node Str Field
 * @num: Node Index use by History
 * Return: List Size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nd, *nd;

	if (!head)
		return (NULL);
	nd = *head;
	new_nd = malloc(sizeof(list_t));
	if (!new_nd)
		return (NULL);
	_memset((void *)new_nd, 0, sizeof(list_t));
	new_nd->num = num;
	if (str)
	{
		new_nd->str = _strdup(str);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = new_nd;
	}
	else
		*head = new_nd;
	return (new_nd);
}

/**
 * print_list_str - Displays List_t Linked List str Elem
 * @h: Ptr to the beginning Node
 * Return: List Size
 */
size_t print_list_str(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - Remove Node at given Posit
 * @head: Addr of Ptr to the Beginning Node
 * @index: Post of Node to Remove
 * Return: one if it worked and 0 if it fails
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nd, *prev_nd;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		nd = *head;
		*head = (*head)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *head;
	while (nd)
	{
		if (x == index)
		{
			prev_nd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		x++;
		prev_nd = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * free_list - Frees All List Nodes
 * @head_ptr: Addr of Ptr 2 Node Head
 */
void free_list(list_t **head_ptr)
{
	list_t *nd, *next_nd, *hd;

	if (!head_ptr || !*head_ptr)
		return;
	hd = *head_ptr;
	nd = hd;
	while (nd)
	{
		next_nd = nd->next;
		free(nd->str);
		free(nd);
		nd = next_nd;
	}
	*head_ptr = NULL;
}
