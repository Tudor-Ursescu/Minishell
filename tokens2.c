/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:07:28 by tursescu          #+#    #+#             */
/*   Updated: 2024/10/28 15:16:58 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*prcs_qt_content(char *line, int start, int end, t_data *data)
{
	char	*temp;
	char	**dqstr;
	char	*result;
	char	*exitcode;
	int		j;

	j = 0;
	temp = ft_strndup(&line[start], end - start - 1);
	dqstr = ft_split(temp, ' ');
	free(temp);
	while (dqstr[j])
	{
		if (dqstr[j][0] == '$' && dqstr[j][1] != '?')
			dqstr[j] = handle_env(dqstr[j], data->new_env);
		j++;
	}
	result = concat_2d_arr(dqstr);
	free_matrix(dqstr);
	exitcode = ft_itoa(data->exit);
	temp = replace_exit(result, exitcode);
	free(result);
	free(exitcode);
	return (temp);
}
