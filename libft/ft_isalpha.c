/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:38:36 by ckonneck          #+#    #+#             */
/*   Updated: 2024/06/10 11:33:00 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// #include <ctype.h> // Include ctype.h for isalpha
// int main(void)
// {
// 	int c;
// 	printf("my alpha %d \n",ft_isalpha(c));
// 	printf("man alpha %d", isalpha(c));
// }