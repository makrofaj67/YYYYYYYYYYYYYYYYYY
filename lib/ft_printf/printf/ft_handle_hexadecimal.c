/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hexadecimal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:03:49 by rakman            #+#    #+#             */
/*   Updated: 2025/01/02 14:42:05 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_hexadecimal(unsigned int nb, char c)
{
	char	*hex;
	int		printed;
	int		i;

	printed = 0;
	hex = ft_itoa_base((unsigned long)nb, 16);
	if (c == 'X')
	{
		i = 0;
		while (hex[i])
		{
			hex[i] = ft_toupper(hex[i]);
			i++;
		}
	}
	ft_putstr_fd(hex, 1);
	printed = ft_strlen(hex);
	free(hex);
	return (printed);
}
