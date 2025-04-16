/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:28:29 by rakman            #+#    #+#             */
/*   Updated: 2025/01/02 14:43:56 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_intlenght(unsigned long nb, int base)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / base;
		len = len + 1;
	}
	return (len);
}

char	*ft_itoa_base(unsigned long nb, int base)
{
	char	*result;
	int		intlenght;
	int		remainder;

	intlenght = ft_intlenght(nb, base);
	result = malloc((intlenght + 1) * sizeof(char));
	result[intlenght] = '\0';
	if (result == NULL)
		return (NULL);
	if (nb == 0)
		result[0] = '0';
	else
	{
		while (nb > 0)
		{
			intlenght--;
			remainder = nb % base;
			if (remainder < 10)
				result[intlenght] = remainder + 48;
			else
				result[intlenght] = remainder + 87;
			nb = nb / base;
		}
	}
	return (result);
}
