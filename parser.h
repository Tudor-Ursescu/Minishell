/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:08:51 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/25 15:07:27 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"

typedef enum e_token_types
{
    T_PIPE,
    T_ARG,
    T_QUOTE,
    T_DQUOTE,
    T_RED_TO,
    T_RED_FROM,
    T_HEREDOC,
    T_REDIR_APPEND,
    T_END
}   t_token_types;

typedef struct	s_args
{
    t_token_types	type;
    char			*value;
    struct s_args   *next;
}					t_args;

typedef struct	s_command
{
	char				*path;
	char				**args;
    struct s_command	*next;
}				t_command;

typedef struct  s_env
{
    char			*value;
	struct s_env	*next;
}   t_env;

typedef struct s_data
{
    t_args      *args;
    t_command   *cmd;
}   t_data;

//ARGS
int	    list_len(t_args *head);
void    free_args(t_args **list);
void    print_arg_list(t_args *head);
t_args	*create_arg(t_token_types type, const char *value);
void	prepend_arg(t_args **list, t_args *new);
void    append_arg(t_args **list, t_args *new);
t_args	*find_last_arg(t_args *head);
int 	add_redir(t_args **head, char *line, int i, int *cmd);
int		add_quote_arg(t_args **list, char *line, int i, char quote);
int		add_arg(t_args **list, char *line, int i, int *cmd);
int 	add_pipe(t_args **head, int *i);
int 	parse_args(t_args **list, char *line);
//UTILS
int		is_word_char(char c);
int		ft_isspace(char c);
char	*ft_strndup(const char *c, int n);
int		skip_whitespace(char *line, int i);
//ENV
t_env   *create_env(char *value);
t_env   *find_last_env(t_env *head);
void	append_env(t_env **list, t_env *new);
void	free_env(t_env **list);
void    print_env_list(t_env *head);
t_env	*init_env_list(char **envp);
void    ft_env(char **envp);
#endif