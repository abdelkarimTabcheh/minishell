#include "../../includes/minishell.h"

/*
	Identifies a special token at a given index and adjusts the index accordingly.
	Returns the length of the identified token.
*/

int process_special_token(const char *str, int *index)
{
    // Check for double character tokens "<<", ">>"
    if ((str[*index] == '<' && str[*index + 1] == '<') ||
        (str[*index] == '>' && str[*index + 1] == '>')) 
    {
        *index += 2;
        return (2);
    }

    // Check for single character tokens "<", ">", "|"
    if (str[*index] == '<' || str[*index] == '>' || str[*index] == '|')
    {
        (*index)++;
        return (1);
    }

    // Return -1 if no special token is found
    return (-1);
}

/*
	Checks if the character at the given index is a stopper,
	including end of string, special tokens, or whitespace.
	Returns non-zero if true, zero otherwise.
*/

int is_stopper(const char *str, int index)
{
    return (!str[index] ||
            (str[index] == '<' && str[index + 1] == '<') ||
            (str[index] == '>' && str[index + 1] == '>') ||
            str[index] == '<' || str[index] == '>' || str[index] == '|' ||
            str[index] == ' ' || str[index] == '\t');
}


/*
	Processes str string to count characters until a stopper is found.
	Tracks quote states to correctly handle quoted segments.
	Returns the number of characters processed.
*/
int	process_str_until_stopper(char *str, int *index, int *in_sq, int *in_dq)
{
	int	count;

	count = 0;
	while (str[*index])
	{
		if (str[*index] == '\'' && *in_dq == 0)
		{
			if (*in_sq == 0)
				*in_sq = 1;
			else
				*in_sq = 0;
		}
		else if (str[*index] == '\"' && *in_sq == 0)
		{
			if (*in_dq == 0)
				*in_dq = 1;
			else
				*in_dq = 0;
		}
		if (is_stopper(str, *index) && *in_sq == 0 && *in_dq == 0)
			return (count);
		(*index)++;
		count++;
	}
	return (count);
}

/*
	Counts non-special characters in the str string, excluding those
	between quotes, until a special character, whitespace, or quote is encountered.
*/
int count_command_char(const char *str, int *index)
{
    int count;
    int in_single_quote;
    int in_double_quote;

    count = 0;
    in_single_quote = 0;
    in_double_quote = 0;

    while (str[*index])
    {
        if (is_stopper(str, *index) && in_single_quote == 0 && in_double_quote == 0)
            return (count);
        count += process_str_until_stopper((char *)str, index, &in_single_quote, &in_double_quote);
    }
    return (count);
}

/*
	Counts the number of characters in the next token from the str string,
	skipping initial whitespace. Determines if the token is a special character
	sequence or a command. Returns the length of the token.
*/
int count_tokens(char *str, int *index) 
{
    int count;
    
    count = -1;

    // Skip whitespace
    while (str[*index] == ' ' || str[*index] == '\t')
        (*index)++;

    // Check for special tokens
    if (str[*index] == '|' || str[*index] == '<' || str[*index] == '>' ||
        !strncmp(&str[*index], "<<", 2) || !strncmp(&str[*index], ">>", 2))
    {
        count = process_special_token(str, index);
    }
    // Check for command tokens
    else if (str[*index])
    {
        count = count_command_char(str, index);
    }

    return (count);
}
