NAME			=	minishell

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -I includes/ -I $(LIB_DIR) -I /Users/$(USER)/.brew/opt/readline/include

LIBFT			=	$(LIB_DIR)libft.a

HEADER			=	includes/minishell.h libft/libft.h

BUILTINS		=	is_build_in		unset	echo	export_all	cd	export	exit	pipex	build_pwd_env

ENV				=	create_env	init_megashell env_helper

VALID			=	valid_parse	valid_cmd redirects	heredoc	del_redir	valid_utils

MAIN			=	minishell	signal signal_helper

PARSING			=	parser env_var	quotes redirect pipe execute

TOOLS			=	lists free_all

SRC				=	$(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
					$(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
					$(addsuffix .c, $(addprefix srcs/valid/, $(VALID))) \
					$(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
					$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
					$(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \

OBJ				=	$(SRC:c=o)

LIB_DIR			=	libft/

all				:	$(NAME)

$(NAME)			:	$(LIBFT) $(OBJ) $(HEADER)
	@echo "\n"
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJ) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
	@echo "\n\033[0mDone !"

$(LIBFT)		:
	@$(MAKE) -sC $(LIB_DIR)

%.o				:		%.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean			:
	@$(MAKE) -sC $(LIB_DIR) clean
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean			:
	@rm -f $(LIBFT)
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re				:	fclean all

norm:
	norminette $(SRC) includes/minishell.h

.PHONY: clean fclean re test norm