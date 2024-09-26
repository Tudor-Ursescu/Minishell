/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:28:54 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/25 14:35:34 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int is_word_char(char c)
{
    return (ft_isalnum(c) || c == '_' || c == '-');
}

int ft_isspace(char c)
{
    return (c == 32 || (c >= 9 && c <= 13));
}

int skip_whitespace(char *line, int i)
{
    while(line[i] && ft_isspace(line[i]))
        i++;
    return (i);
}
