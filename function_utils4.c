/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:56:32 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/29 12:59:39 by ckonneck         ###   ########.fr       */
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
