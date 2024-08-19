#include "minishell.h"

/*the main function in the environment how take the env and
splite to key and value 
creat a node and added to the list*/
t_env	*environment(char **env)
{
	int		i;
	char	**env_line;
	t_env	*head;
	t_env	*node;

	i = 0;
	head = NULL;
	while (env[i])
	{
			env_line = ft_split(env[i], '=');
			if (!env_line)
				return (NULL);
			node = create_env_node(env_line);
			if (!node)
			{
				free_envlist(head);
				free_array(env_line);
				ft_error("error in env list");
			}
			printf("%s=%s\n", node->key, node->value);
			ft_add_env_list(&head, node);
			free_array(env_line);
		i++;
	}
	return (head);
}
