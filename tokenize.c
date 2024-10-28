/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:49:05 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/28 15:14:35 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

int	add_operator(t_token **list, char *line, int i)
{
	t_token	*new;
	int		op_len;
	char	*temp;

	op_len = is_operator(&line[i]);
	if (op_len > 0)
	{
		temp = ft_strndup(&line[i], op_len);
		new = create_token(set_type(&line[i]), temp);
		append_token(list, new);
		free(temp);
		i += op_len;
	}
	return (i);
}

int	add_quote(t_token **list, char *line, int i, t_data *data)
{
	t_token	*new;
	char	quote;
	int		start;
	char	*temp;

	quote = line[i];
	start = ++i;
	while (line[i] && line[i] != quote)
		i++;
	if (!line[i])
	{
		printf("Syntax error: Unclosed quotes detected.\n");
		return (0);
	}
	i++;
	if (quote == '\"')
		temp = process_quoted_content(line, start, i, data);
	else
		temp = ft_strndup(&line[start], i - start - 1);
	new = create_token(set_type(&line[start - 1]), temp);
	free(temp);
	if (!ft_isspace(line[i]) && !is_operator(line + i))
		new->append = 1;
	append_token(list, new);
	return (i);
}

char	*replace_exit(char *str, char *replacement)
{
	char	*pos;
	char	*new_str;
	int		len_before;
	int		len_new;

	pos = ft_strnstr(str, "$?", ft_strlen(str));
	if (!pos)
		return (ft_strdup(str));
	len_before = pos - str;
	len_new = len_before + ft_strlen(replacement) + ft_strlen(pos + 2);
	new_str = (char *)malloc(len_new + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, len_before + 1);
	new_str[len_before] = '\0';
	ft_strcat(new_str, replacement);
	ft_strcat(new_str, pos + 2);
	return (new_str);
}

int	add_words(t_token **list, char *line, int i)
{
	t_token	*new;
	int		start;
	char	*sub;

	start = i;
	while (line[i] && is_word(&line[i]))
		i++;
	if (start != i)
	{
		sub = ft_strndup(&line[start], i - start);
		new = create_token(T_WORD, sub);
		free(sub);
		if (!ft_isspace(line[i]) && !is_operator(line + i))
			new->append = 1;
		append_token(list, new);
	}
	return (i);
}

t_token	*tokenize(char *line, t_data *data)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (line[i])
	{
		i = skip_whitespace(line, i);
		if (is_operator(&line[i]))
			i = add_operator(&tokens, line, i);
		else if (line[i] == '\'' || line[i] == '"')
		{
			i = add_quote(&tokens, line, i, data);
			if (i == 0)
			{
				if (tokens)
					free_tokens(&tokens);
				return (NULL);
			}
		}
		else
			i = add_words(&tokens, line, i);
	}
	return (tokens);
}
