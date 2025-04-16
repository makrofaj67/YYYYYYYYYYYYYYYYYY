/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 05:24:57 by rakman            #+#    #+#             */
/*   Updated: 2024/11/18 05:52:40 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numlen(long num)
{
	size_t	i;

	i = 0;
	if (num <= 0)
	{
		i = 1;
		num = -num;
	}
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	nlen;
	long	number;
	char	*strnum;

	number = n;
	nlen = numlen(number);
	strnum = malloc(sizeof(char) * nlen + 1);
	if (!strnum)
		return (NULL);
	strnum[nlen] = '\0';
	if (number < 0)
	{
		strnum[0] = '-';
		number = -number;
	}
	while (nlen > 0 && number != 0)
	{
		strnum[--nlen] = (number % 10) + '0';
		number /= 10;
	}
	if (n == 0)
		strnum[0] = '0';
	return (strnum);
}
