/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:08:51 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/28 11:48:57 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_sig_nb;

typedef enum e_token_types
{
	T_WORD,
	T_QUOTE,
	T_DQUOTE,
	T_PIPE,
	T_IN,
	T_OUT,
	T_HEREDOC,
	T_APPEND
}					t_token_types;

typedef struct s_token
{
	t_token_types	type;
	char			*value;
	int				append;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			**args;
	struct s_token	*redirections;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct t_pipeinfo
{
	int				prev_fd;
	int				prev_pid;
	int				number_of_pipes;
}					t_pipeinfo;

typedef struct s_data
{
	t_token			*token_list;
	t_cmd			*cmd_list;
	t_env			*env;
	t_pipeinfo		pipeinfo;
	char			**new_env;
	char			*line;
	int				exit;
	int				nb_heredoc;
}					t_data;

void			free_env(t_env **list);
void			free_tokens(t_token **list);
void			free_cmds(t_cmd *head);
void			free_matrix(char **args);
void			free_all(t_data *data);
void			free_all_env(t_data *data);
t_token			*find_next_cmd(t_token *tokens);
t_token			*get_redirections(t_token *tokens);
char			**get_args(t_token *tokens);
size_t			nb_of_args(t_token *tokens);
void			print_cmd_list(t_cmd *cmd_list);
t_cmd			*create_cmd_list(t_token *tokens);
void			link_command(t_cmd **cmd_list, t_cmd **last_cmd,
					t_cmd *new_cmd);
int				process_current_cmd(t_cmd *cmd, t_token *curr_tokens,
					t_cmd *cmd_list);
t_cmd			*create_cmd(void);
t_token_types	set_type(const char *str);
int				list_len(t_token *head);
void			print_token_list(t_token *head);
void			append_token(t_token **list, t_token *new);
t_token			*create_token(t_token_types type, const char *value);
t_token			*find_last_token(t_token *head);
int				add_operator(t_token **list, char *line, int i);
int				add_quote(t_token **list, char *line, int i, t_data *data);
int				add_words(t_token **list, char *line, int i);
t_token			*tokenize(char *line, t_data *data);
int				is_pipe(t_token *token);
int				is_redirection(t_token *token);
int				is_operator(const char *s);
int				is_word(const char *s);
int				ft_isspace(char c);
int				is_quote(char c);
char			*ft_strndup(const char *c, int n);
int				skip_whitespace(char *line, int i);
int				ft_strcmp(const char *s1, char const *s2);
int				has_char(const char *str, int c);
t_env			*create_env(char *value);
t_env			*find_last_env(t_env *head);
void			append_env(t_env **list, t_env *new);
void			print_env_list(t_env **head);
t_env			*init_env_list(char **envp);
t_env			*copy_env_list(t_env *env_list);
void			sort_env_list(t_env *env_list);
void			print_sorted_env(t_env *env_list);
void			ft_export(t_env **env_list, char *name, char *value,
					t_data *data);
t_env			*find_env_var(t_env *env_list, char *name);
void			ft_unset(t_env **env_list, char *name);
void			handle_env_tudor(t_env **env_list, t_token *tokens,
					t_data *data);
void			handle_unset(t_env **env_list, t_token *tokens,
					t_data *data);
void			handle_export(t_env **env_list, t_token *tokens,
					t_data *data);
t_token			*merge_tokens(t_token *tokens);
int				is_valid_identifier(char *name);
char			**env_to_array(t_env *env_list);
int				count_env_vars(t_env *env_list);
char			**copy_env_vars(t_env *env_list, int count);
void			extr_name_value(t_token *token, char **name, char **value);
void			handle_export_no_args(t_env **env_list);
void			prcs_token(t_env **env_list, t_token *token, t_data *data);
t_token			*merge_next_token(t_token *current);
void			u_a_env(t_env **env_list, t_env *var, char *name, char *value);
int				first_token(t_data *data);
int				check_syntax(t_data *data);
void			sig_handle(int sig_nb);
void			signal_init(void);
void			killchild(int sig_nb);
char			*concat_2d_arr(char **arr);
char			*ft_strcat(char *dest, const char *src);
int				find_total_length(char **arr);
int				get_here_nb(t_token *list);

#endif