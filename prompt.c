/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:48 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/16 14:58:08 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *prompt(char *input)
{
	char *prompt;
	input = readline("awaiting command: ");
	prompt = malloc((ft_strlen(input) + 1 )* sizeof(char));

	ft_strlcpy(prompt, input, ft_strlen(input) + 1);
	free(input);
	return(prompt);
}