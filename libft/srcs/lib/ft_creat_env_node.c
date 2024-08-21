#include "../../includes/libft.h"
#include "../../../includes/minishell.h"

int	count_value(char **data)
{
	int i;

	i = 0;
	while (data[i])
		i++;
	return (i);
}

/*if the variable contain in the value '='
this function add the '=' to the value*/
char	*join_free(char *old, char *s1)
{
	char	*new;
	char	*s2;
	char	*temp;

	temp = ft_strdup(old);
	s2 = ft_strjoin(temp, "=");
	new = ft_strjoin(s2, s1);
	free(old);
	free(temp);
	free(s2);
	return (new);
}

/*creat the node of the environment*/
t_env	*create_env_node(char **data)
{
	t_env	*new_node;
	int		i;

	i = 2;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(data[0]);
	if (count_value(data) == 1)
		new_node->value = ft_strdup("");
		
	else
	{
		new_node->value = ft_strdup(data[1]);
		while (data[i])
		{
			new_node->value = join_free(new_node->value, data[i]);
			i++;
		}
	}
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
