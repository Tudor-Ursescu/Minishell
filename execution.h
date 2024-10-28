/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:41:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/28 14:52:38 by ckonneck         ###   ########.fr       */
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

typedef void		(*t_command_func)(char **argv, char **envp, t_data *data);
typedef void		(*t_command_func2)(t_env **env_list, t_token *tokens,
			t_data *data);

typedef struct t_firstcmd
{
	char			*name;
	t_command_func	func;
	t_command_func2	func2;
}					t_firstcmd;

char				*prompt(void);
void				echo(char **argv, char **envp, t_data *data);
void				echo2(char **argv, int i);
int					echo3(char **argv, char **envp, t_data *data);
void				free_call(char **argv, char *input);
void				cd_function(char **argv, char **envp, t_data *data);
void				pwd_function(char **argv, char **envp, t_data *data);
void				lstatcheck(char **argv, t_data *data);
t_firstcmd			*init_command_table(void);
char				*handle_env(char *arg, char **envp);
int					handle_n_flag(char *arg, char **envp);
char				*find_path(const char *cmd, t_data *data);
void				free_tokensexec(char **tokens);
void				execute_path(t_cmd *cmd_list, t_data *data);
int					check_fork(int *pid);
char				*stitching(char **tokens, const char *cmd);
void				exit_function(t_data *data, char *input);
void				heredoc(char *tempfile, t_token *redtemp);
void				handle_redirect_or_execute(t_data *data, t_cmd *cmd_list);
int					checkheredoc(char *input, int temp_fd, char *red_args);
void				handle_pipe(t_data *data, t_cmd *cmd_list,
						t_pipeinfo pipeinfo);
void				execute_absolute_or_relative(char *path, char **argv,
						t_data *data);
void				child_function(int *pipefd, t_data *data, t_cmd *cmd_list,
						int prev_fd);
void				parent_function(int *pipefd, t_cmd *cmd_list, int *prev_fd);
void				restore_fds(int saved_stdin, int saved_stdout);
void				check_next(int pipefd[2], t_cmd *cmd_list);
int					execbuiltin(char **envp, t_firstcmd *command_table,
						t_cmd *cmd_list, t_data *data);
int					check_if_builtin(char **envp, t_cmd *cmd_list,
						t_data *data);
t_pipeinfo			initialize_pipeinfo(t_token *token_list);
void				waitandsave(int pid, t_data *data);
int					handle_input_redirection(char *file);
void				handle_heredocpre(t_data *data, int heredoc_num,
						t_token *redtemp);
int					handle_all_redirections(t_cmd *cmd_list);
int					cd_function2(char **argv, t_data *data);
int					heredoc_loop(int temp_fd, char *red_args);
void				init_tdata(int argc, char **argv, char **envp,
						t_data *data);
int					init_loop(t_data *data);
void				catloop(t_data *data);
void				fork_and_execute(char *path, t_cmd *cmd_list, t_data *data,
						int pid);
int					check_and_print_env(t_data *data);
int					check_and_print_exit(t_data *data);
int					dollarcheck(t_data *data);
void				print_spaces(char **argv);
void				cmd_not_found(t_cmd *cmd_list, t_data *data);
char				*getpath(char *pathstring, t_data *data);
char				*replace_exit(char *str, char *replacement);
void				handle_all_heredocs(t_data *data);
void				unlink_heredocfiles(t_data *data);
void				handle_append_and_out(t_token_types type, char *file);
void				output_redirections(t_token *temp, char *file);
#endif