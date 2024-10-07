/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:33:24 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/18 16:28:01 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || \
		(c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// #include <ctype.h> // Include ctype.h for isalpha
// int main(void)
// {
// 	int c = '_';
// 	printf("\033[1;31m my alpha %d \n \033[0m",ft_isalnum(c));
// 	printf("man alpha %d", isalnum(c));
// }