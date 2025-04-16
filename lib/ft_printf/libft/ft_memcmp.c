/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:13:20 by rakman            #+#    #+#             */
/*   Updated: 2024/11/18 15:30:25 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			iter;
	unsigned char	*str1;
	unsigned char	*str2;

	iter = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (iter < n)
	{
		if (str1[iter] != str2[iter])
			return (str1[iter] - str2[iter]);
		iter++;
	}
	return (0);
}
