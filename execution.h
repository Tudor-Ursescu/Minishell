/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:41:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/22 10:01:35 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "libft/libft.h"
# include "parsing.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
extern int			g_exit;

typedef void		(*command_func)(char **argv, char **envp);
typedef void		(*command_func2)(t_env **env_list, t_token *tokens);

typedef struct t_firstcmd
{
	char			*name;
	command_func	func;
	command_func2	func2;
}					t_firstcmd;



char				*prompt(void);
void				echo(char **argv, char **envp);
void				echo2(char **argv, int i);
int					echo3(char **argv, char **envp);
void				free_call(char **argv, char *input);
void				cd_function(char **argv, char **envp);
void				pwd_function(char **argv, char **envp);
void				lstatcheck(char **argv);
t_firstcmd			*init_command_table(void);
void				env_function(char **argv, char **envp);
char				*handle_env(char *arg, char **envp);
int					handle_n_flag(char *arg, char **envp);
void				export_function(char **argv, char **envp);
void				sort_env(char **env);
void				exportnullarg(char **envp);
void				set_env_variable(const char *var, const char *value,
						char **envp);
char				**copy_env(char **env);
char				*find_path(const char *cmd);
void				free_tokensexec(char **tokens);
void				execute_path(t_cmd *cmd_list, t_data *data);
int					check_fork(int *pid);
char				*stitching(char **tokens, const char *cmd);
void				exit_function(t_data *data, char *input);
void				heredoc(char *red_args);
void				handle_redirect_or_execute(t_data *data, t_cmd *cmd_list);
int					checkheredoc(char *input, int temp_fd, char *red_args);
void				handle_pipe(t_data *data, t_cmd *cmd_list, t_pipeinfo pipeinfo);
void				execute_absolute(char *path, char **argv, t_data *data);
void				execute_relative(char *path, char **argv, t_data *data);
void				child_function(int *pipefd, t_data *data, t_cmd *cmd_list, int prev_fd);
void				parent_function(int *pipefd, t_cmd *cmd_list, int *prev_fd);
void				restore_fds(int saved_stdin, int saved_stdout);
void				check_next(int pipefd[2], t_cmd *cmd_list);
int					execbuiltin(char **envp, t_firstcmd *command_table,
						t_cmd *cmd_list);
int					check_if_builtin(char **envp, t_cmd *cmd_list);
t_pipeinfo			initialize_pipeinfo(t_token *token_list);
void				waitandsave(int pid, t_data *data);
int					handle_input_redirection(int flag, int fd, char *file);
void				handle_append_and_out(t_cmd *cmd_list, int fd);
int					handle_heredocpre(t_cmd *cmd_list, int flag, int fd);
int					handle_all_but_heredoc(t_cmd *cmd_list, int fd, int flag);
int					cd_function2(char **argv);
int					heredoc_loop(int temp_fd, int saved_stdin, int saved_stdout,
						char *red_args);
void				init_tdata(int argc, char **argv, char **envp, t_data *data);
#endif