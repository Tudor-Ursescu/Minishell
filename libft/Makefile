# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 08:26:08 by ckonneck          #+#    #+#              #
#    Updated: 2024/07/09 13:52:35 by ckonneck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS        =    ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_memset.c \
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c \
					ft_printf.c ft_printfchar.c ft_printfnumber.c ft_printfstring.c \
					ft_printfhex.c ft_printfsmallhex.c ft_printfunsigned.c \
					ft_printfpointer.c get_next_line.c get_next_line_utils.c
OBJS        :=    $(SRCS:.c=.o)
CC          =    cc
RM          =    rm -f
CFLAGS      =    -Wall -Werror -Wextra
NAME        =    libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re

#-r: Replace existing members of the archive with new ones. If the archive does not exist, it will be created.
#-c: Create the archive. This option ensures that the archive is created even if it already exists.
#-s: Write an object-file index into the archive. This makes the library searchable, allowing tools like nm, ar,
# and others to quickly find symbols within the library.