/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:16:19 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/10 12:22:30 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// #include <ctype.h> // Include ctype.h for isalpha
// int main(void)
// {
// 	int c = 31;
// 	printf("my isprint %d \n",ft_isprint(c));
// 	printf("man isprint %d", isprint(c));
// }