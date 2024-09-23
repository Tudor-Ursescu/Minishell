/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:41:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/23 10:18:54 by ckonneck         ###   ########.fr       */
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

extern char			**g_env;

typedef void		(*command_func)(char **);
typedef struct s_command
{
	char			*name;
	command_func	func;
}					t_command;

char				*prompt(void);
void				echo(char **argv);
void				echo2(char **argv, int i);
int					echo3(char **argv);
void				free_call(char **argv, char *input);
void				cd_function(char **argv);
void				pwd_function(char **argv);
void				ls_function(char **argv);
void				lstatcheck(char **argv);
void				clear_function(char **argv);
void				punch_or_hit_function(char **argv);
void				uwu_function(char **argv);
t_command			*init_command_table(void);
void				env_function(char **argv);
int					handle_env(char *arg);
int					handle_n_flag(char *arg);
void export_function(char **argv);
void sort_env(char **env);
void	exportnullarg(void);
void	set_env_variable(const char *var, const char *value);
char **copy_env(char **env);