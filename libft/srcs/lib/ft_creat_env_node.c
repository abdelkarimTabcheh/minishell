#include "../../includes/libft.h"
#include "../../../includes/minishell.h"

/*creat the node of the environment*/
t_env	*create_env_node(char **data)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(data[0]);
	new_node->value = ft_strdup(data[1]);
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}