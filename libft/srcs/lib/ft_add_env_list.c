#include "../../includes/libft.h"

t_env	*get_last_env_node(t_env *node_list)
{
	t_env	*current;

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
int	ft_add_env_list(t_env **lst, t_env *new)
{
	t_env	*last_node;

	if (!new || !lst)
		return (0);
	new->next = NULL;
	if (!(*lst))
	{
		(*lst) = new;
		return (1);
	}
	last_node = get_last_env_node(*lst);
	last_node->next = new;
	last_node = *lst;
	return (1);
}
