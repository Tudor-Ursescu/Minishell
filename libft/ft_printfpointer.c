/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfpointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:17:03 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/09 13:54:18 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printfpointer(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (ft_printfstring("(nil)"));
	count += ft_printfstring("0x");
	count += ft_printfsmallhex((unsigned long)ptr);
	return (count);
}
