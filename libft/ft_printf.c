/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:00:29 by ckonneck          #+#    #+#             */
/*   Updated: 2024/07/09 13:54:32 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printfformat(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_printfchar(va_arg(ap, int));
	else if (specifier == 's')
		count += ft_printfstring(va_arg(ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_printfnumber(va_arg(ap, int));
	else if (specifier == 'X')
		count += ft_printfhex(va_arg(ap, unsigned int));
	else if (specifier == 'x')
		count += ft_printfsmallhex(va_arg(ap, unsigned int));
	else if (specifier == 'u')
		count += ft_printfunsigned(va_arg(ap, unsigned int));
	else if (specifier == 'p')
		count += ft_printfpointer(va_arg(ap, unsigned int *));
	else
		count += write(1, "%", 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			count += ft_printfformat(*(++format), ap);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}

// #include <stdio.h>
// int main(void)
// {
// 	void *bro;
// 	ft_printf("mine %d\n",(ft_printf("%X",29348)));
// 	printf("real %d",(printf("%X",29348)));
// }