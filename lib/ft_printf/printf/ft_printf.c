/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:37:57 by rakman            #+#    #+#             */
/*   Updated: 2025/01/02 14:44:06 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_distribution(char c, va_list valist)
{
	int	printed;

	printed = 0;
	if (c == 'c')
		printed += ft_handle_char(va_arg(valist, int));
	else if (c == 's')
		printed += ft_handle_string(va_arg(valist, char *));
	else if (c == 'd' || c == 'i')
		printed += ft_handle_dec_int(va_arg(valist, int));
	else if (c == 'p')
		printed += ft_handle_address(va_arg(valist, void *));
	else if (c == 'u')
		printed += ft_handle_unsigned_int(va_arg(valist, unsigned int));
	else if (c == 'x' || c == 'X')
		printed += ft_handle_hexadecimal(va_arg(valist, unsigned int), c);
	else if (c == '%')
	{
		ft_putchar_fd(c, 1);
		printed++;
	}
	return (printed);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		printed;
	va_list	valist;

	i = 0;
	printed = 0;
	va_start(valist, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				return (printed);
			printed += ft_distribution(str[i + 1], valist);
			i += 2;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			printed++;
			i++;
		}
	}
	va_end(valist);
	return (printed);
}
