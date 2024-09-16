/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:18:06 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/16 17:28:42 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			i = 2;
			while (argv[i])
			{
				printf("%s", argv[i]);
				if (argv[i + 1])
					printf(" ");
				else if (!argv[i + 1] && (ft_strncmp(argv[1], "-n",
							ft_strlen(argv[1])) == 0))
					printf("\033[30;47m%%\033[0m");
				i++;
				printf("\n");
			}
			
		}
		
	}
	else
		printf("\n");
}