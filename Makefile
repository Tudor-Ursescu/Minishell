# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 13:31:15 by ckonneck          #+#    #+#              #
#    Updated: 2024/10/29 13:00:01 by ckonneck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)
LIBFT_DIR = ./libft
LIBS = -L$(LIBFT_DIR) -lft -lreadline
# Source files for minishell
MINISHELL_SRCSTUDOR = parse_utils.c function_utils.c tokens1.c\
				tokens2.c env1.c env2.c env3.c tokenize.c\
				freeing.c cmd1.c cmd2.c debug.c env_utils2.c\
				syntax.c sig_handle.c env_utils1.c function_utils4.c
MINISHELL_SRCSCHRIS = minishell.c prompt.c echo.c cd.c functions.c \
				pathing.c redirect.c heredoc.c pipeline.c \
				freeing2.c function_utils2.c function_utils3.c
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
