/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_decimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:50:51 by rakman            #+#    #+#             */
/*   Updated: 2025/01/02 14:41:51 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_dec_int(int nb)
{
	char	*decint;
	int		len;

	ft_putnbr_fd(nb, 1);
	decint = ft_itoa(nb);
	len = ft_strlen(decint);
	free(decint);
	return (len);
}
