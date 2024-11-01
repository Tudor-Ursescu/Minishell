/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfhex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:46:43 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/09 13:54:25 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printfhex(unsigned long n)
{
	int		count;
	int		base;
	char	*symbols;

	count = 0;
	symbols = "0123456789ABCDEF";
	if (n / 16)
		count += ft_printfhex(n / 16);
	base = n % 16;
	count += ft_printfchar(symbols[base]);
	return (count);
}
