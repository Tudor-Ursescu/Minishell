/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:28:54 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 10:20:39 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	is_word(const char *s)
{
	return (!is_quote(s[0]) && !is_operator(s) && !isspace(s[0]));
}

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_operator(const char *s)
{
	if (!s || !s[0])
		return (0);
	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		return (2);
	else if (s[0] == '|')
		return (1);
	else if (s[0] == '>' || s[0] == '<')
		return (1);
	else
		return (0);
}

t_token_types	set_type(const char *str)
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
	else if (str[0] == '\'')
		return (T_QUOTE);
	else if (str[0] == '"')
		return (T_DQUOTE);
	else
		return (T_WORD);
}
