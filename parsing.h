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
    T_WORD, // 0
    T_QUOTE, // 1
    T_DQUOTE, // 2
    T_PIPE, // 3 
    T_IN,  // <  4
    T_OUT, // >  5 
    T_HEREDOC, // <<  6 
    T_APPEND // >> 7 
}   t_token_types;

typedef struct	s_token
{
    t_token_types	type;
    char		    *value;
    int             append;
    struct s_token  *next;
}					t_token;

typedef struct	s_cmd
{
	char		    **args;
    char            **red_args;
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
//FREE
void    free_env(t_env **list);
void    free_tokens(t_token **list);
void    free_cmds(t_cmd *head);
void	free_matrix(char **args);
void    free_all(t_cmd *cmd_list, t_token *token_list);
//CMD
t_token *find_next_cmd(t_token *tokens);
t_token *get_redirectons(t_token *tokens);
char    **get_args(t_token *tokens);
size_t  nb_of_args(t_token *tokens);
size_t	nb_of_redir(t_token	*tokens);
void    print_cmd_list(t_cmd *cmd_list);
t_cmd	*create_cmd_list(t_token *tokens);
char	**get_red_args(t_token *tokens);
//TOKENS
t_token_types    set_type(const char *str);
int	    list_len(t_token *head);
void    print_token_list(t_token *head);
t_token	*create_token(t_token_types type, const char *value);
void    append_token(t_token **list, t_token *new);
t_token	*find_last_token(t_token *head);
int     add_operator(t_token **list, char *line, int i);
int	    add_quote(t_token **list, char *line, int i);
int	    add_words(t_token **list, char *line, int i);
t_token *tokenize(char *line);
int     is_pipe(t_token *token);
int     is_redirection(t_token *token);
int     is_operator(const char *s);
//UTILS
int     is_word(const char *s);
int     ft_isspace(char c);
int     is_quote(char c);
char	*ft_strndup(const char *c, int n);
int		skip_whitespace(char *line, int i);
int     ft_strcmp(const char *s1, char const *s2);
int     has_char(const char *str, int c);
//ENV
t_env   *create_env(char *value);
t_env   *find_last_env(t_env *head);
void	append_env(t_env **list, t_env *new);
void    print_env_list(t_env *head);
t_env	*init_env_list(char **envp);
void    ft_env(char **envp);
t_env   *copy_env_list(t_env *env_list);
void	sort_env_list(t_env *env_list);
void    print_sorted_env(t_env *env_list);
void	ft_export(t_env **env_list, char *name, char *value);
t_env	*find_env_var(t_env *env_list, char *name);
void	ft_unset(t_env **env_list, char *name);
char    *ft_getenv(t_env *env_list, char *name);

#endif