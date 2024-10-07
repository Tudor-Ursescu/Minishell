/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfstring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:18:18 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/09 13:54:13 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printfstring(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (ft_printfstring("(null)"));
	while (*str)
	{
		ft_printfchar(*(int *)str);
		count++;
		str++;
	}
	return (count);
}
