/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:28:54 by tursescu          #+#    #+#             */
/*   Updated: 2024/09/27 16:04:10 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

t_token_types set_type(const char *str)
{
    if (str[0] == '|')
        return (T_PIPE);
    else if (str[0] == '>' && str[1] == '>')
        return (T_APPEND);
    else if (str[0] == '<' && str[1] == '<')
        return (T_HEREDOC);
    else if (str[0] == '>')
        return (T_OUT);
    else if (str[0] == '<')
        return (T_IN);
    else if (is_word_char(str[0]))
        return (T_WORD);
}

//to do (maybe) a function to concat words into a string