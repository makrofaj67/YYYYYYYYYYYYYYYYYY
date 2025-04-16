/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:15:49 by rakman            #+#    #+#             */
/*   Updated: 2025/01/02 14:41:13 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_address(void *address)
{
	int		printed;
	char	*hex;

	printed = 0;
	if (!address)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	hex = ft_itoa_base((unsigned long)address, 16);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(hex, 1);
	printed += ft_strlen(hex) + 2;
	free(hex);
	return (printed);
}
