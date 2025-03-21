/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:19:42 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 10:21:00 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	first_token(t_data *data)
{
	if (is_pipe(data->token_list))
	{
		printf("Syntax error near unexpected token '%s'\n",
			data->token_list->value);
		data->exit = 2;
		return (1);
	}
	return (0);
}

int	check_syntax(t_data *data)
{
	t_token	*temp;

	temp = data->token_list;
	if (first_token(data))
		return (1);
	while (temp->next)
	{
		if (temp->type > 2 && temp->next->type > 2)
		{
			printf("Syntax error near unexpected token '%s'\n",
				temp->next->value);
			data->exit = 2;
			return (1);
		}
		temp = temp->next;
	}
	if (temp->type > 2)
	{
		printf("Syntax error near unexpected token'\\n'\n");
		data->exit = 2;
		return (1);
	}
	else
		return (0);
}
