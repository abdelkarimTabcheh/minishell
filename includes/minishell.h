#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>

int     count_tokens(char *str, int *index);
t_node	*tokenize_user_input(char *str);
int	    report_syntax_errors(t_node *node_list);
int verify_quotes(t_node *node_list);



#endif