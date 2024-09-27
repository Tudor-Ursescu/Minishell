/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:08:51 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/27 16:01:49 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
    T_WORD,
    T_QUOTE,
    T_DQUOTE,
    T_PIPE,
    T_IN,  // <
    T_OUT, // >
    T_HEREDOC, // <<
    T_APPEND, // >>
    T_END
}   t_token_types;

typedef struct	s_token
{
    t_token_types	type;
    char		    *value;
    struct s_token  *next;
}					t_token;

typedef struct	s_cmd
{
	char		    **args;
    struct s_token  *redirections;      
    struct s_cmd    *next;
}				t_cmd;

typedef struct  s_env
{
    char			*value;
	struct s_env	*next;
}   t_env;

typedef struct s_data
{
    t_token      *args;
    t_cmd        *cmd;
    t_env        *env;
}   t_data;

//TOKENS
int	    list_len(t_token *head);
void    free_tokens(t_token **list);
void    print_token_list(t_token *head);
t_token	*create_token(t_token_types type, const char *value);
void	prepend_token(t_token **list, t_token *new);
void    append_token(t_token **list, t_token *new);
t_token	*find_last_token(t_token *head);
int 	add_redir(t_token **head, char *line, int i, int *cmd);
int		add_quote_arg(t_token **list, char *line, int i, char quote);
int		add_arg(t_token **list, char *line, int i, int *cmd);
int 	add_pipe(t_token **head, int i);
int 	parse_args(t_token **list, char *line);
bool    is_pippe(t_token *token);
bool    is_redirection(t_token *token);
//UTILS
int		is_word_char(char c);
int		ft_isspace(char c);
char	*ft_strndup(const char *c, int n);
int		skip_whitespace(char *line, int i);
int     ft_strcmp(const char *s1, char const *s2);
//ENV
t_env   *create_env(char *value);
t_env   *find_last_env(t_env *head);
void	append_env(t_env **list, t_env *new);
void	free_env(t_env **list);
void    print_env_list(t_env *head);
t_env	*init_env_list(char **envp);
void    ft_env(char **envp);

#endif