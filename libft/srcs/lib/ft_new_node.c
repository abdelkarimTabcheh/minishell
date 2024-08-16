#include "../../includes/libft.h"
#include "../../../includes/minishell.h"

t_node	*ft_new_node(t_token_type type, char *str)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->str = str;
	new_node->next = NULL;
	return (new_node);
}