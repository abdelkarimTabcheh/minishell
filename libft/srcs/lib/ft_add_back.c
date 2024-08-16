#include "../../includes/libft.h"

t_node	*get_last_node(t_node *node_list)
{
	t_node	*current;

	if (!node_list)
		return (NULL);
	current = node_list;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

/*
	add a node to end of linked list
*/
int	ft_add_back(t_node **lst, t_node *new)
{
	t_node	*last_node;

	if (!new || !lst)
		return (0);
	new->next = NULL;
	if (!(*lst))
	{
		(*lst) = new;
		return (1);
	}
	last_node = get_last_node(*lst);
	last_node->next = new;
	last_node = *lst;
	return (1);
}
