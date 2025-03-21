/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:48 by ckonneck          #+#    #+#             */
/*   Updated: 2025/03/21 10:20:50 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*prompt(void)
{
	char	*input;

	input = readline("cat_shell :3  ");
	if (input && *input)
		add_history(input);
	if (!input)
	{
		write(1, "OH GOD YOU KILLED THE CAT! \n", 28);
		write(1, " /\\_/\\\n", 7);
		write(1, "( x.x )\n", 8);
		write(1, " > ^ < \n", 8);
		exit(0);
	}
	return (input);
}
