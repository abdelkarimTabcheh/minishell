#include "minishell.h"


int	is_redir(t_token_type token_type)
{
	return (token_type == REDIRECTION_APPEND || token_type == REDIRECTION_HEREDOC
		|| token_type == REDIRECTION_IN || token_type == REDIRECTION_OUT);
}

/*
	Creates an AST node with the specified token type and initializes its members to NULL or default values.
*/
t_command_node	*init_cmd_node(t_token_type token_type)
{
	t_command_node	*node;

	node = (t_command_node *)malloc(sizeof(t_command_node));
	if (!node)
		return (NULL);
	node->arguments = NULL;
	node->redir_type = UNSET;
	node->token_type = token_type;
    node->right = NULL;
	node->left = NULL;
	return (node);
}

/*
	Counts the number of arguments, including the command, in the token list.
	Stops counting when a non-WORD token is encountered.
*/
int	count_arguments(t_node *token_list)
{
	t_node	*current_token;
	int		arg_count;

	arg_count = 0;
	current_token = token_list;
	while (current_token && current_token->type == WORD)
	{
		arg_count++;
		current_token = current_token->next;
	}
	return (arg_count);
}
/*
	Fills an AST node of type COMMAND with its corresponding arguments.
	Frees the tokens after copying their values, as they are no longer needed.
*/
void	fill_arguments(t_command_node *command_node, t_node **tokens, int arg_count)
{
	int		i;
	t_node	*current_token;
	t_node	*prev_token;

	current_token = *tokens;
	i = 0;
	while (i < arg_count)
	{
		command_node->arguments[i] = ft_strdup(current_token->str);
		prev_token = current_token;
		current_token = current_token->next;
		free(prev_token->str);
		free(prev_token);
		i++;
	}
	command_node->arguments[i] = NULL;
	*tokens = current_token;
}

/*
	Creates a redirection node, typically called from redirections.
*/
t_command_node	*create_redir_node(t_node *token)
{
	t_command_node	*redir_node;

	redir_node = init_cmd_node(token->type);
	redir_node->arguments = (char **)malloc(sizeof(char *) * 2);
	redir_node->arguments[0] = ft_strdup(token->str);
	redir_node->arguments[1] = NULL;
	free(token->str);
	free(token);
	return (redir_node);
}

