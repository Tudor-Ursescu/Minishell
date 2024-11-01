/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfsmallhex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:35:36 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/09 13:54:15 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printfsmallhex(unsigned long n)
{
	int		count;
	int		base;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n / 16)
		count += ft_printfsmallhex(n / 16);
	base = n % 16;
	count += ft_printfchar(symbols[base]);
	return (count);
}
