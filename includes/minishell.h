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

int				count_tokens(char *str, int *index);
t_node			*tokenize_user_input(char *str);
int				report_syntax_errors(t_node *node_list);
int				verify_quotes(t_node *node_list);
void			free_envlist(t_env *head);
void			free_array(char **data);
void			ft_error(char *msg);
t_env	        *environment(char **env);
typedef enum e_redirection_type {
    UNSET,
    EXEC,
    DONE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_OUT_APPEND,
    HEREDOC,
}   t_redirection_type;

typedef struct s_command_node {
    t_token_type            token_type;           // The type of token (e.g., WORD, PIPE, REDIRECTION)
    t_redirection_type      redir_type;     // The type of redirection, if applicable(e.g., INPUT, OUTPUT)
    char                    **arguments;        // Arguments (command) strings
    struct s_command_node   *left;      // Pointer to the left child node
    struct s_command_node   *right;     // Pointer to the right child node
}   t_command_node;

// Structure representing the shell environment, including environment variables and other states.
typedef struct s_shell_env {
	t_env   			*vars;		// Pointer to the head of the linked list of environment variables.
	t_command_node		*tree;		// Pointer to the root of the command tree (AST) used for parsing commands.
	int					exit_code;	// Exit code of the last executed command.
}	t_shell_env;

t_command_node	*init_cmd_node(t_token_type token_type);
int	            count_arguments(t_node *token_list);
void	        fill_arguments(t_command_node *command_node, t_node **tokens, int arg_count);
t_command_node	*parse_redirection_or_command(t_node	**tokens);
t_command_node	*create_redir_node(t_node *token);
int	            is_redir(t_token_type token_type);


#endif