/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:22:46 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/10 12:25:56 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// #include <ctype.h> // Include ctype.h for isalpha
// int main(void)
// {
// 	int c = 69;
// 	printf("my isascii %d \n",ft_isascii(c));
// 	printf("man isascii %d", isascii(c));
// }