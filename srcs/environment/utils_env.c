#include "minishell.h"

void	ft_error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
