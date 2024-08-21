#include "minishell.h"

int is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

/*
	Checks whether a given string has any unclosed quotes.
*/

bool are_quotes_closed(const char   *str)
{
	int     i;
	char    quote;

	i = 0;
	quote = 0; // no quotes are open.
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (quote == str[i])
				quote = 0; // Close the current quote
			else if (quote == 0)
				quote = str[i]; // Open a new quote
		}
		i++;
	}
	return (quote == 0); // Returns true if quotes are closed
}

/*
	Verifies if all nodes in a linked list have properly closed quotes in their strings.
*/
int verify_quotes(t_node *node_list)
{
	t_node  *current;

	current = node_list;
	while (current)
	{
		if (!are_quotes_closed(current->str))
		{
			ft_putendl_fd("Syntax error: unclosed quotes", 2);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

/*
	Searches for syntax errors in the input by checking for binary operations 
	with less than 2 inputs in a linked list of command nodes.
*/

t_node  *find_syntax_error(t_node *node_list)
{
	t_node	*current;

	current = node_list;
	while (current)
	{
		if (!ft_strncmp(current->str, "<<", 2))
		{
			if (!current->next)
				return (current);
		}
		else if (!ft_strncmp(current->str, "|", 1) ||
         (!ft_strncmp(current->str, "<", 1) && ft_strncmp(current->str, "<<", 2)) ||
         !ft_strncmp(current->str, ">", 1) ||
         !ft_strncmp(current->str, ">>", 2))
		 	if (!current->next || node_list == current)
                return (current);
		current = current->next;
	}
	return (NULL);
}

/*
	Checks for syntax errors in a linked list of command nodes and prints appropriate error messages if any errors are found.
*/

int	report_syntax_errors(t_node *node_list)
{
	t_node	*error_node;

	error_node = find_syntax_error(node_list);
	if (error_node != NULL)
	{
		if (!ft_strncmp(error_node->str, "|", 1))
			printf("Error: %s should have a command before and after\n", error_node->str);
		else if (!ft_strncmp(error_node->str, "<<", 2))
			printf("Error: %s should be followed by a valid delimiter\n", error_node->str);
		else
			printf("Error: %s should have a command before and be followed by a valid filename\n", error_node->str);
		return (0);
	}
	return (1);
}