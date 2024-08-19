NAME					= minishell
LIB 					= libft.a
OUT_DIR					= ./
SRC_DIR					= srcs/
TOKENIZATION_DIR		= $(SRC_DIR)tokenizing/
ENVIRONMENT_DIR		= $(SRC_DIR)environment/

SRC_FILES =		$(SRC_DIR)minishell.c \
				$(TOKENIZATION_DIR)utils.c \
				$(TOKENIZATION_DIR)tokenizing.c  \
				$(TOKENIZATION_DIR)error_handling.c \
				$(ENVIRONMENT_DIR)allocation.c \
				$(ENVIRONMENT_DIR)environment.c \
				$(ENVIRONMENT_DIR)utils_env.c \

CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror -Iincludes -lreadline -lncurses


LIB_DIR 			= libft


OBJ_DIR	= objs/
OBJ_FILES = $(addprefix $(OBJ_DIR), $(notdir $(SRC_FILES:.c=.o)))

all: $(OBJ_DIR) $(LIB_DIR)/$(LIB) $(NAME)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIB)
	
$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o : $(TOKENIZATION_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o : $(ENVIRONMENT_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR)/$(LIB):
	@$(MAKE) -s -C $(LIB_DIR)
	@cp $(LIB_DIR)/$(LIB) .

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIB_DIR) clean

fclean: clean
	@rm -f $(LIB)
	@$(MAKE) -s -C $(LIB_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re