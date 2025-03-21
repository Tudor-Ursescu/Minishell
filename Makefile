# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 13:31:15 by ckonneck          #+#    #+#              #
#    Updated: 2025/03/21 10:23:06 by tursescu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)
LIBFT_DIR = ./libft
LIBS = -L$(LIBFT_DIR) -lft -lreadline
# Source files for minishell
MINISHELL_SRCSTUDOR = src/parse_utils.c src/function_utils.c src/tokens1.c\
				src/tokens2.c src/env1.c src/env2.c src/env3.c src/tokenize.c\
				src/freeing.c src/cmd1.c src/cmd2.c src/debug.c src/env_utils2.c\
				src/syntax.c src/sig_handle.c src/env_utils1.c src/function_utils4.c
MINISHELL_SRCSCHRIS = src/minishell.c src/prompt.c src/echo.c src/cd.c src/functions.c \
				src/pathing.c src/redirect.c src/heredoc.c src/pipeline.c \
				src/freeing2.c src/function_utils2.c src/function_utils3.c
MINISHELL_OBJS = $(MINISHELL_SRCSTUDOR:.c=.o) $(MINISHELL_SRCSCHRIS:.c=.o)
# 'all' target
all: $(NAME)

$(NAME): $(MINISHELL_OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(LIBS) -o $(NAME)
	
# Compile libft
libft/libft.a:
	$(MAKE) -C $(LIBFT_DIR)
# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 'clean' rule
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(MINISHELL_OBJS)

# 'fclean' rule
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# 're' rule
re: fclean all

# valgrind rule
valgrind: $(NAME)
		valgrind --leak-check=full --track-origins=yes ./$(NAME) $(ARGS)
		
# extra options: --verbose --show-leak-kinds=all --log-file=valgrind-out.txt
#norminette rule
norminette: $(PHILO_SRSC)
		norminette $(PHILO_SRSC)

# Declare phony targets
.PHONY: all libft clean fclean re
