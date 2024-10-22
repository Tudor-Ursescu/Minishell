/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:57:20 by ckonneck          #+#    #+#             */
/*   Updated: 2024/10/22 16:03:40 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_all_env(t_data *data)
{
	t_env	*temp;
	t_env	*head;

	if (data->new_env)
		free_matrix(data->new_env);
	head = data->env;
	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
	data->env = NULL;
}

void	free_tokensexec(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_call(char **argv, char *input)
{
	int	i;

	free(input);
	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
