/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:27:48 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/17 12:54:45 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *prompt(void)
{
    char *input = readline("uwushell awaits orders :3  ");
    if (input && *input)
        add_history(input);
    return input;
}