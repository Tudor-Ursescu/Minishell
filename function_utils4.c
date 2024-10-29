/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:56:32 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/29 13:47:10 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_n_flag(char *str)
{
	int	i;

	i = 2;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

int	dollarcheck(t_data *data)
{
	if (ft_strncmp(data->line, "$?", ft_strlen("$?")) == 0)
		printf("%d: ", data->exit);
	check_and_print_exit(data);
	if (check_and_print_env(data) == 1)
		return (1);
	return (0);
}

void	pwd_function(char **argv, char **envp, t_data *data)
{
	char	path[1024];
	int		argc;

	(void)envp;
	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
	{
		getcwd(path, sizeof(path));
		printf("%s\n", path);
		data->exit = 0;
	}
	else
	{
		printf("pwd: too many arguments\n");
		data->exit = 1;
	}
}
