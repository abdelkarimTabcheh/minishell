#include "minishell.h"

/*free the list of env*/
void	free_envlist(t_env *head)
{
	while (head)
	{
		t_env *temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
    }
}

/*free the 2d array*/
void	free_array(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}
