/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:07:28 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/23 16:33:15 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	list_len(t_args *head)
{
	t_args *temp;
	size_t i;

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void print_arg_list(t_args *head)
{
	t_args *temp;

	temp = head;
	while (temp)
	{
		printf("%s %d\n", temp->value, temp->type);
		temp = temp->next;
	}
}