/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:41:34 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/17 16:32:39 by ckonneck         ###   ########.fr       */
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

char	*prompt(void);
void	echo(char **argv);
void	echo2(char **argv, int i);
void	free_call(char **argv, char *input);
void	cd_function(char **argv);
void	pwd_function(void);
void	ls_function(void);
void	lstatcheck(char **argv);
