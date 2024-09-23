/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:41:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/23 16:16:45 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <dirent.h>
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char			**g_env;

typedef void		(*command_func)(char **);
typedef struct t_firstcmd
{
	char			*name;
	command_func	func;
}					t_firstcmd;

typedef enum e_token_types
{
    T_CMD,
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

typedef struct  s_args
{
    t_token_types   type;
    char            *value;
    struct s_args   *next;
}                   t_args;

typedef struct  s_command
{
    char                *path;
    char                **args;
    struct s_command    *next;
}               t_command;

typedef struct s_data
{
    t_args      *args;
    t_command   *cmd;
}   t_data;




char				*prompt(void);
void				echo(char **argv);
void				echo2(char **argv, int i);
int					echo3(char **argv);
void				free_call(char **argv, char *input);
void				cd_function(char **argv);
void				pwd_function(char **argv);
void				lstatcheck(char **argv);
void				clear_function(char **argv);
t_firstcmd			*init_command_table(void);
void				env_function(char **argv);
int					handle_env(char *arg);
int					handle_n_flag(char *arg);
void export_function(char **argv);
void sort_env(char **env);
void	exportnullarg(void);
void	set_env_variable(const char *var, const char *value);
char **copy_env(char **env);
char *find_path(const char *cmd);
void	free_tokens(char **tokens);
void execute_path(char **argv);
int	check_fork(int *pid);