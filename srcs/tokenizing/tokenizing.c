#include "minishell.h"

void	free_tokens(t_node **node_list)
{
	t_node	*current;
	t_node	*next;

	if (!node_list || !*node_list)
		return ;
	current = *node_list;
	while (current)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = next;
	}
	*node_list = NULL;
}

/*
	fill tokens with data
*/
void    fill_tokens(t_node **node_list, char *input_str, int prev_i, int i)
{
	char	*str;
	int		index;

	index = 0;
	str = (char *)malloc(sizeof(char) * ((i - prev_i) + 1));
	str[(i - prev_i)] = '\0';
	while (prev_i < i)
		str[index++] = input_str[prev_i++];
	if (str)
	{
		str = ft_strtrim(str, "\t");
		if (!ft_strcmp(str, "<"))
			ft_add_back(node_list, ft_new_node(REDIRECTION_IN, str));
		else if (!ft_strcmp(str, ">"))
			ft_add_back(node_list, ft_new_node(REDIRECTION_OUT, str));
		else if (!ft_strcmp(str, "<<"))
			ft_add_back(node_list, ft_new_node(REDIRECTION_HEREDOC, str));
		else if (!ft_strcmp(str, ">>"))
			ft_add_back(node_list, ft_new_node(REDIRECTION_APPEND, str));
		else if (!ft_strcmp(str, "|"))
			ft_add_back(node_list, ft_new_node(PIPE, str));
		else
			ft_add_back(node_list, ft_new_node(WORD, str));
	}
}

/*
	Tokenizes the user input string into a linked list of tokens,
	handling single quotes, double quotes, special characters,
	and commands. Skips invalid tokens and performs error checking.
*/
t_node	*tokenize_user_input(char *str)
{
	int		i;
	int		count;
	int		prev_index;
	t_node	*tokens;

	i = 0;
	tokens = NULL;
	while (str[i])
	{
		prev_index = i;
		count = count_tokens(str, &i);
		if (count > 0)
			fill_tokens(&tokens, str, prev_index, i);
	}
	if (!report_syntax_errors(tokens) || !verify_quotes(tokens))
	{
		free_tokens(&tokens);
		return (NULL);
	}
	return (tokens);
}
