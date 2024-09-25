# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 13:31:15 by ckonneck          #+#    #+#              #
#    Updated: 2024/09/25 16:24:40 by ckonneck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)
LIBFT_DIR = ./libft
LIBS = -L$(LIBFT_DIR) -lft

# Source files for minishell
MINISHELL_SRCS = minishell.c prompt.c echo.c cd.c functions.c functions2.c \
				pathing.c redirect.c
MINISHELL_OBJS = $(MINISHELL_SRCS:.c=.o)

# 'all' target
all: $(NAME)

$(NAME): libft $(MINISHELL_OBJS)
	$(CC) $(CFLAGS) -lreadline  $(MINISHELL_OBJS) $(LIBS) -o $(NAME)

# Compile libft
libft:
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
