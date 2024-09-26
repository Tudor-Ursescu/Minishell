/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:41:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/26 15:13:45 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define  EXECUTION_H
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
#include <fcntl.h>

struct s_args; // Forward declaration
typedef struct s_args t_args; // Typedef for easier use

typedef void			(*command_func)(char **args, char **envp);
typedef struct t_firstcmd
{
	char				*name;
	command_func		func;
}						t_firstcmd;


// typedef enum e_token_types
// {
// 	T_CMD,
// 	T_PIPE,
// 	T_ARG,
// 	T_QUOTE,
// 	T_DQUOTE,
// 	T_RED_TO,
// 	T_RED_FROM,
// 	T_HEREDOC,
// 	T_REDIR_APPEND,
// 	T_END
// }						t_token_types;

// typedef struct s_args
// {
// 	t_token_types		type;
// 	char				*value;
// 	struct s_args		*next;
// }						t_args;

// typedef struct s_command
// {
// 	char				*path;
// 	char				**args;
// 	struct s_command	*next;
// }						t_command;

// typedef struct s_data
// {
// 	t_args				*args;
// 	t_command			*cmd;
// }						t_data;

char					*prompt(void);
void					echo(char **argv, char **envp);
void					echo2(char **argv, int i);
int						echo3(char **argv, char **envp);
void					free_call(char **argv, char *input);
void					cd_function(char **argv, char **envp);
void					pwd_function(char **argv, char **envp);
void					lstatcheck(char **argv);
t_firstcmd				*init_command_table(void);
void					env_function(char **argv, char **envp);
int						handle_env(char *arg, char **envp);
int						handle_n_flag(char *arg, char **envp);
void					export_function(char **argv, char **envp);
void					sort_env(char **env);
void					exportnullarg(char **envp);
void					set_env_variable(const char *var, const char *value,
							char **envp);
char					**copy_env(char **env);
char					*find_path(const char *cmd);
void					free_tokens(char **tokens);
void	execute_path(t_args *arg_list, char **envp);
int						check_fork(int *pid);
char					*stitching(char **tokens,
							const char *cmd);
void	exit_function(t_firstcmd *command_table, char **argv, char *input, t_args *arg_list);
void    print_error_toast(void);
void input_redirect(char **argv, char **envp);
void output_redirect(char **argv, char **envp);
void output_append(char **argv, char **envp);
void heredoc(char **argv, char **envp);
void	handle_redirect_or_execute(t_args *arg_list, char **envp);
int	checkheredoc(char *input, char **argv, int temp_fd);
void	handle_pipe(char **argv, int number_of_pipes, char **envp);


#endif