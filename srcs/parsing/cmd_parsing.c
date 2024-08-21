#include "minishell.h"

/*
	Creates a command node with commands and their arguments.
*/
t_command_node	*parse_command(t_node **tokens)
{
	t_command_node	*command_node;
	int				arg_count;

	command_node = init_cmd_node(WORD);
	arg_count = count_arguments(*tokens);
	command_node->arguments = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->arguments)
		return (NULL);
	fill_arguments(command_node, tokens, arg_count);
	return (command_node);
}

/*
	Creates a redirection node and links it to the corresponding file node.
*/
t_command_node	*build_redirection_tree(t_node **tokens, t_node *current_token)
{
	t_command_node	*redir_node;

	redir_node = init_cmd_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redir_node->left = parse_redirection_or_command(tokens);
	redir_node->right = create_redir_node(current_token->next);
	free(current_token->str);
	free(current_token);
	return (redir_node);
}

/*
	Recursively parses and creates a redirection node or falls back to parsing a command.
*/
t_command_node	*parse_redirection_or_command(t_node	**tokens)
{
	t_node			*current_token;
	t_command_node	*redir_node;

	if (!(*tokens))
		return (NULL);
	current_token = *tokens;

	if (is_redir((*tokens)->type))
		return (build_redirection_tree(tokens, current_token));

	while (*tokens && (*tokens)->next)
	{
		current_token = (*tokens)->next;
		if (is_redir(current_token->type))
		{
			redir_node = build_redirection_tree(tokens, *tokens);
			*tokens = current_token->next;
			return (redir_node);
		}
		*tokens = current_token;
	}
	return (parse_command(tokens));
}

/*
	Creates a pipe node.
	- The left child parses redirections.
	- The right child recursively parses additional pipes.
	Falls back on parsing redirections if no pipe is found.
*/
t_command_node	*parse_pipe_and_redir(t_node **tokens)
{
	t_node			*current_token;
	t_command_node	*pipe_node;
	t_node			*start;

	start = *tokens;
	while ((*tokens) && (*tokens)->next)
	{
		current_token = (*tokens)->next;
		if (current_token->type == PIPE)
		{
			pipe_node = init_cmd_node(PIPE);
			(*tokens)->next = NULL;
			pipe_node->left = parse_redirection_or_command(&start);
			pipe_node->right = parse_pipe_and_redir(&(current_token->next));
			free(current_token->str);
			free(current_token);
			return (pipe_node);
		}
		(*tokens) = current_token;
	}
	return (parse_redirection_or_command(&start));
}

/*
	Initiates the Abstract Syntax Tree (AST) generation process from the tokenized input.
*/
t_command_node	*generate_ast(t_node **tokens)
{
	if (!tokens || !(*tokens))
		return (NULL);
	return (parse_pipe_and_redir(tokens));
}
