/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:41:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/15 13:33:26 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "libft/libft.h"
# include "parsing.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
// extern int g_sig;

typedef void		(*command_func)(char **argv, char **envp);
typedef struct t_firstcmd
{
	char			*name;
	command_func	func;
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
int					handle_env(char *arg, char **envp);
int					handle_n_flag(char *arg, char **envp);
void				export_function(char **argv, char **envp);
void				sort_env(char **env);
void				exportnullarg(char **envp);
void				set_env_variable(const char *var, const char *value,
						char **envp);
char				**copy_env(char **env);
char				*find_path(const char *cmd);
void				free_tokensexec(char **tokens);
void				execute_path(t_cmd *cmd_list, char **envp);
int					check_fork(int *pid);
char				*stitching(char **tokens, const char *cmd);
void    			exit_function(char **argv, char *input);
void				print_error_toast(void);
void				heredoc(char **argv, char **envp, char *red_args);
void				handle_redirect_or_execute(t_cmd *cmd_list, char **envp);
int					checkheredoc(char *input, int temp_fd, char *red_args);
void				handle_pipe(t_cmd *cmd_list, int numer_of_pipes, char **envp, int prev_fd, int prev_pid);
void				execute_absolute(char *path, char **argv, char **envp);
void				execute_relative(char *path, char **argv, char **envp);
void				setup_signal_handlers(void);
void				handle_sigint(int signum);
void				mini_newline(int signum);
void				load_ammo(int signum);
void	child_function(int *pipefd, t_cmd *cmd_list, char **envp, int prev_fd);
void	parent_function(int *pipefd, t_cmd *cmd_list, int *prev_fd);
void	last_pipe(t_cmd *cmd_list, char **envp, int saved_stdin, int saved_stdout);
void	pipe_end_function(int saved_stdin, int saved_stdout);
void restore_fds(int saved_stdin, int saved_stdout);
void	check_next(int pipefd[2], t_cmd *cmd_list);
int		checkforbuiltin(char **envp, t_firstcmd *command_table, t_cmd *cmd_list, int *found);
#endif