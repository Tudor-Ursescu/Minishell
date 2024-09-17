/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:18:06 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/17 11:47:24 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo2(char **argv, int i)
{
	i = 2;
	if(!argv[2])
		return;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		else if (!argv[i + 1] && (ft_strncmp(argv[1], "-n",
					ft_strlen(argv[1])) == 0))
			printf("\033[30;47m%%\033[0m");
		
		i++;
	}
		printf("\n");
}

void	echo(char **argv)
{
	int	i;

	i = 1;
	if (argv[1])
	{
		if (!(ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0))
		{
			while (argv[i])
			{
				printf("%s", argv[i]);
				if (argv[i + 1])
					printf(" ");
				i++;
			}
			printf("\n");
		}
		else
			echo2(argv, i);
	}
	else
		printf("\n");
}
