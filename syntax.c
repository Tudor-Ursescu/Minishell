/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:19:42 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/15 17:20:26 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	first_token (t_token *list)
{
	if (is_pipe(list))
	{
		printf("Syntax error near unexpected token '%s'\n", list->value);
		return (1);
	}
	return (0);
}

int	check_syntax(t_token *list)
{
	t_token	*temp;

	temp = list;
	if (first_token(list))
		return (1);
	while (temp->next)
	{
		if (temp->type > 2 && temp->next->type > 2)
		{
			printf("Syntax error near unexpected token '%s'\n", 
					temp->next->value);
			return (1);
		}
		temp = temp->next;
	}
	if (temp->type > 2)
	{
		printf("Syntax error near unexpected token'\\n'\n");
		return (1);
	}
	else 
		return (0);
}
